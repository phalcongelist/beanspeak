<?php

if (!defined('TEST_BT_HOST') || !defined('TEST_BT_PORT')) {
    throw new RuntimeException(
        'TEST_BT_HOST and/or TEST_BT_PORT env variables are not defined.'
    );
}
