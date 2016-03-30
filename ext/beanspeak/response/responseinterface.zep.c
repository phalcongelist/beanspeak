
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


/**
 * Beanspeak\Response\ResponseInterface
 */
ZEPHIR_INIT_CLASS(Beanspeak_Response_ResponseInterface) {

	ZEPHIR_REGISTER_INTERFACE(Beanspeak\\Response, ResponseInterface, beanspeak, response_responseinterface, beanspeak_response_responseinterface_method_entry);

	return SUCCESS;

}

/**
 * The name of the response.
 */
ZEPHIR_DOC_METHOD(Beanspeak_Response_ResponseInterface, getResponseName);

