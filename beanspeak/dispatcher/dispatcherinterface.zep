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

namespace Beanspeak\Dispatcher;

use Beanspeak\Command\CommandInterface;
use Beanspeak\Response\Parser\ParserInterface;

/**
 * Beanspeak\Dispatcher\DispatcherInterface
 *
 * Interface for Beanspeak\Dispatcher
 */
interface DispatcherInterface
{
    /**
     * Dispatches the specified command to the connection object.
     */
    public function dispatch(<CommandInterface> command) -> <ParserInterface>;
}
