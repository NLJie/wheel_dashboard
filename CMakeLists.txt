cmake_minimum_required(VERSION 3.10)

project(WheelMeterDisplay 
        VERSION 1.0.0 
        LANGUAGES 
        C 
        CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加可执行文件
add_executable(wheel_meter_display)

# 包含目录
target_include_directories(wheel_meter_display PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

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
    main.cpp
)

# 查找依赖库 (根据实际需要添加)
find_package(Threads REQUIRED)
target_link_libraries(wheel_meter_display PRIVATE Threads::Threads)

# 安装目标
install(TARGETS wheel_meter_display
    RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/usr/bin
)
