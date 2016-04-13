<?php

namespace Beanspeak\Test\Unit\Helper;

use Beanspeak\Client;
use Codeception\TestCase\Test;
use Beanspeak\Test\Module\UnitTest;

/**
 * \Beanspeak\Test\Unit\Helper\Base.php
 * Base class for Beanspeak component
 *
 * @copyright (c) 2016 Phalcon Team
 * @link      http://www.phalconphp.com
 * @author    Serghei Iakovlev <serghei@phalconphp.com>
 * @package   Beanspeak\Test\Unit\Helper
 *
 * The contents of this file are subject to the New BSD License that is
 * bundled with this package in the file LICENSE.txt
 *
 * If you did not receive a copy of the license and are unable to obtain it
 * through the world-wide-web, please send an email to license@phalconphp.com
 * so that we can send you a copy immediately.
 */
class Base extends Test
{
    /**
     * @var Client
     */
    protected $client = null;

    /**
     * UnitTester Object
     * @var UnitTester
     */
    protected $tester;

    /**
     * Executed before each test
     */
    protected function _before()
    {
        if (!defined('TEST_BT_HOST') || !defined('TEST_BT_PORT')) {
            $this->markTestSkipped('TEST_BT_HOST and/or TEST_BT_PORT env variables are not defined.');
        }

        $this->client = new Client([
            'host'       => TEST_BT_HOST,
            'port'       => TEST_BT_PORT,
            'timeout'    => 5,
            'persistent' => true,
            'wretries'   => 2,
        ]);

        try {
            $this->client->connect();
        } catch (\Exception $e) {
            $this->markTestSkipped($e->getMessage());
        }
    }

    /**
     * Executed after each test
     */
    protected function _after()
    {
    }

    /**
     * Returns current UnitTester instance
     * @return UnitTester
     */
    public function getTester()
    {
        return $this->tester;
    }
}
