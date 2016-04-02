
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
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "kernel/operators.h"


/**
 * Beanspeak\Command\Quit
 *
 * Simply closes the connection.
 *
 * <code>
 * use Beanspeak\Command\Quit;
 *
 * $quit = new Quit;
 * </code>
 */
ZEPHIR_INIT_CLASS(Beanspeak_Command_Quit) {

	ZEPHIR_REGISTER_CLASS_EX(Beanspeak\\Command, Quit, beanspeak, command_quit, beanspeak_command_ce, beanspeak_command_quit_method_entry, 0);

	zend_class_implements(beanspeak_command_quit_ce TSRMLS_CC, 1, beanspeak_response_parser_parserinterface_ce);
	return SUCCESS;

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_Quit, getName) {

	

	RETURN_STRING("QUIT", 1);

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_Quit, getCommandLine) {

	

	RETURN_STRING("quit", 1);

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_Quit, hasResponse) {

	

	RETURN_BOOL(0);

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_Quit, parseResponse) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *line_param = NULL, *data_param = NULL, *_0;
	zval *line = NULL, *data = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &line_param, &data_param);

	zephir_get_strval(line, line_param);
	if (!data_param) {
		ZEPHIR_INIT_VAR(data);
		ZVAL_EMPTY_STRING(data);
	} else {
		zephir_get_strval(data, data_param);
	}


	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "QUIT", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "createresponse", NULL, 0, _0);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	RETURN_MM();

}

