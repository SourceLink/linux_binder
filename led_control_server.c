#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <linux/types.h>
#include <stdbool.h>
#include <string.h>

#include <private/android_filesystem_config.h>

#include "binder.h"
#include "led_control_server.h"


#if 1
#define ALOGI(x...) fprintf(stderr, "led_control_server: " x)
#define ALOGE(x...) fprintf(stderr, "led_control_server: " x)
#else
#define ALOGI(x...) 
#define ALOGE(x...) 
#endif


int svcmgr_publish(struct binder_state *bs, uint32_t target, const char *name, void *ptr)
{
    int status;
    unsigned iodata[512/4];
    struct binder_io msg, reply;

    bio_init(&msg, iodata, sizeof(iodata), 4);
    bio_put_uint32(&msg, 0);  // strict mode header
    bio_put_string16_x(&msg, SVC_MGR_NAME);
    bio_put_string16_x(&msg, name);
    bio_put_obj(&msg, ptr);

    if (binder_call(bs, &msg, &reply, target, SVC_MGR_ADD_SERVICE))
        return -1;

    status = bio_get_uint32(&reply);

    binder_done(bs, &msg, &reply);

    return status;
}

static int led_on(void *arg)
{
    int ret = -1;
    char buf[256];
    struct io_manager *manager = (struct io_manager*)arg;

    unsigned int led_num = bio_get_uint32(manager->rx);
    ALOGI("led(%d) will on \n", led_num);

    sprintf(buf, "/sys/class/leds/LED%d/brightness", led_num);
    ret = write_intvalue_to_file(buf, 0);

    ret = (ret != 0 && ret != -1) ? 0 : -1;

    bio_put_uint32(manager->tx, 0);     /* 发送头帧 */
    bio_put_uint32(manager->tx, ret);

    return ret;
}


static int led_off(void *arg)
{
    int ret = -1;
    char buf[256];

    struct io_manager *manager = (struct io_manager*)arg;

    unsigned int led_num = bio_get_uint32(manager->rx);
    ALOGI("led(%d) will off\n", led_num);

    sprintf(buf, "/sys/class/leds/LED%d/brightness", led_num);
    ret = write_intvalue_to_file(buf, 1);
 
    ret = (ret != 0 && ret != -1) ? 0 : -1;

    bio_put_uint32(manager->tx, 0);     /* 发送头帧 */
    bio_put_uint32(manager->tx, ret);

    return ret;
}

static int led_control_server_handler(struct binder_state *bs,
                   struct binder_transaction_data *txn,
                   struct binder_io *msg,
                   struct binder_io *reply)
{
    unsigned int tmp_code = txn->code;
    unsigned int strict_policy = bio_get_uint32(msg);  /* msg 帧头 */
    struct register_server *prs = (struct register_server*)(txn->target.ptr);

    struct io_manager manager = {
        .rx = msg,
        .tx = reply
    };

    /* 更改为链表 */
    while (prs) {
        if(prs->code == tmp_code) {
            if (prs->fun != NULL) {
                prs->fun(&manager);
            }
            break;
        }
        prs++;
    }
    return 0;
}


int main(int argc, char **argv) 
{
    struct binder_state *bs;
    uint32_t svcmgr = BINDER_SERVICE_MANAGER;

	int ret;

    struct register_server  led_control[3] = {
        [0] = {
            .code = 1,
            .fun = led_on
        } , 
        [1] = {
            .code = 2,
            .fun = led_off
        }
    };

    /* 初始化binder组件 */
    bs = binder_open(128*1024);
    if (!bs) {
        ALOGE("failed to open binder driver\n");
        return -1;
    }

    /* add service */
	ret = svcmgr_publish(bs, svcmgr, LED_CONTROL_SERVER_NAME, led_control);

    if (ret) {
        ALOGE("failed to publish %s service\n", LED_CONTROL_SERVER_NAME);
        return -1;
    }

	binder_set_maxthreads(bs, 10);

    binder_loop(bs, led_control_server_handler);

    return 0;
}