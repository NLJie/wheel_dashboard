cmake_minimum_required(VERSION 3.10)

project(WheelMeterDisplay 
        VERSION 1.0.0 
        LANGUAGES 
        C 
        CXX)

# 设置C++标准
# set(BUILD_ROOT_DIR "$ENV{PROJECT_ROOT}/build")


# C++标准设置（推荐方式）
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS_RELEASE "-Wall -O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O3 -DNDEBUG")

include(scripts/common_config.cmake)

# set(LV_USE_KCONFIG ON CACHE BOOL "Enable Kconfig support")

# set(LV_BUILD_USE_KCONFIG ON CACHE BOOL "Enable Kconfig support")

if (LV_USE_LINUX_FBDEV)
    list(APPEND LV_LINUX_BACKEND_SRC main/lib/display_backends/fbdev.c)
    message("${GY}==========> Including FBDEV support${E}")
endif()

# if (LV_USE_EVDEV)
#     message("${GY}==========> Including EVDEV support${E}")
#     list(APPEND LV_LINUX_BACKEND_SRC main/lib/indev_backends/evdev.c)
# endif()

# 设置 LVGL 库路径
add_subdirectory(src/lvgl)

# 添加可执行文件
add_executable(wheel_meter_display)

# 包含目录
target_include_directories(wheel_meter_display PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/main/lib
)

file(GLOB LV_LINUX_SRC main/lib/*.c)

# 源文件
target_sources(wheel_meter_display PRIVATE
    # 核心文件
    src/core/ServiceManager.cpp
    
    # 服务实现
    src/services/UiService.cpp
    src/services/WifiService.cpp
    src/services/SensorService.cpp
    src/services/BluetoothService.cpp
    src/services/OtaService.cpp
    src/services/CastService.cpp

    # 主程序
    main/main.cpp

    main/lib/driver_backends.c
    main/lib/mouse_cursor_icon.c
    main/lib/simulator_util.c
    main/lib/display_backends/fbdev.c
    main/lib/display_backends/aic_fbdev.c
    main/lib/indev_backends/evdev.c
)

# 查找依赖库 (根据实际需要添加)
find_package(Threads REQUIRED)

target_link_libraries(wheel_meter_display PRIVATE 
                    Threads::Threads 
                    lvgl)

# 安装目标
install(TARGETS wheel_meter_display
    RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/usr/bin
)
