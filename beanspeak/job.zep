/*
 +------------------------------------------------------------------------+
 | Beanspeak                                                              |
 +------------------------------------------------------------------------+
 | Copyright (c) 2016 Phalcon Team (https://www.phalconphp.com)           |
 +------------------------------------------------------------------------+
 | This source file is subject to the New BSD License that is bundled     |
 | with this package in the file LICENSE.txt.                             |
 |                                                                        |
 | If you did not receive a copy of the license and are unable to         |
 | obtain it through the world-wide-web, please send an email             |
 | to license@phalconphp.com so we can send you a copy immediately.       |
 +------------------------------------------------------------------------+
 | Authors: Serghei Iakovlev <serghei@phalconphp.com>                     |
 +------------------------------------------------------------------------+
*/

namespace Beanspeak;

/**
 * Beanspeak\Job
 *
 * Represents a job in a beanstalk queue.
 */
class Job
{
	/**
	 * @var Client
	 */
	protected queue;

	/**
	 * @var string
	 */
	protected id { get };

	/**
	 * @var mixed
	 */
	protected body { get };

	/**
	 * Beanspeak\Job constructor
	 */
	public function __construct(<Client> queue, string id, var body)
	{
		let this->{"queue"} = queue,
			this->{"id"}    = id,
			this->{"body"}  = body;
	}

	/**
	 * Removes a job from the server entirely.
	 *
	 * <code>
	 * $job->delete();
	 * </code>
	 */
	public function delete() -> boolean
	{
		var queue, response;

		let queue = this->queue;
		queue->write("delete " . this->id);

		let response = queue->readStatus();

		return isset response[0] && response[0] == "DELETED";
	}

	/**
	 * Allows a worker to request more time to work on a Job.
	 *
	 * <code>
	 * $job->touch();
	 * </code>
	 */
	public function touch() -> boolean
	{
		var queue, response;

		let queue = this->queue;
		queue->write("touch " . this->id);

		let response = queue->readStatus();

		return isset response[0] && response[0] == "TOUCHED";
	}


	/**
	 * Puts a "reserved" job back into the ready queue (and marks its
	 * state as "ready") to be run by any client.
	 *
	 * <code>
	 * $job->release(10, 60 * 60);
	 * </code>
	 */
	public function release(int priority = 1024, int delay = 0) -> boolean
	{
		var queue, response;

		let queue = this->queue;
		queue->write("release " . this->id . " " . priority . " " . delay);

		let response = queue->readStatus();

		return isset response[0] && response[0] == "RELEASED";
	}

	/**
	 * Puts a job into the "buried" state.
	 *
	 * <code>
	 * $job->release(10, 60 * 60);
	 * </code>
	 */
	public function bury(int priority = 1024) -> boolean
	{
		var queue, response;

		let queue = this->queue;
		queue->write("bury " . this->id . " " . priority);

		let response = queue->readStatus();

		return isset response[0] && response[0] == "BURIED";
	}

	/**
	 * Gives statistical information about the specified job if it exists.
	 *
	 * <code>
	 * $stats = $job->stats();
	 * </code>
	 */
	public function stats() -> boolean|array
	{
		var queue, response;

		let queue = this->queue;
		queue->write("stats-job " . this->id);

		let response = queue->readYaml();
		if response[0] != "OK" {
			return false;
		}

		return response[2];
	}

	/**
	 * A variant of Client::kick that operates with a single job identified by its Job ID.
	 *
	 * <code>
	 * $job->kick();
	 * </code>
	 */
	public function kick() -> boolean
	{
		var queue, response;

		let queue = this->queue;
		queue->write("kick-job " . this->id);

		let response = queue->readStatus();

		return isset response[0] && response[0] == "KICKED";
	}

	/**
	 * Checks if the job has been modified after unserializing the object
	 */
	public function __wakeup()
	{
		if typeof this->id != "string" {
			throw new Exception("Unexpected inconsistency in Beanspeak\\Job::__wakeup() - possible break-in attempt!");
		}
	}
}
