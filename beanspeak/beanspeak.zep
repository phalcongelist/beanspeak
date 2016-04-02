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
use Beanspeak\Command\Peek;
use Beanspeak\Command\Quit;
use Beanspeak\Command\Stats;
use Beanspeak\Command\Choose;
use Beanspeak\Command\Reserve;
use Beanspeak\Job\JobInterface;
use Beanspeak\Command\StatsJob;
use Beanspeak\Command\StatsTube;
use Beanspeak\Command\ListTubes;
use Beanspeak\Command\PauseTube;
use Beanspeak\Command\ListTubeUsed;
use Beanspeak\Response\ArrayResponse;
use Beanspeak\Command\ListTubesWatched;
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
     * $task = [
     *     'recipient' => 'user@mail.com',
     *     'subject'   => 'Welcome',
     *     'content'   => $content,
     * ];
     *
     * $queue->put($task, [
     *     'priority' => 999,
     *     'delay'    => 60 * 60,
     *     'ttr'      => 3600,
     * ]):
     * </code>
     */
    public function put(var data, array options = null) -> int
    {
        var  response;

        let response = this->dispatcher->dispatch(new Put(data, options));

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
            return new Job(response->id, unserialize(response->jobdata));
        }

        return false;
    }

    /**
     * Lets the client inspect a job in the system.
     *
     * <code>
     * $peekJob     = $queue->peek(91);        // Returns a Job ID
     * $peekReady   = $queue->peek('ready');   // Inspect the next ready job.
     * $peekDelayed = $queue->peek('delayed'); // Return the delayed job with the shortest delay left.
     * $peekBuried  = $queue->peek('buried');  // Return the next job in the list of buried jobs.
     * </code>
     */
    public function peek(var subject) -> <JobInterface>
    {
        var response;

        let response = this->dispatcher->dispatch(new Peek(subject));

        return new Job(response->id, unserialize(response->jobdata));
    }

    /**
     * Lets the client inspect a job in the system.
     *
     * <code>
     * $queue->peekJob();
     * </code>
     */
    public function peekJob(int id) -> <JobInterface>
    {
        return this->peek(id);
    }

    /**
     * Return the delayed job with the shortest delay left.
     *
     * <code>
     * $queue->peekDelayed();
     * </code>
     */
    public function peekDelayed() -> <JobInterface>
    {
        return this->peek("delayed");
    }

    /**
     * Return the next job in the list of buried jobs.
     *
     * <code>
     * $queue->peekBuried();
     * </code>
     */
    public function peekBuried() -> <JobInterface>
    {
        return this->peek("buried");
    }

    /**
     * Inspect the next ready job.
     *
     * <code>
     * $queue->peekReady();
     * </code>
     */
    public function peekReady() -> <JobInterface>
    {
        return this->peek("ready");
    }

    /**
     * Returns a list of all existing tubes.
     *
     * <code>
     * $queue->listTubes();
     * </code>
     */
    public function listTubes() -> <ArrayResponse>
    {
        return this->dispatcher->dispatch(new ListTubes());
    }

    /**
     * Returns the tube currently being used by the client.
     *
     * <code>
     * $tube = $queue->listTubeUsed();
     * </code>
     */
    public function listTubeUsed() -> string
    {
        var response;

        let response = this->dispatcher->dispatch(new ListTubeUsed());

        return response->tube;
    }

    /**
     * Returns a list tubes currently being watched by the client.
     *
     * <code>
     * $queue->listTubesWatched();
     * </code>
     */
    public function listTubesWatched() -> <ArrayResponse>
    {
        return this->dispatcher->dispatch(new ListTubesWatched());
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
     * Gives statistical information about the specified tube if it exists.
     *
     * <code>
     * $queue->statsTube('process-bitcoin');
     * </code>
     */
    public function statsTube(string! tube) -> <ArrayResponse>
    {
        return this->dispatcher->dispatch(new StatsTube(tube));
    }

    /**
     * Gives statistical information about the specified tube if it exists.
     *
     * <code>
     * $stats = $queue->statsJob(90);
     * $stats = $queue->statsJob($jobObject);
     * </code>
     */
    public function statsJob(var job) -> <ArrayResponse>
    {
        return this->dispatcher->dispatch(new StatsJob(job));
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

    /**
     * Simply closes the connection.
     *
     * <code>
     * $queue->quit();
     * </code>
     */
    public function quit() -> boolean
    {
        var dispatcher, connection;

        let dispatcher = this->dispatcher,
            connection = dispatcher->getConnection();

        if connection->isConnected() {
            dispatcher->dispatch(new Quit());
            connection->disconnect();
        }

        return connection->isConnected() === false;
    }
}
