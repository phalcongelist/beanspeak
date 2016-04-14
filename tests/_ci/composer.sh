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

[ -z "$PHP_VERSION" ] && echo "Need to set PHP_VERSION variable. Fox example: 'export PHP_VERSION=7'" && exit 1;

docker run -it --rm \
  --name=composer-${PHP_VERSION} \
  -v $(pwd):/app \
  -v ${HOME}/.ssh:/root/.ssh \
  -v ${HOME}/.composer:/root/composer \
  phalconphp/composer:${PHP_VERSION} "$@"
