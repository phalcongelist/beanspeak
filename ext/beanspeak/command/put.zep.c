
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
#include "kernel/exception.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/concat.h"
#include "kernel/string.h"
#include "kernel/array.h"


/**
 * Beanspeak\Command\Put
 *
 * Inserts a job into the client's currently used tube.
 *
 * <code>
 * use Beanspeak\Command\Put;
 *
 * $task = [
 *     'recipient' => 'user@mail.com',
 *     'subject'   => 'Welcome',
 *     'content'   => $content,
 * ];
 *
 * $put = new Put($task, 999, 60 * 60, 3600);
 * </code>
 */
ZEPHIR_INIT_CLASS(Beanspeak_Command_Put) {

	ZEPHIR_REGISTER_CLASS_EX(Beanspeak\\Command, Put, beanspeak, command_put, beanspeak_command_ce, beanspeak_command_put_method_entry, 0);

	zend_declare_property_null(beanspeak_command_put_ce, SL("data"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(beanspeak_command_put_ce, SL("priority"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(beanspeak_command_put_ce, SL("delay"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(beanspeak_command_put_ce, SL("ttr"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_class_implements(beanspeak_command_put_ce TSRMLS_CC, 1, beanspeak_response_parser_parserinterface_ce);
	return SUCCESS;

}

/**
 * Beanspeak\Command\Put constructor
 * @throws \InvalidArgumentException
 */
PHP_METHOD(Beanspeak_Command_Put, __construct) {

	int priority, delay, ttr, ZEPHIR_LAST_CALL_STATUS;
	zval *data, *priority_param = NULL, *delay_param = NULL, *ttr_param = NULL, *_0 = NULL, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 3, &data, &priority_param, &delay_param, &ttr_param);

	if (!priority_param) {
		priority = 1024;
	} else {
		priority = zephir_get_intval(priority_param);
	}
	if (!delay_param) {
		delay = 0;
	} else {
		delay = zephir_get_intval(delay_param);
	}
	if (!ttr_param) {
		ttr = 86400;
	} else {
		ttr = zephir_get_intval(ttr_param);
	}


	if (priority > 4294967295) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "The \"priority\" param must less than 4294967295", "beanspeak/command/put.zep", 56);
		return;
	}
	ZEPHIR_CALL_FUNCTION(&_0, "serialize", NULL, 25, data);
	zephir_check_call_status();
	zephir_update_property_this(this_ptr, SL("data"), _0 TSRMLS_CC);
	ZEPHIR_INIT_ZVAL_NREF(_1);
	ZVAL_LONG(_1, priority);
	zephir_update_property_this(this_ptr, SL("priority"), _1 TSRMLS_CC);
	ZEPHIR_INIT_ZVAL_NREF(_1);
	ZVAL_LONG(_1, delay);
	zephir_update_property_this(this_ptr, SL("delay"), _1 TSRMLS_CC);
	ZEPHIR_INIT_ZVAL_NREF(_1);
	ZVAL_LONG(_1, ttr);
	zephir_update_property_this(this_ptr, SL("ttr"), _1 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_Put, getName) {

	

	RETURN_STRING("PUT", 1);

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
		ZEPHIR_RETURN_CALL_FUNCTION("mb_strlen", NULL, 26, _0$$3, &_1$$3);
		zephir_check_call_status();
		RETURN_MM();
	}
	_2 = zephir_fetch_nproperty_this(this_ptr, SL("data"), PH_NOISY_CC);
	RETURN_MM_LONG(zephir_fast_strlen_ev(_2));

}

/**
 * {@inheritdoc}
 * @throws \Beanspeak\Command\Exception
 */
PHP_METHOD(Beanspeak_Command_Put, parseResponse) {

	zval *_2$$3;
	zephir_fcall_cache_entry *_5 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *line_param = NULL, *data_param = NULL, *id$$3 = NULL, *_0$$3 = NULL, *_1$$3, *_3$$4, *_4$$4 = NULL, *_6$$4, *_7$$5, *_8$$5 = NULL, *_9$$5, *_10$$6, *_11$$6 = NULL, *_12$$6, *_13$$7, *_14$$7 = NULL, *_15$$7, *_16;
	zval *line = NULL, *data = NULL, *_17;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &line_param, &data_param);

	zephir_get_strval(line, line_param);
	if (!data_param) {
		ZEPHIR_INIT_VAR(data);
		ZVAL_EMPTY_STRING(data);
	} else {
		zephir_get_strval(data, data_param);
	}


	if (zephir_start_with_str(line, SL("INSERTED"))) {
		ZEPHIR_INIT_VAR(id$$3);
		ZVAL_NULL(id$$3);
		ZEPHIR_INIT_VAR(_0$$3);
		ZVAL_STRING(_0$$3, "#^INSERTED (\\d+)$#", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_INIT_VAR(_1$$3);
		ZVAL_STRING(_1$$3, "$1", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_FUNCTION(&id$$3, "preg_replace", NULL, 23, _0$$3, _1$$3, line);
		zephir_check_temp_parameter(_0$$3);
		zephir_check_temp_parameter(_1$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_2$$3);
		zephir_create_array(_2$$3, 1, 0 TSRMLS_CC);
		add_assoc_long_ex(_2$$3, SS("id"), zephir_get_intval(id$$3));
		ZEPHIR_INIT_NVAR(_0$$3);
		ZVAL_STRING(_0$$3, "INSERTED", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "createresponse", NULL, 0, _0$$3, _2$$3);
		zephir_check_temp_parameter(_0$$3);
		zephir_check_call_status();
		RETURN_MM();
	}
	if (zephir_start_with_str(line, SL("BURIED"))) {
		ZEPHIR_INIT_VAR(_3$$4);
		object_init_ex(_3$$4, beanspeak_command_exception_ce);
		ZEPHIR_CALL_METHOD(&_4$$4, this_ptr, "getname", &_5, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_6$$4);
		ZEPHIR_CONCAT_VS(_6$$4, _4$$4, ": server ran out of memory trying to grow the priority queue data structure");
		ZEPHIR_CALL_METHOD(NULL, _3$$4, "__construct", NULL, 1, _6$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(_3$$4, "beanspeak/command/put.zep", 127 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (zephir_start_with_str(line, SL("JOB_TOO_BIG"))) {
		ZEPHIR_INIT_VAR(_7$$5);
		object_init_ex(_7$$5, beanspeak_command_exception_ce);
		ZEPHIR_CALL_METHOD(&_8$$5, this_ptr, "getname", &_5, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_9$$5);
		ZEPHIR_CONCAT_VS(_9$$5, _8$$5, ": job data exceeds server-enforced limit");
		ZEPHIR_CALL_METHOD(NULL, _7$$5, "__construct", NULL, 1, _9$$5);
		zephir_check_call_status();
		zephir_throw_exception_debug(_7$$5, "beanspeak/command/put.zep", 131 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (zephir_start_with_str(line, SL("EXPECTED_CRLF"))) {
		ZEPHIR_INIT_VAR(_10$$6);
		object_init_ex(_10$$6, beanspeak_command_exception_ce);
		ZEPHIR_CALL_METHOD(&_11$$6, this_ptr, "getname", &_5, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_12$$6);
		ZEPHIR_CONCAT_VS(_12$$6, _11$$6, ": CRLF expected");
		ZEPHIR_CALL_METHOD(NULL, _10$$6, "__construct", NULL, 1, _12$$6);
		zephir_check_call_status();
		zephir_throw_exception_debug(_10$$6, "beanspeak/command/put.zep", 135 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (zephir_start_with_str(line, SL("DRAINING"))) {
		ZEPHIR_INIT_VAR(_13$$7);
		object_init_ex(_13$$7, beanspeak_command_exception_ce);
		ZEPHIR_CALL_METHOD(&_14$$7, this_ptr, "getname", &_5, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_15$$7);
		ZEPHIR_CONCAT_VS(_15$$7, _14$$7, ": server has been put into 'drain mode' and is no longer accepting new jobs");
		ZEPHIR_CALL_METHOD(NULL, _13$$7, "__construct", NULL, 1, _15$$7);
		zephir_check_call_status();
		zephir_throw_exception_debug(_13$$7, "beanspeak/command/put.zep", 139 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(_16);
	object_init_ex(_16, beanspeak_command_exception_ce);
	ZEPHIR_INIT_VAR(_17);
	ZEPHIR_CONCAT_SV(_17, "Unhandled response: ", line);
	ZEPHIR_CALL_METHOD(NULL, _16, "__construct", NULL, 1, _17);
	zephir_check_call_status();
	zephir_throw_exception_debug(_16, "beanspeak/command/put.zep", 142 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

