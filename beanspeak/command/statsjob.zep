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
use InvalidArgumentException;
use Beanspeak\Job\JobInterface;
use Beanspeak\Response\Parser\Yaml;
use Beanspeak\Response\Parser\ParserInterface;

/**
 * Beanspeak\Command\StatsJob
 *
 * Gives  statistical information about the specified job if it exists.
 *
 * <code>
 * use Beanspeak\Command\StatsJob;
 *
 * $stats = new StatsJob(90);
 * $stats = new StatsJob($jobObject);
 * </code>
 */
class StatsJob extends Command
{
    private id;

    /**
     * Beanspeak\Command\StatsJob constructor
     * @throws \InvalidArgumentException
     */
    public function __construct(var job)
    {
        if typeof job == "object" && job instanceof JobInterface {
            let this->id = job->getId();
        } elseif typeof job == "int" || ctype_digit(job) {
            let this->id = (int) job;
        } else {
            throw new InvalidArgumentException("The \"job\" param must be either instanceof JobInterface or integer. Got: " . typeof job);
        }
    }

    /**
     * {@inheritdoc}
     */
    public function getName() -> string
    {
        return "STATS-JOB";
    }

    /**
     * {@inheritdoc}
     */
    public function getCommandLine()
    {
        return "stats-job " . this->id;
    }

    /**
     * {@inheritdoc}
     */
    public function getResponseParser() -> <ParserInterface>
    {
        return new Yaml;
    }
}
