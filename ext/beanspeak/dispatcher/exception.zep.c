
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"


/**
 * Beanspeak\Dispatcher\Exception
 */
ZEPHIR_INIT_CLASS(Beanspeak_Dispatcher_Exception) {

	ZEPHIR_REGISTER_CLASS_EX(Beanspeak\\Dispatcher, Exception, beanspeak, dispatcher_exception, zend_exception_get_default(TSRMLS_C), NULL, 0);

	return SUCCESS;

}

