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

namespace Beanstalk\Connection;

/**
 * Beanstalk\Connection\ConnectionInterface
 */
interface ConnectionInterface
{
    /**
     * Makes a connection to the Beanstalkd server.
     */
    public function connect() -> resource;

    /**
     * Returns the host for this connection.
     */
    public function getHost() -> string;

    /**
     * Returns the port for this connection.
     */
    public function getPort() -> int;

    /**
     * Returns the connect timeout for this connection.
     */
    public function getConnectTimeout() -> int;

    /**
     * Whether the connection is persistent or not?
     */
    public function isPersistent() -> boolean;
}
