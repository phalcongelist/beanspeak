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
 * Beanspeak\Command\Release
 *
 * Puts a "reserved" job back into the ready queue (and marks its state as "ready")
 * to be run by any client.
 *
 * <code>
 * use Beanspeak\Command\Release;
 *
 * $command = new Release(89, 10, 60 * 60);
 * $command = new Release($jobObject, 10, 60 * 60);
 * </code>
 */
class Release extends Command implements ParserInterface
{
    private id;
    private pri;
    private delay;

    /**
     * Beanspeak\Command\Release constructor
     * @throws \Beanspeak\Command\Exception
     */
    public function __construct(var job, int! pri = 1024, int! delay = 0)
    {
        if typeof job == "object" && job instanceof JobInterface {
            let this->id = job->getId();
        } elseif typeof job == "int" || ctype_digit(job) {
            let this->id = (int) job;
        } else {
            throw new Exception("The \"job\" param must be either instanceof JobInterface or integer. Got: " . typeof job);
        }

        let this->pri   = pri,
            this->delay = delay;
    }

    /**
     * {@inheritdoc}
     */
    public function getName() -> string
    {
        return "RELEASE";
    }

    /**
     * {@inheritdoc}
     */
    public function getCommandLine() -> string
    {
        return "release " . this->id . " " . this->pri . " " . this->delay;
    }

    /**
     * {@inheritdoc}
     * @throws \Beanspeak\Command\Exception
     */
     public function parseResponse(string line, string data = null) -> <ResponseInterface>
     {
         if starts_with(line, "RELEASED") {
             return this->createResponse("RELEASED");
         }

         if starts_with(line, "BURIED") {
             throw new Exception(this->getName() . ": out of memory trying to grow data structure by release Job ID #" . this->id);
         }

         if starts_with(line, "NOT_FOUND") {
             throw new Exception(this->getName() . ": Job ID #" . this->id . " doesn't exist or is not reserved by client");
         }

         throw new Exception("Unhandled response: " . line);
     }
}
