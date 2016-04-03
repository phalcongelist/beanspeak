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
 * Beanspeak\Command\Touch
 *
 * Allows a worker to request more time to work on a Job.
 *
 * <code>
 * use Beanspeak\Command\Touch;
 *
 * $command = new Touch(89);
 * $command = new Touch($jobObject);
 * </code>
 */
class Touch extends Command implements ParserInterface
{
    private id;

    /**
     * Beanspeak\Command\Touch constructor
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
        return "TOUCH";
    }

    /**
     * {@inheritdoc}
     */
    public function getCommandLine() -> string
    {
        return "touch " . this->id;
    }

    /**
     * {@inheritdoc}
     * @throws \Beanspeak\Command\Exception
     */
     public function parseResponse(string line, string data = null) -> <ResponseInterface>
     {
         if starts_with(line, "TOUCHED") {
             return this->createResponse("TOUCHED");
         }

         if starts_with(line, "NOT_FOUND") {
             throw new Exception(this->getName() . ": Job ID #" . this->id . " does not exist or is not reserved by client");
         }

         throw new Exception("Unhandled response: " . line);
     }
}
