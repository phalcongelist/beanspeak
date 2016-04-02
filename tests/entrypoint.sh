#!/usr/bin/env bash

echo "/tmp/core-%e.%p" | tee /proc/sys/kernel/core_pattern
ulimit -c unlimited

exec "$@"
