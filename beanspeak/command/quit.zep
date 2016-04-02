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
 * Beanspeak\Command\Quit
 *
 * Simply closes the connection.
 *
 * <code>
 * use Beanspeak\Command\Quit;
 *
 * $quit = new Quit;
 * </code>
 */
class Quit extends Command implements ParserInterface
{
    /**
     * {@inheritdoc}
     */
    public function getName() -> string
    {
        return "QUIT";
    }

    /**
     * {@inheritdoc}
     */
    public function getCommandLine() -> string
    {
        return "quit";
    }

    /**
     * {@inheritdoc}
     */
    public function hasResponse() -> boolean
    {
        return false;
    }

    /**
     * {@inheritdoc}
     */
    public function parseResponse(string line, string data = null) -> <ResponseInterface>
    {
       return this->createResponse("QUIT");
    }
}
