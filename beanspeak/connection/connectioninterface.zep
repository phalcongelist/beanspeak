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

namespace Beanspeak\Connection;

/**
 * Beanspeak\Connection\ConnectionInterface
 */
interface ConnectionInterface
{
    /**
     * Makes a connection to the Beanstalk server.
     */
    public function connect() -> resource;

    /**
     * Closes the connection to the Beanstalk server.
     */
    public function disconnect() -> boolean;

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
     * Returns the write retries for this connection.
     */
    public function getWriteRetries() -> int;

    /**
     * Whether the connection is persistent or not.
     */
    public function isPersistent() -> boolean;

    /**
     * Whether the connection is established or not.
     */
    public function isConnected() -> boolean;

    /**
     * Writes data to the socket. Performs a connection if none is available.
     */
    public function write(string data) -> void;
}
