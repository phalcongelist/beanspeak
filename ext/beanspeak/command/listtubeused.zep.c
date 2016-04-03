
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
#include "kernel/array.h"
#include "kernel/operators.h"


/**
 * Beanspeak\Command\ListTubeUsed
 *
 * Returns the tube currently being used by the client.
 *
 * <code>
 * use Beanspeak\Command\ListTubeUsed;
 *
 * $tube = new ListTubeUsed;
 * </code>
 */
ZEPHIR_INIT_CLASS(Beanspeak_Command_ListTubeUsed) {

	ZEPHIR_REGISTER_CLASS_EX(Beanspeak\\Command, ListTubeUsed, beanspeak, command_listtubeused, beanspeak_command_ce, beanspeak_command_listtubeused_method_entry, 0);

	zend_class_implements(beanspeak_command_listtubeused_ce TSRMLS_CC, 1, beanspeak_response_parser_parserinterface_ce);
	return SUCCESS;

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_ListTubeUsed, getName) {

	

	RETURN_STRING("LIST-TUBE-USED", 1);

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_ListTubeUsed, getCommandLine) {

	

	RETURN_STRING("list-tube-used", 1);

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_ListTubeUsed, parseResponse) {

	zval *_0;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *line_param = NULL, *data_param = NULL, *_1 = NULL, *_2, *_3 = NULL;
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
	zephir_create_array(_0, 1, 0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "#^USING (.+)$#", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_STRING(_2, "$1", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_FUNCTION(&_3, "preg_replace", NULL, 14, _1, _2, line);
	zephir_check_temp_parameter(_1);
	zephir_check_temp_parameter(_2);
	zephir_check_call_status();
	zephir_array_update_string(&_0, SL("tube"), &_3, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_STRING(_1, "USING", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "createresponse", NULL, 0, _1, _0);
	zephir_check_temp_parameter(_1);
	zephir_check_call_status();
	RETURN_MM();

}

