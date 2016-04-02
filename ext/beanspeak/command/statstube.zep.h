
extern zend_class_entry *beanspeak_command_statstube_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Command_StatsTube);

PHP_METHOD(Beanspeak_Command_StatsTube, __construct);
PHP_METHOD(Beanspeak_Command_StatsTube, getName);
PHP_METHOD(Beanspeak_Command_StatsTube, getCommandLine);
PHP_METHOD(Beanspeak_Command_StatsTube, getResponseParser);

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_command_statstube___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, tube)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(beanspeak_command_statstube_method_entry) {
	PHP_ME(Beanspeak_Command_StatsTube, __construct, arginfo_beanspeak_command_statstube___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Beanspeak_Command_StatsTube, getName, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_StatsTube, getCommandLine, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_StatsTube, getResponseParser, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
