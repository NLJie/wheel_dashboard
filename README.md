# 轮车仪表功能框架


# 一、核心功能模块

1. **驾驶信息显示**  
   - **车速与里程**：实时显示当前车速及累计/单次里程，支持多模式切换（如经济/运动模式）。  
   - **转速与档位**：显示发动机转速（燃油车）或电机转速（电动车），部分车型配备档位指示。  
   - **导航集成**：高级仪表可集成导航信息，支持路线投屏或语音提示。

# 二、SDK 软件服务

功能服务包括：UiService、NetworkService、SensorService、BluetoothService、CastService、OTAService

## 显示服务：UiService

- 显示GUI框架LVGL;
- 支持显示车速、里程、报警信息等;

## 传感器服务: SensorService

- 车速、电量、燃油、压力、温度

## 网络服务: NetworkService

- WIFI 管理
- MQTT 协议栈
- HTTP 协议栈

## 蓝牙服务: BluetoothService

- 蓝牙管理

## 投屏服务: CastService

- 投屏管理

## OTA服务: OTAService

- OTA 方法

# 三、SDK 使用方法

mkdir build && cd build && cmake ..
make

wheel_meter_display/
├── CMakeLists.txt
├── include/
│   ├── services/
│   │   ├── ui_service.h
│   │   ├── network_service.h
│   │   ├── sensor_service.h
│   │   ├── bluetooth_service.h
│   │   ├── cast_service.h
│   │   └── ota_service.h
│   └── core/
│       ├── service_manager.h
│       └── types.h
├── src/
│   ├── services/
│   │   ├── ui_service.cpp
│   │   ├── network_service.cpp
│   │   ├── sensor_service.cpp
│   │   ├── bluetooth_service.cpp
│   │   ├── cast_service.cpp
│   │   └── ota_service.cpp
│   └── core/
│       └── service_manager.cpp
└── apps/
    └── main.cpp