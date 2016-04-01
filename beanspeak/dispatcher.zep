/*
 +------------------------------------------------------------------------+
 | Beanspeak                                                              |
 +------------------------------------------------------------------------+
 | Copyright (c) 2016 Phalcon Team (http://www.phalconphp.com)            |
 +------------------------------------------------------------------------+
 | This source file is subject to the New BSD License that is bundled     |
 | with this package in the file docs/LICENSE.txt.                        |
 |                                                                        |
 | If you did not receive a copy of the license and are unable to         |
 | obtain it through the world-wide-web, please send an email             |
 | to license@phalconphp.com so we can send you a copy immediately.       |
 +------------------------------------------------------------------------+
 | Authors: Serghei Iakovlev <serghei@phalconphp.com>                     |
 +------------------------------------------------------------------------+
*/

namespace Beanspeak;

use Beanspeak\Command\CommandInterface;
use Beanspeak\Response\ResponseInterface;
use Beanspeak\Dispatcher\DispatcherInterface;
use Beanspeak\Connection\ConnectionInterface;
use Beanspeak\Connection\ConnectionAwareInterface;
use Beanspeak\Connection\Exception as ConnectionException;
use Beanspeak\Dispatcher\Exception as DispatcherException;

/**
 * Beanspeak\Dispatcher
 */
class Dispatcher implements DispatcherInterface, ConnectionAwareInterface
{
    // See https://github.com/kr/beanstalk/blob/master/err.go
    const EXCEPTION_BAD_FORMAT      = 0;
    const EXCEPTION_BURIED          = 1;
    const EXCEPTION_DEADLINE_SOON   = 2;
    const EXCEPTION_DRAINING        = 3;
    const EXCEPTION_EXPECTED_CRLF   = 4;
    const EXCEPTION_INTERNAL_ERROR  = 5;
    const EXCEPTION_JOB_TOO_BIG     = 6;
    const EXCEPTION_NOT_FOUND       = 7;
    const EXCEPTION_NOT_IGNORED     = 8;
    const EXCEPTION_OUT_OF_MEMORY   = 9;
    const EXCEPTION_TIMED_OUT       = 10;
    const EXCEPTION_UNKNOWN_COMMAND = 11;

    const EXCEPTION_NO_CRLF         = 255;

    /**
     * @var ConnectionInterface
     */
    protected connection;

    protected lastCommand = null;

    protected statusMessages = [];

    protected responseData = null;

    protected responseLine = null;

    /**
     * Beanspeak\Dispatcher constructor.
     */
    public function __construct(<ConnectionInterface> connection = null)
    {
        let connection = connection ?: new Connection;

        let this->connection = connection;
    }

    /**
     * {@inheritdoc}
     */
    public function getConnection() -> <ConnectionInterface>
    {
        return this->connection;
    }

    /**
     * {@inheritdoc}
     */
    public function setConnection(<ConnectionInterface> connection) -> <Dispatcher>
    {
        let this->connection = connection;

        return this;
    }

    /**
     * {@inheritdoc}
     *
     * @throws \Beanspeak\Dispatcher\Exception
     */
    public function dispatch(<CommandInterface> command) -> <ResponseInterface>
    {
        var e;

        try {
            this->_dispatch(command);
        } catch ConnectionException, e {
            this->_reconnect();
            this->_dispatch(command);
        } catch \Exception, e {
            throw new DispatcherException(e->getMessage(), e->getCode(), e);
        }

        return command
            ->getResponseParser()
            ->parseResponse(this->responseLine, this->responseData);
    }

    /**
     * {@inheritdoc}
     */
    public function getLastCommand() -> <CommandInterface>
    {
        return this->lastCommand;
    }

    internal function _dispatch(<CommandInterface> command) -> void
    {
        var connection, preparedcmd, responseLine;

        let connection = this->connection;
        connection->connect();

        let this->lastCommand = command;
        let preparedcmd = command->getCommandLine() . "\r\n";

        if command->hasData() {
            let preparedcmd .= command->getData() . "\r\n";
        }

        connection->write(preparedcmd);

        let responseLine = connection->getLine();

        this->checkStatusMessage(responseLine);

        this->parseData(responseLine);

        let this->responseLine = responseLine;
    }

    /**
     * Creates a new connection object, based on the existing connection object.
     */
    internal function _reconnect() -> void
    {
        var newc, oldc;

        let oldc = this->connection;
        let newc = new Connection([
            "host"          : oldc->getHost(),
            "port"          : oldc->getPort(),
            "timeout"       : oldc->getConnectTimeout(),
            "persistent"    : oldc->isPersistent(),
            "write_retries" : oldc->getWriteRetries()
        ]);

        let this->connection = newc;
    }

    internal function checkStatusMessage(string content) -> void
    {
        var message;
        array statusMessages;

        let statusMessages = this->statusMessages,
            message        = preg_replace("#^(\S+).*$#s", "$1", content);

        if empty statusMessages {
            let statusMessages = [
                "BAD_FORMAT":      self::EXCEPTION_BAD_FORMAT,
                "BURIED":          self::EXCEPTION_BURIED,
                "DEADLINE_SOON":   self::EXCEPTION_DEADLINE_SOON,
                "DRAINING":        self::EXCEPTION_DRAINING,
                "EXPECTED_CRLF":   self::EXCEPTION_EXPECTED_CRLF,
                "INTERNAL_ERROR":  self::EXCEPTION_INTERNAL_ERROR,
                "JOB_TOO_BIG":     self::EXCEPTION_JOB_TOO_BIG,
                "NOT_FOUND":       self::EXCEPTION_NOT_FOUND,
                "NOT_IGNORED":     self::EXCEPTION_NOT_IGNORED,
                "OUT_OF_MEMORY":   self::EXCEPTION_OUT_OF_MEMORY,
                "TIMED_OUT":       self::EXCEPTION_TIMED_OUT,
                "UNKNOWN_COMMAND": self::EXCEPTION_UNKNOWN_COMMAND
            ];

            let this->statusMessages = statusMessages;
        }

        if isset statusMessages[message] {
            throw new Exception(
                message . " in response to '" . this->lastCommand->getName() . "'",
                statusMessages[message]
            );
        }
    }

    internal function parseData(string content) -> void
    {
        var connection, dataLength, data, message, crlf;

        let connection = this->connection,
            message    = preg_replace("#^(\S+).*$#s", "$1", content),
            data       = null;

        array dataResponses = [
            "RESERVED" : true,
            "FOUND"    : true,
            "OK"       : true
        ];

        if isset dataResponses[message] {
            let dataLength = preg_replace("#^.*\b(\d+)$#", "$1", content),
                data       = connection->read(dataLength),
                crlf       = connection->read(2);

            if "\r\n" !== crlf {
                throw new Exception(
                    "Expected 2 bytes of CRLF after " . dataLength . " bytes of data",
                    self::EXCEPTION_NO_CRLF
                );
            }
        }

        let this->responseData = data;
    }
}
