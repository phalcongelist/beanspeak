
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


/**
 * Beanspeak\ResponseInterface
 */
ZEPHIR_INIT_CLASS(Beanspeak_ResponseInterface) {

	ZEPHIR_REGISTER_INTERFACE(Beanspeak, ResponseInterface, beanspeak, responseinterface, beanspeak_responseinterface_method_entry);

	return SUCCESS;

}

/**
 * The name of the response.
 */
ZEPHIR_DOC_METHOD(Beanspeak_ResponseInterface, getResponseName);

