
extern zend_class_entry *beanspeak_response_responseinterface_ce;

ZEPHIR_INIT_CLASS(Beanspeak_Response_ResponseInterface);

ZEPHIR_INIT_FUNCS(beanspeak_response_responseinterface_method_entry) {
	PHP_ABSTRACT_ME(Beanspeak_Response_ResponseInterface, getName, NULL)
	PHP_FE_END
};
