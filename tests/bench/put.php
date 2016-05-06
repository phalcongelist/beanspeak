<?php

use Beanspeak\Client;

defined('TEST_BT_HOST') || define('TEST_BT_HOST', getenv('TEST_BT_HOST') ?: '127.0.0.1');
defined('TEST_BT_PORT') || define('TEST_BT_PORT', getenv('TEST_BT_PORT') ?: 11300);

$client = new Client([
    'host' => TEST_BT_HOST,
    'port' => TEST_BT_PORT,
]);

$client->connect();

$startTime = microtime(true);
for ($i = 0; $i < 100000; $i++) {
    $client->put($i, 1024, 0, 60);
}
$endTime = microtime(true);

printf(
    "Put items: 100000pcs\nPut size: %db\nPut time: %.5fs\nPut memory: %.2fmb (peak %.2fmb)",
    PHP_INT_SIZE * 100000,
    number_format($endTime - $startTime, 5),
    round(memory_get_usage() / (1024 * 1024), 2),
    round(memory_get_peak_usage() / (1024 * 1024), 2)
);
