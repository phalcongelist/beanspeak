# Beanspeak [![Build Status](https://travis-ci.org/phalcongelist/beanspeak.svg?branch=master)][0]

Beanspeak is the best way to interact with [beanstalkd workqueue][1] in PHP.
Beanspeak is designed as a C-extension for PHP and aims to be the most complete,
stable and fastest solution for PHP world. It's simple, lightweight, and completely
specialized for job queueing.

**Work in progress. Do not use at production**

Supported PHP versions: **5.5**, **5.6**, **7**

The `beanstalkd` up to the latest version 1.10 is supported.
All commands and responses specified in the [protocol documentation][2] for
`beanstalkd` 1.10 are implemented.

## Contributing

See [CONTRIBUTING.md](docs/CONTRIBUTING.md).

## License

Beanspeak is open source software licensed under the [New BSD License](docs/LICENSE.md).
© Phalcon Framework Team and contributors

[0]: https://travis-ci.org/phalcongelist/beanspeak
[1]: http://kr.github.io/beanstalkd/
[2]: https://github.com/kr/beanstalkd/blob/v1.10/doc/protocol.md
