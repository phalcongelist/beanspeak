<?php

namespace Beanspeak\Test\Unit;

use UnitTester;
use Beanspeak\Client;
use Beanspeak\Exception;

/**
 * \Beanspeak\Test\Unit\ConnectCest
 * Tests the \Beanspeak\Client component
 *
 * @copyright (c) 2016 Phalcon Team
 * @link      http://www.phalconphp.com
 * @author    Serghei Iakovlev <serghei@phalconphp.com>
 * @package   Beanspeak\Test\Unit
 *
 * The contents of this file are subject to the New BSD License that is
 * bundled with this package in the file LICENSE.txt
 *
 * If you did not receive a copy of the license and are unable to obtain it
 * through the world-wide-web, please send an email to license@phalconphp.com
 * so that we can send you a copy immediately.
 */
class ConnectCest
{
    public function testPersistentConnection(UnitTester $I)
    {
        $client = new Client([
            'host' => TEST_BT_HOST,
            'port' => TEST_BT_PORT,
        ]);

        $I->assertFalse($client->isConnected());
        $I->assertFalse($client->disconnect());

        $I->assertTrue(is_resource($client->connect()));
        $I->assertTrue($client->isConnected());

        $client->useTube('test');

        $I->assertTrue($client->disconnect());
        $I->assertFalse($client->isConnected());
    }

    public function testNonPersistentConnection(UnitTester $I)
    {
        $client = new Client([
            'host'       => TEST_BT_HOST,
            'port'       => TEST_BT_PORT,
            'persistent' => false,
        ]);

        $I->assertFalse($client->isConnected());
        $I->assertFalse($client->disconnect());

        $I->assertTrue(is_resource($client->connect()));
        $I->assertTrue($client->isConnected());

        $client->useTube('test');

        $I->assertTrue($client->disconnect());
        $I->assertFalse($client->isConnected());
    }

    public function testConnectionFailsToIncorrectPort(UnitTester $I)
    {
        $client = new Client([
            'host' => TEST_BT_HOST,
            'port' => TEST_BT_PORT + 9,
        ]);

        $I->expectException(new Exception(sprintf(
                "pfsockopen(): unable to connect to %s:%s (Connection refused)", TEST_BT_HOST, TEST_BT_PORT + 9
            )),
            function() use ($client) {
                $client->connect();
            }
        );
    }

    public function testConnectionFailsToIncorrectHost(UnitTester $I)
    {
        $client = new Client([
            'host' => 'TEST_BT_HOST',
            'port' => TEST_BT_PORT,
        ]);

        $I->expectException(new Exception(
                'pfsockopen(): php_network_getaddresses: getaddrinfo failed: Name or service not known'
            ), function() use ($client) {
            $client->connect();
        });
    }
}
