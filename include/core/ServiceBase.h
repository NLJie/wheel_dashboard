#ifndef SERVICE_BASE_H
#define SERVICE_BASE_H

#include <string>

enum class ServiceStatus {
    UNINITIALIZED,
    INITIALIZED,
    RUNNING,
    STOPPED,
    ERROR
};

class ServiceBase {
public:
    virtual ~ServiceBase() {}

    // 生命周期
    virtual void init() = 0;
    virtual void deinit() = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void update() = 0;

    // 控制
    virtual void restart() {
        stop();
        start();
    }

    // 服务信息
    virtual std::string getName() const = 0;
    virtual ServiceStatus getStatus() const = 0;

    // 使能开关
    virtual void setEnabled(bool en) = 0;
    virtual bool isEnabled() const = 0;
};

#endif // SERVICE_BASE_H
