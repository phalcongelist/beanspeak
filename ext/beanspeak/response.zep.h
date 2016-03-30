
extern zend_class_entry *beanspeak_response_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Response);

PHP_METHOD(Beanspeak_Response, __construct);
PHP_METHOD(Beanspeak_Response, getRawContent);
PHP_METHOD(Beanspeak_Response, getRawData);
PHP_METHOD(Beanspeak_Response, parseData);
PHP_METHOD(Beanspeak_Response, checkStatusMessage);
static zend_object_value zephir_init_properties_Beanspeak_Response(zend_class_entry *class_type TSRMLS_DC);

ZEND_BEGIN_ARG_INFO_EX(arginfo_beanspeak_response___construct, 0, 0, 2)
	ZEND_ARG_OBJ_INFO(0, command, Beanspeak\\Command\\CommandInterface, 0)
	ZEND_ARG_OBJ_INFO(0, connection, Beanspeak\\Connection\\ConnectionInterface, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(beanspeak_response_method_entry) {
	PHP_ME(Beanspeak_Response, __construct, arginfo_beanspeak_response___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Beanspeak_Response, getRawContent, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Response, getRawData, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Beanspeak_Response, parseData, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(Beanspeak_Response, checkStatusMessage, NULL, ZEND_ACC_PROTECTED)
	PHP_FE_END
};
