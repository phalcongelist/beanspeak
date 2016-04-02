
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
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/fcall.h"
#include "kernel/object.h"
#include "kernel/exception.h"
#include "kernel/concat.h"
#include "kernel/array.h"


/**
 * Beanspeak\Dispatcher
 */
ZEPHIR_INIT_CLASS(Beanspeak_Dispatcher) {

	ZEPHIR_REGISTER_CLASS(Beanspeak, Dispatcher, beanspeak, dispatcher, beanspeak_dispatcher_method_entry, 0);

	/**
	 * @var ConnectionInterface
	 */
	zend_declare_property_null(beanspeak_dispatcher_ce, SL("connection"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(beanspeak_dispatcher_ce, SL("lastCommand"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(beanspeak_dispatcher_ce, SL("statusMessages"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(beanspeak_dispatcher_ce, SL("responseData"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(beanspeak_dispatcher_ce, SL("responseLine"), ZEND_ACC_PROTECTED TSRMLS_CC);

	beanspeak_dispatcher_ce->create_object = zephir_init_properties_Beanspeak_Dispatcher;
	zend_declare_class_constant_long(beanspeak_dispatcher_ce, SL("EXCEPTION_BAD_FORMAT"), 0 TSRMLS_CC);

	zend_declare_class_constant_long(beanspeak_dispatcher_ce, SL("EXCEPTION_BURIED"), 1 TSRMLS_CC);

	zend_declare_class_constant_long(beanspeak_dispatcher_ce, SL("EXCEPTION_DEADLINE_SOON"), 2 TSRMLS_CC);

	zend_declare_class_constant_long(beanspeak_dispatcher_ce, SL("EXCEPTION_DRAINING"), 3 TSRMLS_CC);

	zend_declare_class_constant_long(beanspeak_dispatcher_ce, SL("EXCEPTION_EXPECTED_CRLF"), 4 TSRMLS_CC);

	zend_declare_class_constant_long(beanspeak_dispatcher_ce, SL("EXCEPTION_INTERNAL_ERROR"), 5 TSRMLS_CC);

	zend_declare_class_constant_long(beanspeak_dispatcher_ce, SL("EXCEPTION_JOB_TOO_BIG"), 6 TSRMLS_CC);

	zend_declare_class_constant_long(beanspeak_dispatcher_ce, SL("EXCEPTION_NOT_FOUND"), 7 TSRMLS_CC);

	zend_declare_class_constant_long(beanspeak_dispatcher_ce, SL("EXCEPTION_NOT_IGNORED"), 8 TSRMLS_CC);

	zend_declare_class_constant_long(beanspeak_dispatcher_ce, SL("EXCEPTION_OUT_OF_MEMORY"), 9 TSRMLS_CC);

	zend_declare_class_constant_long(beanspeak_dispatcher_ce, SL("EXCEPTION_TIMED_OUT"), 10 TSRMLS_CC);

	zend_declare_class_constant_long(beanspeak_dispatcher_ce, SL("EXCEPTION_UNKNOWN_COMMAND"), 11 TSRMLS_CC);

	zend_declare_class_constant_long(beanspeak_dispatcher_ce, SL("EXCEPTION_NO_CRLF"), 255 TSRMLS_CC);

	zend_class_implements(beanspeak_dispatcher_ce TSRMLS_CC, 1, beanspeak_dispatcher_dispatcherinterface_ce);
	zend_class_implements(beanspeak_dispatcher_ce TSRMLS_CC, 1, beanspeak_connection_connectionawareinterface_ce);
	return SUCCESS;

}

/**
 * Beanspeak\Dispatcher constructor.
 */
PHP_METHOD(Beanspeak_Dispatcher, __construct) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *connection = NULL, *_0 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &connection);

	if (!connection) {
		ZEPHIR_CPY_WRT(connection, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(connection);
	}


	ZEPHIR_INIT_VAR(_0);
	if (!(zephir_is_true(connection))) {
		ZEPHIR_INIT_NVAR(_0);
		object_init_ex(_0, beanspeak_connection_ce);
		ZEPHIR_CALL_METHOD(NULL, _0, "__construct", NULL, 17);
		zephir_check_call_status();
	} else {
		ZEPHIR_CPY_WRT(_0, connection);
	}
	ZEPHIR_CPY_WRT(connection, _0);
	zephir_update_property_this(this_ptr, SL("connection"), connection TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Dispatcher, getConnection) {

	

	RETURN_MEMBER(this_ptr, "connection");

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Dispatcher, setConnection) {

	zval *connection;

	zephir_fetch_params(0, 1, 0, &connection);



	zephir_update_property_this(this_ptr, SL("connection"), connection TSRMLS_CC);
	RETURN_THISW();

}

/**
 * {@inheritdoc}
 *
 * @throws \Beanspeak\Dispatcher\Exception
 */
PHP_METHOD(Beanspeak_Dispatcher, dispatch) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *command, *e = NULL, *_3 = NULL, *_4, *_5, *_0$$5, *_1$$5 = NULL, *_2$$5 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &command);




	/* try_start_1: */

		ZEPHIR_CALL_INTERNAL_METHOD_NORETURN_P1(this_ptr, zep_Beanspeak_Dispatcher__dispatch, command);
		zephir_check_call_status_or_jump(try_end_1);

	try_end_1:

	if (EG(exception)) {
		ZEPHIR_CPY_WRT(e, EG(exception));
		if (zephir_instance_of_ev(e, beanspeak_connection_exception_ce TSRMLS_CC)) {
			zend_clear_exception(TSRMLS_C);
			ZEPHIR_CALL_INTERNAL_METHOD_NORETURN_P0(this_ptr, zep_Beanspeak_Dispatcher__reconnect);
			zephir_check_call_status();
			ZEPHIR_CALL_INTERNAL_METHOD_NORETURN_P1(this_ptr, zep_Beanspeak_Dispatcher__dispatch, command);
			zephir_check_call_status();
		}
		ZEPHIR_CPY_WRT(e, EG(exception));
		if (zephir_instance_of_ev(e, zend_exception_get_default(TSRMLS_C) TSRMLS_CC)) {
			zend_clear_exception(TSRMLS_C);
			ZEPHIR_INIT_VAR(_0$$5);
			object_init_ex(_0$$5, beanspeak_dispatcher_exception_ce);
			ZEPHIR_CALL_METHOD(&_1$$5, e, "getmessage", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&_2$$5, e, "getcode", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, _0$$5, "__construct", NULL, 1, _1$$5, _2$$5, e);
			zephir_check_call_status();
			zephir_throw_exception_debug(_0$$5, "beanspeak/dispatcher.zep", 106 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZEPHIR_CALL_METHOD(&_3, command, "getresponseparser", NULL, 0);
	zephir_check_call_status();
	_4 = zephir_fetch_nproperty_this(this_ptr, SL("responseLine"), PH_NOISY_CC);
	_5 = zephir_fetch_nproperty_this(this_ptr, SL("responseData"), PH_NOISY_CC);
	ZEPHIR_RETURN_CALL_METHOD(_3, "parseresponse", NULL, 0, _4, _5);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Dispatcher, getLastCommand) {

	

	RETURN_MEMBER(this_ptr, "lastCommand");

}

void zep_Beanspeak_Dispatcher__dispatch(int ht, zval *return_value, zval **return_value_ptr, zval *this_ptr, int return_value_used, zval *command_ext TSRMLS_DC) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *command, *connection = NULL, *preparedcmd = NULL, *responseLine = NULL, *_0, *_1 = NULL, *_2 = NULL, *_3$$3 = NULL, *_4$$3;

	ZEPHIR_MM_GROW();
	command = command_ext;




	_0 = zephir_fetch_nproperty_this(this_ptr, SL("connection"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(connection, _0);
	ZEPHIR_CALL_METHOD(NULL, connection, "connect", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_this(this_ptr, SL("lastCommand"), command TSRMLS_CC);
	ZEPHIR_CALL_METHOD(&_1, command, "getcommandline", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(preparedcmd);
	ZEPHIR_CONCAT_VS(preparedcmd, _1, "\r\n");
	ZEPHIR_CALL_METHOD(&_2, command, "hasdata", NULL, 0);
	zephir_check_call_status();
	if (zephir_is_true(_2)) {
		ZEPHIR_CALL_METHOD(&_3$$3, command, "getdata", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_4$$3);
		ZEPHIR_CONCAT_VS(_4$$3, _3$$3, "\r\n");
		zephir_concat_self(&preparedcmd, _4$$3 TSRMLS_CC);
	}
	ZEPHIR_CALL_METHOD(NULL, connection, "write", NULL, 0, preparedcmd);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&responseLine, connection, "getline", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_INTERNAL_METHOD_NORETURN_P1(this_ptr, zep_Beanspeak_Dispatcher_checkStatusMessage, responseLine);
	zephir_check_call_status();
	ZEPHIR_CALL_INTERNAL_METHOD_NORETURN_P1(this_ptr, zep_Beanspeak_Dispatcher_parseData, responseLine);
	zephir_check_call_status();
	zephir_update_property_this(this_ptr, SL("responseLine"), responseLine TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Creates a new connection object, based on the existing connection object.
 */
void zep_Beanspeak_Dispatcher__reconnect(int ht, zval *return_value, zval **return_value_ptr, zval *this_ptr, int return_value_used TSRMLS_DC) {

	zval *_0;
	zval *newc = NULL, *oldc = NULL, *_1 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(oldc);
	zephir_read_property_this(&oldc, this_ptr, SL("connection"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(newc);
	object_init_ex(newc, beanspeak_connection_ce);
	ZEPHIR_INIT_VAR(_0);
	zephir_create_array(_0, 5, 0 TSRMLS_CC);
	ZEPHIR_CALL_METHOD(&_1, oldc, "gethost", NULL, 0);
	zephir_check_call_status();
	zephir_array_update_string(&_0, SL("host"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_CALL_METHOD(&_1, oldc, "getport", NULL, 0);
	zephir_check_call_status();
	zephir_array_update_string(&_0, SL("port"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_CALL_METHOD(&_1, oldc, "getconnecttimeout", NULL, 0);
	zephir_check_call_status();
	zephir_array_update_string(&_0, SL("timeout"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_CALL_METHOD(&_1, oldc, "ispersistent", NULL, 0);
	zephir_check_call_status();
	zephir_array_update_string(&_0, SL("persistent"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_CALL_METHOD(&_1, oldc, "getwriteretries", NULL, 0);
	zephir_check_call_status();
	zephir_array_update_string(&_0, SL("write_retries"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_CALL_METHOD(NULL, newc, "__construct", NULL, 17, _0);
	zephir_check_call_status();
	zephir_update_property_this(this_ptr, SL("connection"), newc TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

void zep_Beanspeak_Dispatcher_checkStatusMessage(int ht, zval *return_value, zval **return_value_ptr, zval *this_ptr, int return_value_used, zval *content_param_ext TSRMLS_DC) {

	zval *statusMessages = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *content_param = NULL, *message = NULL, *_0, *_1, *_2, *_3$$4, *_4$$4, *_5$$4 = NULL, *_6$$4, *_7$$4;
	zval *content = NULL;

	ZEPHIR_MM_GROW();
	content_param = content_param_ext;


	zephir_get_strval(content, content_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("statusMessages"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(statusMessages, _0);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "#^(\\S+).*$#s", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_STRING(_2, "$1", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_FUNCTION(&message, "preg_replace", NULL, 10, _1, _2, content);
	zephir_check_temp_parameter(_1);
	zephir_check_temp_parameter(_2);
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
		ZEPHIR_INIT_VAR(_3$$4);
		object_init_ex(_3$$4, beanspeak_exception_ce);
		_4$$4 = zephir_fetch_nproperty_this(this_ptr, SL("lastCommand"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(&_5$$4, _4$$4, "getname", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_6$$4);
		ZEPHIR_CONCAT_VSVS(_6$$4, message, " in response to '", _5$$4, "'");
		zephir_array_fetch(&_7$$4, statusMessages, message, PH_NOISY | PH_READONLY, "beanspeak/dispatcher.zep", 197 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(NULL, _3$$4, "__construct", NULL, 1, _6$$4, _7$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(_3$$4, "beanspeak/dispatcher.zep", 197 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_MM_RESTORE();

}

void zep_Beanspeak_Dispatcher_parseData(int ht, zval *return_value, zval **return_value_ptr, zval *this_ptr, int return_value_used, zval *content_param_ext TSRMLS_DC) {

	zval *dataResponses;
	int ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_3 = NULL;
	zval *content_param = NULL, *connection = NULL, *dataLength = NULL, *data = NULL, *message = NULL, *crlf = NULL, *_0, *_1, *_2, *_4$$3 = NULL, *_5$$3, _6$$3, *_7$$4, *_8$$4, *_9$$4;
	zval *content = NULL;

	ZEPHIR_MM_GROW();
	content_param = content_param_ext;


	zephir_get_strval(content, content_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("connection"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(connection, _0);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "#^(\\S+).*$#s", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_STRING(_2, "$1", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_FUNCTION(&message, "preg_replace", &_3, 10, _1, _2, content);
	zephir_check_temp_parameter(_1);
	zephir_check_temp_parameter(_2);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(data);
	ZVAL_NULL(data);
	ZEPHIR_INIT_VAR(dataResponses);
	zephir_create_array(dataResponses, 3, 0 TSRMLS_CC);
	zephir_array_update_string(&dataResponses, SL("RESERVED"), &ZEPHIR_GLOBAL(global_true), PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&dataResponses, SL("FOUND"), &ZEPHIR_GLOBAL(global_true), PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&dataResponses, SL("OK"), &ZEPHIR_GLOBAL(global_true), PH_COPY | PH_SEPARATE);
	if (zephir_array_isset(dataResponses, message)) {
		ZEPHIR_INIT_VAR(_4$$3);
		ZVAL_STRING(_4$$3, "#^.*\\b(\\d+)$#", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_INIT_VAR(_5$$3);
		ZVAL_STRING(_5$$3, "$1", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_FUNCTION(&dataLength, "preg_replace", &_3, 10, _4$$3, _5$$3, content);
		zephir_check_temp_parameter(_4$$3);
		zephir_check_temp_parameter(_5$$3);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&data, connection, "read", NULL, 0, dataLength);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(_4$$3);
		ZVAL_LONG(_4$$3, 2);
		ZEPHIR_CALL_METHOD(&crlf, connection, "read", NULL, 0, _4$$3);
		zephir_check_call_status();
		ZEPHIR_SINIT_VAR(_6$$3);
		ZVAL_STRING(&_6$$3, "\r\n", 0);
		if (!ZEPHIR_IS_IDENTICAL(&_6$$3, crlf)) {
			ZEPHIR_INIT_VAR(_7$$4);
			object_init_ex(_7$$4, beanspeak_exception_ce);
			ZEPHIR_INIT_VAR(_8$$4);
			ZEPHIR_CONCAT_SVS(_8$$4, "Expected 2 bytes of CRLF after ", dataLength, " bytes of data");
			ZEPHIR_INIT_VAR(_9$$4);
			ZVAL_LONG(_9$$4, 255);
			ZEPHIR_CALL_METHOD(NULL, _7$$4, "__construct", NULL, 1, _8$$4, _9$$4);
			zephir_check_call_status();
			zephir_throw_exception_debug(_7$$4, "beanspeak/dispatcher.zep", 224 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	zephir_update_property_this(this_ptr, SL("responseData"), data TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

static zend_object_value zephir_init_properties_Beanspeak_Dispatcher(zend_class_entry *class_type TSRMLS_DC) {

		zval *_0, *_1$$3;

		ZEPHIR_MM_GROW();
	
	{
		zval *this_ptr = NULL;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		_0 = zephir_fetch_nproperty_this(this_ptr, SL("statusMessages"), PH_NOISY_CC);
		if (Z_TYPE_P(_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(_1$$3);
			array_init(_1$$3);
			zephir_update_property_this(this_ptr, SL("statusMessages"), _1$$3 TSRMLS_CC);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJVAL_P(this_ptr);
	}

}

