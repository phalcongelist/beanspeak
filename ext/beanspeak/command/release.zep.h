
extern zend_class_entry *beanspeak_command_release_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Command_Release);

PHP_METHOD(Beanspeak_Command_Release, __construct);
PHP_METHOD(Beanspeak_Command_Release, getName);
PHP_METHOD(Beanspeak_Command_Release, getCommandLine);
PHP_METHOD(Beanspeak_Command_Release, parseResponse);

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_command_release___construct, 0, 0, 3)
	ZEND_ARG_INFO(0, job)
	ZEND_ARG_INFO(0, pri)
	ZEND_ARG_INFO(0, delay)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_command_release_parseresponse, 0, 0, 1)
	ZEND_ARG_INFO(0, line)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(beanspeak_command_release_method_entry) {
	PHP_ME(Beanspeak_Command_Release, __construct, arginfo_beanspeak_command_release___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Beanspeak_Command_Release, getName, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_Release, getCommandLine, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_Release, parseResponse, arginfo_beanspeak_command_release_parseresponse, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
