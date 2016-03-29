
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/array.h"
#include "kernel/exception.h"


/**
 * Beanspeak\Response
 */
ZEPHIR_INIT_CLASS(Beanspeak_Response) {

	ZEPHIR_REGISTER_CLASS(Beanspeak, Response, beanspeak, response, beanspeak_response_method_entry, 0);

	zend_declare_property_null(beanspeak_response_ce, SL("connection"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(beanspeak_response_ce, SL("command"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(beanspeak_response_ce, SL("commandName"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(beanspeak_response_ce, SL("content"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(beanspeak_response_ce, SL("data"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(beanspeak_response_ce, SL("statusMessages"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(beanspeak_response_ce, SL("dataResponses"), ZEND_ACC_PROTECTED TSRMLS_CC);

	beanspeak_response_ce->create_object = zephir_init_properties_Beanspeak_Response;
	zend_declare_class_constant_long(beanspeak_response_ce, SL("EXCEPTION_BAD_FORMAT"), 0 TSRMLS_CC);

	zend_declare_class_constant_long(beanspeak_response_ce, SL("EXCEPTION_BURIED"), 1 TSRMLS_CC);

	zend_declare_class_constant_long(beanspeak_response_ce, SL("EXCEPTION_DEADLINE_SOON"), 2 TSRMLS_CC);

	zend_declare_class_constant_long(beanspeak_response_ce, SL("EXCEPTION_DRAINING"), 3 TSRMLS_CC);

	zend_declare_class_constant_long(beanspeak_response_ce, SL("EXCEPTION_EXPECTED_CRLF"), 4 TSRMLS_CC);

	zend_declare_class_constant_long(beanspeak_response_ce, SL("EXCEPTION_INTERNAL_ERROR"), 5 TSRMLS_CC);

	zend_declare_class_constant_long(beanspeak_response_ce, SL("EXCEPTION_JOB_TOO_BIG"), 6 TSRMLS_CC);

	zend_declare_class_constant_long(beanspeak_response_ce, SL("EXCEPTION_NOT_FOUND"), 7 TSRMLS_CC);

	zend_declare_class_constant_long(beanspeak_response_ce, SL("EXCEPTION_NOT_IGNORED"), 8 TSRMLS_CC);

	zend_declare_class_constant_long(beanspeak_response_ce, SL("EXCEPTION_OUT_OF_MEMORY"), 9 TSRMLS_CC);

	zend_declare_class_constant_long(beanspeak_response_ce, SL("EXCEPTION_TIMED_OUT"), 10 TSRMLS_CC);

	zend_declare_class_constant_long(beanspeak_response_ce, SL("EXCEPTION_UNKNOWN_COMMAND"), 11 TSRMLS_CC);

	zend_declare_class_constant_long(beanspeak_response_ce, SL("EXCEPTION_NO_CRLF"), 255 TSRMLS_CC);

	zend_class_implements(beanspeak_response_ce TSRMLS_CC, 1, beanspeak_response_responseinterface_ce);
	return SUCCESS;

}

/**
 * Beanspeak\Response constructor
 *
 * @param string content
 */
PHP_METHOD(Beanspeak_Response, __construct) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *command, *connection, *_0 = NULL, *_1 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &command, &connection);



	zephir_update_property_this(this_ptr, SL("command"), command TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("connection"), connection TSRMLS_CC);
	ZEPHIR_CALL_METHOD(&_0, connection, "getline", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_this(this_ptr, SL("content"), _0 TSRMLS_CC);
	ZEPHIR_CALL_METHOD(&_1, command, "getname", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_this(this_ptr, SL("commandName"), _1 TSRMLS_CC);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "checkstatusmessage", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "parsedata", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Response, getContent) {

	

	RETURN_MEMBER(this_ptr, "content");

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Response, getData) {

	

	RETURN_MEMBER(this_ptr, "data");

}

PHP_METHOD(Beanspeak_Response, parseData) {

	zval *connection = NULL, *dataLength = NULL, *content = NULL, *data = NULL, *message = NULL, *crlf = NULL, *_0, *_1, *_2, *_3, *_5$$4 = NULL, *_6$$4, _7$$4, *_8$$5, _9$$5, *_10$$5 = NULL, *_11$$5;
	zval *dataResponses = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_4 = NULL;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("dataResponses"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(dataResponses, _0);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("content"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(content, _1);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_STRING(_2, "#^(\\S+).*$#s", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_INIT_VAR(_3);
	ZVAL_STRING(_3, "$1", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_FUNCTION(&message, "preg_replace", &_4, 14, _2, _3, content);
	zephir_check_temp_parameter(_2);
	zephir_check_temp_parameter(_3);
	zephir_check_call_status();
	if (ZEPHIR_IS_EMPTY(dataResponses)) {
		ZEPHIR_INIT_NVAR(dataResponses);
		zephir_create_array(dataResponses, 3, 0 TSRMLS_CC);
		zephir_array_update_string(&dataResponses, SL("RESERVED"), &ZEPHIR_GLOBAL(global_true), PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&dataResponses, SL("FOUND"), &ZEPHIR_GLOBAL(global_true), PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&dataResponses, SL("OK"), &ZEPHIR_GLOBAL(global_true), PH_COPY | PH_SEPARATE);
		zephir_update_property_this(this_ptr, SL("dataResponses"), dataResponses TSRMLS_CC);
	}
	ZEPHIR_INIT_VAR(data);
	ZVAL_NULL(data);
	if (zephir_array_isset(dataResponses, message)) {
		ZEPHIR_INIT_VAR(_5$$4);
		ZVAL_STRING(_5$$4, "#^.*\\b(\\d+)$#", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_INIT_VAR(_6$$4);
		ZVAL_STRING(_6$$4, "$1", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_FUNCTION(&dataLength, "preg_replace", &_4, 14, _5$$4, _6$$4, content);
		zephir_check_temp_parameter(_5$$4);
		zephir_check_temp_parameter(_6$$4);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&data, connection, "read", NULL, 0, dataLength);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(_5$$4);
		ZVAL_LONG(_5$$4, 2);
		ZEPHIR_CALL_METHOD(&crlf, connection, "read", NULL, 0, _5$$4);
		zephir_check_call_status();
		ZEPHIR_SINIT_VAR(_7$$4);
		ZVAL_STRING(&_7$$4, "\r\n", 0);
		if (!ZEPHIR_IS_IDENTICAL(&_7$$4, crlf)) {
			ZEPHIR_INIT_VAR(_8$$5);
			object_init_ex(_8$$5, beanspeak_response_exception_ce);
			ZEPHIR_SINIT_VAR(_9$$5);
			ZVAL_STRING(&_9$$5, "Expected 2 bytes of CRLF after %u bytes of data", 0);
			ZEPHIR_CALL_FUNCTION(&_10$$5, "sprintf", NULL, 6, &_9$$5, dataLength);
			zephir_check_call_status();
			ZEPHIR_INIT_VAR(_11$$5);
			ZVAL_LONG(_11$$5, 255);
			ZEPHIR_CALL_METHOD(NULL, _8$$5, "__construct", NULL, 9, _10$$5, _11$$5);
			zephir_check_call_status();
			zephir_throw_exception_debug(_8$$5, "beanspeak/response.zep", 116 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	zephir_update_property_this(this_ptr, SL("data"), data TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Beanspeak_Response, checkStatusMessage) {

	zval *statusMessages = NULL;
	zval *content = NULL, *message = NULL, *_0, *_1, *_2, *_3, *_4$$4, *_5$$4, _6$$4, *_7$$4 = NULL, *_8$$4;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("statusMessages"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(statusMessages, _0);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("content"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(content, _1);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_STRING(_2, "#^(\\S+).*$#s", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_INIT_VAR(_3);
	ZVAL_STRING(_3, "$1", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_FUNCTION(&message, "preg_replace", NULL, 14, _2, _3, content);
	zephir_check_temp_parameter(_2);
	zephir_check_temp_parameter(_3);
	zephir_check_call_status();
	if (ZEPHIR_IS_EMPTY(statusMessages)) {
		ZEPHIR_INIT_NVAR(statusMessages);
		zephir_create_array(statusMessages, 12, 0 TSRMLS_CC);
		add_assoc_long_ex(statusMessages, SS("BAD_FORMAT"), 0);
		add_assoc_long_ex(statusMessages, SS("BURIED"), 1);
		add_assoc_long_ex(statusMessages, SS("DEADLINE_SOON"), 2);
		add_assoc_long_ex(statusMessages, SS("DRAINING"), 3);
		add_assoc_long_ex(statusMessages, SS("EXPECTED_CRLF"), 4);
		add_assoc_long_ex(statusMessages, SS("INTERNAL_ERROR"), 5);
		add_assoc_long_ex(statusMessages, SS("JOB_TOO_BIG"), 6);
		add_assoc_long_ex(statusMessages, SS("NOT_FOUND"), 7);
		add_assoc_long_ex(statusMessages, SS("NOT_IGNORED"), 8);
		add_assoc_long_ex(statusMessages, SS("OUT_OF_MEMORY"), 9);
		add_assoc_long_ex(statusMessages, SS("TIMED_OUT"), 10);
		add_assoc_long_ex(statusMessages, SS("UNKNOWN_COMMAND"), 11);
		zephir_update_property_this(this_ptr, SL("statusMessages"), statusMessages TSRMLS_CC);
	}
	if (zephir_array_isset(statusMessages, message)) {
		ZEPHIR_INIT_VAR(_4$$4);
		object_init_ex(_4$$4, beanspeak_response_exception_ce);
		_5$$4 = zephir_fetch_nproperty_this(this_ptr, SL("commandName"), PH_NOISY_CC);
		ZEPHIR_SINIT_VAR(_6$$4);
		ZVAL_STRING(&_6$$4, "%s in response to '%s'", 0);
		ZEPHIR_CALL_FUNCTION(&_7$$4, "sprintf", NULL, 6, &_6$$4, message, _5$$4);
		zephir_check_call_status();
		zephir_array_fetch(&_8$$4, statusMessages, message, PH_NOISY | PH_READONLY, "beanspeak/response.zep", 155 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(NULL, _4$$4, "__construct", NULL, 9, _7$$4, _8$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(_4$$4, "beanspeak/response.zep", 155 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_MM_RESTORE();

}

static zend_object_value zephir_init_properties_Beanspeak_Response(zend_class_entry *class_type TSRMLS_DC) {

		zval *_0, *_2, *_1$$3, *_3$$4;

		ZEPHIR_MM_GROW();
	
	{
		zval *this_ptr = NULL;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		_0 = zephir_fetch_nproperty_this(this_ptr, SL("dataResponses"), PH_NOISY_CC);
		if (Z_TYPE_P(_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(_1$$3);
			array_init(_1$$3);
			zephir_update_property_this(this_ptr, SL("dataResponses"), _1$$3 TSRMLS_CC);
		}
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("statusMessages"), PH_NOISY_CC);
		if (Z_TYPE_P(_2) == IS_NULL) {
			ZEPHIR_INIT_VAR(_3$$4);
			array_init(_3$$4);
			zephir_update_property_this(this_ptr, SL("statusMessages"), _3$$4 TSRMLS_CC);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJVAL_P(this_ptr);
	}

}

