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

class Connection implements ConnectionInterface
{
    private socket;
    protected options = [] { get, set };

    /**
     * Beanstalk\Connection
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

        let this->options = options;
    }

    /**
     * Makes a connection to the Beanstalkd server
     *
     * @throws \Beanstalk\Connection\Exception
     */
    public function connect() -> resource
    {
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

        return socket;
    }
}
