
#ifdef HAVE_CONFIG_H
#include "../../../ext_config.h"
#endif

#include <php.h>
#include "../../../php_ext.h"
#include "../../../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


/**
 * Beanspeak\Response\Parser\ParserInterface
 *
 * A parser for response data sent from the beanstalkd server.
 */
ZEPHIR_INIT_CLASS(Beanspeak_Response_Parser_ParserInterface) {

	ZEPHIR_REGISTER_INTERFACE(Beanspeak\\Response\\Parser, ParserInterface, beanspeak, response_parser_parserinterface, beanspeak_response_parser_parserinterface_method_entry);

	return SUCCESS;

}

/**
 * Parses raw response data into a Response object.
 */
ZEPHIR_DOC_METHOD(Beanspeak_Response_Parser_ParserInterface, parse);

