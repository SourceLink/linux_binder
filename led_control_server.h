#ifndef _LED_CONTROL_SERVER_H
#define _LED_CONTROL_SERVER_H


#include "sl_inc/so_core/so_file.h"

#define LED_CONTROL_SERVER_NAME     "led_control_server"

#define LED_CONTROL_ON               1
#define LED_CONTROL_OFF              2

typedef int (*server_handle)(void *arg);

struct register_server {
    unsigned int   code;
    server_handle  fun;
};


struct io_manager {
    struct binder_io *rx;
    struct binder_io *tx;
};

#endif