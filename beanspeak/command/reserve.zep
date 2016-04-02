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

namespace Beanspeak\Command;

use Beanspeak\Command;
use Beanspeak\Response\ResponseInterface;
use Beanspeak\Response\Parser\ParserInterface;

/**
 * Beanspeak\Command\Reserve
 *
 * Reserves/locks a ready job from the specified tube.
 *
 * <code>
 * use Beanspeak\Command\Reserve;
 *
 * $reserve = new Reserve(60 * 60 * 2);
 * </code>
 */
class Reserve extends Command implements ParserInterface
{
    private timeout = null;

    /**
     * Beanspeak\Command\Reserve constructor
     */
    public function __construct(var timeout = null)
    {
        if is_numeric(timeout) {
            let this->timeout = (int) timeout;
        }
    }

    /**
     * {@inheritdoc}
     */
    public function getName() -> string
    {
        if this->timeout {
            return "RESERVE-WITH-TIMEOUT";
        }

        return "RESERVE";
    }

    /**
     * {@inheritdoc}
     */
    public function getCommandLine()
    {
        var timeout;
        let timeout = this->timeout;

        if typeof timeout == "int" {
            return "reserve-with-timeout " . timeout;
        }

        return "reserve";
    }

    /**
     * {@inheritdoc}
     */
    public function parseResponse(string line, string data = null) -> <ResponseInterface>
    {
        if !starts_with(line, "RESERVED") {
            return this->createResponse(line);
        }

        var response;
        let response = explode(" ", line);

        return this->createResponse(response[0], [
            "id"      : (int) response[1],
            "jobdata" : data
        ]);
    }
}
