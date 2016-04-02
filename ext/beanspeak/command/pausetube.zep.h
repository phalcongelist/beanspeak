
extern zend_class_entry *beanspeak_command_pausetube_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Command_PauseTube);

PHP_METHOD(Beanspeak_Command_PauseTube, __construct);
PHP_METHOD(Beanspeak_Command_PauseTube, getName);
PHP_METHOD(Beanspeak_Command_PauseTube, getCommandLine);
PHP_METHOD(Beanspeak_Command_PauseTube, parseResponse);

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_command_pausetube___construct, 0, 0, 2)
	ZEND_ARG_INFO(0, tube)
	ZEND_ARG_INFO(0, delay)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_command_pausetube_parseresponse, 0, 0, 1)
	ZEND_ARG_INFO(0, line)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(beanspeak_command_pausetube_method_entry) {
	PHP_ME(Beanspeak_Command_PauseTube, __construct, arginfo_beanspeak_command_pausetube___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Beanspeak_Command_PauseTube, getName, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_PauseTube, getCommandLine, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_PauseTube, parseResponse, arginfo_beanspeak_command_pausetube_parseresponse, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
