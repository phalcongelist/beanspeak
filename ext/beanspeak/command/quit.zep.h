
extern zend_class_entry *beanspeak_command_quit_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Command_Quit);

PHP_METHOD(Beanspeak_Command_Quit, getName);
PHP_METHOD(Beanspeak_Command_Quit, getCommandLine);
PHP_METHOD(Beanspeak_Command_Quit, hasResponse);
PHP_METHOD(Beanspeak_Command_Quit, parseResponse);

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_command_quit_parseresponse, 0, 0, 1)
	ZEND_ARG_INFO(0, line)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(beanspeak_command_quit_method_entry) {
	PHP_ME(Beanspeak_Command_Quit, getName, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_Quit, getCommandLine, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_Quit, hasResponse, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_Quit, parseResponse, arginfo_beanspeak_command_quit_parseresponse, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
