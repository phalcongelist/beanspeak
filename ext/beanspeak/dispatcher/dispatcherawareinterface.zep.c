
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


/**
 * Beanspeak\Dispatcher\DispatcherAwareInterface
 *
 * This interface must be implemented in those classes that uses internally the
 * Beanspeak\Dispatcher that creates them.
 */
ZEPHIR_INIT_CLASS(Beanspeak_Dispatcher_DispatcherAwareInterface) {

	ZEPHIR_REGISTER_INTERFACE(Beanspeak\\Dispatcher, DispatcherAwareInterface, beanspeak, dispatcher_dispatcherawareinterface, beanspeak_dispatcher_dispatcherawareinterface_method_entry);

	return SUCCESS;

}

/**
 * Sets the Dispatcher.
 */
ZEPHIR_DOC_METHOD(Beanspeak_Dispatcher_DispatcherAwareInterface, setDispatcher);

/**
 * Returns the Dispatcher.
 */
ZEPHIR_DOC_METHOD(Beanspeak_Dispatcher_DispatcherAwareInterface, getDispatcher);

