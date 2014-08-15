LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := linear-alloc-fix
LOCAL_SRC_FILES := LinearAllocFix.c

LOCAL_LDLIBS := -ldl -llog

include $(BUILD_SHARED_LIBRARY)