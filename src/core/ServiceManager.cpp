#include "core/ServiceManager.h"
#include "core/Log.h"

#define TAG "ServiceManager"

void ServiceManager::registerService(std::shared_ptr<ServiceBase> service) {
    auto key = std::type_index(typeid(*service));
    services[key] = service;
    // OS_LOGI("Registered service: %s", service->getName().c_str());
}

// void ServiceManager::initAll() {
//     for (auto& [_, service] : services) {
//         if (!service->isEnabled()) continue;
//         service->init();
//     }
// }

void ServiceManager::startService() {
    // 第 1 轮：所有服务 init
    for (auto& [_, service] : services) {
        if (!service->isEnabled()) continue;
        service->init();
    }

    // 第 2 轮：所有服务 start
    for (auto& [_, service] : services) {
        if (!service->isEnabled()) continue;
        service->start();
    }
}

// void ServiceManager::startAll() {
//     for (auto& [_, service] : services) {
//         if (!service->isEnabled()) continue;
//         service->start();
//     }
// }

void ServiceManager::updateAll() {
    for (auto& [_, service] : services) {
        if (!service->isEnabled()) continue;
        service->update();
    }
}

void ServiceManager::stopAll() {
    for (auto& [_, service] : services) {
        if (!service->isEnabled()) continue;
        service->stop();
    }
}

void ServiceManager::deinitAll() {
    for (auto& [_, service] : services) {
        if (!service->isEnabled()) continue;
        service->deinit();
    }
}
