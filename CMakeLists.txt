cmake_minimum_required(VERSION 3.20)

# 实际使用最好用设定PICO_SDK_PATH和pico_sdk_import.cmake的方法进行初始化
# 必须在peoject()之前设定
include(pico-sdk/pico_sdk_init.cmake)

# 启用Release
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_C_STANDARD 11)
#set(CMAKE_CXX_STANDARD 20)

project(rp2040-tos VERSION 0.0.1 LANGUAGES C CXX ASM)

pico_sdk_init()

include_directories(
        include
        TencentOS-tiny/arch/arm/arm-v7m/cortex-m0+/gcc
        TencentOS-tiny/arch/arm/arm-v7m/common/include
        TencentOS-tiny/kernel/core/include
        TencentOS-tiny/osal/cmsis_os
        )

aux_source_directory(src APP_SOURCE)
aux_source_directory(TencentOS-tiny/arch/arm/arm-v7m/cortex-m0+/gcc PORT_C)
aux_source_directory(TencentOS-tiny/arch/arm/arm-v7m/common COMMON_C)
aux_source_directory(TencentOS-tiny/kernel/core OS_KERNEL)

add_executable(rp2040-tos
        ${APP_SOURCE}
        ${PORT_C}
        ${COMMON_C}
        ${OS_KERNEL}

        TencentOS-tiny/arch/arm/arm-v7m/cortex-m0+/gcc/port_s.S
        TencentOS-tiny/osal/cmsis_os/cmsis_os.c
        )

target_link_libraries(rp2040-tos
        pico_stdlib
        pico_multicore
        cmsis_core
        )

pico_enable_stdio_usb(rp2040-tos 1)
pico_enable_stdio_uart(rp2040-tos 0)
pico_add_extra_outputs(rp2040-tos)
