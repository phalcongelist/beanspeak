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
use Beanspeak\Response\Parser\ParserInterface;
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

    protected statusMessages = [];

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
     * If a Beanspeak\Connection\Exception occurs, the connection is reset,
     * and the command is re-attempted once.
     *
     * @throws \Beanspeak\Dispatcher\Exception
     */
    public function dispatch(<CommandInterface> command) -> <ResponseInterface>
    {
        var response, e;

        try {
            let response = this->_dispatch(command);
        } catch ConnectionException, e {
            this->_reconnect();
            let response = this->_dispatch(command);
        } catch \Exception, e {
            throw new DispatcherException(e->getMessge(), e->getCode(), e);
        }

        return response;
    }

    internal function _dispatch(<CommandInterface> command) -> <ResponseInterface>
    {
        var connection, preparedcmd, responseLine, responseMsg,
            statusMessages, dataLength, dataResponses, data, crlf;

        let connection = this->connection;
        connection->connect();

        let preparedcmd = command->getCommandLine() . "\r\n";

        if command->hasData() {
            let preparedcmd .= command->getData() . "\r\n";
        }

        connection->write(preparedcmd);

        let responseLine = connection->getLine(),
            responseMsg  = preg_replace("#^(\S+).*$#s", "$1", responseLine);

        let statusMessages = this->statusMessages;
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

        if isset statusMessages[responseMsg] {
            throw new Exception(
                sprintf("%s in response to '%s'", responseMsg, command),
                statusMessages[responseMsg]
            );
        }

        let dataResponses = [
            "RESERVED" : true,
            "FOUND"    : true,
            "OK"       : true
        ];

        let data = null;

        if isset dataResponses[responseMsg] {
            let dataLength = preg_replace("#^.*\b(\d+)$#", "$1", responseLine),
                data       = connection->read(dataLength),
                crlf       = connection->read(2);

            if "\r\n" !== crlf {
                throw new Exception(
                    sprintf("Expected 2 bytes of CRLF after %u bytes of data", dataLength, command),
                    self::EXCEPTION_NO_CRLF
                );
            }
        }

        return command->getResponseParser()->parse(responseLine, data);
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
}
