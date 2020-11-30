#ifndef LEDDEV_H
#define LEDDEV_H

#include <linux/ioctl.h>

#define MAJOR_NUM 100
#define DEVICE_NAME "ioctl_led_hawkboard"

#define IOCTL_SET_MSG _IOR(MAJOR_NUM, 0, char *)
#define IOCTL_GET_MSG _IOW(MAJOR_NUM, 1, char *)

#endif
