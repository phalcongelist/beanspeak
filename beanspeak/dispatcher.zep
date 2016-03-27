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
    protected connection;

    /**
     * Beanspeak\Dispatcher constructor
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
     * @todo
     * @throws \Beanspeak\Dispatcher\Exception
     */
    public function dispatch(<CommandInterface> command) -> <ResponseInterface>
    {
        var response, parser, e;

        try {
            this->connection->connect();

            let parser = command->getResponseParser();
            let response = parser->parse("");
        } catch ConnectionException, e {
            // perform command
            this->reconnect();

            let parser = command->getResponseParser();
            let response = parser->parse("");
        } catch \Exception, e {
            throw new DispatcherException(e->getMessge(), e->getCode(), e);
        }

        return response;
    }

    /**
     * Creates a new connection object, based on the existing connection object
     */
    private function reconnect()
    {
        var newc, oldc;

        let oldc = this->connection;
        let newc = new Connection([
            "host" : oldc->getHost(),
            "port" : oldc->getPort(),
            "timeout" : oldc->getConnectTimeout(),
            "persistent" : oldc->isPersistent()
        ]);

        newc->connect();

        let this->connection = newc;
    }
}
