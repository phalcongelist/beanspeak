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
use Beanspeak\Command\CommandInterface;
use Beanspeak\Response\ResponseInterface;
use Beanspeak\Connection\ConnectionInterface;

/**
 * Beanspeak\Command
 */
abstract class Command implements CommandInterface
{
    /**
     * {@inheritdoc}
     */
    public function getCommandName() -> string
    {
        return strtoupper(array_pop(explode("\\", get_called_class())));
    }

    /**
     * {@inheritdoc}
     *
     * @throws \Beanspeak\Command\Exception
     */
    public function execute(<ConnectionInterface> connection) -> <ResponseInterface>
    {
        var preparedcmd;

        let preparedcmd = this->getCommandLine() . "\r\n";

        if this->hasData() {
            let preparedcmd .= this->getData() . "\r\n";
        }

        connection->write(preparedcmd);

        return new Response(this, connection);
    }

    /**
     * {@inheritdoc}
     */
    public function hasData()
    {
        return false;
    }

    /*
     * {@inheritdoc}
     */
    public function getData()
    {
        throw new Exception("Command has no data");
    }

    /*
     * {@inheritdoc}
     */
    public function getDataLength()
    {
        throw new Exception("Command has no data");
    }

    /**
     * {@inheritdoc}
     */
    public function __toString() -> string
    {
        return this->getCommandLine();
    }
}
