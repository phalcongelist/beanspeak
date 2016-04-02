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
 * Beanspeak\Command\Peek
 *
 * Lets the client inspect a job in the system.
 *
 * <code>
 * use Beanspeak\Command\Peek;
 *
 * $peekJob     = new Peek(75);
 * $peekReady   = new Peek('ready');
 * $peekDelayed = new Peek('delayed');
 * $peekBuried  = new Peek('buried');
 * </code>
 */
class Peek extends Command implements ParserInterface
{
    private jobId = null;
    private commandSuffix = "";

    /**
     * Beanspeak\Command\Peek constructor
     * @throws \Beanspeak\Command\Exception
     */
    public function __construct(var subject)
    {
        if typeof subject == "int" || ctype_digit(subject) {
            let this->jobId = subject;
        } elseif typeof subject == "string" {
            if subject == "ready" || subject == "delayed" || subject == "buried" {
                let this->commandSuffix = "-" . subject;
            } else {
                throw new Exception("Invalid peek subject: " . subject);
            }
        } else {
            throw new Exception("Peek subject must be either integer or string got: " . typeof subject);
        }
    }

    /**
     * {@inheritdoc}
     */
    public function getName() -> string
    {
        string name = "PEEK";
        var commandSuffix;

        let commandSuffix = this->commandSuffix;

        if !empty(commandSuffix) {
            let name .= strtoupper(commandSuffix);
        }

        return name;
    }

    /**
     * {@inheritdoc}
     */
    public function getCommandLine() -> string
    {
        string command = "peek";
        var commandSuffix;

        let commandSuffix = this->commandSuffix;

        if !empty(commandSuffix) {
            return command . commandSuffix;
        }

        return command . " " . this->jobId;
    }

    /**
     * {@inheritdoc}
     * @throws \Beanspeak\Command\Exception
     */
    public function parseResponse(string line, string data = null) -> <ResponseInterface>
    {
        if starts_with(line, "NOT_FOUND") {
            if this->jobId !== null {
                throw new Exception(this->getName() . ": Job ID #" . this->jobId . " does not exist");
            } else {
                throw new Exception(this->getName() . ": There are no jobs in the '" . this->commandSuffix . "' status");
            }
        }

        var matches = null;

        if preg_match("#^FOUND (\d+) \d+$#", line, matches) {
            return this->createResponse("FOUND", [
                "id"      : (int) matches[1],
                "jobdata" : data
            ]);
        }

        throw new Exception("Unhandled response: " . line);
    }
}
