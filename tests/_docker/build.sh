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

docker_bin="$(which docker 2> /dev/null)"

[ -z "${TRAVIS_PHP_VERSION}" ] && echo "Need to set TRAVIS_PHP_VERSION variable. Fox example: 'export TRAVIS_PHP_VERSION=7.0'" && exit 1;

sed -i '' s/sudo//g $(pwd)/ext/install
chmod +x $(pwd)/ext/install

${docker_bin} run -it --rm \
  --entrypoint /app/ext/install \
  --privileged=true \
  -e TRAVIS_PHP_VERSION="${TRAVIS_PHP_VERSION}" \
  -e DOCKER_BUILD=1 \
  --name build-beanspeak-${TRAVIS_PHP_VERSION} \
  -v $(pwd):/app \
  --workdir /app/ext \
  phalconphp/php:${TRAVIS_PHP_VERSION} bash