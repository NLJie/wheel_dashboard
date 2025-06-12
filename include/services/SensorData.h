#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

enum class GearPosition {
    PARK,
    REVERSE,
    NEUTRAL,
    DRIVE,
    LOW,
    UNKNOWN
};

struct SensorData {
    float speed_kmh;        // 速度 km/h
    float trip_km;          // 小计里程 km
    float battery_percent;  // 电量 %
    float fuel_percent;     // 油量 %
    float temperature_c;    // 温度 °C
    int light_level;        // 感光等级（0-100）

    // 新增字段
    GearPosition gear;      // 当前挡位
    bool left_turn_signal;  // 左转向灯
    bool right_turn_signal; // 右转向灯
    bool position_lamp;     // 示宽灯（小灯）
    bool high_beam;         // 远光灯
    bool low_beam;          // 近光灯
    bool engine_fault;      // 发动机故障灯
    bool fuel_warning;      // 油量警告灯
    bool neutral;           // 是否空挡
    bool abs_warning;       // ABS 状态灯
    int engine_rpm;         // 发动机转速 RPM

    SensorData()
        : speed_kmh(0), trip_km(0), battery_percent(100), fuel_percent(100),
          temperature_c(25), light_level(50), gear(GearPosition::PARK),
          left_turn_signal(false), right_turn_signal(false), position_lamp(false),
          high_beam(false), low_beam(false), engine_fault(false), fuel_warning(false),
          neutral(true), abs_warning(false), engine_rpm(0) {}
};

#endif // SENSOR_DATA_H
