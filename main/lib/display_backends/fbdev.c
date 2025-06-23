/**
 * @file fbdev.c
 *
 * 传统 framebuffer 设备
 *
 * 基于原始仓库中的文件修改而来
 *
 * 拆分到独立文件
 * 版权所有 © 2025 EDGEMTech Ltd.
 *
 * 作者: EDGEMTech Ltd, Erik Tagirov (erik.tagirov@edgemtech.ch)
 *
 */

/*********************
 *      引入头文件
 *********************/
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lvgl.h"
#if LV_USE_LINUX_FBDEV
#include "../simulator_util.h"
#include "../backends.h"

/*********************
 *      宏定义
 *********************/

/**********************
 *      类型定义
 **********************/

/**********************
 *  静态函数声明
 **********************/

static lv_display_t *init_fbdev(void);
static void run_loop_fbdev(void);

/**********************
 *  静态变量
 **********************/

static char *backend_name = "FBDEV";

/**********************
 *      宏定义
 **********************/

/**********************
 *   全局函数
 **********************/

/**
 * 注册 framebuffer 后端
 *
 * @param backend 后端描述结构体
 * @description 配置后端描述符
 */
int backend_init_fbdev(backend_t *backend)
{
    LV_ASSERT_NULL(backend);

    backend->handle->display = malloc(sizeof(display_backend_t));
    LV_ASSERT_NULL(backend->handle->display);

    backend->handle->display->init_display = init_fbdev;
    backend->handle->display->run_loop = run_loop_fbdev;
    backend->name = backend_name;
    backend->type = BACKEND_DISPLAY;

    return 0;
}

/**********************
 *   静态函数
 **********************/

/**
 * 初始化 framebuffer 驱动
 *
 * @return 返回创建的 LVGL 显示对象
 */
static lv_display_t *init_fbdev(void)
{
    const char *device = getenv_default("LV_LINUX_FBDEV_DEVICE", "/dev/fb0");
    lv_display_t *disp = lv_linux_fbdev_create();

    if (disp == NULL) {
        return NULL;
    }

    lv_linux_fbdev_set_file(disp, device);

    return disp;
}

/**
 * framebuffer 驱动的主循环
 */
static void run_loop_fbdev(void)
{
    uint32_t idle_time;

    /* 处理 LVGL 的任务 */
    while (true) {

        /* 返回下一个定时器任务的延时时间（ms） */
        idle_time = lv_timer_handler();
        usleep(idle_time * 1000);  // 转换为微秒
    }
}

#endif /*LV_USE_LINUX_FBDEV*/
