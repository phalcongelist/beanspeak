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

GREEN="\033[0;32m"
NC="\033[0m"

echo -e "\n\tWelcome to the Docker testing container.\n"

mkdir -p /tmp/beanspeak
echo "/tmp/beanspeak/core-%e.%p" | tee /proc/sys/kernel/core_pattern &> /dev/null

echo -e "\tIf a Segmentation Fault is happens use:"
echo -e "\t${GREEN}gdb php /tmp/beanspeak/core-*${NC}"
echo -e "\tfor debugging.\n"

ulimit -c unlimited

export PHP_EXTENSION_DIR=`/usr/local/phpenv/versions/$(phpenv global)/bin/php-config --extension-dir`

echo -e "\tPHP extension path:"
echo -e "\t${GREEN}${PHP_EXTENSION_DIR}${NC}\n"

ln -s /ext/beanspeak.so ${PHP_EXTENSION_DIR}/beanspeak.so
ln -s /ext/beanspeak.ini /usr/local/phpenv/versions/$(phpenv global)/etc/conf.d/50-beanspeak.ini

php --ri beanspeak

# exec "$@"
exit 0;
