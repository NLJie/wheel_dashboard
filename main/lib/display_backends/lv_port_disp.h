/*
 * Copyright (c) 2022-2024, ArtInChip Technology Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#ifndef LV_PORT_DISP_H
#define LV_PORT_DISP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <linux/fb.h>
#include "lvgl.h"

#ifndef DISP_SHOW_FPS
#define DISP_SHOW_FPS 1
#endif

#ifndef FBDEV_PATH
#define FBDEV_PATH  "/dev/fb0"
#endif

typedef struct {
    int fb;                     // framebuffer设备文件描述符，通常是打开/dev/fbX得到的
    struct fb_var_screeninfo vinfo;  // 帧缓冲可变屏幕信息（分辨率、色深等）
    struct fb_fix_screeninfo finfo;  // 帧缓冲固定屏幕信息（显存起始地址、行长等）

    lv_thread_t thread;         // 用于刷新显示的线程对象（LVGL线程封装）
    lv_thread_sync_t sync;      // 线程同步对象（如互斥锁、条件变量）用于刷新同步
    lv_thread_sync_t sync_notify; // 线程通知同步对象，用于刷新完成通知

    bool exit_status;           // 控制刷新线程退出的标志，true表示退出线程

    bool sync_ready;            // 同步准备就绪标志，表示可开始刷新
    bool flush_act;             // 当前是否正在执行刷新操作的标志

    uint8_t *buf;               // 绘图缓冲区指针，LVGL绘图内容写入此内存
    int fd;                     // 绘图缓冲区对应的文件描述符（如dma-buf或mmap）

    int buf_id;                 // 当前绘图缓冲区ID，用于多缓冲区切换标识

    bool rotate_en;             // 是否启用屏幕旋转功能
    int rotate_degree;          // 屏幕旋转角度，单位为度（如90、180、270）

    uint8_t *buf_mapped;        // 映射到用户空间的缓冲区地址（mmap返回的指针）

    bool double_buf;            // 是否启用双缓冲机制（减少撕裂，提高流畅度）

    int buf_size;               // 绘图缓冲区大小，单位字节
    int fb_size;                // framebuffer总显存大小，单位字节

    int fps;                    // 当前帧率统计，用于性能监控
} aic_disp_t;


void lv_port_disp_init(void);

static inline int fbdev_draw_fps()
{
#if DISP_SHOW_FPS
    lv_display_t *disp = lv_display_get_default();
    aic_disp_t *aic_disp = (aic_disp_t *)lv_display_get_user_data(disp);
    return aic_disp->fps;
#else
    return 0;
#endif
}

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_PORT_DISP_H*/
