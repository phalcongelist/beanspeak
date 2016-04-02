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

use Beanspeak\Job;
use Beanspeak\Command\Put;
use Beanspeak\Command\Stats;
use Beanspeak\Command\Choose;
use Beanspeak\Command\Reserve;
use Beanspeak\Job\JobInterface;
use Beanspeak\Command\PauseTube;
use Beanspeak\Response\ArrayResponse;
use Beanspeak\Dispatcher\DispatcherInterface;
use Beanspeak\Dispatcher\DispatcherAwareInterface;

/**
 * Beanspeak\Beanspeak
 *
 * Class to access the beanstalk queue service.
 *
 * <code>
 * use Beanspeak\Beanspeak;
 *
 * $queue = new Beanspeak([
 *     'host'       => '127.0.0.1',
 *     'port'       => 11300,
 *     'persistent' => true,
 * ]);
 * </code>
 *
 * @link https://github.com/kr/beanstalkd/
 */
class Beanspeak implements DispatcherAwareInterface
{
    /**
     * The internal Dispatcher.
     * @var \Beanspeak\Dispatcher\DispatcherInterface
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
    public function put(var data, array options = null) -> int
    {
        var priority, delay, ttr, serialized, response;

        // Priority is 100 by default
        if !fetch priority, options["priority"] {
            let priority = "100";
        }

        if !fetch delay, options["delay"] {
            let delay = "0";
        }

        if !fetch ttr, options["ttr"] {
            let ttr = "86400";
        }

        // Data is automatically serialized before be sent to the server
        let serialized = serialize(data);

        let response = this->dispatcher->dispatch(new Put(serialized, priority, delay, ttr));

        return response->id;
    }

    /**
     * Change the active tube.
     *
     * <code>
     * $queue->choose('mail-queue');
     * </code>
     */
    public function choose(string! tube) -> string
    {
        var response;
        let response = this->dispatcher->dispatch(new Choose(tube));

        return response->tube;
    }

    /**
     * Reserves/locks a ready job from the specified tube.
     *
     * <code>
     * $queue->reserve();
     * </code>
     */
    public function reserve(var timeout = null) -> boolean|<JobInterface>
    {
        var response;

        let response = this->dispatcher->dispatch(new Reserve(timeout));

        if response->getResponseName() == "RESERVED" {
            return new Job(response->id, response->jobdata);
        }

        return false;
    }

    /**
     * Gives statistical information about the system as a whole.
     *
     * <code>
     * $queue->stats();
     * </code>
     */
    public function stats() -> <ArrayResponse>
    {
        return this->dispatcher->dispatch(new Stats());
    }

    /**
     * The pause-tube command can delay any new job being reserved for a given time.
     *
     * <code>
     * $queue->pauseTube('process-video', 60 * 60);
     * </code>
     */
    public function pauseTube(string! tube, int! delay) -> int
    {
        var response;

        let response = this->dispatcher->dispatch(new PauseTube(tube, delay));

        return response->delay;
    }
}
