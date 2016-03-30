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
use Beanspeak\Response\ResponseParserInterface;

/**
 * Beanspeak\Command
 */
abstract class Command implements CommandInterface
{
    /**
     * {@inheritdoc}
     */
    public function getName() -> string
    {
        return strtoupper(array_pop(explode("\\", get_called_class())));
    }

    /**
     * {@inheritdoc}
     */
    public function hasData()
    {
        return false;
    }

    /**
     * {@inheritdoc}
     */
    public function getData()
    {
        throw new Exception("Command has no data");
    }

    /**
     * {@inheritdoc}
     */
    public function getDataLength()
    {
        throw new Exception("Command has no data");
    }

    /**
     * {@inheritdoc}
     * Concrete implementation must either:
     * a) implement ResponseParserInterface
     * b) override this getResponseParser method
     */
    public function getResponseParser() -> <ResponseParserInterface>
    {
       return this;
    }

    /**
     * {@inheritdoc}
     */
    public function __toString() -> string
    {
        return this->getCommandLine();
    }

    /**
     * Creates a Response for the given data.
     */
    protected function createResponse(string name, array data = [])
    {
        return new ArrayResponse(name, data);
    }
}
