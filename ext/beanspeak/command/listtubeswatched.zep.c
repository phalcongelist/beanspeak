
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
 * Beanspeak\Command\ListTubesWatched
 *
 * Returns a list tubes currently being watched by the client.
 *
 * <code>
 * use Beanspeak\Command\ListTubesWatched;
 *
 * $watched = new ListTubesWatched;
 * </code>
 */
ZEPHIR_INIT_CLASS(Beanspeak_Command_ListTubesWatched) {

	ZEPHIR_REGISTER_CLASS_EX(Beanspeak\\Command, ListTubesWatched, beanspeak, command_listtubeswatched, beanspeak_command_ce, beanspeak_command_listtubeswatched_method_entry, 0);

	return SUCCESS;

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_ListTubesWatched, getName) {

	

	RETURN_STRING("LIST-TUBES-WATCHED", 1);

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_ListTubesWatched, getCommandLine) {

	

	RETURN_STRING("list-tubes-watched", 1);

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Beanspeak_Command_ListTubesWatched, getResponseParser) {

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

