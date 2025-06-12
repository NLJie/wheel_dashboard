#!/bin/bash

set -e

CONFIG_DIR="config"
CONFIG_FILE=".config"
KCONFIG_FILE="Kconfig"

# 确保 config 目录存在
mkdir -p "$CONFIG_DIR"

function show_usage() {
    echo "Usage:"
    echo "  $0 config <defconfig_name>          # 载入 config/defconfig_name 作为当前配置"
    echo "  $0 menuconfig                       # 进入menuconfig界面编辑配置"
    echo "  $0 savedefconfig <defconfig_name>   # 保存当前配置为 config/defconfig_name"
    echo "  $0 full_clean                       # 清除工程"
}

function load_config() {
    local name=$1
    local defconfig_path="$CONFIG_DIR/${name}_defconfig"
    if [ ! -f "$defconfig_path" ]; then
        echo "Error: defconfig file '$defconfig_path' not found."
        exit 1
    fi

    echo "Loading config from $defconfig_path ..."
    cp "$defconfig_path" "$CONFIG_FILE"
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
    config)
        if [ -z "$2" ]; then
            echo "Error: defconfig name required."
            show_usage
            exit 1
        fi
        load_config "$2"
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
    *)
        show_usage
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