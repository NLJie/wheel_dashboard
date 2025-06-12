#define TAG "Cast"
#include "services/CastService.h"
#include "core/Log.h"

CastService::CastService()
    : status(ServiceStatus::UNINITIALIZED), enabled(true), isCasting(false) {}

void CastService::init() {
    OS_LOGI("Init");
    // 初始化投屏模块，加载配置
    status = ServiceStatus::INITIALIZED;
}

void CastService::start() {
    OS_LOGI("Start");
    // 准备投屏资源，如启动接收线程或配置网络
    status = ServiceStatus::RUNNING;
}

void CastService::update() {
    if (!enabled || status != ServiceStatus::RUNNING) return;

    // 检查是否有投屏连接请求，维护投屏状态
    if (!isCasting) {
        OS_LOGD("Waiting for cast connection...");
        // 模拟接收到投屏请求
        isCasting = true;
        OS_LOGI("Casting started");
    } else {
        // 模拟持续投屏
        OS_LOGD("Casting in progress...");
    }
}

void CastService::stop() {
    OS_LOGW("Stop");
    // 停止投屏服务
    if (isCasting) {
        OS_LOGI("Casting stopped");
        isCasting = false;
    }
    status = ServiceStatus::STOPPED;
}

void CastService::deinit() {
    OS_LOGI("Deinit");
    // 清理投屏资源
    status = ServiceStatus::UNINITIALIZED;
}

std::string CastService::getName() const {
    return "CastService";
}

ServiceStatus CastService::getStatus() const {
    return status;
}

void CastService::setEnabled(bool en) {
    enabled = en;
}

bool CastService::isEnabled() const {
    return enabled;
}
