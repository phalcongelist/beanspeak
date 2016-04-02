
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

	HashTable *_4$$5;
	HashPosition _3$$5;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *line_param = NULL, *data_param = NULL, *report = NULL, *key = NULL, *value = NULL, *_2, *_7, *_0$$4, *tmp$$5 = NULL, **_5$$5, *_6$$6 = NULL;
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
	ZEPHIR_CALL_INTERNAL_METHOD_P1(&report, this_ptr, zep_Beanspeak_Response_Parser_Yaml_yamlParse, data);
	zephir_check_call_status();
	_2 = zephir_fetch_nproperty_this(this_ptr, SL("mode"), PH_NOISY_CC);
	if (ZEPHIR_IS_STRING(_2, "list")) {
		ZEPHIR_INIT_VAR(tmp$$5);
		array_init(tmp$$5);
		zephir_is_iterable(report, &_4$$5, &_3$$5, 0, 0, "beanspeak/response/parser/yaml.zep", 67);
		for (
		  ; zephir_hash_get_current_data_ex(_4$$5, (void**) &_5$$5, &_3$$5) == SUCCESS
		  ; zephir_hash_move_forward_ex(_4$$5, &_3$$5)
		) {
			ZEPHIR_GET_HMKEY(key, _4$$5, _3$$5);
			ZEPHIR_GET_HVALUE(value, _5$$5);
			ZEPHIR_INIT_LNVAR(_6$$6);
			ZEPHIR_CONCAT_VSV(_6$$6, key, " ", value);
			zephir_array_append(&tmp$$5, _6$$6, PH_SEPARATE, "beanspeak/response/parser/yaml.zep", 64);
		}
		ZEPHIR_CPY_WRT(report, tmp$$5);
	}
	object_init_ex(return_value, beanspeak_response_arrayresponse_ce);
	ZEPHIR_INIT_VAR(_7);
	ZVAL_STRING(_7, "OK", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 2, _7, report);
	zephir_check_temp_parameter(_7);
	zephir_check_call_status();
	RETURN_MM();

}

void zep_Beanspeak_Response_Parser_Yaml_yamlParse(int ht, zval *return_value, zval **return_value_ptr, zval *this_ptr, int return_value_used, zval *data_param_ext TSRMLS_DC) {

	HashTable *_8;
	HashPosition _7;
	zend_bool _0, _4, _6;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *data_param = NULL, *lines = NULL, *values = NULL, *value = NULL, *respoonse = NULL, *_1, *_2, _3, *_5, **_9, *_10$$7 = NULL, *_11$$7, *_12$$7 = NULL, *_13$$7, _14$$7 = zval_used_for_init;
	zval *data = NULL;

	ZEPHIR_MM_GROW();
	data_param = data_param_ext;


	if (!data_param) {
		ZEPHIR_INIT_VAR(data);
		ZVAL_EMPTY_STRING(data);
	} else {
		zephir_get_strval(data, data_param);
	}


	ZEPHIR_INIT_VAR(respoonse);
	array_init(respoonse);
	_0 = 1 != 1;
	if (!(_0)) {
		_0 = ZEPHIR_IS_EMPTY(data);
	}
	if (_0) {
		array_init(return_value);
		RETURN_MM();
	}
	if ((zephir_function_exists_ex(SS("yaml_parse") TSRMLS_CC) == SUCCESS)) {
		ZEPHIR_RETURN_CALL_FUNCTION("yaml_parse", NULL, 17, data);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(_1);
	zephir_fast_trim(_1, data, NULL , ZEPHIR_TRIM_RIGHT TSRMLS_CC);
	zephir_get_strval(data, _1);
	ZEPHIR_INIT_VAR(_2);
	zephir_fast_trim(_2, data, NULL , ZEPHIR_TRIM_RIGHT TSRMLS_CC);
	ZEPHIR_SINIT_VAR(_3);
	ZVAL_STRING(&_3, "#[\r\n]+#", 0);
	ZEPHIR_CALL_FUNCTION(&lines, "preg_split", NULL, 18, &_3, _2);
	zephir_check_call_status();
	_4 = zephir_array_isset_long(lines, 0);
	if (_4) {
		zephir_array_fetch_long(&_5, lines, 0, PH_NOISY | PH_READONLY, "beanspeak/response/parser/yaml.zep", 88 TSRMLS_CC);
		_4 = ZEPHIR_IS_STRING(_5, "---");
	}
	if (_4) {
		ZEPHIR_MAKE_REF(lines);
		ZEPHIR_CALL_FUNCTION(NULL, "array_shift", NULL, 19, lines);
		ZEPHIR_UNREF(lines);
		zephir_check_call_status();
	}
	_6 = Z_TYPE_P(lines) != IS_ARRAY;
	if (!(_6)) {
		_6 = ZEPHIR_IS_EMPTY(lines);
	}
	if (_6) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_is_iterable(lines, &_8, &_7, 0, 0, "beanspeak/response/parser/yaml.zep", 101);
	for (
	  ; zephir_hash_get_current_data_ex(_8, (void**) &_9, &_7) == SUCCESS
	  ; zephir_hash_move_forward_ex(_8, &_7)
	) {
		ZEPHIR_GET_HVALUE(values, _9);
		ZEPHIR_INIT_NVAR(value);
		zephir_fast_explode_str(value, SL(":"), values, LONG_MAX TSRMLS_CC);
		ZEPHIR_INIT_NVAR(_10$$7);
		zephir_array_fetch_long(&_11$$7, value, 1, PH_NOISY | PH_READONLY, "beanspeak/response/parser/yaml.zep", 98 TSRMLS_CC);
		zephir_fast_trim(_10$$7, _11$$7, NULL , ZEPHIR_TRIM_BOTH TSRMLS_CC);
		ZEPHIR_INIT_NVAR(_12$$7);
		zephir_array_fetch_long(&_13$$7, value, 0, PH_NOISY | PH_READONLY, "beanspeak/response/parser/yaml.zep", 98 TSRMLS_CC);
		ZEPHIR_SINIT_NVAR(_14$$7);
		ZVAL_LONG(&_14$$7, '- ');
		zephir_fast_trim(_12$$7, _13$$7, &_14$$7, ZEPHIR_TRIM_LEFT TSRMLS_CC);
		zephir_array_update_zval(&respoonse, _12$$7, &_10$$7, PH_COPY | PH_SEPARATE);
	}
	RETURN_CCTOR(respoonse);

}

