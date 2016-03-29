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

namespace Beanspeak;

use Beanspeak\Response\Exception;
use Beanspeak\Command\CommandInterface;
use Beanspeak\Response\ResponseInterface;
use Beanspeak\Connection\ConnectionInterface;

/**
 * Beanspeak\Response
 */
class Response implements ResponseInterface
{
    // See https://github.com/kr/beanstalk/blob/master/err.go
    const EXCEPTION_BAD_FORMAT      = 0;
    const EXCEPTION_BURIED          = 1;
    const EXCEPTION_DEADLINE_SOON   = 2;
    const EXCEPTION_DRAINING        = 3;
    const EXCEPTION_EXPECTED_CRLF   = 4;
    const EXCEPTION_INTERNAL_ERROR  = 5;
    const EXCEPTION_JOB_TOO_BIG     = 6;
    const EXCEPTION_NOT_FOUND       = 7;
    const EXCEPTION_NOT_IGNORED     = 8;
    const EXCEPTION_OUT_OF_MEMORY   = 9;
    const EXCEPTION_TIMED_OUT       = 10;
    const EXCEPTION_UNKNOWN_COMMAND = 11;

    const EXCEPTION_NO_CRLF         = 255;

    protected connection;
    protected command;
    protected commandName;
    protected content;
    protected data;
    protected statusMessages = [];
    protected dataResponses = [];

    /**
     * Beanspeak\Response constructor
     *
     * @param string content
     */
    public function __construct(<CommandInterface> command, <ConnectionInterface> connection)
    {
        let this->command     = command,
            this->connection  = connection,
            this->content     = connection->getLine(),
            this->commandName = command->getName();

        this->checkStatusMessage();

        this->parseData();
    }

    /**
     * {@inheritdoc}
     */
    public function getContent() -> string
    {
        return this->content;
    }

    /**
     * {@inheritdoc}
     */
    public function getData() -> var
    {
        return this->data;
    }

    protected function parseData() -> void
    {
        array dataResponses;
        var connection, dataLength, content, data, message, crlf;       

        let dataResponses = this->dataResponses,
            content       = this->content,
            message       = preg_replace("#^(\S+).*$#s", "$1", content);

        if empty dataResponses {
            let dataResponses = [
                "RESERVED" : true,
                "FOUND"    : true,
                "OK"       : true
            ];

            let this->dataResponses = dataResponses;
        }

        let data = null;
        if isset dataResponses[message] {
            let dataLength = preg_replace("#^.*\b(\d+)$#", "$1", content),
                data       = connection->read(dataLength),
                crlf       = connection->read(2);

            if "\r\n" !== crlf {
                throw new Exception(
                    sprintf("Expected 2 bytes of CRLF after %u bytes of data", dataLength),
                    self::EXCEPTION_NO_CRLF
                );
            }
        }

        let this->data = data;
    }

    protected function checkStatusMessage() -> void
    {
        var content, message;
        array statusMessages;

        let statusMessages = this->statusMessages,
            content        = this->content,
            message        = preg_replace("#^(\S+).*$#s", "$1", content);

        if empty statusMessages {
            let statusMessages = [
                "BAD_FORMAT":      self::EXCEPTION_BAD_FORMAT,
                "BURIED":          self::EXCEPTION_BURIED,
                "DEADLINE_SOON":   self::EXCEPTION_DEADLINE_SOON,
                "DRAINING":        self::EXCEPTION_DRAINING,
                "EXPECTED_CRLF":   self::EXCEPTION_EXPECTED_CRLF,
                "INTERNAL_ERROR":  self::EXCEPTION_INTERNAL_ERROR,
                "JOB_TOO_BIG":     self::EXCEPTION_JOB_TOO_BIG,
                "NOT_FOUND":       self::EXCEPTION_NOT_FOUND,
                "NOT_IGNORED":     self::EXCEPTION_NOT_IGNORED,
                "OUT_OF_MEMORY":   self::EXCEPTION_OUT_OF_MEMORY,
                "TIMED_OUT":       self::EXCEPTION_TIMED_OUT,
                "UNKNOWN_COMMAND": self::EXCEPTION_UNKNOWN_COMMAND
            ];

            let this->statusMessages = statusMessages;
        }

        if isset statusMessages[message] {
            throw new Exception(
                sprintf("%s in response to '%s'", message, this->commandName),
                statusMessages[message]
            );
        }
    }
}