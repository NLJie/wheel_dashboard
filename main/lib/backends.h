/**
 * @file backends.h
 *
 * 设备后端抽象层的接口定义
 *
 * 版权所有 (c) 2025 EDGEMTech Ltd.
 *
 * 作者: EDGEMTech Ltd, Erik Tagirov (erik.tagirov@edgemtech.ch)
 *
 */
#ifndef BACKENDS_H
#define BACKENDS_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      引入头文件
 *********************/

/*********************
 *      宏定义
 *********************/

/**********************
 *      类型定义
 **********************/

/* 显示驱动初始化函数的原型 */
typedef lv_display_t *(*display_init_t)(void);

/* 主循环函数的原型 */
typedef void (*run_loop_t)(void);

/* 表示一个显示驱动的句柄 */
typedef struct {
    display_init_t init_display; /* 创建/初始化显示的函数 */
    run_loop_t run_loop;         /* 驱动句柄的主循环函数 */
    lv_display_t *display;       /* 已创建的 LVGL 显示对象 */
} display_backend_t;

/* 输入设备驱动初始化函数的原型 */
typedef lv_indev_t *(*indev_init_t)(lv_display_t *display);

/* 表示一个输入设备驱动后端 */
typedef struct {
    indev_init_t init_indev; /* 初始化输入设备的函数 */
} indev_backend_t;

/* 将所有类型的驱动后端统一封装 */
typedef union {
    display_backend_t *display; /* 显示设备后端 */
    indev_backend_t *indev;     /* 输入设备后端 */
} backend_handle_t;

/* 定义驱动后端的类型 */
typedef enum {
    BACKEND_DISPLAY, /* 显示后端 */
    BACKEND_INDEV    /* 输入设备后端 */
} backend_type_t;

/* 驱动后端描述结构体 */
typedef struct {
    backend_handle_t *handle; /* 后端驱动的句柄（显示或输入） */
    char *name;               /* 后端名称 */
    backend_type_t type;      /* 后端类型（显示或输入） */
} backend_t;

/* 用于注册后端的函数原型 */
typedef int (*backend_init_t)(backend_t *);

/**********************
 * 全局函数声明
 **********************/

/* 图形显示后端初始化函数 */
int backend_init_fbdev(backend_t *backend);   /* Linux framebuffer */
int backend_init_aic_fbdev(backend_t *backend);   /* Linux framebuffer */
int backend_init_drm(backend_t *backend);     /* Linux DRM */
int backend_init_sdl(backend_t *backend);     /* SDL */
int backend_init_glfw3(backend_t *backend);   /* OpenGL GLFW3 */
int backend_init_wayland(backend_t *backend); /* Wayland */
int backend_init_x11(backend_t *backend);     /* X11 */

/* 输入设备后端初始化函数 */
int backend_init_evdev(backend_t *backend);   /* Linux evdev 输入事件接口 */

/**********************
 *      宏定义
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* BACKENDS_H */
