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

        if !isset options["write_retries"] {
            let options["write_retries"] = 8;
        }

        let options["host"]          = (string) options["host"],
            options["port"]          = (string) options["port"],
            options["timeout"]       = (int) options["timeout"],
            options["write_retries"] = (int) options["write_retries"],
            options["persistent"]    = (boolean) options["persistent"],

            this->options = options;
    }

    /**
     * {@inheritdoc}
     */
    public function isConnected() -> boolean
    {
        var socket;

        let socket = this->socket;

        return typeof socket == "resource";
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
    public function getWriteRetries() -> int
    {
        return this->options["write_retries"];
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
    public function write(string data) -> int
    {
        var socket, part, fwritec, retries, written, step;

        // Performs a connection if none is available
        this->connect();

        let retries = this->options["write_retries"],
            socket  = this->socket,
            step    = 0,
            fwritec = 0,
            written = 0;

        while written < strlen(data) {
            let step++;

            if step >= retries && !written {
                throw new Exception(sprintf("fwrite() failed to write data after %d tries", retries));
            }

            let part    = substr(data, written),
                fwritec = fwrite(socket, part);

            let written += fwritec;
        }

        return written;
    }
}
