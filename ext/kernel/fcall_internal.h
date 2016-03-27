#ifndef ZEPHIR_KERNEL_FCALL_INTERNAL_H
#define ZEPHIR_KERNEL_FCALL_INTERNAL_H
	#define ZEPHIR_CALL_INTERNAL_METHOD_P1(return_value_ptr, object, method, p0) \
		do { \
			ZEPHIR_BACKUP_SCOPE() \
			ZEPHIR_BACKUP_THIS_PTR() \
			ZEPHIR_SET_THIS(object); \
			ZEPHIR_SET_SCOPE((Z_TYPE_P(object) == IS_OBJECT ? Z_OBJCE_P(object) : NULL), (Z_TYPE_P(object) == IS_OBJECT ? Z_OBJCE_P(object) : NULL)); \
			ZEPHIR_INIT_NVAR(*(return_value_ptr)); \
			Z_ADDREF_P(p0); \
			method(0, *return_value_ptr, return_value_ptr, object, 1, p0 TSRMLS_CC); \
			Z_DELREF_P(p0); \
			ZEPHIR_LAST_CALL_STATUS = EG(exception) ? FAILURE : SUCCESS; \
			ZEPHIR_RESTORE_THIS_PTR(); \
			ZEPHIR_RESTORE_SCOPE(); \
		} while (0)
	
#endif
