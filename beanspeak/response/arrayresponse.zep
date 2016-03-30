/*
 +------------------------------------------------------------------------+
 | Beanspeak                                                              |
 +------------------------------------------------------------------------+
 | Copyright (c) 2016 Phalcon Team (http://www.phalconphp.com)            |
 +------------------------------------------------------------------------+
 | This source file is subject to the New BSD License that is bundled     |
 | with this package in the file docs/LICENSE.txt.                        |
 |                                                                        |
 | If you did not receive a copy of the license and are unable to         |
 | obtain it through the world-wide-web, please send an email             |
 | to license@phalconphp.com so we can send you a copy immediately.       |
 +------------------------------------------------------------------------+
 | Authors: Serghei Iakovlev <serghei@phalconphp.com>                     |
 +------------------------------------------------------------------------+
*/

namespace Beanspeak\Response;

/**
 * Beanspeak\Response\ArrayResponse
 *
 * A response with an ArrayObject interface to key => value data.
 */
class ArrayResponse extends \ArrayObject implements ResponseInterface
{
    private name;

    /**
     * Beanspeak\Response\ArrayResponse constructor
     */
    public function __construct(string name, array data = [])
    {
        let this->name = name;

        parent::__construct(data);
    }

    /**
     * {@inheritdoc}
     */
    public function getResponseName() -> string
    {
       return this->name; 
    }

    /**
     * Object property access to ArrayObject data.
     */
    public function __get(string name) -> var
    {
        var key;

        let key = this->transformPropertyName(name);

        return this->offsetExists(key) ? this->offsetGet(key) : null;
    }

    /**
     * Object property access to ArrayObject data.
     */
    public function __isset(string name) -> boolean
    {
        var key;

        let key = this->transformPropertyName(name);

        return this->offsetExists(key);
    }

    /**
     * Tranform underscored property name to hyphenated array key.
     */
    private function transformPropertyName(string name) -> string
    {
        return str_replace("_", "-", name);
    }
}