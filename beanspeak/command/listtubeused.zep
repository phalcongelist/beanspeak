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
 * Beanspeak\Command\ListTubeUsed
 *
 * Returns the tube currently being used by the client.
 *
 * <code>
 * use Beanspeak\Command\ListTubeUsed;
 *
 * $tube = new ListTubeUsed;
 * </code>
 */
class ListTubeUsed extends Command implements ParserInterface
{
    /**
     * {@inheritdoc}
     */
    public function getName() -> string
    {
        return "LIST-TUBE-USED";
    }

    /**
     * {@inheritdoc}
     */
    public function getCommandLine() -> string
    {
        return "list-tube-used";
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
