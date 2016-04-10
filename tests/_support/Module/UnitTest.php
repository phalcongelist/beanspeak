<?php

namespace Beanspeak\Test\Module;

use UnitTester;
use Codeception\Specify;
use Codeception\TestCase\Test;

/**
 * \Beanspeak\Test\Module\UnitTest
 * Base class for all Unit tests
 *
 * @copyright (c) 2016 Phalcon Team
 * @link      http://www.phalconphp.com
 * @author    Serghei Iakovlev <serghei@phalconphp.com>
 * @package   Beanspeak\Test\Module
 *
 * The contents of this file are subject to the New BSD License that is
 * bundled with this package in the file LICENSE.txt
 *
 * If you did not receive a copy of the license and are unable to obtain it
 * through the world-wide-web, please send an email to license@phalconphp.com
 * so that we can send you a copy immediately.
 */
class UnitTest extends Test
{
    use Specify;

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
