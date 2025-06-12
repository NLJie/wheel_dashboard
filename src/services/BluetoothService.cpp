#include "services/BluetoothService.h"
#include "core/Log.h"
#include <iostream>

#define TAG "Bluetooth"

BluetoothService::BluetoothService()
    : status(ServiceStatus::UNINITIALIZED), enabled(true) {}

void BluetoothService::init() {
    OS_LOGI("Init");
    status = ServiceStatus::INITIALIZED;
}

void BluetoothService::start() {
    OS_LOGI("Start");
    status = ServiceStatus::RUNNING;
}

void BluetoothService::update() {
    if (!enabled || status != ServiceStatus::RUNNING) 
        return;
    
    OS_LOGD("Updating...");
}

void BluetoothService::stop() {
    OS_LOGD("Stop");
    status = ServiceStatus::STOPPED;
}

void BluetoothService::deinit() {
    OS_LOGD("Deinit");
    status = ServiceStatus::UNINITIALIZED;
}

std::string BluetoothService::getName() const {
    return "BluetoothService";
}

ServiceStatus BluetoothService::getStatus() const {
    return status;
}

void BluetoothService::setEnabled(bool en) {
    enabled = en;
}

bool BluetoothService::isEnabled() const {
    return enabled;
}
