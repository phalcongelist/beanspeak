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

docker_bin="$(which docker.io 2> /dev/null || which docker 2> /dev/null)"

[ -z "$PHP_VERSION" ] && echo "Need to set PHP_VERSION variable. Fox example: 'export PHP_VERSION=7'" && exit 1;
[ -z "$TEST_BT_HOST" ] && TEST_BT_HOST="beanstalk_srv"
[ -z "$TRAVIS_BUILD_DIR" ] && TRAVIS_BUILD_DIR=$(cd $(dirname "$1") && pwd -P)/$(basename "$1")

chmod +x ${TRAVIS_BUILD_DIR}/tests/_ci/entrypoint.sh

#  3) Run tests
${docker_bin} run -it --rm \
  --entrypoint /entrypoint.sh \
  --privileged=true \
  --net=beanstalk_nw \
  -e TEST_BT_HOST="${TEST_BT_HOST}" \
  -e PHP_VERSION="${PHP_VERSION}" \
  --name test-beanspeak-${PHP_VERSION} \
  -v ${TRAVIS_BUILD_DIR}/tests/_ci/backtrace.sh:/backtrace.sh \
  -v ${TRAVIS_BUILD_DIR}/tests/_ci/entrypoint.sh:/entrypoint.sh \
  -v ${TRAVIS_BUILD_DIR}/vendor:/app/vendor \
  -v ${TRAVIS_BUILD_DIR}/codeception.yml:/app/codeception.yml \
  -v ${TRAVIS_BUILD_DIR}/tests:/app/tests \
  -v ${TRAVIS_BUILD_DIR}/ext/modules/beanspeak.so:/ext/beanspeak.so \
  phalconphp/php:${PHP_VERSION} bash