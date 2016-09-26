#!/usr/bin/env bash
#
#  Beanspeak
#
#  Copyright (c) 2016 Phalcon Team (https://www.phalconphp.com)
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

${docker_bin} run -d \
    --restart=always \
    --expose=11300 \
    --net=beanstalk_nw \
    --name beanstalk_srv \
    --publish="11300:11300" \
    phalconphp/beanstalkd:1.10 sh -c "beanstalkd -l 0.0.0.0 -p 11300"
