#!/usr/bin/env bash
#
# Dockerized PHP

docker run -it --rm --name=php-$1 -p 8000:8000 -v $(pwd):/www phalconphp/php:$1 "$@"
