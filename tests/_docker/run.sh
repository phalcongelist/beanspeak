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
#
#  HOW TO USE IT:
#
#  1) Create network
#  docker network create --driver bridge beanstalk_nw
#
#  2) Run beanstalkd
#  docker run -d --net=beanstalk_nw --name beanstalk_srv phalconphp/beanstalkd:1.10 sh -c "beanstalkd -l 0.0.0.0 -p 11300"
#

docker_bin="$(which docker 2> /dev/null)"

#  Ability to run tests as:
#  build.sh relative/path/to/the/test.php
#  or
#  build.sh "relative/path/to/the/test.php --debug"
RUN_ARGS="$@"
shift

[ -z "${TRAVIS_PHP_VERSION}" ] && echo "Need to set TRAVIS_PHP_VERSION variable. Fox example: 'export TRAVIS_PHP_VERSION=7.0'" && exit 1;
[ -z "${TEST_BT_HOST}" ] && TEST_BT_HOST="beanstalk_srv"

chmod +x $(pwd)/tests/_docker/entrypoint.sh

#  3) Clean local memory
if [ -z ${TRAVIS} ]; then ${docker_bin} restart ${TEST_BT_HOST}; fi

#  4) Run tests
${docker_bin} run -it --rm \
  --entrypoint /entrypoint.sh \
  --privileged=true \
  --net=beanstalk_nw \
  -e TEST_BT_HOST="${TEST_BT_HOST}" \
  -e TRAVIS_PHP_VERSION="${TRAVIS_PHP_VERSION}" \
  -e RUN_ARGS="${RUN_ARGS}" \
  --name test-beanspeak-${TRAVIS_PHP_VERSION} \
  -v $(pwd)/tests/_ci/backtrace.sh:/backtrace.sh \
  -v $(pwd)/tests/_docker/entrypoint.sh:/entrypoint.sh \
  -v $(pwd)/vendor:/app/vendor \
  -v $(pwd)/codeception.yml:/app/codeception.yml \
  -v $(pwd)/tests:/app/tests \
  -v $(pwd)/ext/modules/beanspeak.so:/ext/beanspeak.so \
  -v $(pwd)/ext:/zephir/ext \
  phalconphp/php:${TRAVIS_PHP_VERSION} bash
