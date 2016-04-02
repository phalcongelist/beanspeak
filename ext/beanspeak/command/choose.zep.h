
extern zend_class_entry *beanspeak_command_choose_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Command_Choose);

PHP_METHOD(Beanspeak_Command_Choose, __construct);
PHP_METHOD(Beanspeak_Command_Choose, getName);
PHP_METHOD(Beanspeak_Command_Choose, getCommandLine);
PHP_METHOD(Beanspeak_Command_Choose, parseResponse);

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_command_choose___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, tube)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_command_choose_parseresponse, 0, 0, 1)
	ZEND_ARG_INFO(0, line)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(beanspeak_command_choose_method_entry) {
	PHP_ME(Beanspeak_Command_Choose, __construct, arginfo_beanspeak_command_choose___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Beanspeak_Command_Choose, getName, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_Choose, getCommandLine, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_Choose, parseResponse, arginfo_beanspeak_command_choose_parseresponse, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
