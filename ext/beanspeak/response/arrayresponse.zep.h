
extern zend_class_entry *beanspeak_response_arrayresponse_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Response_ArrayResponse);

PHP_METHOD(Beanspeak_Response_ArrayResponse, __construct);
PHP_METHOD(Beanspeak_Response_ArrayResponse, getResponseName);
PHP_METHOD(Beanspeak_Response_ArrayResponse, __get);
PHP_METHOD(Beanspeak_Response_ArrayResponse, __isset);
void zep_Beanspeak_Response_ArrayResponse_transformPropertyName(int ht, zval *return_value, zval **return_value_ptr, zval *this_ptr, int return_value_used, zval *name_param_ext TSRMLS_DC);

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_response_arrayresponse___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_ARRAY_INFO(0, data, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_response_arrayresponse___get, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_response_arrayresponse___isset, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_response_arrayresponse_transformpropertyname, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(beanspeak_response_arrayresponse_method_entry) {
	PHP_ME(Beanspeak_Response_ArrayResponse, __construct, arginfo_beanspeak_response_arrayresponse___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Beanspeak_Response_ArrayResponse, getResponseName, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Response_ArrayResponse, __get, arginfo_beanspeak_response_arrayresponse___get, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Response_ArrayResponse, __isset, arginfo_beanspeak_response_arrayresponse___isset, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
