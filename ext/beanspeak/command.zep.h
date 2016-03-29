
extern zend_class_entry *beanspeak_command_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Command);

PHP_METHOD(Beanspeak_Command, getCommandName);
PHP_METHOD(Beanspeak_Command, __toString);

ZEPHIR_INIT_FUNCS(beanspeak_command_method_entry) {
	PHP_ME(Beanspeak_Command, getCommandName, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command, __toString, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
