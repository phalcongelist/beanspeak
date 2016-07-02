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

# Create .ssh if it non exists
mkdir -p ${HOME}/.ssh
mkdir -p ${HOME}/.composer

docker_bin="$(which docker.io 2> /dev/null || which docker 2> /dev/null)"

[ -z "$TRAVIS_PHP_VERSION" ] && echo "Need to set TRAVIS_PHP_VERSION variable. Fox example: 'export TRAVIS_PHP_VERSION=7.0'" && exit 1;
[ -z "$TRAVIS_BUILD_DIR" ] && TRAVIS_BUILD_DIR=$(pwd)

${docker_bin} run -it --rm \
  --name composer-${TRAVIS_PHP_VERSION} \
  -v $TRAVIS_BUILD_DIR:/app \
  -v ${HOME}/.ssh:/root/.ssh \
  -v ${HOME}/.composer:/root/composer \
  phalconphp/composer:${TRAVIS_PHP_VERSION} "$@"
