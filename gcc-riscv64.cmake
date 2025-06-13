# 目标系统信息
set(CMAKE_SYSTEM_NAME    Linux)
set(CMAKE_SYSTEM_PROCESSOR riscv64)

set(tools ${CMAKE_SOURCE_DIR}/tools/toolchains/riscv64-linux-glibc-x86_64-V2.10.1)
set(CMAKE_C_COMPILER ${tools}/bin/riscv64-unknown-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER ${tools}/bin/riscv64-unknown-linux-gnu-g++)

# 自动取 sysroot
execute_process(
  COMMAND ${CMAKE_C_COMPILER} -print-sysroot
  OUTPUT_VARIABLE SYSROOT
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
set(CMAKE_SYSROOT ${SYSROOT})

# 常用嵌入式优化
set(CMAKE_C_FLAGS            "${CMAKE_C_FLAGS} -ffunction-sections -fdata-sections -fno-stack-protector")
set(CMAKE_CXX_FLAGS          "${CMAKE_CXX_FLAGS} -ffunction-sections -fdata-sections -fno-stack-protector")
set(CMAKE_EXE_LINKER_FLAGS   "${CMAKE_EXE_LINKER_FLAGS} -Wl,--gc-sections")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--gc-sections")
