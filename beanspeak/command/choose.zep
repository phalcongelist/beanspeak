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
 * Beanspeak\Command\Use
 *
 * The "use" command is for producers. Subsequent put commands will put jobs
 * into the tube specified by this command. If no use command has been issued,
 * jobs will be put into the tube named "default".
 *
 * <code>
 * use Beanspeak\Command\Choose;
 *
 * $command = new Choose('mail-queue');
 * </code>
 */
class Choose extends Command implements ParserInterface
{
    private tube;

    /**
     * Beanspeak\Command\Use constructor
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
        return "USE";
    }

    /**
     * {@inheritdoc}
     */
    public function getCommandLine() -> string
    {
        return "use " . this->tube;
    }

    /**
     * {@inheritdoc}
     * @throws \Beanspeak\Command\Exception
     */
    public function parseResponse(string line, string data = null) -> <ResponseInterface>
    {
       if starts_with(line, "USING") {
           return this->createResponse("USING", [
               "tube" : preg_replace("#^USING (.+)$#", "$1", line)
           ]);
       }

       throw new Exception("Unhandled response: " . line);
    }
}
