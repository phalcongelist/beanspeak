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
 * Beanspeak\Command\StatsTube
 *
 * Gives statistical information about the specified tube if it exists.
 *
 * <code>
 * use Beanspeak\Command\StatsTube;
 *
 * $stats = new StatsTube('process-bitcoin');
 * </code>
 */
class StatsTube extends Command
{
    private tube;

    /**
     * Beanspeak\Command\StatsTube constructor
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
        return "STATS-TUBE";
    }

    /**
     * {@inheritdoc}
     */
    public function getCommandLine()
    {
        return "stats-tube " . this->tube;
    }

    /**
     * {@inheritdoc}
     */
    public function getResponseParser() -> <ParserInterface>
    {
        return new Yaml;
    }
}
