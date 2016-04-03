
extern zend_class_entry *beanspeak_command_kick_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Command_Kick);

PHP_METHOD(Beanspeak_Command_Kick, __construct);
PHP_METHOD(Beanspeak_Command_Kick, getName);
PHP_METHOD(Beanspeak_Command_Kick, getCommandLine);
PHP_METHOD(Beanspeak_Command_Kick, parseResponse);

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_command_kick___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, bound)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_command_kick_parseresponse, 0, 0, 1)
	ZEND_ARG_INFO(0, line)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(beanspeak_command_kick_method_entry) {
	PHP_ME(Beanspeak_Command_Kick, __construct, arginfo_beanspeak_command_kick___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Beanspeak_Command_Kick, getName, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_Kick, getCommandLine, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_Kick, parseResponse, arginfo_beanspeak_command_kick_parseresponse, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
