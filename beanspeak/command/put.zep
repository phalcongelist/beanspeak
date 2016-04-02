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
 * Beanspeak\Command\Put
 *
 * Inserts a job into the client's currently used tube.
 *
 * <code>
 * use Beanspeak\Command\Put;
 *
 * $put = new Put(
 *     [
 *         'recipient' => 'user@mail.com',
 *         'subject'   => 'Welcome',
 *         'content'   => $content,
 *     ],
 *     999,
 *     60 * 60,
 *     3600,
 * );
 * </code>
 */
class Put extends Command implements ParserInterface
{
    private data;
    private priority;
    private delay;
    private ttr;

    /**
     * Beanspeak\Command\Put constructor
     */
    public function __construct(string! data, int priority, int delay, int ttr)
    {
        let this->data     = data,
            this->priority = priority,
            this->delay    = delay,
            this->ttr      = ttr;
    }

    /**
     * {@inheritdoc}
     */
    public function getName() -> string
    {
        return "PUT";
    }

    /**
     * {@inheritdoc}
     */
    public function getCommandLine() -> string
    {
        return "put " . this->priority . " " . this->delay . " " . this->ttr . " " . this->getDataLength();
    }

    /**
     * {@inheritdoc}
     */
    public function hasData()
    {
        return true;
    }

    /**
     * {@inheritdoc}
     */
    public function getData()
    {
        return this->data;
    }

    /**
     * {@inheritdoc}
     */
    public function getDataLength()
    {
        if function_exists("mb_strlen") {
            return mb_strlen(this->data, "latin1");
        }

        return strlen(this->data);
    }

    /**
     * {@inheritdoc}
     *  @throws \Beanspeak\Command\Exception
     */
    public function parseResponse(string line, string data = null) -> <ResponseInterface>
    {
        var matches = null;

        if preg_match("#^INSERTED (\d+)$#", line, matches) {
            return this->createResponse("INSERTED", ["id" : (int) matches[1]]);
        }

        if starts_with(line, "BURIED") {
            throw new Exception(this->getName() . ": server ran out of memory trying to grow the priority queue data structure");
        }

        if starts_with(line, "JOB_TOO_BIG") {
            throw new Exception(this->getName() . ": job data exceeds server-enforced limit");
        }

        if starts_with(line, "EXPECTED_CRLF") {
            throw new Exception(this->getName() . ": CRLF expected");
        }

        if starts_with(line, "DRAINING") {
            throw new Exception(this->getName() . ": server has been put into 'drain mode' and is no longer accepting new jobs");
        }

        throw new Exception("Unhandled response: " . line);
    }
}
