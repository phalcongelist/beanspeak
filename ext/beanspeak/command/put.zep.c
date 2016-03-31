
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
#include "kernel/object.h"
#include "kernel/memory.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/operators.h"
#include "kernel/concat.h"
#include "kernel/fcall.h"
#include "kernel/string.h"
#include "kernel/array.h"


/**
 * Beanspeak\Command\Put
 *
 * Inserts a job into the client's currently used tube.
 */
ZEPHIR_INIT_CLASS(Beanspeak_Command_Put) {

	ZEPHIR_REGISTER_CLASS_EX(Beanspeak\\Command, Put, beanspeak, command_put, beanspeak_command_ce, beanspeak_command_put_method_entry, 0);

	zend_declare_property_null(beanspeak_command_put_ce, SL("data"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(beanspeak_command_put_ce, SL("priority"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(beanspeak_command_put_ce, SL("delay"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(beanspeak_command_put_ce, SL("ttr"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_class_implements(beanspeak_command_put_ce TSRMLS_CC, 1, beanspeak_response_responseparserinterface_ce);
	return SUCCESS;

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_Put, getName) {

	

	RETURN_STRING("PUT", 1);

}

/**
 * Beanspeak\Command\Put constructor
 */
PHP_METHOD(Beanspeak_Command_Put, __construct) {

	int priority, delay, ttr;
	zval *data_param = NULL, *priority_param = NULL, *delay_param = NULL, *ttr_param = NULL, *_0;
	zval *data = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 4, 0, &data_param, &priority_param, &delay_param, &ttr_param);

	if (unlikely(Z_TYPE_P(data_param) != IS_STRING && Z_TYPE_P(data_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'data' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (likely(Z_TYPE_P(data_param) == IS_STRING)) {
		zephir_get_strval(data, data_param);
	} else {
		ZEPHIR_INIT_VAR(data);
		ZVAL_EMPTY_STRING(data);
	}
	priority = zephir_get_intval(priority_param);
	delay = zephir_get_intval(delay_param);
	ttr = zephir_get_intval(ttr_param);


	zephir_update_property_this(this_ptr, SL("data"), data TSRMLS_CC);
	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(_0, priority);
	zephir_update_property_this(this_ptr, SL("priority"), _0 TSRMLS_CC);
	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(_0, delay);
	zephir_update_property_this(this_ptr, SL("delay"), _0 TSRMLS_CC);
	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(_0, ttr);
	zephir_update_property_this(this_ptr, SL("ttr"), _0 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_Put, getCommandLine) {

	zval *_0, *_1, *_2, *_3 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("priority"), PH_NOISY_CC);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("delay"), PH_NOISY_CC);
	_2 = zephir_fetch_nproperty_this(this_ptr, SL("ttr"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_3, this_ptr, "getdatalength", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CONCAT_SVSVSVSV(return_value, "put ", _0, " ", _1, " ", _2, " ", _3);
	RETURN_MM();

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_Put, hasData) {

	

	RETURN_BOOL(1);

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_Put, getData) {

	

	RETURN_MEMBER(this_ptr, "data");

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_Put, getDataLength) {

	zval *_0$$3, _1$$3, *_2;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	if ((zephir_function_exists_ex(SS("mb_strlen") TSRMLS_CC) == SUCCESS)) {
		_0$$3 = zephir_fetch_nproperty_this(this_ptr, SL("data"), PH_NOISY_CC);
		ZEPHIR_SINIT_VAR(_1$$3);
		ZVAL_STRING(&_1$$3, "latin1", 0);
		ZEPHIR_RETURN_CALL_FUNCTION("mb_strlen", NULL, 6, _0$$3, &_1$$3);
		zephir_check_call_status();
		RETURN_MM();
	}
	_2 = zephir_fetch_nproperty_this(this_ptr, SL("data"), PH_NOISY_CC);
	RETURN_MM_LONG(zephir_fast_strlen_ev(_2));

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_Put, parseResponse) {

	zval *_2$$3;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *line_param = NULL, *data_param = NULL, *matches = NULL, *name = NULL, *_0, _1, *_5, _6, *_9, *_10, _11, *_14, *_15, _16, *_19, *_20, _21, *_24, *_3$$3, *_4$$3, *_7$$4, *_8$$4, *_12$$5, *_13$$5, *_17$$6, *_18$$6, *_22$$7, *_23$$7;
	zval *line = NULL, *data = NULL, *_25;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &line_param, &data_param);

	zephir_get_strval(line, line_param);
	if (!data_param) {
		ZEPHIR_INIT_VAR(data);
		ZVAL_EMPTY_STRING(data);
	} else {
		zephir_get_strval(data, data_param);
	}


	ZEPHIR_INIT_VAR(matches);
	ZVAL_NULL(matches);
	ZEPHIR_INIT_VAR(_0);
	ZEPHIR_SINIT_VAR(_1);
	ZVAL_STRING(&_1, "#^INSERTED (\\d+)$#", 0);
	zephir_preg_match(_0, &_1, line, matches, 0, 0 , 0  TSRMLS_CC);
	if (zephir_is_true(_0)) {
		ZEPHIR_INIT_VAR(_2$$3);
		zephir_create_array(_2$$3, 1, 0 TSRMLS_CC);
		ZEPHIR_OBS_VAR(_3$$3);
		zephir_array_fetch_long(&_3$$3, matches, 1, PH_NOISY, "beanspeak/command/put.zep", 100 TSRMLS_CC);
		add_assoc_long_ex(_2$$3, SS("id"), zephir_get_intval(_3$$3));
		ZEPHIR_INIT_VAR(_4$$3);
		ZVAL_STRING(_4$$3, "INSERTED", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "createresponse", NULL, 0, _4$$3, _2$$3);
		zephir_check_temp_parameter(_4$$3);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_CALL_METHOD(&name, this_ptr, "getname", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_5);
	ZEPHIR_SINIT_VAR(_6);
	ZVAL_STRING(&_6, "#^BURIED (\\d)+$#", 0);
	zephir_preg_match(_5, &_6, line, matches, 0, 0 , 0  TSRMLS_CC);
	if (zephir_is_true(_5)) {
		ZEPHIR_INIT_VAR(_7$$4);
		object_init_ex(_7$$4, beanspeak_command_exception_ce);
		ZEPHIR_INIT_VAR(_8$$4);
		ZEPHIR_CONCAT_VS(_8$$4, name, ": server ran out of memory trying to grow the priority queue data structure");
		ZEPHIR_CALL_METHOD(NULL, _7$$4, "__construct", NULL, 7, _8$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(_7$$4, "beanspeak/command/put.zep", 106 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(_9);
	ZEPHIR_INIT_VAR(_10);
	ZEPHIR_SINIT_VAR(_11);
	ZVAL_STRING(&_11, "#^JOB_TOO_BIG$#", 0);
	zephir_preg_match(_10, &_11, line, _9, 0, 0 , 0  TSRMLS_CC);
	if (zephir_is_true(_10)) {
		ZEPHIR_INIT_VAR(_12$$5);
		object_init_ex(_12$$5, beanspeak_command_exception_ce);
		ZEPHIR_INIT_VAR(_13$$5);
		ZEPHIR_CONCAT_VS(_13$$5, name, ": job data exceeds server-enforced limit");
		ZEPHIR_CALL_METHOD(NULL, _12$$5, "__construct", NULL, 7, _13$$5);
		zephir_check_call_status();
		zephir_throw_exception_debug(_12$$5, "beanspeak/command/put.zep", 110 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(_14);
	ZEPHIR_INIT_VAR(_15);
	ZEPHIR_SINIT_VAR(_16);
	ZVAL_STRING(&_16, "#^EXPECTED_CRLF#", 0);
	zephir_preg_match(_15, &_16, line, _14, 0, 0 , 0  TSRMLS_CC);
	if (zephir_is_true(_15)) {
		ZEPHIR_INIT_VAR(_17$$6);
		object_init_ex(_17$$6, beanspeak_command_exception_ce);
		ZEPHIR_INIT_VAR(_18$$6);
		ZEPHIR_CONCAT_VS(_18$$6, name, ": CRLF expected");
		ZEPHIR_CALL_METHOD(NULL, _17$$6, "__construct", NULL, 7, _18$$6);
		zephir_check_call_status();
		zephir_throw_exception_debug(_17$$6, "beanspeak/command/put.zep", 114 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(_19);
	ZEPHIR_INIT_VAR(_20);
	ZEPHIR_SINIT_VAR(_21);
	ZVAL_STRING(&_21, "#^DRAINING#", 0);
	zephir_preg_match(_20, &_21, line, _19, 0, 0 , 0  TSRMLS_CC);
	if (zephir_is_true(_20)) {
		ZEPHIR_INIT_VAR(_22$$7);
		object_init_ex(_22$$7, beanspeak_command_exception_ce);
		ZEPHIR_INIT_VAR(_23$$7);
		ZEPHIR_CONCAT_VS(_23$$7, name, ": server has been put into 'drain mode' and is no longer accepting new jobs");
		ZEPHIR_CALL_METHOD(NULL, _22$$7, "__construct", NULL, 7, _23$$7);
		zephir_check_call_status();
		zephir_throw_exception_debug(_22$$7, "beanspeak/command/put.zep", 118 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(_24);
	object_init_ex(_24, beanspeak_command_exception_ce);
	ZEPHIR_INIT_VAR(_25);
	ZEPHIR_CONCAT_SV(_25, "Unhandled response: ", line);
	ZEPHIR_CALL_METHOD(NULL, _24, "__construct", NULL, 7, _25);
	zephir_check_call_status();
	zephir_throw_exception_debug(_24, "beanspeak/command/put.zep", 121 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

