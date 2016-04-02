
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
#include "kernel/object.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/memory.h"
#include "kernel/string.h"
#include "kernel/fcall.h"
#include "kernel/concat.h"
#include "kernel/hash.h"
#include "kernel/array.h"


/**
 * Beanspeak\Response\Parser\Yaml
 */
ZEPHIR_INIT_CLASS(Beanspeak_Response_Parser_Yaml) {

	ZEPHIR_REGISTER_CLASS(Beanspeak\\Response\\Parser, Yaml, beanspeak, response_parser_yaml, beanspeak_response_parser_yaml_method_entry, 0);

	zend_declare_property_null(beanspeak_response_parser_yaml_ce, SL("mode"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_class_implements(beanspeak_response_parser_yaml_ce TSRMLS_CC, 1, beanspeak_response_parser_parserinterface_ce);
	return SUCCESS;

}

/**
 * Beanspeak\Response\Parser\Yaml constructor.
 */
PHP_METHOD(Beanspeak_Response_Parser_Yaml, __construct) {

	zend_bool _0;
	zval *mode_param = NULL;
	zval *mode = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &mode_param);

	if (unlikely(Z_TYPE_P(mode_param) != IS_STRING && Z_TYPE_P(mode_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'mode' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (likely(Z_TYPE_P(mode_param) == IS_STRING)) {
		zephir_get_strval(mode, mode_param);
	} else {
		ZEPHIR_INIT_VAR(mode);
		ZVAL_EMPTY_STRING(mode);
	}


	_0 = !ZEPHIR_IS_STRING(mode, "list");
	if (_0) {
		_0 = !ZEPHIR_IS_STRING(mode, "dict");
	}
	if (_0) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(beanspeak_response_parser_exception_ce, "Parser mode must be either list or dict", "beanspeak/response/parser/yaml.zep", 36);
		return;
	}
	zephir_update_property_this(this_ptr, SL("mode"), mode TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Fetch a YAML payload from the Beanstalkd server
 * @throws \Beanspeak\Response\Parser\Exception
 */
PHP_METHOD(Beanspeak_Response_Parser_Yaml, parseResponse) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *line_param = NULL, *data_param = NULL, *response = NULL, *_2, *_3, *_0$$4;
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
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(beanspeak_response_parser_exception_ce, "Server reported: NOT_FOUND", "beanspeak/response/parser/yaml.zep", 51);
		return;
	}
	if (!(zephir_start_with_str(line, SL("OK ")))) {
		ZEPHIR_INIT_VAR(_0$$4);
		object_init_ex(_0$$4, beanspeak_response_parser_exception_ce);
		ZEPHIR_INIT_VAR(_1$$4);
		ZEPHIR_CONCAT_SV(_1$$4, "Unhandled response: ", line);
		ZEPHIR_CALL_METHOD(NULL, _0$$4, "__construct", NULL, 1, _1$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(_0$$4, "beanspeak/response/parser/yaml.zep", 55 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	_2 = zephir_fetch_nproperty_this(this_ptr, SL("mode"), PH_NOISY_CC);
	ZEPHIR_CALL_INTERNAL_METHOD_P2(&response, this_ptr, zep_Beanspeak_Response_Parser_Yaml_yamlParse, _2, data);
	zephir_check_call_status();
	object_init_ex(return_value, beanspeak_response_arrayresponse_ce);
	ZEPHIR_INIT_VAR(_3);
	ZVAL_STRING(_3, "OK", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 2, _3, response);
	zephir_check_temp_parameter(_3);
	zephir_check_call_status();
	RETURN_MM();

}

void zep_Beanspeak_Response_Parser_Yaml_yamlParse(int ht, zval *return_value, zval **return_value_ptr, zval *this_ptr, int return_value_used, zval *mode_param_ext, zval *data_param_ext TSRMLS_DC) {

	HashTable *_16, *_2$$5;
	HashPosition _15, _1$$5;
	zend_bool _0, _8, _10;
	zephir_fcall_cache_entry *_14 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *mode_param = NULL, *data_param = NULL, *lines = NULL, *values = NULL, *value = NULL, *response = NULL, *_5, *_6, _7, *_9, **_17, *key$$5 = NULL, *value$$5 = NULL, *tmp$$5 = NULL, **_3$$5, *_4$$6 = NULL, *_11$$8 = NULL, *_12$$8, _13$$8, *_18$$11 = NULL, _19$$11 = zval_used_for_init, *_20$$12 = NULL, *_21$$12, *_22$$12 = NULL, *_23$$12, _24$$12 = zval_used_for_init;
	zval *mode = NULL, *data = NULL;

	ZEPHIR_MM_GROW();
	mode_param = mode_param_ext;

	data_param = data_param_ext;


	if (unlikely(Z_TYPE_P(mode_param) != IS_STRING && Z_TYPE_P(mode_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'mode' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (likely(Z_TYPE_P(mode_param) == IS_STRING)) {
		zephir_get_strval(mode, mode_param);
	} else {
		ZEPHIR_INIT_VAR(mode);
		ZVAL_EMPTY_STRING(mode);
	}
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
		ZEPHIR_CALL_FUNCTION(&response, "yaml_parse", NULL, 18, data);
		zephir_check_call_status();
		if (ZEPHIR_IS_STRING(mode, "list")) {
			ZEPHIR_INIT_VAR(tmp$$5);
			array_init(tmp$$5);
			zephir_is_iterable(response, &_2$$5, &_1$$5, 0, 0, "beanspeak/response/parser/yaml.zep", 81);
			for (
			  ; zephir_hash_get_current_data_ex(_2$$5, (void**) &_3$$5, &_1$$5) == SUCCESS
			  ; zephir_hash_move_forward_ex(_2$$5, &_1$$5)
			) {
				ZEPHIR_GET_HMKEY(key$$5, _2$$5, _1$$5);
				ZEPHIR_GET_HVALUE(value$$5, _3$$5);
				ZEPHIR_INIT_LNVAR(_4$$6);
				ZEPHIR_CONCAT_VSV(_4$$6, key$$5, ": ", value$$5);
				zephir_array_append(&tmp$$5, _4$$6, PH_SEPARATE, "beanspeak/response/parser/yaml.zep", 78);
			}
			ZEPHIR_CPY_WRT(response, tmp$$5);
		}
		RETURN_CCTOR(response);
	}
	ZEPHIR_INIT_VAR(_5);
	zephir_fast_trim(_5, data, NULL , ZEPHIR_TRIM_RIGHT TSRMLS_CC);
	zephir_get_strval(data, _5);
	ZEPHIR_INIT_VAR(_6);
	zephir_fast_trim(_6, data, NULL , ZEPHIR_TRIM_RIGHT TSRMLS_CC);
	ZEPHIR_SINIT_VAR(_7);
	ZVAL_STRING(&_7, "#[\r\n]+#", 0);
	ZEPHIR_CALL_FUNCTION(&lines, "preg_split", NULL, 19, &_7, _6);
	zephir_check_call_status();
	_8 = zephir_array_isset_long(lines, 0);
	if (_8) {
		zephir_array_fetch_long(&_9, lines, 0, PH_NOISY | PH_READONLY, "beanspeak/response/parser/yaml.zep", 90 TSRMLS_CC);
		_8 = ZEPHIR_IS_STRING(_9, "---");
	}
	if (_8) {
		ZEPHIR_MAKE_REF(lines);
		ZEPHIR_CALL_FUNCTION(NULL, "array_shift", NULL, 20, lines);
		ZEPHIR_UNREF(lines);
		zephir_check_call_status();
	}
	_10 = Z_TYPE_P(lines) != IS_ARRAY;
	if (!(_10)) {
		_10 = ZEPHIR_IS_EMPTY(lines);
	}
	if (_10) {
		ZEPHIR_CALL_FUNCTION(&_11$$8, "print_r", NULL, 21, lines, ZEPHIR_GLOBAL(global_true));
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_12$$8);
		ZEPHIR_CONCAT_SV(_12$$8, "YAML parse error. Raw data: ", _11$$8);
		ZEPHIR_SINIT_VAR(_13$$8);
		ZVAL_LONG(&_13$$8, 512);
		ZEPHIR_CALL_FUNCTION(NULL, "trigger_error", &_14, 22, _12$$8, &_13$$8);
		zephir_check_call_status();
		array_init(return_value);
		RETURN_MM();
	}
	if (ZEPHIR_IS_STRING(mode, "list")) {
		RETURN_CCTOR(lines);
	}
	zephir_is_iterable(lines, &_16, &_15, 0, 0, "beanspeak/response/parser/yaml.zep", 113);
	for (
	  ; zephir_hash_get_current_data_ex(_16, (void**) &_17, &_15) == SUCCESS
	  ; zephir_hash_move_forward_ex(_16, &_15)
	) {
		ZEPHIR_GET_HVALUE(values, _17);
		ZEPHIR_INIT_NVAR(value);
		zephir_fast_explode_str(value, SL(":"), values, LONG_MAX TSRMLS_CC);
		if (!(zephir_array_isset_long(value, 1))) {
			ZEPHIR_INIT_LNVAR(_18$$11);
			ZEPHIR_CONCAT_SV(_18$$11, "YAML parse error for line: ", values);
			ZEPHIR_SINIT_NVAR(_19$$11);
			ZVAL_LONG(&_19$$11, 512);
			ZEPHIR_CALL_FUNCTION(NULL, "trigger_error", &_14, 22, _18$$11, &_19$$11);
			zephir_check_call_status();
		} else {
			ZEPHIR_INIT_NVAR(_20$$12);
			zephir_array_fetch_long(&_21$$12, value, 1, PH_NOISY | PH_READONLY, "beanspeak/response/parser/yaml.zep", 109 TSRMLS_CC);
			zephir_fast_trim(_20$$12, _21$$12, NULL , ZEPHIR_TRIM_BOTH TSRMLS_CC);
			ZEPHIR_INIT_NVAR(_22$$12);
			zephir_array_fetch_long(&_23$$12, value, 0, PH_NOISY | PH_READONLY, "beanspeak/response/parser/yaml.zep", 109 TSRMLS_CC);
			ZEPHIR_SINIT_NVAR(_24$$12);
			ZVAL_STRING(&_24$$12, "- ", 0);
			zephir_fast_trim(_22$$12, _23$$12, &_24$$12, ZEPHIR_TRIM_LEFT TSRMLS_CC);
			zephir_array_update_zval(&response, _22$$12, &_20$$12, PH_COPY | PH_SEPARATE);
		}
	}
	RETURN_CCTOR(response);

}

