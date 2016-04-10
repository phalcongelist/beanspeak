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

docker run -it --rm \
  --entrypoint /entrypoint.sh \
  --privileged=true \
  --net=bridge \
  --name=test-beanspeak \
  -v ${TRAVIS_BUILD_DIR}/tests/_ci/entrypoint.sh:/entrypoint.sh \
  -v ${TRAVIS_BUILD_DIR}/ext/modules/beanspeak.so:/ext/beanspeak.so \
  -v ${TRAVIS_BUILD_DIR}/tests/_ci/beanspeak.ini:/ext/beanspeak.ini \
  phalconphp/php:${PHP_VERSION} bash
