/*
 +------------------------------------------------------------------------+
 | Beanspeak                                                              |
 +------------------------------------------------------------------------+
 | Copyright (c) 2016 Phalcon Team (http://www.phalconphp.com)            |
 +------------------------------------------------------------------------+
 | This source file is subject to the New BSD License that is bundled     |
 | with this package in the file LICENSE.txt.                             |
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
    /**
     * @var ConnectionInterface
     */
    protected connection;

    /**
     * Last used command
     * @var null|string
     */
    protected lastCommand = null;

    /**
     * Response data from last used command
     * @var null|string
     */
    protected responseData = null;

    /**
     * Response data from last used command
     * @var null|string
     */
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
        var e, responseParser;

        try {
            this->_dispatch(command);
        } catch ConnectionException, e {
            this->_reconnect();
            this->_dispatch(command);
        } catch \Exception, e {
            throw new DispatcherException(e->getMessage(), e->getCode(), e);
        }

        let responseParser = command->getResponseParser();

        return responseParser->parseResponse(this->responseLine, this->responseData);
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
        var connection, preparedcmd;

        let connection = this->connection;
        connection->connect();

        let this->lastCommand = command;
        let preparedcmd = command->getCommandLine() . "\r\n";

        if command->hasData() {
            let preparedcmd .= command->getData() . "\r\n";
        }

        connection->write(preparedcmd);

        if command->hasResponse() {
            let this->responseLine = connection->getLine();
            this->parseData();
        } else {
            let this->responseLine = command->getName();
        }
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

        newc->connect();

        let this->connection = newc;
    }

    internal function parseData() -> void
    {
        var connection, dataLength, data, crlf, response;

        let data     = null,
            response = this->responseLine;

        if starts_with(response, "OK") || starts_with(response, "FOUND") || starts_with(response, "RESERVED") {
            let dataLength = preg_replace("#^.*\b(\d+)$#", "$1", response),
                connection = this->connection,
                data       = connection->read(dataLength),
                crlf       = connection->read(2);

            if "\r\n" !== crlf {
                throw new Exception(
                    this->lastCommand->getName() . ": expected 2 bytes of CRLF after " . dataLength . " bytes of data"
                );
            }
        }

        let this->responseData = data;
    }
}
