# Stm32mp157d M4

This is a project for STM32MP157D cortex M4 core. It is consist of 3 parts:

1. RTOS:      FREEROTS for now, plan to replace it with Threadx in furture.
2. OpenAMP:   used to implement inter processor communication, a open-source middleware framework.
3. User Code: Application source code implementation.

## Getting Started

## Repository Structure and Usage

### Directory layout

    .
    +---InterProcessorCom
        +---CA7                                # Reserved for cortex A7 core
        |   \---DeviceTree
        |       \---InterProcessorCom
        |           +---kernel
        |           +---optee-os
        |           +---tf-a
        |           \---u-boot
        +---CM4                                # Cortex M4 core source code
        |   +---Core
        |   |   +---Inc
        |   |   +---Src
        |   |   +---Startup
        |   |   \---ThreadSafe
        |   +---Drivers
        |   |   \---STM32MP1xx_HAL_Driver
        |   +---Middlewares
        |   |   \---Third_Party
        |   |       +---FreeRTOS
        |   |       \---OpenAMP
        |   +---OPENAMP
        |   \---RemoteProc
        +---Common
        |   \---System
        +---Drivers
        |   +---CMSIS
        |   |   +---Device
        |   |   |   \---ST
        |   |   |       \---STM32MP1xx
        |   |   |           +---Include
        |   |   |           \---Source
        |   |   |               \---Templates
        |   |   \---Include
        |   \---STM32MP1xx_HAL_Driver
        |       +---Inc
        |       |   \---Legacy
        |       \---Src
        +---Middlewares
        |   \---Third_Party
        |       +---FreeRTOS
        |       |   \---Source
        |       |       +---CMSIS_RTOS_V2
        |       |       +---include
        |       |       \---portable
        |       |           +---GCC
        |       |           |   \---ARM_CM4F
        |       |           \---MemMang
        |       \---OpenAMP
        |           +---libmetal
        |           |   \---lib
        |           |       +---include
        |           |       |   \---metal
        |           |       |       +---compiler
        |           |       |       +---processor
        |           |       |       |   \---arm
        |           |       |       \---system
        |           |       |           +---freertos
        |           |       |           |   \---template
        |           |       |           \---generic
        |           |       |               \---template
        |           |       \---system
        |           |           +---freertos
        |           |           |   \---template
        |           |           \---generic
        |           |               \---template
        |           +---open-amp
        |           |   \---lib
        |           |       +---include
        |           |       |   \---openamp
        |           |       +---proxy
        |           |       +---remoteproc
        |           |       +---rpmsg
        |           |       \---virtio
        |           \---virtual_driver
        \---ThreadSafe

## Branch and Release

## Building and using

