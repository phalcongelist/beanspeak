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

use Beanspeak\Command\Exception;
use Beanspeak\Response\ArrayResponse;
use Beanspeak\Command\CommandInterface;
use Beanspeak\Response\ResponseInterface;
use Beanspeak\Response\Parser\ParserInterface;

/**
 * Beanspeak\Command
 *
 * A command to be sent to the beanstalkd server, and response processing logic.
 */
abstract class Command implements CommandInterface
{
    /**
     * {@inheritdoc}
     */
    public function hasData() -> boolean
    {
        return false;
    }

    /**
     * {@inheritdoc}
     */
    public function getData() -> string
    {
        throw new Exception("The " . this->getName() . " command has no data");
    }

    /**
     * {@inheritdoc}
     */
    public function getDataLength() -> int
    {
        throw new Exception("The " . this->getName() . " command has no data");
    }

    /**
     * {@inheritdoc}
     */
    public function getResponseParser() -> <ParserInterface>
    {
       return this;
    }

    /**
     * Creates a Response for the given data.
     */
    protected function createResponse(string name, array data = []) -> <ResponseInterface>
    {
        return new ArrayResponse(name, data);
    }

    /**
     * {@inheritdoc}
     */
    public function __toString() -> string
    {
        return this->getCommandLine();
    }
}
