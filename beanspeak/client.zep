/*
 +------------------------------------------------------------------------+
 | Beanspeak                                                              |
 +------------------------------------------------------------------------+
 | Copyright (c) 2016 Phalcon Team (http://www.phalconphp.com)            |
 +------------------------------------------------------------------------+
 | This source file is subject to the New BSD License that is bundled     |
 | with this package in the file LICENSE.txt.                             |
 |                                                                        |
 | If you did not receive a copy of the license and are unable to         |
 | obtain it through the world-wide-web, please send an email             |
 | to license@phalconphp.com so we can send you a copy immediately.       |
 +------------------------------------------------------------------------+
 | Authors: Serghei Iakovlev <serghei@phalconphp.com>                     |
 +------------------------------------------------------------------------+
*/

namespace Beanspeak;

/**
 * Beanspeak\Client
 *
 * Class to access the beanstalk queue service.
 *
 * Implements the beanstalk protocol spec 1.10.
 *
 * <code>
 * use Beanspeak\Client;
 *
 * // Each connection parameter is optional
 * $queue = new Client([
 *     'host'       => '127.0.0.1', // The beanstalk server hostname or IP address to connect to
 *     'port'       => 11300,       // The port of the server to connect to
 *     'timeout'    => 60,          // Timeout in seconds when establishing the connection
 *     'persistent' => true,        // Whether to make the connection persistent or not
 *     'wretries'   => 8,           // Write retries
 * ]);
 * </code>
 *
 * @link https://github.com/kr/beanstalkd/
 */
class Client
{
    /**
     * The current socket connection.
     * @var resource
     */
    protected socket;

    /**
     * The current connection options.
     * @var array
     */
    protected options = [];

    /**
     * The current used tube.
     * @var string
     */
    protected usedTube = "default" { get } ;

    /**
     * The current watched tubes.
     * @var array
     */
    protected watchedTubes = [ "default" : true ] { get } ;

    /**
     * Beanspeak\Client constructor
     */
    public function __construct(array options = null)
    {
        array defaults = [
            "host"       : "127.0.0.1",
            "port"       : "11300",
            "persistent" : true,
            "timeout"    : "60",
            "wretries"   : 8
        ];

        if typeof options != "array" {
            let this->options = defaults;
        } else {
            let this->options = options + defaults;
        }
    }

    /**
     * Makes a connection to the Beanstalk server.
     *
     * The resulting stream will not have any timeout set on it.
     * Which means it can wait an unlimited amount of time until a packet
     * becomes available.
     *
     * @throws Exception
     */
    public function connect() -> resource
    {
        var e, options, socket, usedTube;

        if this->isConnected() {
            this->disconnect();
        }

        let options = this->options;

        try {
            if options["persistent"] {
                let socket = pfsockopen(options["host"], options["port"], null, null, options["timeout"]);
            } else {
                let socket = fsockopen(options["host"], options["port"], null, null, options["timeout"]);
            }

            if typeof socket != "resource" {
                throw new Exception("Can't connect to Beanstalk server.");
            }
        } catch  \Exception, e {
            throw new Exception(e->getMessage());
        }


        stream_set_timeout(socket, -1, null);

        let this->socket = socket,
            usedTube     = this->usedTube;

        if usedTube != "default" {
            this->useTube(usedTube);
        }

        return socket;
    }

    /**
     * Destructor, disconnects from the server.
     */
    public function __destruct()
    {
        this->disconnect();
    }

    /**
     * Closes the connection to the Beanstalk server.
     *
     * Will throw an exception if closing the connection fails, to allow
     * handling the then undefined state.
     *
     * @throws Exception
     */
    public function disconnect() -> boolean
    {
        var socket, status;

        if !this->isConnected() {
            return false;
        }

        let socket = this->socket,
            status = fclose(socket);

        if !status {
            throw new Exception("Failed to close connection.");
        }

        let this->socket = null;

        return true;
    }

    /**
     * Whether the connection is established or not.
     */
    public function isConnected() -> boolean
    {
        return typeof this->socket == "resource";
    }

    /**
     * Inserts a job into the client's currently used tube.
     *
     * <code>
     * $task = [
     *     'recipient' => 'user@mail.com',
     *     'subject'   => 'Welcome',
     *     'content'   => $content,
     * ];
     *
     * $put = $queue->pit($task, 999, 60 * 60, 3600);
     * </code>
     */
    public function put(var data, int priority = 1024, int delay = 0, int ttr = 86400) -> int|boolean
    {
        var status, response, serialized, length;

        // Data is automatically serialized before be sent to the server
        let serialized = serialize(data),
            length     = strlen(serialized);

        this->write("put " . priority . " " . delay . " " . ttr . " " . length . "\r\n" . serialized);

        let response = this->readStatus();

        if isset response[1] {
            let status = response[0];

            if status == "INSERTED" || status == "BURIED" {
                return (int) response[1];
            }
        }

        return false;
    }

    /**
     * Inserts a job into the desired tube.
     *
     * <code>
     * $task = [
     *     'recipient' => 'user@mail.com',
     *     'subject'   => 'Welcome',
     *     'content'   => $content,
     * ];
     *
     * $queue->putInTube('tube-name', $task, 999, 60 * 60, 3600);
     * </code>
     */
    public function putInTube(string! tube, var data, int priority = 1024, int delay = 0, int ttr = 86400) -> boolean|int
    {
        var  response;

        let response = this->useTube(tube);
        if typeof response == "object" {
            return this->put(data, priority, delay, ttr);
        }

        return false;
    }

    /**
     * Change the active tube.
     *
     * The "use" command is for producers. Subsequent put commands will put jobs
     * into the tube specified by this command. If no use command has been issued,
     * jobs will be put into the tube named "default".
     *
     * <code>
     * $queue->useTube('mail-queue');
     * </code>
     *
     * @throws Exception
     */
    public function useTube(string! tube) -> <Client>
    {
        var response, status, used;

        let used = this->usedTube;
        if used == tube {
            return this;
        }

        this->write("use " . tube);

        let response = this->readStatus();

        if isset response[1] && response[0] == "USING" {
            let status = response[0];

            if status == "USING" {
                let this->usedTube = tube;
                return this;
            }
        }

        throw new Exception(
            "Unable to change the active tube. Server response: ". join(" ", response)
        );
    }

    /**
     * Lets the client inspect a job in the system.
     *
     * <code>
     * $peekJob = $queue->peek($jobId);
     * </code>
     */
    public function peekJob(int id) -> boolean|<Job>
    {
        var response;

        this->write("peek " . id);

        let response = this->readStatus();
        if isset response[2] && response[0] == "FOUND" {
            return new Job(this, response[1], unserialize(this->read(response[2])));
        }

        return false;
    }

    /**
     * Return the delayed job with the shortest delay left.
     *
     * <code>
     * $queue->peekDelayed();
     * </code>
     */
    public function peekDelayed() -> boolean|<Job>
    {
        var response;

        this->write("peek-delayed");

        let response = this->readStatus();
        if isset response[2] && response[0] == "FOUND" {
            return new Job(this, response[1], unserialize(this->read(response[2])));
        }

        return false;
    }

    /**
     * Return the next job in the list of buried jobs.
     *
     * <code>
     * $queue->peekBuried();
     * </code>
     */
    public function peekBuried() -> boolean|<Job>
    {
        var response;

        this->write("peek-buried");

        let response = this->readStatus();
        if isset response[2] && response[0] == "FOUND" {
            return new Job(this, response[1], unserialize(this->read(response[2])));
        }

        return false;
    }

    /**
     * Inspect the next ready job.
     *
     * <code>
     * $queue->peekReady();
     * </code>
     */
    public function peekReady() -> boolean|<Job>
    {
        var response;

        this->write("peek-ready");

        let response = this->readStatus();
        if isset response[2] && response[0] == "FOUND" {
            return new Job(this, response[1], unserialize(this->read(response[2])));
        }

        return false;
    }

    /**
     * Moves jobs into the ready queue.
     * The Kick command applies only to the currently used tube.
     *
     * <code>
     * $queue->kick(3);
     * </code>
     */
    public function kick(int bound) -> boolean|int
    {
        var response;

        this->write("kick " . bound);

        let response = this->readStatus();
        if isset response[1] && response[0] == "KICKED" {
            return (int) response[1];
        }

        return false;
    }

    /**
     * Adds the named tube to the watch list for the current connection.
     *
     * <code>
     * $count = $queue->watch($tube);
     * </code>
     */
    public function watch(string! tube) -> boolean|int
    {
        var response;

        this->write("watch " . tube);

        let response = this->readStatus();
        if isset response[1] && response[0] == "WATCHING" {
            return (int) response[1];
        }

        return false;
    }

    /**
     * Removes the named tube from the watch list for the current connection.
     *
     * <code>
     * $count = $queue->ignore('tube-name);
     * </code>
     */
    public function ignore(string! tube) -> <Client>
    {
        var response, watchedTubes;

        let watchedTubes = this->watchedTubes;

        if  isset watchedTubes[tube] {
            this->write("ignore " . tube);

            let response = this->readStatus();
            if response[0] == "NOT_IGNORED" {
                throw new Exception("Cannot ignore last tube in watchlist.");
            }

            if !isset response[1] || response[0] == "WATCHING" {
                throw new Exception("Unhandled response: " . join(" ", response));
            }

            unset(watchedTubes[tube]);
            let this->watchedTubes = watchedTubes;
        }

        return this;
    }

    /**
     * Gives statistical information about the system as a whole.
     *
     * <code>
     * $queue->stats();
     * </code>
     */
    public function stats() -> boolean|array
    {
        var response;

        this->write("stats");

        let response = this->readYaml();
        if response[0] != "OK" {
            return false;
        }

        return response[2];
    }

    /**
     * Gives statistical information about the specified tube if it exists.
     *
     * <code>
     * $stats = $queue->statsTube('process-bitcoin');
     * </code>
     */
    public function statsTube(string! tube) -> boolean|array
    {
        var response;

        this->write("stats-tube " . tube);

        let response = this->readYaml();
        if response[0] != "OK" {
            return false;
        }

        return response[2];
    }

    /**
     * Returns a list of all existing tubes.
     *
     * <code>
     * $tubes = $queue->listTubes();
     * </code>
     */
    public function listTubes() -> boolean|array
    {
        var response;

        this->write("list-tubes");

        let response = this->readYaml();
        if response[0] != "OK" {
            return false;
        }

        return response[2];
    }

    /**
     * Returns the tube currently being used by the client.
     *
     * <code>
     * $tube = $queue->listTubeUsed();
     * </code>
     *
     * @throws Exception
     */
    public function listTubeUsed(boolean ask = false) -> string
    {
        var response;

        if !ask {
            return this->usedTube;
        }

        this->write("list-tube-used");

        let response = this->readStatus();

        if isset response[1] && response[0] == "USING" {
            let this->usedTube = response[1];
            return response[1];
        }

        throw new Exception("Unhandled response form beanstalkd server: " . join(" ", response));
    }

    /**
     * Returns a list tubes currently being watched by the client.
     *
     * <code>
     * $tubes = $queue->listTubesWatched();
     * </code>
     */
    public function listTubesWatched() -> boolean|array
    {
        var response;

        this->write("list-tubes-watched");

        let response = this->readYaml();
        if response[0] != "OK" {
            return false;
        }

        return response[2];
    }

    /**
     * Can delay any new job being reserved for a given time.
     *
     * <code>
     * $queue->pauseTube('process-video', 60 * 60);
     * </code>
     */
    public function pauseTube(string! tube, int delay) -> boolean
    {
        var response;

        this->write("pause-tube " . tube . " " . delay);

        let response = this->readStatus();
        if !isset response[0] || response[0] != "PAUSED" {
            return false;
        }

        return true;
    }

    /**
     * Resume the tube.
     *
     * <code>
     * $queue->resumeTube('process-video');
     * </code>
     */
    public function resumeTube(string! tube) -> boolean
    {
        return this->pauseTube(tube, 0);
    }

    /**
     * Simply closes the connection.
     *
     * <code>
     * $queue->quit();
     * </code>
     */
    public function quit() -> boolean
    {
        this->write("quit");
        this->disconnect();

        return typeof this->socket != "resource";
    }

    /**
     * Writes data to the socket.
     * Performs a connection if none is available.
     * @throws Exception
     */
    public function write(string data) -> int
    {
        var socket, retries, written, step, length;

        if !this->isConnected() {
            this->connect();

            if !this->isConnected() {
                throw new Exception("Unable to establish connection with beanstalkd server.");
            }
        }

        let retries = this->options["wretries"],
            socket  = this->socket,
            data   .= "\r\n",
            step    = 0,
            written = 0;

        let length = strlen(data);

        while written < length {
            let step++;

            if step >= retries && !written {
                throw new Exception("Failed to write data to socket after " . retries . " tries.");
            }

            let written += fwrite(socket, substr(data, written));
        }

        return written;
    }

    /**
     * Reads a packet from the socket.
     * Performs a connection if none is available.
     * @throws Exception
     */
    public function read(int length = 0) -> boolean|string
    {
        var socket, data, meta;

        if !this->isConnected() {
            this->connect();

            if !this->isConnected() {
                return false;
            }
        }

        let socket = this->socket;

        if length {
            if feof(socket) {
                throw new Exception("Failed to read data from socket (EOF).");
            }

            let data = stream_get_line(socket, length + 2),
                meta = stream_get_meta_data(socket);

            if meta["timed_out"] {
                throw new Exception("Connection timed out upon attempt to read data from socket.");
            }

            if false === data {
                throw new Exception("Failed to read data from socket.");
            }

            let data = rtrim(data, "\r\n");
        } else {
            let data = stream_get_line(socket, 16384, "\r\n");
        }

        array errors = [
            "UNKNOWN_COMMAND" : "Unnown command.",
            "JOB_TOO_BIG"     : "Job data exceeds server-enforced limit.",
            "BAD_FORMAT"      : "Bad command format.",
            "OUT_OF_MEMORY"   : "Out of memory."
        ];

        if isset errors[data] {
            throw new Exception(errors[data]);
        }

        return data;
    }

    /**
     * Fetch a YAML payload from the Beanstalkd server.
     */
    final public function readYaml() -> array
    {
        var response, status, data = [], bytes = 0;

        let response = this->readStatus();

        if isset response[0] {
            let status = response[0];
        } else {
            let status = "UNKNOWN";
        }

        if isset response[1] {
            let bytes = response[1],
                data  = this->yamlParse();
        }

        return [
            status,
            bytes,
            data
        ];
    }

    /**
     * Reads the latest status from the Beanstalkd server.
     */
    final public function readStatus() -> array
    {
        var status;
        let status = this->read();
        if false === status {
            return [];
        }

        return explode(" ", status);
    }

    private function yamlParse() -> array
    {
        var data, lines, key, value, values, tmp, response = [];

        let data = this->read();

        if typeof data != "string" || empty(data) {
            return [];
        }

        if function_exists("yaml_parse") {
            let response = yaml_parse(data);

            return response;
        }

        let data  = rtrim(data),
            lines = preg_split("#[\r\n]+#", rtrim(data));

        if isset lines[0] && lines[0] == "---" {
            array_shift(lines);
        }

        if typeof lines != "array" || empty(lines) {
            trigger_error("YAML parse error.", E_USER_WARNING);
            return [];
        }

        for key, value in lines {
            if starts_with(value, "-") {
                let value = ltrim(value, "- ");
            } elseif strpos(value, ":") !== false {
                let values = explode(":", value);

                if !isset values[1] {
                    trigger_error("YAML parse error for line: \"" . value . "\"", E_USER_WARNING);
                } else {
                    let key   = values[0],
                        value = ltrim(values[1], " ");
                }
            }

            if is_numeric(value) {
                let tmp = (int) value;

                if tmp == value {
                    let value = tmp;
                } else {
                    let value = doubleval(value);
                }
            }

            let response[key] = value;
        }

        return response;
    }
}
