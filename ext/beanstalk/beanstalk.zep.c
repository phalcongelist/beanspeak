
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/fcall.h"
#include "kernel/object.h"


ZEPHIR_INIT_CLASS(Beanstalk_Beanstalk) {

	ZEPHIR_REGISTER_CLASS(Beanstalk, Beanstalk, beanstalk, beanstalk, beanstalk_beanstalk_method_entry, 0);

	zend_declare_property_null(beanstalk_beanstalk_ce, SL("connection"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_class_implements(beanstalk_beanstalk_ce TSRMLS_CC, 1, beanstalk_beanstalkinterface_ce);
	return SUCCESS;

}

PHP_METHOD(Beanstalk_Beanstalk, __construct) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *connection = NULL, *_0 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &connection);

	if (!connection) {
		ZEPHIR_CPY_WRT(connection, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(connection);
	}


	ZEPHIR_INIT_VAR(_0);
	if (!(zephir_is_true(connection))) {
		ZEPHIR_INIT_NVAR(_0);
		object_init_ex(_0, beanstalk_connection_ce);
		ZEPHIR_CALL_METHOD(NULL, _0, "__construct", NULL, 1);
		zephir_check_call_status();
	} else {
		ZEPHIR_CPY_WRT(_0, connection);
	}
	ZEPHIR_CPY_WRT(connection, _0);
	zephir_update_property_this(this_ptr, SL("connection"), connection TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

