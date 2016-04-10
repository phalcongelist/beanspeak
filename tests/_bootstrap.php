<?php

error_reporting(-1);
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);

setlocale(LC_ALL, 'en_US.utf-8');
date_default_timezone_set('UTC');

if (function_exists('mb_internal_encoding')) {
    mb_internal_encoding('utf-8');
}

if (function_exists('mb_substitute_character')) {
    mb_substitute_character('none');
}

clearstatcache();

$root = realpath(dirname(__FILE__)) . DIRECTORY_SEPARATOR;

defined('TESTS_PATH')   || define('TESTS_PATH', $root);
defined('PROJECT_PATH') || define('PROJECT_PATH', dirname(TESTS_PATH) . DIRECTORY_SEPARATOR);
defined('PATH_DATA')    || define('PATH_DATA', $root .  '_data' . DIRECTORY_SEPARATOR);
defined('PATH_OUTPUT')  || define('PATH_OUTPUT', $root .  '_output' . DIRECTORY_SEPARATOR);

unset($root);

if (!file_exists(PROJECT_PATH . 'vendor/autoload.php')) {
    throw new RuntimeException(
        'Unable to locate autoloader. ' .
        'Install dependencies from the project root directory to run test suite: `composer install`.'
    );
}

include_once PROJECT_PATH . 'vendor/autoload.php';
