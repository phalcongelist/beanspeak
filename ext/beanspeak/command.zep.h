
extern zend_class_entry *beanspeak_command_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Command);

PHP_METHOD(Beanspeak_Command, hasData);
PHP_METHOD(Beanspeak_Command, getData);
PHP_METHOD(Beanspeak_Command, getDataLength);
PHP_METHOD(Beanspeak_Command, getResponseParser);
PHP_METHOD(Beanspeak_Command, createResponse);
PHP_METHOD(Beanspeak_Command, __toString);

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_command_createresponse, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_ARRAY_INFO(0, data, 1)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(beanspeak_command_method_entry) {
	PHP_ME(Beanspeak_Command, hasData, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command, getData, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command, getDataLength, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command, getResponseParser, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Command, createResponse, arginfo_beanspeak_command_createresponse, ZEND_ACC_PROTECTED)
	PHP_ME(Beanspeak_Command, __toString, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
