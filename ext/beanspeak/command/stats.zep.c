
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
#include "kernel/fcall.h"
#include "kernel/memory.h"


/**
 * Beanspeak\Command\Stats
 *
 * Statistical information about the system as a whole.
 *
 * <code>
 * use Beanspeak\Command\Stats;
 *
 * $stats = new Stats;
 * </code>
 */
ZEPHIR_INIT_CLASS(Beanspeak_Command_Stats) {

	ZEPHIR_REGISTER_CLASS_EX(Beanspeak\\Command, Stats, beanspeak, command_stats, beanspeak_command_ce, beanspeak_command_stats_method_entry, 0);

	return SUCCESS;

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_Stats, getName) {

	

	RETURN_STRING("STATS", 1);

}

PHP_METHOD(Beanspeak_Command_Stats, getCommandLine) {

	

	RETURN_STRING("stats", 1);

}

PHP_METHOD(Beanspeak_Command_Stats, getResponseParser) {

	zval *_0;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	object_init_ex(return_value, beanspeak_response_parser_yaml_ce);
	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "dict", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 12, _0);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	RETURN_MM();

}

