# Background

[![GitHub repo size](https://img.shields.io/github/repo-size/IOsetting/HML_FwLib_STC12)](https://github.com/IOsetting/HML_FwLib_STC12)
[![GitHub](https://img.shields.io/github/license/IOsetting/HML_FwLib_STC12)](https://github.com/IOsetting/HML_FwLib_STC12/blob/master/LICENSE)
[![GitHub tag (latest by date)](https://img.shields.io/github/v/tag/IOsetting/HML_FwLib_STC12?color=26a69a)](https://github.com/IOsetting/HML_FwLib_STC12/tags)

## What is HML_FwLib_STC12

This is a lite firmware library for STC12C5A60S2 series MCU, forked from [HML_FwLib_STC11](https://github.com/MCU-ZHISHAN-IoT/HML_FwLib_STC11).

HML_FwLib_STC12 is a member of HML firmware libraries, providing interface functions for on-chip resource of STC MCUs, including ADC, GPIO, IAP, PCA, TIM, UART, external interrupt, power management and watchdog. The STC12C5A60S2 series is a variant of Intel 8051 and a descendant of STC89,STC90,STC11, which offers additional hardware peripherals. More details can be found at http://www.stcmicro.com/stc/stc12c5a32s2.html.

We intend to provide a lite firmware library that makes coding easier (also more readable code). All source codes are written in C language and for [SDCC compiler](http://sdcc.sourceforge.net/), i.e., it can only be compiled by SDCC. This choice is motivated by the fact that SDCC is free and highly efficient, while there are very few examples of application about SDCC on the Internet. We hope that, as one of the early attempts to develop MCU projects using SDCC, this work will make SDCC become more popular among MCU developers.<br>

Please visit [detail page](https://hw.zhishan-iot.tk/page/hml/detail/fwlib_stc10.html) for more information!

## Feature
+ Based on [SDCC compiler](http://sdcc.sourceforge.net/).
+ Cover most on-chip resource of STC12 series MCUs.
+ GPL-3.0 licensed open source library.
+ A variety of examples to help you get started in using HML_FwLib_STC12.


# Usage

Here is a list of the all on-chip peripheral drivers and examples that need to be ported.

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
| TIM | timer | supported |
| UART | universal asynchronous receiver/transmitter | supported |
| WDT | watchdog | supported |

## Prerequisite
+ [GNU Make](http://www.gnu.org/software/make/manual/make.html)(recommend)
+ [SDCC compiler](http://sdcc.sourceforge.net/)
+ *\[for Windows\]* Unix shell tools([msys](http://www.mingw.org/wiki/MSYS), [Cygwin](http://www.cygwin.com/), [GNUwin32](http://gnuwin32.sourceforge.net/)) needed by makefile for HML_FwLib_STC12

## Development

### file structure

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

### configuration

There are several parameters need to be configured by user manually.

#### \_\_CONF\_COMPILE\_xxx (for conditional compilation)
In order to ensure the projects based on HML_FwLib_STC12 can be downloaded into the limited on-chip flash space of STC12 MCUs, the developers can modify the macro definition named `__CONF_COMPILE_xxx` in *conf.h* to specify which piece of codewill take part in compilation, then it will reduce size of final .hex file. If user only use GPIO module, then user just need to enable `__CONF_COMPILE_GPIO` macro in *conf.h*. Some macros for conditional compilation rely on others. For example, before you define the macro definition `__CONF_COMPILE_RCC`, the macro `__CONF_COMPILE_UTIL` should be defined, otherwise the compilation would be failed.
####  \_\_CONF\_FRE\_CLKIN
The macro mark frequency of clock source, including extern crystal oscillator or internal RC oscillating circuit, and it's defined in *conf.h*.
#### \_\_CONF\_MCU\_MODEL
The macro mark the model of target MCU and is defined in *conf.h*.

### code & compilation

There is a source file named *test.c* under *usr* directory, we have put a main function here. User can add and modify own code here, then enter <kbd>make</kbd> in terminal, the Makefile will work and complete compilation. Besides, user can enter <kbd>make help</kbd> to get all usages.

Certainly, you can just add *inc* and *src* directory into your project structure, and write your own makefile to build a custom project. 

## Development in PlatformIO with VSCode

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
```
[env:stc12c5a56s2]
platform = intel_mcs51
board = stc12c5a56s2
build_flags =
    -D__CONF_FRE_CLKIN=11059200
    ;-D__CONF_FRE_CLKIN=22118400
    ;-D__CONF_FRE_CLKIN=12000000
    -D__CONF_MCU_MODEL=MCU_MODEL_STC12C5A56S2
upload_speed = 115200
upload_flags =
    -b$UPLOAD_SPEED
```


## Contribute

HML_FwLib_STC12 is GPL-3.0-licensed open source software. We welcome contributions big and small!


## License

HML_FwLib_STC12 is licensed under GPL-3.0.
