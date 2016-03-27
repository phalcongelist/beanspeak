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

use Beanspeak\Connection\ConnectionInterface;
use Beanspeak\Connection\ConnectionAwareInterface;

/**
 * Beanspeak\Beanspeak
 *
 * Class to access the beanstalk queue service.
 */
class Beanspeak implements ConnectionAwareInterface
{
    protected connection;

    /**
     * Beanspeak\Beanspeak constructor
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
    public function setConnection(<ConnectionInterface> connection) -> <Beanspeak>
    {
        let this->connection = connection;

        return this;
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
