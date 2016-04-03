#!/usr/bin/env bash

GREEN="\033[0;32m"
NC="\033[0m"

echo -e "\n\tWelcome to the Docker testing container.\n"

mkdir -p /tmp/beanspeak
echo "/tmp/beanspeak/core-%e.%p" | tee /proc/sys/kernel/core_pattern &> /dev/null

echo -e "\tIf a Segmentation Fault is happens use:"
echo -e "\t${GREEN}gdb php /tmp/beanspeak/core-*${NC}"
echo -e "\tfor debugging.\n"

ulimit -c unlimited

exec "$@"
