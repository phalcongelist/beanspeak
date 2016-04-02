
extern zend_class_entry *beanspeak_command_peek_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Command_Peek);

PHP_METHOD(Beanspeak_Command_Peek, __construct);
PHP_METHOD(Beanspeak_Command_Peek, getName);
PHP_METHOD(Beanspeak_Command_Peek, getCommandLine);
PHP_METHOD(Beanspeak_Command_Peek, parseResponse);

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_command_peek___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, subject)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_command_peek_parseresponse, 0, 0, 1)
	ZEND_ARG_INFO(0, line)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(beanspeak_command_peek_method_entry) {
	PHP_ME(Beanspeak_Command_Peek, __construct, arginfo_beanspeak_command_peek___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Beanspeak_Command_Peek, getName, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_Peek, getCommandLine, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_Peek, parseResponse, arginfo_beanspeak_command_peek_parseresponse, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
