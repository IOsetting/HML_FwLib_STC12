# HML_FwLib_STC12

[![GitHub repo size](https://img.shields.io/github/repo-size/IOsetting/HML_FwLib_STC12)](https://github.com/IOsetting/HML_FwLib_STC12)
[![GitHub](https://img.shields.io/github/license/IOsetting/HML_FwLib_STC12)](https://github.com/IOsetting/HML_FwLib_STC12/blob/master/LICENSE)
[![GitHub tag (latest by date)](https://img.shields.io/github/v/tag/IOsetting/HML_FwLib_STC12?color=26a69a)](https://github.com/IOsetting/HML_FwLib_STC12/tags)

## 关于

HML_FwLib_STC12 是一个面向 STC12 系列MCU的封装库, 是 [HML_FwLib_STC11](https://github.com/MCU-ZHISHAN-IoT/HML_FwLib_STC11) 项目的一个独立分支.

STC12 系列属于英特尔8051 MCU的一个变种, 是STC的STC89,STC90,STC11系列的后继型号, 相对于早期型号提供了更多的片上资源, 增加了硬件实现的ADC, PCA, SPI和PWM等常用功能. 更多的细节可以查看官方介绍 http://www.stcmicro.com/stc/stc12c5a32s2.html.

HML_FwLib_STC12 与其它 HML 封装库一样, 将MCU的片上资源进行包装并提供便捷的编程接口, 让开发者可以在项目中以类似STM32的编程方式, 快捷使用 ADC, GPIO, IAP, PCA, TIM, UART, EXTI, 电源管理以及看门狗等片上资源.

## 特性

+ 基于 [SDCC compiler](http://sdcc.sourceforge.net/)
+ (几乎)完整覆盖 STC12 系列 MCU 的片上资源
+ GPL-3.0 开源协议
+ 丰富的代码例子供开发参考

此表格展示了支持的片上资源列表

| Peripheral | Description | Status |
| --- | --- | --- |
| extended bus | Intel 8080 bus receiver/transmitter | supported |
| ADC  | A/D conversion | supported |
| EXTI | extern interrupt | supported |
| GPIO | I/O peripheral | supported  |
| IAP | in application programming | supported |
| PCA | 16-bit capture/compare and 8-bit PWM | supported |
| PWR | power management | supported |
| RCC | reset & clock control | supported |
| SPI | full-duplex, high-speed serial peripheral interface | supported |
| TIM | timer | supported |
| UART | universal asynchronous receiver/transmitter | supported |
| WDT | watchdog | supported |

# 如何使用

请查看代码仓库的[WIKI](https://github.com/IOsetting/HML_FwLib_STC12/wiki)

## 需要的环境
+ [GNU Make](http://www.gnu.org/software/make/manual/make.html)(recommend)
+ [SDCC compiler](http://sdcc.sourceforge.net/)
+ *\[Windows用户\]* Unix shell tools([msys](http://www.mingw.org/wiki/MSYS), [Cygwin](http://www.cygwin.com/), [GNUwin32](http://gnuwin32.sourceforge.net/)) needed by makefile for HML_FwLib_STC12

## 开发

### 文件结构

```bash
HML_FwLib_STC12
├─doc          #store related documents about HML_FwLib_STC12
├─example      #provide some example files with *.c format to help users learn about HML_FwLib_STC12
├─inc          #include all header files(*.h) of HML_FwLib_STC12
├─obj          #store all output files, including *.hex,*.ihx,*.lk,*.rel and others during compilation
├─src          #store all source files(*.c) of HML_FwLib_STC12
├─usr          #store makefile and a source file which includes main function
├─library.json #library definition for PlatformIO integration
├─LICENSE      #license of HML_FwLib_STC12
├─README.md    #this file
└─VERSION      #version code of HML_FwLib_STC12
```

### 编译参数

There are several parameters need to be configured by user manually.

#### \_\_CONF\_COMPILE\_xxx (for conditional compilation)
In order to ensure the projects based on HML_FwLib_STC12 can be downloaded into the limited on-chip flash space of STC12 MCUs, the developers can modify the macro definition named `__CONF_COMPILE_xxx` in *conf.h* to specify which piece of codewill take part in compilation, then it will reduce size of final .hex file. If user only use GPIO module, then user just need to enable `__CONF_COMPILE_GPIO` macro in *conf.h*. Some macros for conditional compilation rely on others. For example, before you define the macro definition `__CONF_COMPILE_RCC`, the macro `__CONF_COMPILE_UTIL` should be defined, otherwise the compilation would be failed.
####  \_\_CONF\_FRE\_CLKIN
The macro mark frequency of clock source, including extern crystal oscillator or internal RC oscillating circuit, and it's defined in *conf.h*.
#### \_\_CONF\_MCU\_MODEL
The macro mark the model of target MCU and is defined in *conf.h*.

### 示例代码及编译

There is a source file named *test.c* under *usr* directory, we have put a main function here. User can add and modify own code here, then enter <kbd>make</kbd> in terminal, the Makefile will work and complete compilation. Besides, user can enter <kbd>make help</kbd> to get all usages.

Certainly, you can just add *inc* and *src* directory into your project structure, and write your own makefile to build a custom project. 

## 在VS Code中开发

PlatformIO turns VSCode into a complete IDE for compiling and developing embeded projects. HML_FwLib_STC12 is a perfect library for STC12C5A60S2 series MCU projects. For example, see the structure of a typical PlatformIO project:
```
|--include
|--lib
|  |
|  |--HML_FwLib_STC12
|  |  |--docs
|  |  |--examples
|  |  |--inc
|  |  |--src
|  |  |- library.json
|  |
|  |--Other_Libraries
|
|- platformio.ini
|--src
   |- main.c
```
Building and uploading will be managed by PlatformIO, so additional flags are needed in you platformio.ini, 
* `-D__CONF_FRE_CLKIN`, required, specify the oscillator frequency
* `-D__CONF_MCU_MODEL`, required, specify the MCU model
* `upload_speed` and `upload_flags`, optional, it will improve the ISP speed

For example
```bash
[env:stc12c5a56s2]
platform = intel_mcs51
board = stc12c5a56s2
build_flags =
    -D__CONF_FRE_CLKIN=11059200
    -D__CONF_MCU_MODEL=MCU_MODEL_STC12C5A56S2
upload_speed = 115200
upload_flags =
    -b$UPLOAD_SPEED
```
