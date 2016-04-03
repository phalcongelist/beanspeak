
extern zend_class_entry *beanspeak_command_watch_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Command_Watch);

PHP_METHOD(Beanspeak_Command_Watch, __construct);
PHP_METHOD(Beanspeak_Command_Watch, getName);
PHP_METHOD(Beanspeak_Command_Watch, getCommandLine);
PHP_METHOD(Beanspeak_Command_Watch, parseResponse);

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_command_watch___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, tube)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_command_watch_parseresponse, 0, 0, 1)
	ZEND_ARG_INFO(0, line)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(beanspeak_command_watch_method_entry) {
	PHP_ME(Beanspeak_Command_Watch, __construct, arginfo_beanspeak_command_watch___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Beanspeak_Command_Watch, getName, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_Watch, getCommandLine, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_Watch, parseResponse, arginfo_beanspeak_command_watch_parseresponse, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
