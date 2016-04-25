<?php

namespace Helper;

use Codeception\Module;
use Codeception\TestInterface;

/**
 * \Helper\Bench
 *
 * Here you can define custom actions
 * all public methods declared in helper class will be available in $I
 *
 * @copyright (c) 2016 Phalcon Team
 * @link      http://www.phalconphp.com
 * @author    Serghei Iakovlev <serghei@phalconphp.com>
 * @package   Helper
 *
 * The contents of this file are subject to the New BSD License that is
 * bundled with this package in the file LICENSE.txt
 *
 * If you did not receive a copy of the license and are unable to obtain it
 * through the world-wide-web, please send an email to license@phalconphp.com
 * so that we can send you a copy immediately.
 */
class Bench extends Module
{
    /**
     * @var \Codeception\TestInterface
     */
    protected $test;

    /**
     * Executed before each test.
     *
     * @param \Codeception\TestInterface $test
     */
    public function _before(TestInterface $test)
    {
        $this->test = $test;
    }

    /**
     * Executed after each test.
     *
     * @param \Codeception\TestInterface $test
     */
    public function _after(TestInterface $test)
    {
    }
}
