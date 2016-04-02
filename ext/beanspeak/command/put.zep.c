
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
 *
 * <code>
 * use Beanspeak\Command\Put;
 *
 * $put = new Put(
 *     [
 *         'recipient' => 'user@mail.com',
 *         'subject'   => 'Welcome',
 *         'content'   => $content,
 *     ],
 *     999,
 *     60 * 60,
 *     3600,
 * );
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
		ZEPHIR_RETURN_CALL_FUNCTION("mb_strlen", NULL, 11, _0$$3, &_1$$3);
		zephir_check_call_status();
		RETURN_MM();
	}
	_2 = zephir_fetch_nproperty_this(this_ptr, SL("data"), PH_NOISY_CC);
	RETURN_MM_LONG(zephir_fast_strlen_ev(_2));

}

/**
 * {@inheritdoc}
 *  @throws \Beanspeak\Command\Exception
 */
PHP_METHOD(Beanspeak_Command_Put, parseResponse) {

	zval *_2$$3;
	zephir_fcall_cache_entry *_7 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *line_param = NULL, *data_param = NULL, *matches = NULL, *_0, _1, *_18, *_3$$3, *_4$$3, *_5$$4, *_6$$4 = NULL, *_8$$4, *_9$$5, *_10$$5 = NULL, *_11$$5, *_12$$6, *_13$$6 = NULL, *_14$$6, *_15$$7, *_16$$7 = NULL, *_17$$7;
	zval *line = NULL, *data = NULL, *_19;

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
		zephir_array_fetch_long(&_3$$3, matches, 1, PH_NOISY, "beanspeak/command/put.zep", 115 TSRMLS_CC);
		add_assoc_long_ex(_2$$3, SS("id"), zephir_get_intval(_3$$3));
		ZEPHIR_INIT_VAR(_4$$3);
		ZVAL_STRING(_4$$3, "INSERTED", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "createresponse", NULL, 0, _4$$3, _2$$3);
		zephir_check_temp_parameter(_4$$3);
		zephir_check_call_status();
		RETURN_MM();
	}
	if (zephir_start_with_str(line, SL("BURIED"))) {
		ZEPHIR_INIT_VAR(_5$$4);
		object_init_ex(_5$$4, beanspeak_command_exception_ce);
		ZEPHIR_CALL_METHOD(&_6$$4, this_ptr, "getname", &_7, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_8$$4);
		ZEPHIR_CONCAT_VS(_8$$4, _6$$4, ": server ran out of memory trying to grow the priority queue data structure");
		ZEPHIR_CALL_METHOD(NULL, _5$$4, "__construct", NULL, 1, _8$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(_5$$4, "beanspeak/command/put.zep", 119 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (zephir_start_with_str(line, SL("JOB_TOO_BIG"))) {
		ZEPHIR_INIT_VAR(_9$$5);
		object_init_ex(_9$$5, beanspeak_command_exception_ce);
		ZEPHIR_CALL_METHOD(&_10$$5, this_ptr, "getname", &_7, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_11$$5);
		ZEPHIR_CONCAT_VS(_11$$5, _10$$5, ": job data exceeds server-enforced limit");
		ZEPHIR_CALL_METHOD(NULL, _9$$5, "__construct", NULL, 1, _11$$5);
		zephir_check_call_status();
		zephir_throw_exception_debug(_9$$5, "beanspeak/command/put.zep", 123 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (zephir_start_with_str(line, SL("EXPECTED_CRLF"))) {
		ZEPHIR_INIT_VAR(_12$$6);
		object_init_ex(_12$$6, beanspeak_command_exception_ce);
		ZEPHIR_CALL_METHOD(&_13$$6, this_ptr, "getname", &_7, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_14$$6);
		ZEPHIR_CONCAT_VS(_14$$6, _13$$6, ": CRLF expected");
		ZEPHIR_CALL_METHOD(NULL, _12$$6, "__construct", NULL, 1, _14$$6);
		zephir_check_call_status();
		zephir_throw_exception_debug(_12$$6, "beanspeak/command/put.zep", 127 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (zephir_start_with_str(line, SL("DRAINING"))) {
		ZEPHIR_INIT_VAR(_15$$7);
		object_init_ex(_15$$7, beanspeak_command_exception_ce);
		ZEPHIR_CALL_METHOD(&_16$$7, this_ptr, "getname", &_7, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(_17$$7);
		ZEPHIR_CONCAT_VS(_17$$7, _16$$7, ": server has been put into 'drain mode' and is no longer accepting new jobs");
		ZEPHIR_CALL_METHOD(NULL, _15$$7, "__construct", NULL, 1, _17$$7);
		zephir_check_call_status();
		zephir_throw_exception_debug(_15$$7, "beanspeak/command/put.zep", 131 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(_18);
	object_init_ex(_18, beanspeak_command_exception_ce);
	ZEPHIR_INIT_VAR(_19);
	ZEPHIR_CONCAT_SV(_19, "Unhandled response: ", line);
	ZEPHIR_CALL_METHOD(NULL, _18, "__construct", NULL, 1, _19);
	zephir_check_call_status();
	zephir_throw_exception_debug(_18, "beanspeak/command/put.zep", 134 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

