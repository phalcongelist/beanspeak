
extern zend_class_entry *beanspeak_response_arrayresponse_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Response_ArrayResponse);

PHP_METHOD(Beanspeak_Response_ArrayResponse, __construct);
PHP_METHOD(Beanspeak_Response_ArrayResponse, getResponseName);

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_response_arrayresponse___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_ARRAY_INFO(0, data, 1)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(beanspeak_response_arrayresponse_method_entry) {
	PHP_ME(Beanspeak_Response_ArrayResponse, __construct, arginfo_beanspeak_response_arrayresponse___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Beanspeak_Response_ArrayResponse, getResponseName, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
