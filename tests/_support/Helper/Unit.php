<?php

namespace Helper;

use Codeception\Module;
use Codeception\Specify\Config as SpecifyConfig;
use Codeception\TestInterface;

/**
 * Unit Helper
 *
 * Here you can define custom actions
 * all public methods declared in helper class will be available in $I
 *
 * @package Helper
 */
class Unit extends Module
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
        SpecifyConfig::setDeepClone(false);
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
