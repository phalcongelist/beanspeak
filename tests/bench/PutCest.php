<?php

namespace Beanspeak\Test\Bench;

use UnitTester;
use Beanspeak\Client;
use Codeception\Lib\Console\Output;
use PHPUnit_Framework_SkippedTestError as SkipException;

/**
 * \Beanspeak\Test\Bench\PutCest
 * Benchmark for the \Beanspeak\Client::put command
 *
 * @copyright (c) 2016 Phalcon Team
 * @link      http://www.phalconphp.com
 * @author    Serghei Iakovlev <serghei@phalconphp.com>
 * @package   Beanspeak\Test\Bench
 *
 * The contents of this file are subject to the New BSD License that is
 * bundled with this package in the file LICENSE.txt
 *
 * If you did not receive a copy of the license and are unable to obtain it
 * through the world-wide-web, please send an email to license@phalconphp.com
 * so that we can send you a copy immediately.
 */
class PutCest
{
    /**
     * @var \Codeception\Lib\Console\Output
     */
    protected $output;

    public function _before(UnitTester $I)
    {
        if (!defined('TEST_BT_HOST') || !defined('TEST_BT_PORT')) {
            throw new SkipException(
                'TEST_BT_HOST and/or TEST_BT_PORT env variables are not defined.'
            );
        }

        $this->output = new Output(['interactive' => false]);
    }

    public function put(UnitTester $I)
    {
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

        $this->output->notification(sprintf(
            " Put items: 100000 | Put size: %db | Total time: % 2.5fs. | Mem: % 5.2fm (peak % 5.2fm)",
            PHP_INT_SIZE * 100000,
            number_format($endTime - $startTime, 5),
            round(memory_get_usage() / (1024 * 1024), 2),
            round(memory_get_peak_usage() / (1024 * 1024), 2)
        ));
    }
}
