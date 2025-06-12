#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>

// 控制是否启用 DEBUG 日志
#define ENABLE_LOG_DEBUG 1

// ANSI颜色定义
#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"

// 获取当前时间字符串（同之前）
inline std::string currentDateTime() {
    auto now = std::chrono::system_clock::now();
    auto t_c = std::chrono::system_clock::to_time_t(now);
    std::tm tm;
#if defined(_WIN32)
    localtime_s(&tm, &t_c);
#else
    localtime_r(&t_c, &tm);
#endif
    char buf[32];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tm);
    return std::string(buf);
}

// 核心带颜色日志宏（自动根据 level 选择颜色）
#define LOG_BASE_COLOR(level, color, tag, msg) \
    std::cout << color << "[" << currentDateTime() << "][" << level << "][" << tag << "] " << msg << COLOR_RESET << std::endl;

// 具体日志等级宏（TAG 必须在当前 cpp 中定义）
#define OS_LOGI(msg) LOG_BASE_COLOR("INFO", COLOR_GREEN, TAG, msg)
#define OS_LOGW(msg) LOG_BASE_COLOR("WARN", COLOR_YELLOW, TAG, msg)
#define OS_LOGE(msg) LOG_BASE_COLOR("ERROR", COLOR_RED, TAG, msg)

#if ENABLE_LOG_DEBUG
#define OS_LOGD(msg) LOG_BASE_COLOR("DEBUG", COLOR_BLUE, TAG, msg)
#else
#define OS_LOGD(msg)
#endif

#endif // LOG_H
