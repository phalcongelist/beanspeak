
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


/**
 * Beanspeak\ResponseParserInterface
 */
ZEPHIR_INIT_CLASS(Beanspeak_ResponseParserInterface) {

	ZEPHIR_REGISTER_INTERFACE(Beanspeak, ResponseParserInterface, beanspeak, responseparserinterface, beanspeak_responseparserinterface_method_entry);

	return SUCCESS;

}

/**
 * Parses raw response data into a Response object.
 */
ZEPHIR_DOC_METHOD(Beanspeak_ResponseParserInterface, parseResponse);

