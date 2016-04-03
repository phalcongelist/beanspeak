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
use Beanspeak\Job\JobInterface;
use Beanspeak\Response\ResponseInterface;
use Beanspeak\Response\Parser\ParserInterface;

/**
 * Beanspeak\Command\KickJob
 *
 * A variant of kick that operates with a single job identified by its Job ID.
 * If the given job id exists and is in a buried or delayed state, it will be
 * moved to the ready queue of the the same tube where it currently belongs.
 *
 * <code>
 * use Beanspeak\Command\KickJob;
 *
 * $command = new KickJob(43);
 * </code>
 */
class KickJob extends Command implements ParserInterface
{
    private id;

    /**
     * Beanspeak\Command\KickJob constructor
     * @throws \Beanspeak\Command\Exception
     */
    public function __construct(var job)
    {
        if typeof job == "object" && job instanceof JobInterface {
            let this->id = job->getId();
        } elseif typeof job == "int" || ctype_digit(job) {
            let this->id = (int) job;
        } else {
            throw new Exception("The \"job\" param must be either instanceof JobInterface or integer. Got: " . typeof job);
        }
    }

    /**
     * {@inheritdoc}
     */
    public function getName() -> string
    {
        return "KICK-JOB";
    }

    /**
     * {@inheritdoc}
     */
    public function getCommandLine() -> string
    {
        return "kick-job " . this->id;
    }

    /**
     * {@inheritdoc}
     * @throws \Beanspeak\Command\Exception
     */
     public function parseResponse(string line, string data = null) -> <ResponseInterface>
     {
         if starts_with(line, "KICKED") {
             return this->createResponse("KICKED");
         }

        if starts_with(line, "NOT_FOUND") {
            throw new Exception(this->getName() . ": Job " . this->id . " does not exist or is not in a kickable state");
        }

        throw new Exception("Unhandled response: " . line);
    }
}
