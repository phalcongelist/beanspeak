
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
 * Beanspeak\Command\ListTubes
 *
 * Returns a list of all existing tubes.
 *
 * <code>
 * use Beanspeak\Command\ListTubes;
 *
 * $list = new ListTubes;
 * </code>
 */
ZEPHIR_INIT_CLASS(Beanspeak_Command_ListTubes) {

	ZEPHIR_REGISTER_CLASS_EX(Beanspeak\\Command, ListTubes, beanspeak, command_listtubes, beanspeak_command_ce, beanspeak_command_listtubes_method_entry, 0);

	return SUCCESS;

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_ListTubes, getName) {

	

	RETURN_STRING("LIST-TUBES", 1);

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_ListTubes, getCommandLine) {

	

	RETURN_STRING("list-tubes", 1);

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_ListTubes, getResponseParser) {

	zval *_0;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	object_init_ex(return_value, beanspeak_response_parser_yaml_ce);
	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "list", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 14, _0);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	RETURN_MM();

}

