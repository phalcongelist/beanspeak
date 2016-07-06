#!/usr/bin/env bash
#
#  Beanspeak
#
#  Copyright (c) 2016 Phalcon Team (http://www.phalconphp.com)
#
#  This source file is subject to the New BSD License that is bundled
#  with this package in the file LICENSE.txt.
#
#  If you did not receive a copy of the license and are unable to
#  obtain it through the world-wide-web, please send an email
#  to license@phalconphp.com so we can send you a copy immediately.
#
#  Authors: Serghei Iakovlev <serghei@phalconphp.com>

docker_bin="$(which docker.io 2> /dev/null || which docker 2> /dev/null)"

[ -z "$TRAVIS_PHP_VERSION" ] && echo "Need to set TRAVIS_PHP_VERSION variable. Fox example: 'export TRAVIS_PHP_VERSION=7.0'" && exit 1;

${docker_bin} run -it --rm \
    --privileged=true \
    -e ZEND_DONT_UNLOAD_MODULES=1 \
    -v $(pwd):/zephir \
    phalconphp/zephir:${TRAVIS_PHP_VERSION} "$@"

ret=$?

if [ ${ret} -ne 0 ]; then
    errors="$(pwd)/compile-errors.log"
    if [ -e ${errors} ]; then
        cat ${errors}
    fi
fi
