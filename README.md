# HML_FwLib_STC11
[![Jenkins](https://img.shields.io/jenkins/build?jobUrl=http%3A%2F%2Fjenkins.zhishan-iot.tk%3A12463%2Fjob%2FHML_FwLib_STC11)](http://jenkins.zhishan-iot.tk:12463/job/HML_FwLib_STC11)
[![GitHub repo size](https://img.shields.io/github/repo-size/MCU-ZHISHAN-IoT/HML_FwLib_STC11)](https://github.com/MCU-ZHISHAN-IoT/HML_FwLib_STC11)
[![GitHub](https://img.shields.io/github/license/MCU-ZHISHAN-IoT/HML_FwLib_STC11)](https://github.com/MCU-ZHISHAN-IoT/HML_FwLib_STC11/blob/master/LICENSE)
[![GitHub tag (latest by date)](https://img.shields.io/github/v/tag/MCU-ZHISHAN-IoT/HML_FwLib_STC11?color=26a69a)](https://github.com/MCU-ZHISHAN-IoT/HML_FwLib_STC11/tags)
## What is HML_FwLib_STC11
HML_FwLib_STC11 is a member component of HML firmware library, **providing a group of interface functions for users to operate on-chip resource of STC11 MCUs**, including GPIO, IAP, timer, UART, external interrupt, power management and watchdog. The STC11 MCU is a kind of Intel MCS-51 based MCU which released by [STC Micro](http://www.stcmcu.com/)(*宏晶*). Compared to STC10 series, STC11 provides dedicated wake-up timer for power down mode.

We intend to provide a lite and easy-use firmware library that can help future developers to complete projects based on STC11 MCUs more easily and quickly. All source codes are written in C language and for [SDCC compiler](http://sdcc.sourceforge.net/), i.e., it can only be compiled by SDCC. This choice is motivated by the fact that SDCC is free and highly efficient, while there are very few examples of application about SDCC on the Internet. We hope that, as one of the early attempts to develop MCU projects using SDCC, this work will make SDCC become more popular among MCU developers.<br>

Please visit [detail page](https://hw.zhishan-iot.tk/page/hml/detail/fwlib_stc10.html) for more information to get started it!

## Feature
+ :dart:Based on [SDCC compiler](http://sdcc.sourceforge.net/).
+ Cover all on-chip resource of STC11 series MCUs.
+ Open all source code on [Github](https://github.com) and licensed under the [WTPL2](https://wtfpl2.com/).
+ Readable code and provide examples to help you get started it.

# What's working
Here is a list of the all on-chip peripheral drivers and examples that need to be ported.

| Peripheral | Description | Status |
| --- | --- | --- |
| extended bus | Intel 8080 bus receiver/transmitter | supported |
| EXTI | extern interrupt | supported |
| GPIO | I/O peripheral | supported  |
| IAP | in application programming | supported |
| PWR | power management | supported |
| RCC | reset & clock control | supported |
| TIM | timer | supported |
| UART | universal asynchronous receiver/transmitter | supported |
| WDT | watchdog | supported |

## Prerequisite
+ [GNU Make](http://www.gnu.org/software/make/manual/make.html)(recommend)
+ [SDCC compiler](http://sdcc.sourceforge.net/)
+ *\[for Windows\]* Unix shell tools([msys](http://www.mingw.org/wiki/MSYS), [Cygwin](http://www.cygwin.com/), [GNUwin32](http://gnuwin32.sourceforge.net/)) needed by makefile for HML_FwLib_STC11

## Usage
### file structure
```bash
HML_FwLib_STC11
├─doc      #store related documents about HML_FwLib_STC11
├─example  #provide some example files with *.c format to help users learn about HML_FwLib_STC11
├─inc      #include all header files(*.h) of HML_FwLib_STC11
├─obj      #store all output files, including *.hex,*.ihx,*.lk,*.rel and others during compilation
├─src      #store all source files(*.c) of HML_FwLib_STC11
├─usr      #store makefile and a source file which includes main function
├─LICENSE  #license of HML_FwLib_STC11
└─VERSION  #version code of HML_FwLib_STC11
```
### configuration
There are several parameters need to be configured by user manually.
#### \_\_CONF\_COMPILE\_xxx (for conditional compilation)
In order to ensure the projects based on HML_FwLib_STC11 can be downloaded into the limited on-chip flash space of STC11 MCUs, the developers can modify the macro definition named `__CONF_COMPILE_xxx` in *conf.h* to specify which piece of codewill take part in compilation, then it will reduce size of final .hex file. If user only use GPIO module, then user just need to enable `__CONF_COMPILE_GPIO` macro in *conf.h*. Some macros for conditional compilation rely on others. For example, before you define the macro definition `__CONF_COMPILE_RCC`, the macro `__CONF_COMPILE_UTIL` should be defined, otherwise the compilation would be failed.
####  \_\_CONF\_FRE\_CLKIN
The macro mark frequency of clock source, including extern crystal oscillator or internal RC oscillating circuit, and it's defined in *conf.h*.
#### \_\_CONF\_MCU\_MODEL
The macro mark the model of target MCU and is defined in *conf.h*.
### code & compilation
There is a source file named *test.c* under *usr* directory, we have put a main function here. User can add and modify own code here, then enter <kbd>make</kbd> in terminal, the Makefile will work and complete compilation. Besides, user can enter <kbd>make help</kbd> to get all usages.

Certainly, you can just add *inc* and *src* directory into your project structure, and write your own makefile to build a custom project. 

## Contributing
Welcome suggestions and contribution from you! You can fork it or contact us via *[mcu@zhishan-iot.tk](mailto:mcu@zhishan-iot.tk)*.

## License
HML_FwLib_STC11 is licensed under the [WTFPL2](https://wtfpl2.com/).

##  Team

|member        | role              |e-mail                        |
|--------------|-------------------|------------------------------|
| Amy Chung    | Testing           |[zhongliguo@zhishan-iot.tk](mailto:zhongliguo@zhishan-iot.tk) |
| Weilun Fong  | **Director**      |[wlf@zhishan-iot.tk](mailto:wlf@zhishan-iot.tk) |
