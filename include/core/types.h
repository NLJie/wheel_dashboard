#ifndef CORE_TYPES_H
#define CORE_TYPES_H

#include <cstdint>
#include <string>
#include <chrono>
#include <functional>

namespace core {

// 传感器数据类型
struct SensorData {
    float speed;          // km/h
    float odometer;       // km
    float battery_level;  // 0-100%
    float temperature;    // °C
    uint32_t error_code;  // 错误码
    std::chrono::system_clock::time_point timestamp;
};

// 网络状态
struct NetworkStatus {
    bool connected;
    std::string ip_address;
    int signal_strength;  // dBm
};

// 蓝牙设备信息
struct BluetoothDevice {
    std::string name;
    std::string address;
    int rssi;
    bool connected;
};

// OTA更新状态
enum class OTAStatus {
    IDLE,
    CHECKING,
    DOWNLOADING,
    INSTALLING,
    SUCCESS,
    FAILED
};

// 回调函数类型
using SensorCallback = std::function<void(const SensorData&)>;
using NetworkCallback = std::function<void(const NetworkStatus&)>;
using BluetoothCallback = std::function<void(const BluetoothDevice&)>;
using OTACallback = std::function<void(OTAStatus)>;

} // namespace core

#endif // CORE_TYPES_H