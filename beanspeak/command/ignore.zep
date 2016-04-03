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
 * Beanspeak\Command\Ignore
 *
 * Removes the named tube from the watch list for the current connection.
 *
 * <code>
 * use Beanspeak\Command\Ignore;
 *
 * $command = new Ignore($tube);
 * </code>
 */
class Ignore extends Command implements ParserInterface
{
    private tube;

    /**
     * Beanspeak\Command\Ignore constructor
     */
    public function __construct(string! tube)
    {
        let this->tube = tube;
    }

    /**
     * {@inheritdoc}
     */
    public function getName() -> string
    {
        return "IGNORE";
    }

    /**
     * {@inheritdoc}
     */
    public function getCommandLine() -> string
    {
        return "ignore " . this->tube;
    }

    /**
     * {@inheritdoc}
     * @throws \Beanspeak\Command\Exception
     */
     public function parseResponse(string line, string data = null) -> <ResponseInterface>
     {
         if starts_with(line, "WATCHING") {
             var ignored;

             let ignored = preg_replace("#^WATCHING (\d+)$#", "$1", line);

             return this->createResponse("WATCHING", [
                 "count" : (int) ignored
             ]);
         }

         if starts_with(line, "NOT_IGNORED") {
             throw new Exception(this->getName() . ": cannot ignore last tube in watchlist");
         }

         throw new Exception("Unhandled response: " . line);
     }
}
