
extern zend_class_entry *beanspeak_command_reserve_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Command_Reserve);

PHP_METHOD(Beanspeak_Command_Reserve, __construct);
PHP_METHOD(Beanspeak_Command_Reserve, getName);
PHP_METHOD(Beanspeak_Command_Reserve, getCommandLine);
PHP_METHOD(Beanspeak_Command_Reserve, parseResponse);

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_command_reserve___construct, 0, 0, 0)
	ZEND_ARG_INFO(0, timeout)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_command_reserve_parseresponse, 0, 0, 1)
	ZEND_ARG_INFO(0, line)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(beanspeak_command_reserve_method_entry) {
	PHP_ME(Beanspeak_Command_Reserve, __construct, arginfo_beanspeak_command_reserve___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Beanspeak_Command_Reserve, getName, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_Reserve, getCommandLine, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_Reserve, parseResponse, arginfo_beanspeak_command_reserve_parseresponse, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
