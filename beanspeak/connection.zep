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

use Beanspeak\Connection\Exception;
use Beanspeak\Connection\ConnectionInterface;

/**
 * Beanspeak\Connection
 *
 * Represents a connection to a beanstalkd instance
 */
class Connection implements ConnectionInterface
{
    private socket;
    private data = [];

    /**
     * Connection options
     */
    private options = [];

    /**
     * Beanspeak\Connection constructor
     */
    public function __construct(array options = [])
    {
        if !isset options["host"] {
            let options["host"] = "127.0.0.1";
        }

        if !isset options["port"] {
            let options["port"] = 11300;
        }

        if !isset options["timeout"] {
            let options["timeout"] = 60;
        }

        if !isset options["persistent"] {
            let options["persistent"] = false;
        }

        let options["host"] = (string) options["host"];
        let options["port"] = (string) options["port"];
        let options["timeout"] = (int) options["timeout"];
        let options["persistent"] = (boolean) options["persistent"];

        let this->options = options;
    }

    /**
     * {@inheritdoc}
     */
    public function isConnected() -> boolean
    {
        return typeof this->socket == "resource";
    }

    /**
     * {@inheritdoc}
     *
     * @throws \Beanspeak\Connection\Exception
     */
    public function connect() -> resource
    {
        if !this->isConnected() {
            var options, socket, $function;

            let options = this->options;

            if options["persistent"] {
                let $function = "pfsockopen";
            } else {
                let $function = "fsockopen";
            }

            let socket = {$function}(options["host"], options["port"], null, null, options["timeout"]);

            if typeof socket != "resource" {
                throw new Exception("Can't connect to Beanstalk server.");
            }

            stream_set_timeout(socket, -1, 0);

            let this->socket = socket;
        }

        return this->socket;
    }

    /**
     * {@inheritdoc}
     */
    public function disconnect() -> boolean
    {
        var socket;

        let socket = this->socket;
        if typeof socket != "resource" {
            return false;
        }

        fclose(socket);

        return true;
    }

    /**
     * {@inheritdoc}
     */
    public function getHost() -> string
    {
        return this->options["host"];
    }

    /**
     * {@inheritdoc}
     */
    public function getPort() -> int
    {
        return this->options["port"];
    }

    /**
     * {@inheritdoc}
     */
    public function getConnectTimeout() -> int
    {
        return this->options["timeout"];
    }

    /**
     * {@inheritdoc}
     */
    public function isPersistent() -> boolean
    {
        return this->options["persistent"];
    }

    /**
     * {@inheritdoc}
     */
    public function write(string data) -> void
    {
        int retries = 8,
            written = 0;

        var socket, substring, fwritec;

        let this->data = [],
            socket = this->socket;

        socket->connect();

        while written < strlen(data) {
            let substring = substr(data, written),
                fwritec   = fwrite(socket, substring);

            this->logwriteCall(fwritec);
            if this->isFullWithNoWrites() {
                throw new Exception("fwrite() failed to write data after 8 tries");
            }

            let written += fwritec;
        }
    }

    internal function isFull(int limit = 8) -> boolean
    {
        return count(this->data) >= limit;
    }

    internal function hasWrites() -> boolean
    {
        return (boolean) array_sum(this->data);
    }

    internal function isFullWithNoWrites() -> boolean
    {
        return this->isFull() && !this->hasWrites();
    }

    internal function logwriteCall(int write) -> int
    {
        if this->isFull() {
            array_shift(this->data);
        }

        let this->data[] = write;

        return write;
    }
}
