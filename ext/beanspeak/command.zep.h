
extern zend_class_entry *beanspeak_command_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Command);

PHP_METHOD(Beanspeak_Command, getCommandName);
PHP_METHOD(Beanspeak_Command, execute);
PHP_METHOD(Beanspeak_Command, hasData);
PHP_METHOD(Beanspeak_Command, getData);
PHP_METHOD(Beanspeak_Command, getDataLength);
PHP_METHOD(Beanspeak_Command, __toString);

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_command_execute, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, connection, Beanspeak\\Connection\\ConnectionInterface, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(beanspeak_command_method_entry) {
	PHP_ME(Beanspeak_Command, getCommandName, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command, execute, arginfo_beanspeak_command_execute, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command, hasData, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command, getData, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command, getDataLength, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command, __toString, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
