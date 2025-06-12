#define TAG "OTA"
#include "services/OtaService.h"
#include "core/Log.h"

OtaService::OtaService()
    : status(ServiceStatus::UNINITIALIZED), enabled(true), updateInProgress(false) {}

void OtaService::init() {
    OS_LOGI("Init");
    // 初始化OTA组件，加载配置
    status = ServiceStatus::INITIALIZED;
}

void OtaService::start() {
    OS_LOGI("Start");
    // 准备OTA任务（可能是监听网络升级信号）
    status = ServiceStatus::RUNNING;
}

void OtaService::update() {
    if (!enabled || status != ServiceStatus::RUNNING) return;

    // 检查是否有可用固件，或处理OTA流程进度
    if (!updateInProgress) {
        OS_LOGD("Checking for OTA update...");
        // 示例触发
        updateInProgress = true;
        // 假设已检测到更新，可开始下载或验证
        OS_LOGI("Firmware update started...");
    }
}

void OtaService::stop() {
    OS_LOGW("Stop");
    // 停止OTA服务任务
    status = ServiceStatus::STOPPED;
}

void OtaService::deinit() {
    OS_LOGI("Deinit");
    // 清理资源
    status = ServiceStatus::UNINITIALIZED;
}

std::string OtaService::getName() const {
    return "OtaService";
}

ServiceStatus OtaService::getStatus() const {
    return status;
}

void OtaService::setEnabled(bool en) {
    enabled = en;
}

bool OtaService::isEnabled() const {
    return enabled;
}
