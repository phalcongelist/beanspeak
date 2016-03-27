
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


/**
 * Beanstalk\Connection\ConnectionInterface
 */
ZEPHIR_INIT_CLASS(Beanstalk_Connection_ConnectionInterface) {

	ZEPHIR_REGISTER_INTERFACE(Beanstalk\\Connection, ConnectionInterface, beanstalk, connection_connectioninterface, beanstalk_connection_connectioninterface_method_entry);

	return SUCCESS;

}

/**
 * Makes a connection to the Beanstalkd server
 */
ZEPHIR_DOC_METHOD(Beanstalk_Connection_ConnectionInterface, connect);

