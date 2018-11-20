LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CFLAGS += -DBINDER_IPC_32BIT=1
 
LOCAL_SRC_FILES:= service_manager.c binder.c

LOCAL_C_INCLUDES += system/core/include/cutils

LOCAL_MODULE:= service_manager_my

include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)

LOCAL_CFLAGS += -DBINDER_IPC_32BIT=1

LOCAL_SRC_FILES:= test_server.c binder.c

LOCAL_C_INCLUDES += system/core/include/cutils

LOCAL_MODULE:= test_server

include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)

LOCAL_CFLAGS += -DBINDER_IPC_32BIT=1

LOCAL_SRC_FILES:= test_client.c binder.c

LOCAL_C_INCLUDES += system/core/include/cutils

LOCAL_MODULE:= test_client

include $(BUILD_EXECUTABLE)
