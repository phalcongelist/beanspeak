
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


/**
 * Beanspeak\Connection\ConnectionInterface
 */
ZEPHIR_INIT_CLASS(Beanspeak_Connection_ConnectionInterface) {

	ZEPHIR_REGISTER_INTERFACE(Beanspeak\\Connection, ConnectionInterface, beanspeak, connection_connectioninterface, beanspeak_connection_connectioninterface_method_entry);

	return SUCCESS;

}

/**
 * Makes a connection to the Beanstalk server.
 */
ZEPHIR_DOC_METHOD(Beanspeak_Connection_ConnectionInterface, connect);

/**
 * Closes the connection to the Beanstalk server.
 */
ZEPHIR_DOC_METHOD(Beanspeak_Connection_ConnectionInterface, disconnect);

/**
 * Returns the host for this connection.
 */
ZEPHIR_DOC_METHOD(Beanspeak_Connection_ConnectionInterface, getHost);

/**
 * Returns the port for this connection.
 */
ZEPHIR_DOC_METHOD(Beanspeak_Connection_ConnectionInterface, getPort);

/**
 * Returns the connect timeout for this connection.
 */
ZEPHIR_DOC_METHOD(Beanspeak_Connection_ConnectionInterface, getConnectTimeout);

/**
 * Returns the write retries for this connection.
 */
ZEPHIR_DOC_METHOD(Beanspeak_Connection_ConnectionInterface, getWriteRetries);

/**
 * Whether the connection is persistent or not.
 */
ZEPHIR_DOC_METHOD(Beanspeak_Connection_ConnectionInterface, isPersistent);

/**
 * Whether the connection is established or not.
 */
ZEPHIR_DOC_METHOD(Beanspeak_Connection_ConnectionInterface, isConnected);

/**
 * Writes data to the socket. Performs a connection if none is available.
 */
ZEPHIR_DOC_METHOD(Beanspeak_Connection_ConnectionInterface, write);

