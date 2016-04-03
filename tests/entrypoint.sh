#!/usr/bin/env bash

echo -e "\n\tWelcome to the Docker testing container.\n"

mkdir -p /tmp/beanspeak
echo "/tmp/beanspeak/core-%e.%p" | tee /proc/sys/kernel/core_pattern &> /dev/null

echo -e "\tIf a Segmentation Fault is happens use:"
echo -e "\tgdb php /tmp/beanspeak/core-* for debugging.\n"

ulimit -c unlimited

exec "$@"
