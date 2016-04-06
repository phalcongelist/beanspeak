# -*- coding: utf-8 -*-
#
# Beanspeak documentation build configuration file
from recommonmark.parser import CommonMarkParser

source_parsers = {
    '.md': CommonMarkParser,
}

source_suffix = ['.rst', '.md']
