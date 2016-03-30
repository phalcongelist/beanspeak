
extern zend_class_entry *beanspeak_command_put_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Command_Put);

PHP_METHOD(Beanspeak_Command_Put, __construct);
PHP_METHOD(Beanspeak_Command_Put, getCommandLine);
PHP_METHOD(Beanspeak_Command_Put, hasData);
PHP_METHOD(Beanspeak_Command_Put, getData);
PHP_METHOD(Beanspeak_Command_Put, getDataLength);
PHP_METHOD(Beanspeak_Command_Put, parseResponse);

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_command_put___construct, 0, 0, 4)
	ZEND_ARG_INFO(0, data)
	ZEND_ARG_INFO(0, priority)
	ZEND_ARG_INFO(0, delay)
	ZEND_ARG_INFO(0, ttr)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_command_put_parseresponse, 0, 0, 1)
	ZEND_ARG_INFO(0, line)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(beanspeak_command_put_method_entry) {
	PHP_ME(Beanspeak_Command_Put, __construct, arginfo_beanspeak_command_put___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Beanspeak_Command_Put, getCommandLine, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_Put, hasData, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_Put, getData, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_Put, getDataLength, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_Put, parseResponse, arginfo_beanspeak_command_put_parseresponse, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
