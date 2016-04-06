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
use InvalidArgumentException;
use Beanspeak\Response\ResponseInterface;
use Beanspeak\Response\Parser\ParserInterface;

/**
 * Beanspeak\Command\Watch
 *
 * Adds the named tube to the watch list for the current connection.
 *
 * <code>
 * use Beanspeak\Command\Watch;
 *
 * $command = new Watch($tube);
 * </code>
 */
class Watch extends Command implements ParserInterface
{
    private tube;

    /**
     * Beanspeak\Command\Touch constructor
     * @throws \InvalidArgumentException
     */
    public function __construct(string! tube)
    {
        var length;

        let length = strlen(tube);

        if length > 200 {
            throw new InvalidArgumentException("The \"tube\" param must be less than 200 bytes. Got: " . length);
        }

        let this->tube = tube;
    }


    /**
     * {@inheritdoc}
     */
    public function getName() -> string
    {
        return "WATCH";
    }

    /**
     * {@inheritdoc}
     */
    public function getCommandLine() -> string
    {
        return "watch " . this->tube;
    }

    /**
     * {@inheritdoc}
     * @throws \Beanspeak\Command\Exception
     */
     public function parseResponse(string line, string data = null) -> <ResponseInterface>
     {
         if starts_with(line, "WATCHING") {
             var count = null;

             let count = preg_replace("#^WATCHING (\d+)$#", "$1", line);

             return this->createResponse("WATCHING", [
                 "count" : (int) count
             ]);
         }

         throw new Exception("Unhandled response: " . line);
     }
}
