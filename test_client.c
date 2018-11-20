/* Copyright 2008 The Android Open Source Project
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <linux/types.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <private/android_filesystem_config.h>

#include "binder.h"
#include "led_control_server.h"

#if 1
#define ALOGI(x...) fprintf(stderr, "test_client: " x)
#define ALOGE(x...) fprintf(stderr, "test_client: " x)
#else
#define ALOGI(x...) 
#define ALOGE(x...) 
#endif

uint32_t svcmgr_lookup(struct binder_state *bs, uint32_t target, const char *name)
{
    uint32_t handle;
    unsigned iodata[512/4];
    struct binder_io msg, reply;

    bio_init(&msg, iodata, sizeof(iodata), 4);
    bio_put_uint32(&msg, 0);  // strict mode header
    bio_put_string16_x(&msg, SVC_MGR_NAME);
    bio_put_string16_x(&msg, name);

    if (binder_call(bs, &msg, &reply, target, SVC_MGR_GET_SERVICE))
        return 0;

    handle = bio_get_ref(&reply);

    if (handle)
        binder_acquire(bs, handle);

    binder_done(bs, &msg, &reply);

    return handle;
}


int interface_led_on(struct binder_state *bs, unsigned int handle, unsigned char led_enum)
{
    unsigned iodata[512/4];
    struct binder_io msg, reply;
    int ret = -1;
	int exception;

    bio_init(&msg, iodata, sizeof(iodata), 4);
    bio_put_uint32(&msg, 0);  // strict mode header
    bio_put_uint32(&msg, led_enum);

    if (binder_call(bs, &msg, &reply, handle, LED_CONTROL_ON))
        return ret;
    
    exception = bio_get_uint32(&reply);
	if (exception == 0)
		ret = bio_get_uint32(&reply);

    binder_done(bs, &msg, &reply);

    return ret;
}

int interface_led_off(struct binder_state *bs, unsigned int handle, unsigned char led_enum)
{
    unsigned iodata[512/4];
    struct binder_io msg, reply;
    int ret = -1;
	int exception;

    bio_init(&msg, iodata, sizeof(iodata), 4);
    bio_put_uint32(&msg, 0);  // strict mode header
    bio_put_uint32(&msg, led_enum);

    if (binder_call(bs, &msg, &reply, handle, LED_CONTROL_OFF))
        return ret;

    exception = bio_get_uint32(&reply);
    ALOGE("exception = %d\n", exception);
	if (exception == 0)
		ret = bio_get_uint32(&reply);

    binder_done(bs, &msg, &reply);

    return ret;
}

int main(int argc, char **argv)
{
    struct binder_state *bs;
    uint32_t svcmgr = BINDER_SERVICE_MANAGER;
	unsigned int g_led_control_handle;

	if (argc < 3) {
        ALOGE("Usage:\n");
        ALOGE("%s led <on|off>\n", argv[0]);
        return -1;
	}

    bs = binder_open(128*1024);
    if (!bs) {
        ALOGE("failed to open binder driver\n");
        return -1;
    }

	g_led_control_handle = svcmgr_lookup(bs, svcmgr, LED_CONTROL_SERVER_NAME);
	if (!g_led_control_handle) {
        ALOGE( "failed to get led control service\n");
        return -1;
	}

	ALOGI("Handle for led control service = %d\n", g_led_control_handle);

    struct timespec time_start , time_end;

	if (!strcmp(argv[1], "led"))
	{
        clock_gettime(CLOCK_REALTIME, &time_start);  // 获取当前时间
        ALOGI("start time %lus, %luns\n", time_start.tv_sec, time_start.tv_nsec);
		if (!strcmp(argv[2], "on")) {
			if (interface_led_on(bs, g_led_control_handle, 2) == 0) {
              ALOGI("led was on\n");  
            }
		} else if (!strcmp(argv[2], "off")) {
			if (interface_led_off(bs, g_led_control_handle, 2) == 0) {
                ALOGI("led was off\n"); 
            }
		}
        clock_gettime(CLOCK_REALTIME, &time_end);  // 上一条打印语句执行之后，获取当前时间
        ALOGI("end time %lus, %luns\n", time_end.tv_sec, time_end.tv_nsec);
	}

    // 计算出一条打印语句的运行时间
    ALOGI("duration: %lus %luns\n", time_end.tv_sec - time_start.tv_sec, time_end.tv_nsec - time_start.tv_nsec);

	binder_release(bs, g_led_control_handle);

    return 0;
}
