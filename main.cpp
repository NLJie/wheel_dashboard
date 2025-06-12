#include <memory>
#include <unistd.h>

#include "core/ServiceManager.h"
#include "services/UiService.h"
#include "services/SensorService.h"
#include "services/BluetoothService.h"
#include "services/WifiService.h"
#include "services/OtaService.h"
#include "services/CastService.h"

int main() {
    ServiceManager manager;

    // 注册服务
    manager.registerService(std::make_shared<UiService>(manager));      // 1
    manager.registerService(std::make_shared<SensorService>());         // 2
    // manager.registerService(std::make_shared<BluetoothService>());      // 3
    // manager.registerService(std::make_shared<WifiService>());           // 4
    // manager.registerService(std::make_shared<OtaService>());            // 5
    // manager.registerService(std::make_shared<CastService>());           // 6

    // 初始化并启动服务
    manager.startService();
    // manager.initAll();
    // manager.startAll();

    // 模拟主循环
    while (true) {
        manager.updateAll();
        // sleep(1);
        usleep(200000);
        // sleep(100ms)... etc.
    }

    // 停止服务
    manager.stopAll();
    manager.deinitAll();

    return 0;
}
