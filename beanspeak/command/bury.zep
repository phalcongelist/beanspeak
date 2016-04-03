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
 * Beanspeak\Command\Bury
 *
 * Puts a job into the "buried" state.
 *
 * <code>
 * use Beanspeak\Command\Bury;
 *
 * $command = new Bury(89, 10);
 * $command = new Bury($jobObject, 10);
 * </code>
 */
class Bury extends Command implements ParserInterface
{
    private id;
    private priority;

    /**
     * Beanspeak\Command\Bury constructor
     * @throws \Beanspeak\Command\Exception
     */
    public function __construct(var job, int priority)
    {
        if typeof job == "object" && job instanceof JobInterface {
            let this->id = job->getId();
        } elseif typeof job == "int" || ctype_digit(job) {
            let this->id = (int) job;
        } else {
            throw new Exception("The \"job\" param must be either instanceof JobInterface or integer. Got: " . typeof job);
        }

        let this->priority = priority;
    }

    /**
     * {@inheritdoc}
     */
    public function getName() -> string
    {
        return "BURY";
    }

    /**
     * {@inheritdoc}
     */
    public function getCommandLine() -> string
    {
        return "bury " . this->id . " " . this->priority;
    }

    /**
     * {@inheritdoc}
     * @throws \Beanspeak\Command\Exception
     */
     public function parseResponse(string line, string data = null) -> <ResponseInterface>
     {
         if starts_with(line, "BURIED") {
             return this->createResponse("BURIED");
         }

         if starts_with(line, "NOT_FOUND") {
             throw new Exception(this->getName() . ": Job ID #" . this->id . " is not reserved or does not exist");
         }

         throw new Exception("Unhandled response: " . line);
     }
}
