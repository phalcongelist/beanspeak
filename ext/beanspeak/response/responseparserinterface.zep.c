
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


/**
 * Beanspeak\Response\ResponseParserInterface
 */
ZEPHIR_INIT_CLASS(Beanspeak_Response_ResponseParserInterface) {

	ZEPHIR_REGISTER_INTERFACE(Beanspeak\\Response, ResponseParserInterface, beanspeak, response_responseparserinterface, beanspeak_response_responseparserinterface_method_entry);

	return SUCCESS;

}

/**
 * Parses raw response data into a Response object.
 */
ZEPHIR_DOC_METHOD(Beanspeak_Response_ResponseParserInterface, parseResponse);

