
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
#include "kernel/array.h"


/**
 * Beanspeak\Dispatcher
 */
ZEPHIR_INIT_CLASS(Beanspeak_Dispatcher) {

	ZEPHIR_REGISTER_CLASS(Beanspeak, Dispatcher, beanspeak, dispatcher, beanspeak_dispatcher_method_entry, 0);

	zend_declare_property_null(beanspeak_dispatcher_ce, SL("connection"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_class_implements(beanspeak_dispatcher_ce TSRMLS_CC, 1, beanspeak_dispatcher_dispatcherinterface_ce);
	zend_class_implements(beanspeak_dispatcher_ce TSRMLS_CC, 1, beanspeak_connection_connectionawareinterface_ce);
	return SUCCESS;

}

/**
 * Beanspeak\Dispatcher constructor
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
		ZEPHIR_CALL_METHOD(NULL, _0, "__construct", NULL, 1);
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
 * If a Beanspeak\Connection\Exception occurs, the connection is reset,
 * and the command is re-attempted once.
 *
 * @todo
 * @throws \Beanspeak\Dispatcher\Exception
 */
PHP_METHOD(Beanspeak_Dispatcher, dispatch) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *command, *response = NULL, *parser = NULL, *e = NULL, *_0$$3, *_1$$3, *_2$$4, *_3$$5, *_4$$5 = NULL, *_5$$5 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &command);




	/* try_start_1: */

		_0$$3 = zephir_fetch_nproperty_this(this_ptr, SL("connection"), PH_NOISY_CC);
		ZEPHIR_CALL_METHOD(NULL, _0$$3, "connect", NULL, 0);
		zephir_check_call_status_or_jump(try_end_1);
		ZEPHIR_CALL_METHOD(&parser, command, "getresponseparser", NULL, 0);
		zephir_check_call_status_or_jump(try_end_1);
		ZEPHIR_INIT_VAR(_1$$3);
		ZVAL_STRING(_1$$3, "", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(&response, parser, "parse", NULL, 0, _1$$3);
		zephir_check_temp_parameter(_1$$3);
		zephir_check_call_status_or_jump(try_end_1);

	try_end_1:

	if (EG(exception)) {
		ZEPHIR_CPY_WRT(e, EG(exception));
		if (zephir_instance_of_ev(e, beanspeak_connection_exception_ce TSRMLS_CC)) {
			zend_clear_exception(TSRMLS_C);
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "reconnect", NULL, 4);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&parser, command, "getresponseparser", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_INIT_VAR(_2$$4);
			ZVAL_STRING(_2$$4, "", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_CALL_METHOD(&response, parser, "parse", NULL, 0, _2$$4);
			zephir_check_temp_parameter(_2$$4);
			zephir_check_call_status();
		}
		ZEPHIR_CPY_WRT(e, EG(exception));
		if (zephir_instance_of_ev(e, zend_exception_get_default(TSRMLS_C) TSRMLS_CC)) {
			zend_clear_exception(TSRMLS_C);
			ZEPHIR_INIT_VAR(_3$$5);
			object_init_ex(_3$$5, beanspeak_dispatcher_exception_ce);
			ZEPHIR_CALL_METHOD(&_4$$5, e, "getmessge", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&_5$$5, e, "getcode", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, _3$$5, "__construct", NULL, 5, _4$$5, _5$$5, e);
			zephir_check_call_status();
			zephir_throw_exception_debug(_3$$5, "beanspeak/dispatcher.zep", 89 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	RETURN_CCTOR(response);

}

/**
 * Creates a new connection object, based on the existing connection object
 */
PHP_METHOD(Beanspeak_Dispatcher, reconnect) {

	zval *_0;
	zval *newc = NULL, *oldc = NULL, *_1 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(oldc);
	zephir_read_property_this(&oldc, this_ptr, SL("connection"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(newc);
	object_init_ex(newc, beanspeak_connection_ce);
	ZEPHIR_INIT_VAR(_0);
	zephir_create_array(_0, 4, 0 TSRMLS_CC);
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
	ZEPHIR_CALL_METHOD(NULL, newc, "__construct", NULL, 1, _0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, newc, "connect", NULL, 2);
	zephir_check_call_status();
	zephir_update_property_this(this_ptr, SL("connection"), newc TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

