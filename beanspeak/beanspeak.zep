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

use Beanspeak\Command\Put;
use Beanspeak\Dispatcher\DispatcherInterface;
use Beanspeak\Dispatcher\DispatcherAwareInterface;

/**
 * Beanspeak\Beanspeak
 *
 * Class to access the beanstalk queue service.
 */
class Beanspeak implements DispatcherAwareInterface
{
    /**
     * The internal Dispatcher.
     * @var DispatcherInterface
     */
    protected dispatcher;

    /**
     * Beanspeak\Beanspeak constructor
     */
    public function __construct(<DispatcherInterface> dispatcher = null)
    {
        let dispatcher = dispatcher ?: new Dispatcher;

        let this->dispatcher = dispatcher;
    }

    /**
     * {@inheritdoc}
     */
    public function setDispatcher(<DispatcherInterface> dispatcher) -> <Beanspeak>
    {
         let this->dispatcher = dispatcher;

         return this;
    }

    /**
     * {@inheritdoc}
     */
    public function getDispatcher() -> <DispatcherInterface>
    {
        return this->dispatcher;
    }

    /**
     * Inserts jobs into the queue.
     *
     * Example:
     * <code>
     * $queue->put(
     *     [
     *         'recipient' => 'user@mail.com',
     *         'subject'   => 'Welcome',
     *         'content'   => $content,
     *     ],
     *     [
     *         'priority' => 999,
     *         'delay'    => 60 * 60,
     *         'ttr'      => 3600,
     *     ],
     * );
     * </code>
     */
    public function put(var data, array options = null)
    {
        var priority, delay, ttr, serialized, dispatcher, response;

        /**
         * Priority is 100 by default
         */
        if !fetch priority, options["priority"] {
            let priority = "100";
        }

        if !fetch delay, options["delay"] {
            let delay = "0";
        }

        if !fetch ttr, options["ttr"] {
            let ttr = "86400";
        }

        /**
         * Data is automatically serialized before be sent to the server
         */
        let serialized = serialize(data),
            dispatcher = this->dispatcher;

        let response = dispatcher->dispatch(new Put(serialized, priority, delay, ttr));

        return response->id;
    }
}
