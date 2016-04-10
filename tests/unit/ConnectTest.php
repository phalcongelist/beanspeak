<?php

namespace Beanspeak\Test\Unit;

use Beanspeak\Test\Unit\Helper\Base;

/**
 * \Beanspeak\Test\Unit\ConnectTest
 * Tests the \Beanspeak\Client component
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
class ConnectTest extends Base
{
    public function testConnect()
    {
        $this->client->disconnect();

        $this->assertFalse($this->client->isConnected());
        $this->assertFalse($this->client->disconnect());

        $this->assertTrue(is_resource($this->client->connect()));
        $this->assertTrue($this->client->isConnected());

        $this->assertTrue($this->client->disconnect());
        $this->assertFalse($this->client->isConnected());
    }
}
