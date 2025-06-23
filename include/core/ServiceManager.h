#ifndef SERVICE_MANAGER_H
#define SERVICE_MANAGER_H

#include <memory>
#include <unordered_map>
#include <typeindex>
#include <typeinfo>
#include <string>
#include <vector>
#include "core/ServiceBase.h"

class ServiceManager {
public:
    // 注册服务
    void registerService(std::shared_ptr<ServiceBase> service);

    // 模板函数：获取指定类型的服务
    template<typename T>
    std::shared_ptr<T> getService();

    // 初始化所有服务
    void initAll();

    // 启动所有服务
    void startAll();

    // 停止所有服务
    void stopAll();

    // 释放所有服务
    void deinitAll();

    // 更新所有服务（调用每个服务的 update()）
    void updateAll();

private:
    std::unordered_map<std::type_index, std::shared_ptr<ServiceBase>> services;
};

// 模板函数必须定义在头文件
template<typename T>
std::shared_ptr<T> ServiceManager::getService() {
    auto it = services.find(std::type_index(typeid(T)));
    if (it != services.end()) {
        return std::dynamic_pointer_cast<T>(it->second);
    }
    return nullptr;
}

#endif // SERVICE_MANAGER_H
