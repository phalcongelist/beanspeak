
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


/**
 * Beanstalk\Connection\ConnectionAwareInterface
 */
ZEPHIR_INIT_CLASS(Beanstalk_Connection_ConnectionAwareInterface) {

	ZEPHIR_REGISTER_INTERFACE(Beanstalk\\Connection, ConnectionAwareInterface, beanstalk, connection_connectionawareinterface, beanstalk_connection_connectionawareinterface_method_entry);

	return SUCCESS;

}

/**
 * Returns the internal connection object.
 */
ZEPHIR_DOC_METHOD(Beanstalk_Connection_ConnectionAwareInterface, getConnection);

/**
 * Sets the connection object.
 */
ZEPHIR_DOC_METHOD(Beanstalk_Connection_ConnectionAwareInterface, setConnection);

