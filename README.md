# Beanspeak [![Build Status](https://travis-ci.org/phalcongelist/beanspeak.svg?branch=master)][0]

Beanspeak is the best way to interact with [beanstalkd workqueue][1] in PHP.
Beanspeak is designed as a C-extension for PHP and aims to be the most complete,
stable and fastest solution for PHP world. It's simple, lightweight, and
completely specialized for job queueing.

Supported PHP versions: **5.4**, **5.5**, **5.6**, **7**

The `beanstalkd` up to the latest version 1.10 is supported.
All commands and responses specified in the [protocol documentation][2] for
`beanstalkd` 1.10 are implemented.

## Why Beanstalk?

Illya has an excellent blog post [Scalable Work Queues with Beanstalk](http://www.igvita.com/2010/05/20/scalable-work-queues-with-beanstalk/)
and Adam Wiggins posted [an excellent comparison](http://adam.heroku.com/past/2010/4/24/beanstalk_a_simple_and_fast_queueing_backend/).

You will find that `beanstalkd` is an underrated but incredibly powerful project
that is extremely well-suited as a job or messaging queue. Significantly better
suited for this task than Redis or a traditional RDBMS. Beanstalk is a simple
and fast work queue service rolled into a single binary - it is the `memcached`
of work queues. Originally built to power the backend for the 'Causes' Facebook app,
it is a mature and production ready open source project.
[PostRank](http://www.postrank.com/) has used beanstalk to reliably process millions
of jobs a day.

A single instance of Beanstalk is perfectly capable of handling thousands of jobs
a second (or more, depending on your job size) because it is an in-memory,
event-driven system. Powered by `libevent` under the hood, it requires zero setup
(launch and forget, like `memcached`), optional log based persistence, an easily
parsed [ASCII protocol](https://github.com/kr/beanstalkd/blob/master/doc/protocol.en-US.md),
and a rich set of tools for job management that go well beyond a simple **FIFO**
work queue.

Beanstalkd supports the following features out of the box:

| Feature | Description                     |
| ------- | ------------------------------- |
| **Easy Setup**       | Quick to install, no files to edit, no settings to tweak. |
| **Speed**            | Process thousands of jobs per second without breaking a sweat. |
| **Client Support**   | Client libraries exist for over 21 languages including PHP, Python, Ruby, and Go. |
| **Tubes**            | Supports multiple work queues created automatically on demand. |
| **Reliable**         | Beanstalk’s reserve, work, delete cycle ensures reliable processing. |
| **Scheduling**       | Delay enqueuing jobs by a specified interval to be processed later. |
| **Priorities**       | Important jobs go to the head of the queue and get processed sooner. |
| **Persistence**      | Jobs are stored in memory for speed, but logged to disk for safe keeping. |
| **Scalability**      | Client-side federation provides effortless horizontal scalability. |
| **Error Handling**   | Bury any job which causes an error for later debugging and inspection. |
| **Simple Debugging** | Talk directly to the `beanstalkd` server over telnet to get a handle on your app. |
| **Efficiency**       | Each `beanstalkd` process can handle tens of thousands of open connections. |
| **Memory Usage**     | Use the built-in `ulimit` OS feature to cap `beanstalkd`'s memory consumption. |

Keep in mind that these features are supported out of the box with `beanstalkd`
and requires no special php specific logic.
In the end, **beanstalkd is the ideal job queue** and has the added benefit of
being easy to setup and configure.

## Contributing

See [CONTRIBUTING.md](docs/CONTRIBUTING.md).

## License

Beanspeak is open source software licensed under the [New BSD License](docs/LICENSE.md).
© Phalcon Framework Team and contributors

[0]: https://travis-ci.org/phalcongelist/beanspeak
[1]: http://kr.github.io/beanstalkd/
[2]: https://github.com/kr/beanstalkd/blob/v1.10/doc/protocol.txt
