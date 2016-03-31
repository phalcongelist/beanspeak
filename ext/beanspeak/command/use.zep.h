
extern zend_class_entry *beanspeak_command_use_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Command_Use);

PHP_METHOD(Beanspeak_Command_Use, __construct);
PHP_METHOD(Beanspeak_Command_Use, getName);
PHP_METHOD(Beanspeak_Command_Use, getCommandLine);
PHP_METHOD(Beanspeak_Command_Use, parseResponse);

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_command_use___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, tube)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_command_use_parseresponse, 0, 0, 1)
	ZEND_ARG_INFO(0, line)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(beanspeak_command_use_method_entry) {
	PHP_ME(Beanspeak_Command_Use, __construct, arginfo_beanspeak_command_use___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Beanspeak_Command_Use, getName, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_Use, getCommandLine, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_Use, parseResponse, arginfo_beanspeak_command_use_parseresponse, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
