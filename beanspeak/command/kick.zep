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
 * Beanspeak\Command\Kick
 *
 * Moves jobs into the ready queue.
 * The Kick command applies only to the currently used tube.
 *
 * <code>
 * use Beanspeak\Command\Kick;
 *
 * $command = new Kick($bound);
 * </code>
 */
class Kick extends Command implements ParserInterface
{
    private bound;

    /**
     * Beanspeak\Command\Kick constructor
     */
    public function __construct(int! bound)
    {
        let this->bound = bound;
    }

    /**
     * {@inheritdoc}
     */
    public function getName() -> string
    {
        return "KICK";
    }

    /**
     * {@inheritdoc}
     */
    public function getCommandLine() -> string
    {
        return "kick " . this->bound;
    }

    /**
     * {@inheritdoc}
     */
     public function parseResponse(string line, string data = null) -> <ResponseInterface>
     {
         var kicked;

         let kicked = preg_replace("#^KICKED (.+)$#", "$1", line);

         return this->createResponse("KICKED", [
             "kicked" : (int) kicked
         ]);
     }
}
