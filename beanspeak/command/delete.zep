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
use InvalidArgumentException;
use Beanspeak\Job\JobInterface;
use Beanspeak\Response\ResponseInterface;
use Beanspeak\Response\Parser\ParserInterface;

/**
 * Beanspeak\Command\Delete
 *
 * Removes a job from the server entirely.
 *
 * <code>
 * use Beanspeak\Command\Delete;
 *
 * $command = new Delete(18);
 * $command = new Delete($jobObject);
 * </code>
 */
class Delete extends Command implements ParserInterface
{
    private id;

    /**
     * Beanspeak\Command\Delete constructor
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
        return "DELETE";
    }

    /**
     * {@inheritdoc}
     */
    public function getCommandLine() -> string
    {
        return "delete " . this->id;
    }

    /**
     * {@inheritdoc}
     * @throws \Beanspeak\Command\Exception
     */
     public function parseResponse(string line, string data = null) -> <ResponseInterface>
     {
         if starts_with(line, "DELETED") {
             return this->createResponse("DELETED");
         }

         if starts_with(line, "NOT_FOUND") {
             throw new Exception(this->getName() . ": Cannot delete Job ID #" . this->id);
         }

        throw new Exception("Unhandled response: " . line);
     }
}
