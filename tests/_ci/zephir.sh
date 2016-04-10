#!/usr/bin/env bash
#
# Dockerized Zephir

docker run -it --rm --name=zephir-$1 -v $(pwd):/zephir phalconphp/zephir:$1 "$@"
