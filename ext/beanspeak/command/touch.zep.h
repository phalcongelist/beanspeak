
extern zend_class_entry *beanspeak_command_touch_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Command_Touch);

PHP_METHOD(Beanspeak_Command_Touch, __construct);
PHP_METHOD(Beanspeak_Command_Touch, getName);
PHP_METHOD(Beanspeak_Command_Touch, getCommandLine);
PHP_METHOD(Beanspeak_Command_Touch, parseResponse);

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_command_touch___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, job)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_command_touch_parseresponse, 0, 0, 1)
	ZEND_ARG_INFO(0, line)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(beanspeak_command_touch_method_entry) {
	PHP_ME(Beanspeak_Command_Touch, __construct, arginfo_beanspeak_command_touch___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Beanspeak_Command_Touch, getName, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_Touch, getCommandLine, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_Touch, parseResponse, arginfo_beanspeak_command_touch_parseresponse, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
