namespace Beanstalk;

class Beanstalk implements BeanstalkInterface
{
    protected connection;

    public function __construct(<ConnectionInterface> connection = null)
    {
        let connection = connection ?: new Connection;

        let this->connection = connection;
    }
}
