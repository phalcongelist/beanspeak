/*
 +------------------------------------------------------------------------+
 | Beanspeak                                                              |
 +------------------------------------------------------------------------+
 | Copyright (c) 2016 Phalcon Team (http://www.phalconphp.com)            |
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

use Beanspeak\Job\JobInterface;

/**
 * Beanspeak\Job
 *
 * Represents a job in a beanstalk queue.
 */
class Job implements JobInterface
{
    private id;
    private data;

    /**
     * Beanspeak\Job constructor
     */
    public function __construct(int id, var data)
    {
        let this->id   = id,
            this->data = data;
    }

    /**
     * {@inheritdoc}
     */
    public function getId() -> int
    {
        return this->id;
    }

    /**
     * {@inheritdoc}
     */
    public function getData() -> var
    {
        return this->data;
    }
}
