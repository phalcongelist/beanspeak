
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

use Beanspeak\Dispatcher\DispatcherInterface;

/**
 * Beanspeak\Dispatcher\DispatcherAwareInterface
 *
 * This interface must be implemented in those classes that uses internally the Beanspeak\Dispatcher that creates them
 */
interface DispatcherAwareInterface
{
    /**
     * Sets the Dispatcher.
     */
    public function setDispatcher(<DispatcherInterface> dispatcher);

    /**
     * Returns the Dispatcher.
     */
    public function getDispatcher() -> <DispatcherInterface>;
}
