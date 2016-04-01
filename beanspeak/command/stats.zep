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
use Beanspeak\Response\Parser\Yaml;
use Beanspeak\Response\ResponseParserInterface;

/**
 * Beanspeak\Command\Stats
 *
 * Statistical information about the system as a whole.
 *
 * <code>
 * use Beanspeak\Command\Stats;
 *
 * $stats = new Stats;
 * </code>
 */
class Stats extends Command
{
    /**
     * {@inheritdoc}
     */
    public function getName() -> string
    {
        return "STATS";
    }

    public function getCommandLine()
    {
        return "stats";
    }

    public function getResponseParser()
    {
        return new Yaml("dict");
    }
}
