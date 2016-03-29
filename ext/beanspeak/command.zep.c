
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
#include "kernel/fcall.h"
#include "kernel/memory.h"


/**
 * Beanspeak\Command
 */
ZEPHIR_INIT_CLASS(Beanspeak_Command) {

	ZEPHIR_REGISTER_CLASS(Beanspeak, Command, beanspeak, command, beanspeak_command_method_entry, ZEND_ACC_EXPLICIT_ABSTRACT_CLASS);

	zend_class_implements(beanspeak_command_ce TSRMLS_CC, 1, beanspeak_command_commandinterface_ce);
	return SUCCESS;

}

/**
 * The string representation of the object.
 */
PHP_METHOD(Beanspeak_Command, __toString) {

	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "getcommandline", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();

}

