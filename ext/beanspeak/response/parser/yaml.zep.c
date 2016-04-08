
#ifdef HAVE_CONFIG_H
#include "../../../ext_config.h"
#endif

#include <php.h>
#include "../../../php_ext.h"
#include "../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/operators.h"
#include "kernel/exception.h"
#include "kernel/string.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/concat.h"
#include "kernel/object.h"
#include "kernel/array.h"
#include "kernel/hash.h"


/**
 * Beanspeak\Response\Parser\Yaml
 */
ZEPHIR_INIT_CLASS(Beanspeak_Response_Parser_Yaml) {

	ZEPHIR_REGISTER_CLASS(Beanspeak\\Response\\Parser, Yaml, beanspeak, response_parser_yaml, beanspeak_response_parser_yaml_method_entry, 0);

	zend_class_implements(beanspeak_response_parser_yaml_ce TSRMLS_CC, 1, beanspeak_response_parser_parserinterface_ce);
	return SUCCESS;

}

/**
 * Fetch a YAML payload from the Beanstalkd server
 * @throws \Beanspeak\Response\Parser\Exception
 */
PHP_METHOD(Beanspeak_Response_Parser_Yaml, parseResponse) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *line_param = NULL, *data_param = NULL, *response = NULL, *_2, *_0$$4;
	zval *line = NULL, *data = NULL, *_1$$4;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &line_param, &data_param);

	zephir_get_strval(line, line_param);
	if (!data_param) {
		ZEPHIR_INIT_VAR(data);
		ZVAL_EMPTY_STRING(data);
	} else {
		zephir_get_strval(data, data_param);
	}


	if (ZEPHIR_IS_STRING(line, "NOT_FOUND")) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(beanspeak_response_parser_exception_ce, "Server reported: NOT_FOUND", "beanspeak/response/parser/yaml.zep", 38);
		return;
	}
	if (!(zephir_start_with_str(line, SL("OK ")))) {
		ZEPHIR_INIT_VAR(_0$$4);
		object_init_ex(_0$$4, beanspeak_response_parser_exception_ce);
		ZEPHIR_INIT_VAR(_1$$4);
		ZEPHIR_CONCAT_SV(_1$$4, "Unhandled response: ", line);
		ZEPHIR_CALL_METHOD(NULL, _0$$4, "__construct", NULL, 1, _1$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(_0$$4, "beanspeak/response/parser/yaml.zep", 42 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_INTERNAL_METHOD_P1(&response, this_ptr, zep_Beanspeak_Response_Parser_Yaml_yamlParse, data);
	zephir_check_call_status();
	object_init_ex(return_value, beanspeak_response_arrayresponse_ce);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_STRING(_2, "OK", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 2, _2, response);
	zephir_check_temp_parameter(_2);
	zephir_check_call_status();
	RETURN_MM();

}

void zep_Beanspeak_Response_Parser_Yaml_yamlParse(int ht, zval *return_value, zval **return_value_ptr, zval *this_ptr, int return_value_used, zval *data_param_ext TSRMLS_DC) {

	HashTable *_12;
	HashPosition _11;
	zend_bool _0, _4, _6;
	zephir_fcall_cache_entry *_10 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *data_param = NULL, *lines = NULL, *values = NULL, *value = NULL, *response = NULL, *_1, *_2, _3, *_5, **_13, *_7$$6 = NULL, *_8$$6, _9$$6, *_14$$8 = NULL, _15$$8 = zval_used_for_init, *_16$$9 = NULL, *_17$$9, *_18$$9 = NULL, *_19$$9, _20$$9 = zval_used_for_init;
	zval *data = NULL;

	ZEPHIR_MM_GROW();
	data_param = data_param_ext;


	if (!data_param) {
		ZEPHIR_INIT_VAR(data);
		ZVAL_EMPTY_STRING(data);
	} else {
		zephir_get_strval(data, data_param);
	}


	ZEPHIR_INIT_VAR(response);
	array_init(response);
	_0 = 1 != 1;
	if (!(_0)) {
		_0 = ZEPHIR_IS_EMPTY(data);
	}
	if (_0) {
		array_init(return_value);
		RETURN_MM();
	}
	if ((zephir_function_exists_ex(SS("yaml_parse") TSRMLS_CC) == SUCCESS)) {
		ZEPHIR_CALL_FUNCTION(&response, "yaml_parse", NULL, 33, data);
		zephir_check_call_status();
		RETURN_CCTOR(response);
	}
	ZEPHIR_INIT_VAR(_1);
	zephir_fast_trim(_1, data, NULL , ZEPHIR_TRIM_RIGHT TSRMLS_CC);
	zephir_get_strval(data, _1);
	ZEPHIR_INIT_VAR(_2);
	zephir_fast_trim(_2, data, NULL , ZEPHIR_TRIM_RIGHT TSRMLS_CC);
	ZEPHIR_SINIT_VAR(_3);
	ZVAL_STRING(&_3, "#[\r\n]+#", 0);
	ZEPHIR_CALL_FUNCTION(&lines, "preg_split", NULL, 34, &_3, _2);
	zephir_check_call_status();
	_4 = zephir_array_isset_long(lines, 0);
	if (_4) {
		zephir_array_fetch_long(&_5, lines, 0, PH_NOISY | PH_READONLY, "beanspeak/response/parser/yaml.zep", 67 TSRMLS_CC);
		_4 = ZEPHIR_IS_STRING(_5, "---");
	}
	if (_4) {
		ZEPHIR_MAKE_REF(lines);
		ZEPHIR_CALL_FUNCTION(NULL, "array_shift", NULL, 35, lines);
		ZEPHIR_UNREF(lines);
		zephir_check_call_status();
	}
	_6 = Z_TYPE_P(lines) != IS_ARRAY;
	if (!(_6)) {
		_6 = ZEPHIR_IS_EMPTY(lines);
	}
	if (_6) {
		ZEPHIR_CALL_FUNCTION(&_7$$6, "print_r", NULL, 36, lines, ZEPHIR_GLOBAL(global_true));
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_8$$6);
		ZEPHIR_CONCAT_SV(_8$$6, "YAML parse error. Raw data: ", _7$$6);
		ZEPHIR_SINIT_VAR(_9$$6);
		ZVAL_LONG(&_9$$6, 512);
		ZEPHIR_CALL_FUNCTION(NULL, "trigger_error", &_10, 37, _8$$6, &_9$$6);
		zephir_check_call_status();
		array_init(return_value);
		RETURN_MM();
	}
	zephir_is_iterable(lines, &_12, &_11, 0, 0, "beanspeak/response/parser/yaml.zep", 86);
	for (
	  ; zephir_hash_get_current_data_ex(_12, (void**) &_13, &_11) == SUCCESS
	  ; zephir_hash_move_forward_ex(_12, &_11)
	) {
		ZEPHIR_GET_HVALUE(values, _13);
		ZEPHIR_INIT_NVAR(value);
		zephir_fast_explode_str(value, SL(":"), values, LONG_MAX TSRMLS_CC);
		if (!(zephir_array_isset_long(value, 1))) {
			ZEPHIR_INIT_LNVAR(_14$$8);
			ZEPHIR_CONCAT_SV(_14$$8, "YAML parse error for line: ", values);
			ZEPHIR_SINIT_NVAR(_15$$8);
			ZVAL_LONG(&_15$$8, 512);
			ZEPHIR_CALL_FUNCTION(NULL, "trigger_error", &_10, 37, _14$$8, &_15$$8);
			zephir_check_call_status();
		} else {
			ZEPHIR_INIT_NVAR(_16$$9);
			zephir_array_fetch_long(&_17$$9, value, 1, PH_NOISY | PH_READONLY, "beanspeak/response/parser/yaml.zep", 82 TSRMLS_CC);
			zephir_fast_trim(_16$$9, _17$$9, NULL , ZEPHIR_TRIM_BOTH TSRMLS_CC);
			ZEPHIR_INIT_NVAR(_18$$9);
			zephir_array_fetch_long(&_19$$9, value, 0, PH_NOISY | PH_READONLY, "beanspeak/response/parser/yaml.zep", 82 TSRMLS_CC);
			ZEPHIR_SINIT_NVAR(_20$$9);
			ZVAL_STRING(&_20$$9, "- ", 0);
			zephir_fast_trim(_18$$9, _19$$9, &_20$$9, ZEPHIR_TRIM_LEFT TSRMLS_CC);
			zephir_array_update_zval(&response, _18$$9, &_16$$9, PH_COPY | PH_SEPARATE);
		}
	}
	RETURN_CCTOR(response);

}

