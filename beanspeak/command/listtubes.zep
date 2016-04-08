/*
 +------------------------------------------------------------------------+
 | Beanspeak                                                              |
 +------------------------------------------------------------------------+
 | Copyright (c) 2016 Phalcon Team (http://www.phalconphp.com)            |
 +------------------------------------------------------------------------+
 | This source file is subject to the New BSD License that is bundled     |
 | with this package in the file LICENSE.txt.                             |
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
use Beanspeak\Response\Parser\Yaml;
use Beanspeak\Response\Parser\ParserInterface;

/**
 * Beanspeak\Command\ListTubes
 *
 * Returns a list of all existing tubes.
 *
 * <code>
 * use Beanspeak\Command\ListTubes;
 *
 * $list = new ListTubes;
 * </code>
 */
class ListTubes extends Command
{
    /**
     * {@inheritdoc}
     */
    public function getName() -> string
    {
        return "LIST-TUBES";
    }

    /**
     * {@inheritdoc}
     */
    public function getCommandLine() -> string
    {
        return "list-tubes";
    }

    /**
     * {@inheritdoc}
     */
    public function getResponseParser() -> <ParserInterface>
    {
        return new Yaml;
    }
}
