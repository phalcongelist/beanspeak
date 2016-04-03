
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
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/concat.h"
#include "kernel/fcall.h"


/**
 * Beanspeak\Command\StatsTube
 *
 * Gives statistical information about the specified tube if it exists.
 *
 * <code>
 * use Beanspeak\Command\StatsTube;
 *
 * $stats = new StatsTube('process-bitcoin');
 * </code>
 */
ZEPHIR_INIT_CLASS(Beanspeak_Command_StatsTube) {

	ZEPHIR_REGISTER_CLASS_EX(Beanspeak\\Command, StatsTube, beanspeak, command_statstube, beanspeak_command_ce, beanspeak_command_statstube_method_entry, 0);

	zend_declare_property_null(beanspeak_command_statstube_ce, SL("tube"), ZEND_ACC_PRIVATE TSRMLS_CC);

	return SUCCESS;

}

/**
 * Beanspeak\Command\StatsTube constructor
 */
PHP_METHOD(Beanspeak_Command_StatsTube, __construct) {

	zval *tube_param = NULL;
	zval *tube = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &tube_param);

	if (unlikely(Z_TYPE_P(tube_param) != IS_STRING && Z_TYPE_P(tube_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'tube' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (likely(Z_TYPE_P(tube_param) == IS_STRING)) {
		zephir_get_strval(tube, tube_param);
	} else {
		ZEPHIR_INIT_VAR(tube);
		ZVAL_EMPTY_STRING(tube);
	}


	zephir_update_property_this(this_ptr, SL("tube"), tube TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_StatsTube, getName) {

	

	RETURN_STRING("STATS-TUBE", 1);

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_StatsTube, getCommandLine) {

	zval *_0;


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("tube"), PH_NOISY_CC);
	ZEPHIR_CONCAT_SV(return_value, "stats-tube ", _0);
	return;

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_StatsTube, getResponseParser) {

	zval *_0;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	object_init_ex(return_value, beanspeak_response_parser_yaml_ce);
	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "dict", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 20, _0);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	RETURN_MM();

}

