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

use Beanspeak\Command;
use Beanspeak\Response\ResponseInterface;
use Beanspeak\Response\Parser\ParserInterface;

/**
 * Beanspeak\Command\PauseTube
 *
 * The pause-tube command can delay any new job being reserved for a given time.
 *
 * <code>
 * use Beanspeak\Command\PauseTube;
 *
 * $pause = new PauseTube('process-video', 60 * 60);
 * </code>
 */
class PauseTube extends Command implements ParserInterface
{
    private tube;
    private delay;

    /**
     * Beanspeak\Command\PauseTube constructor
     */
    public function __construct(string! tube, int! delay)
    {
        let this->tube  = tube,
            this->delay = delay;
    }

    /**
     * {@inheritdoc}
     */
    public function getName() -> string
    {
        return "PAUSE-TUBE";
    }

    /**
     * {@inheritdoc}
     */
    public function getCommandLine() -> string
    {
        return "pause-tube " . this->tube . " " . this->delay;
    }

    /**
     * {@inheritdoc}
     * @throws \Beanspeak\Command\Exception
     */
    public function parseResponse(string line, string data = null) -> <ResponseInterface>
    {
        if starts_with(line, "NOT_FOUND") {
            throw new Exception(this->getName() . ": tube " . this->tube . " doesn't exist");
        }

        if starts_with(line, "PAUSED") {
            return this->createResponse("PAUSED", ["delay" : this->delay]);
        }

        throw new Exception("Unhandled response: " . line);
    }
}
