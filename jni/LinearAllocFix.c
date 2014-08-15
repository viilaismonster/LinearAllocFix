#include <pthread.h>
#include "LinearAllocFix.h"
#include <android/log.h>
#include <stdio.h>
#include <sys/mman.h>

#define LOG_TAG "*LinearAllocFix*"
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define MEMORY_MIN 32768

#define TARGET_VAL 5*1024*1024
#define HACK_VAL 8*1024*1024

// copy from https://github.com/android/platform_dalvik/blob/android-2.3.7_r1/vm/LinearAlloc.h#L33
typedef struct LinearAllocHdr {
    int     curOffset;          /* offset where next data goes */
    pthread_mutex_t lock;       /* controls updates to this struct */

    char*   mapAddr;            /* start of mmap()ed region */
    int     mapLength;          /* length of region */
    int     firstOffset;        /* for chasing through */

    short*  writeRefCount;      /* for ENFORCE_READ_ONLY */
} LinearAllocHdr;

int* hdrMapLength = NULL;
struct LinearAllocHdr* hdr = NULL;

jint JNI_OnLoad(JavaVM* vm, void* reserved) {

	void** ptr = (void**)MEMORY_MIN;
	char* line;
	int max = 2*MEMORY_MIN;

	while(max--) {
		if(*ptr == (void*)vm) {
			line = malloc(100*sizeof(char));
			sprintf(line, "find VM %d = %d", ptr, *ptr);
			LOGI(line);
			free(line);
		}
		if(*(int*)ptr == TARGET_VAL) {
			line = malloc(100*sizeof(char));
			sprintf(line, "%d = %d", ptr, *ptr);
			LOGE(line);
			free(line);
			hdrMapLength = (int*)ptr;
			hdr = (void*)(ptr-3);
			break;
		}
		ptr++;
	}

	if(hdr) {
		line = malloc(100*sizeof(char));
		sprintf(line, " hdr->curOffset=%d mapLength=%d firstOffset=%d",
				hdr->curOffset, hdr->mapLength, hdr->firstOffset);
		LOGI(line);
		free(line);
	}

	return JNI_VERSION_1_4;
}

JNIEXPORT jlong JNICALL Java_info_viila_android_linearallocfix_lib_LinearAllocFix_current(
    JNIEnv * env,
    jobject context) {

	if(!hdrMapLength)
		return -1;

	return *hdrMapLength;
}

JNIEXPORT jlong JNICALL Java_info_viila_android_linearallocfix_lib_LinearAllocFix_hack(
    JNIEnv * env,
    jobject context) {

	if(!hdrMapLength)
		return -1;

	pthread_mutex_lock(&hdr->lock);

	*hdrMapLength = HACK_VAL;
	hdr->mapAddr = mmap(NULL, hdr->mapLength, PROT_READ | PROT_WRITE,
	        MAP_PRIVATE | MAP_ANON, -1, 0);

	pthread_mutex_unlock(&hdr->lock);

	return *hdrMapLength;
}


JNIEXPORT jlong JNICALL Java_info_viila_android_linearallocfix_lib_LinearAllocFix_debug(
    JNIEnv * env,
    jobject context,
    jint offset, jint attr) {

	return -1;
}
