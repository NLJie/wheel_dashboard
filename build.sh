#!/bin/bash

set -e

CONFIG_DIR="config"
CONFIG_FILE=".config"
KCONFIG_FILE="main/Kconfig"

export PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
TOOLCHAIN_FILE="$PROJECT_ROOT/tools/toolchains/gcc-riscv64.cmake"

# 确保 config 目录存在
mkdir -p "$CONFIG_DIR"

function show_usage() {
    echo "Usage:"
    echo "  $0 config           # 载入 config/defconfig_name 作为当前配置"
    echo "  $0 menuconfig       # 进入menuconfig界面编辑配置"
    echo "  $0 savedefconfig    # 保存当前配置为 config/defconfig_name"
    echo "  $0 full_clean       # 清除工程"
}

function load_config() {
    local config_files=($CONFIG_DIR/*_defconfig)

    if [ ${#config_files[@]} -eq 0 ]; then
        echo "Error: no defconfig files found in $CONFIG_DIR."
        exit 1
    fi

    echo "Available configuration files:"
    local i=1
    for file in "${config_files[@]}"; do
        echo "  [$i] $(basename "$file")"
        ((i++))
    done

    read -p "Select a configuration to load [1-${#config_files[@]}]: " index
    if [[ $index -lt 1 || $index -gt ${#config_files[@]} ]]; then
        echo "Invalid selection."
        exit 1
    fi

    local selected_file="${config_files[$((index-1))]}"
    echo "Loading config from $selected_file ..."
    cp "$selected_file" "$CONFIG_FILE"
}


function run_menuconfig() {
    if [ ! -f "$CONFIG_FILE" ]; then
        echo "No existing config found, creating default config ..."
        # 可以自动生成默认配置，若有需要
        # 这里简单touch空文件，实际可调用 kconfig-mconf --defconfig
        touch "$CONFIG_FILE"
    fi
    KCONFIG_CONFIG="$CONFIG_FILE" kconfig-mconf "$KCONFIG_FILE"
}

function run_full_clean() {
    if [ ! -f "$CONFIG_FILE" ]; then
        echo "No existing config found, no need to clear ..."
    else
        echo "Cleaning config and build artifacts..."
    fi

    rm -f .config .config.old        # -f 防止文件不存在时报错
    rm -rf build                    # -rf 删除目录且不报错

    echo "Clean done."
}


function save_defconfig() {
    local name=$1
    local defconfig_path="$CONFIG_DIR/${name}_defconfig"
    if [ ! -f "$CONFIG_FILE" ]; then
        echo "Error: no .config file found. Please run menuconfig first."
        exit 1
    fi

    echo "Saving defconfig to $defconfig_path ..."
    scripts/kconfig/defconfig.sh "$CONFIG_FILE" "$defconfig_path"
}


case "$1" in
    help)
        show_usage
        ;;
    config)
        load_config
        ;;
    menuconfig)
        run_menuconfig
        ;;
    fullclean)
        run_full_clean
        ;;
    savedefconfig)
        if [ -z "$2" ]; then
            echo "Error: defconfig name required."
            show_usage
            exit 1
        fi
        save_defconfig "$2"
        ;;
    riscv)
        cp .config src/lvgl/
        mkdir -p build && cd build
        cmake .. -DLV_USE_KCONFIG=ON \
            -DCMAKE_TOOLCHAIN_FILE="$TOOLCHAIN_FILE"
        make -j$(nproc)
        adb push wheel_meter_display /root/ || true
        exit 0
        ;;
    *)
        cp .config src/lvgl/
        mkdir build && cd build && cmake .. -DLV_USE_KCONFIG=ON
        make -j16
        exit 1
        ;;
esac

# if [ "$1" == "menuconfig" ]; then
#     make -f Makefile.kconfig menuconfig
#     exit 0
# fi

# echo "Usage: $0 menuconfig"

# rm build -rf
# mkdir build && cd build && cmake ..
# make -j10
# make install