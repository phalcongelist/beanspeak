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

namespace Beanstalk;

use Beanstalk\Connection\Exception;
use Beanstalk\Connection\ConnectionInterface;

/**
 * Beanstalk\Connection
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
     * Beanstalk\Connection constructor
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
     * @throws \Beanstalk\Connection\Exception
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
}
