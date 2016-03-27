
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


/**
 * Beanspeak\Connection\ConnectionAwareInterface
 */
ZEPHIR_INIT_CLASS(Beanspeak_Connection_ConnectionAwareInterface) {

	ZEPHIR_REGISTER_INTERFACE(Beanspeak\\Connection, ConnectionAwareInterface, beanspeak, connection_connectionawareinterface, beanspeak_connection_connectionawareinterface_method_entry);

	return SUCCESS;

}

/**
 * Returns the internal connection object.
 */
ZEPHIR_DOC_METHOD(Beanspeak_Connection_ConnectionAwareInterface, getConnection);

/**
 * Sets the connection object.
 */
ZEPHIR_DOC_METHOD(Beanspeak_Connection_ConnectionAwareInterface, setConnection);

