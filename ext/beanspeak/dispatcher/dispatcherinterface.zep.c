
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


/**
 * Beanspeak\Dispatcher\DispatcherInterface
 *
 * Interface for Beanspeak\Dispatcher
 */
ZEPHIR_INIT_CLASS(Beanspeak_Dispatcher_DispatcherInterface) {

	ZEPHIR_REGISTER_INTERFACE(Beanspeak\\Dispatcher, DispatcherInterface, beanspeak, dispatcher_dispatcherinterface, beanspeak_dispatcher_dispatcherinterface_method_entry);

	return SUCCESS;

}

/**
 * Dispatches the specified command to the connection object.
 */
ZEPHIR_DOC_METHOD(Beanspeak_Dispatcher_DispatcherInterface, dispatch);

/**
 * Returns the lastest dispatched command.
 */
ZEPHIR_DOC_METHOD(Beanspeak_Dispatcher_DispatcherInterface, getLastCommand);

