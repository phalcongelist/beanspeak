
extern zend_class_entry *beanspeak_command_delete_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Command_Delete);

PHP_METHOD(Beanspeak_Command_Delete, __construct);
PHP_METHOD(Beanspeak_Command_Delete, getName);
PHP_METHOD(Beanspeak_Command_Delete, getCommandLine);
PHP_METHOD(Beanspeak_Command_Delete, parseResponse);

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_command_delete___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, job)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_command_delete_parseresponse, 0, 0, 1)
	ZEND_ARG_INFO(0, line)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(beanspeak_command_delete_method_entry) {
	PHP_ME(Beanspeak_Command_Delete, __construct, arginfo_beanspeak_command_delete___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Beanspeak_Command_Delete, getName, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_Delete, getCommandLine, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command_Delete, parseResponse, arginfo_beanspeak_command_delete_parseresponse, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
