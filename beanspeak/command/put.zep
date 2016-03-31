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
use Beanspeak\Response\ResponseParserInterface;

/**
 * Beanspeak\Command\Put
 *
 * Inserts a job into the client's currently used tube.
 */
class Put extends Command implements ResponseParserInterface
{
    private data;
    private priority;
    private delay;
    private ttr;

    /**
     * {@inheritdoc}
     */
    public function getName() -> string
    {
        return "PUT";
    }

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
        if (function_exists("mb_strlen")) {
            return mb_strlen(this->data, "latin1");
        }

        return strlen(this->data);
    }

    /**
     * {@inheritdoc}
     */
    public function parseResponse(string line, string data = null) -> <ResponseInterface>
    {
        var matches, name;

        let matches = null;

        if (preg_match("#^INSERTED (\d+)$#", line, matches)) {
            return this->createResponse("INSERTED", ["id" : (int) matches[1]]);
        }

        let name = this->getName();

        if (preg_match("#^BURIED (\d)+$#", line, matches)) {
            throw new Exception(name . ": server ran out of memory trying to grow the priority queue data structure");
        }

        if (preg_match("#^JOB_TOO_BIG$#", line)) {
            throw new Exception(name . ": job data exceeds server-enforced limit");
        }

        if (preg_match("#^EXPECTED_CRLF#", line)) {
            throw new Exception(name . ": CRLF expected");
        }

        if (preg_match("#^DRAINING#", line)) {
            throw new Exception(name . ": server has been put into 'drain mode' and is no longer accepting new jobs");
        }

        throw new Exception("Unhandled response: " . line);
    }
}
