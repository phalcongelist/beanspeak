
extern zend_class_entry *beanspeak_command_bury_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Command_Bury);

PHP_METHOD(Beanspeak_Command_Bury, __construct);
PHP_METHOD(Beanspeak_Command_Bury, getName);
PHP_METHOD(Beanspeak_Command_Bury, getCommandLine);
PHP_METHOD(Beanspeak_Command_Bury, parseResponse);

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_command_bury___construct, 0, 0, 2)
	ZEND_ARG_INFO(0, job)
	ZEND_ARG_INFO(0, priority)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_command_bury_parseresponse, 0, 0, 1)
	ZEND_ARG_INFO(0, line)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(beanspeak_command_bury_method_entry) {
	PHP_ME(Beanspeak_Command_Bury, __construct, arginfo_beanspeak_command_bury___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Beanspeak_Command_Bury, getName, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_Bury, getCommandLine, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_Bury, parseResponse, arginfo_beanspeak_command_bury_parseresponse, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
