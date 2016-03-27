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

namespace Beanspeak\Command;

use Beanspeak\Parser\ParserInterface;

/**
 * Beanspeak\Command\CommandInterface
 */
interface CommandInterface
{
    /**
     * The command line, without trailing CRLF.
     */
    public function getCommandLine() -> string;

    /**
     * Whether the command is followed by data.
     */
    public function hasData() -> boolean;

    /**
     *  The binary data to follow the command.
     */
    public function getData() -> string;

    /**
     * The length of the binary data in bytes.
     */
    public function getDataLength() -> int;

    /**
     * The response parser for the command.
     */
    public function getResponseParser() -> <ParserInterface>;
}
