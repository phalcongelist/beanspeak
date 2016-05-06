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

PURPLE="\e[0;35m"
GREEN="\033[0;32m"
YELLOW="\e[1;33m"
NC="\033[0m"

echo -e "\nWelcome to the Docker testing container."

mkdir -p /tmp/beanspeak
echo "/tmp/beanspeak/core-%e.%p" | tee /proc/sys/kernel/core_pattern &> /dev/null

ulimit -c unlimited

export PHP_EXTENSION_DIR=`php-config --extension-dir`

echo -e "If a Segmentation Fault is happens use: ${PURPLE}bash /backtrace.sh${NC}"
echo -e "PHP extension path: ${PURPLE}${PHP_EXTENSION_DIR}${NC}\n"

ln -s /ext/beanspeak.so ${PHP_EXTENSION_DIR}/beanspeak.so
[[ "${TRAVIS_PHP_VERSION}" == "7" ]] || ln -s /app/tests/_ci/beanspeak.ini /etc/php5/cli/conf.d/50-beanspeak.ini;
[[ "${TRAVIS_PHP_VERSION}" != "7" ]] || ln -s /app/tests/_ci/beanspeak.ini /etc/php/7.0/cli/conf.d/50-beanspeak.ini;

export BEANSPEAK_VERSION=`php --ri beanspeak | grep "Version =" | awk '{print $3}'`

echo -e "${GREEN}Beanspeak${NC}   version ${YELLOW}${BEANSPEAK_VERSION}${NC}"
/app/vendor/bin/codecept --version

/app/vendor/bin/codecept build &> /dev/null

echo -e ""
/app/vendor/bin/codecept run "${RUN_ARGS}"

result_codecept=$?

if [ ${result_codecept} -ne 0 ]; then
  bash /backtrace.sh
fi

echo -e ""

# Benchmarks
FILES=/app/tests/bench/*.php
i=0

for file in ${FILES}
do
  name=${file##*/}
  echo -e "=== Start ${name%.*} benchmark ===\n"
  chrt -f 99 /usr/bin/time -f "\nTotal time: %E\nContext Switches: %c\nWaits: %w\n" php ${file}
done

result_bench=$?

if [ ${result_codecept} -ne 0 -o ${result_bench} -ne 0 ];
then
   exit 1;
fi

exit 0
