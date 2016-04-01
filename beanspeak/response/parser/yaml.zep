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

namespace Beanspeak\Response\Parser;

use Beanspeak\Response\ArrayResponse;
use Beanspeak\Response\ResponseInterface;

/**
 * Beanspeak\Response\Parser\Yaml
 */
class Yaml implements ParserInterface
{
    private mode;

    /**
     * Beanspeak\Response\Parser\Yaml constructor.
     */
    public function __construct(string! mode)
    {
        if mode != "list" && mode != "dict" {
            throw new Exception("Parser mode must be either list or dict");
        }

        let this->mode = mode;
    }

    /**
     * Fetch a YAML payload from the Beanstalkd server
     * @throws \Beanspeak\Response\Parser\Exception
     */
    public function parseResponse(string line, string data = null) -> <ResponseInterface>
    {
        var report, key, value;

        if line == "NOT_FOUND" {
            throw new Exception("Server reported: NOT_FOUND");
        }

        if !starts_with(line, "OK ") {
            throw new Exception("Unhandled response: " . line);
        }

        let report = yaml_parse(data);

        if this->mode == "list" {
            var tmp = [];

            for key, value in report {
                let tmp[] = key . " " . value;
            }

            let report = tmp;
        }

        return new ArrayResponse("OK", report);
    }
}
