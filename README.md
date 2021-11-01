# HML_FwLib_STC12

[![GitHub repo size](https://img.shields.io/github/repo-size/IOsetting/HML_FwLib_STC12)](https://github.com/IOsetting/HML_FwLib_STC12)
[![GitHub](https://img.shields.io/github/license/IOsetting/HML_FwLib_STC12)](https://github.com/IOsetting/HML_FwLib_STC12/blob/master/LICENSE)
[![GitHub tag (latest by date)](https://img.shields.io/github/v/tag/IOsetting/HML_FwLib_STC12?color=26a69a)](https://github.com/IOsetting/HML_FwLib_STC12/tags)

## 关于

HML_FwLib_STC12 是面向*STC12*系列单片机的C语言封装库, *STC12*系列单片机是[宏晶公司](https://www.stcmcudata.com/)的产品, 发布于2007年. 这个系列的型号有*STC12C5A60S2*, *STC12C5A56S2*等, *STC12*系列是STC89,STC90,STC11系列的后继型号, 相对于早期型号增加了ADC, PCA, SPI和PWM等片内外设. 更多的细节可以查看[官方介绍](http://www.stcmicro.com/stc/stc12c5a32s2.html), [STC12C5Axx Datasheet](http://www.stcmicro.com/datasheet/STC12C5A60S2-en.pdf). *STC12*是使用经典引脚布局的最后一个系列, 从*STC15*系列开始使用了新的引脚布局.

这个封装库是[HML_FwLib_STC11](https://github.com/MCU-ZHISHAN-IoT/HML_FwLib_STC11)项目的一个分支(在此感谢原开发团队), 在其基础上对*STC12*的寄存器定义做了调整和适配, 对新增的硬件外设ADC, PWM, UART2, SPI等增加了对应的库方法, 并增加了对应的代码示例.

HML_FwLib_STC12 与其它 HML 封装库一样, 将MCU的片上资源进行包装并提供便捷的编程接口, 让开发者可以在项目中以类似STM32的编程方式, 快捷使用 ADC, GPIO, IAP, PCA, TIM, UART, EXTI, 电源管理以及看门狗等片上资源.

## 特性

+ 基于 [SDCC compiler](http://sdcc.sourceforge.net/)
+ (几乎)完整覆盖 STC12 系列 MCU 的片上资源
+ GPL-3.0 开源协议
+ 丰富的代码例子供开发参考, 有立即可用的MAX7219, nRF24L01, DS1302, DS12C887, TM1650参考代码

封装库支持的功能列表

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

请查看[WIKI](https://github.com/IOsetting/HML_FwLib_STC12/wiki), 里面详细介绍了命令行方式和IDE界面方式的安装和使用.

## 需要的环境

+ [GNU Make](http://www.gnu.org/software/make/manual/make.html)(recommend)
+ [SDCC compiler](http://sdcc.sourceforge.net/)

## 开发

### 文件结构

```bash
HML_FwLib_STC12
├─doc          # 文档
├─example      # 使用封装库的代码例子
├─inc          # 封装库的头文件(*.h)
├─obj          # 编译过程中产生的文件
├─src          # 封装库的源代码(*.c)
├─usr          # 项目代码及 makefile
├─library.json # 用于PlatformIO集成的库结构定义文件
├─LICENSE      # 授权
├─README.md    # 本文件
└─VERSION      # 版本
```

### 编译参数

使用本封装库时需要开发者配置的参数

#### \_\_CONF\_COMPILE\_xxx (用于条件编译)
为了节约有限的片内资源, 开发者可以修改*conf.h*中的`__CONF_COMPILE_xxx`用于选择参与编译的部分, 从而减小最终产生的.hex文件大小. 例如如果只用到GPIO模块, 可以只启用`__CONF_COMPILE_GPIO`. 因为一些模块的编译依赖于其他模块, 例如`__CONF_COMPILE_RCC`依赖于`__CONF_COMPILE_UTIL`, 启用前者时必须也启用后者, 否则编译会失败.
####  \_\_CONF\_FRE\_CLKIN
用于标记时钟源的频率, 在*conf.h*中定义
#### \_\_CONF\_MCU\_MODEL
标记目标单片机型号, 在*conf.h*中定义

### 示例代码及编译

在*usr*下有一个文件名为*test.c*的示例文件, 您可以修改其中的代码后在命令行下输入 <kbd>make</kbd>, 这时会执行Makefile中定义的过程完成编译. 另外, 可以输入<kbd>make help</kbd>查看编译选项.

## 使用 PlatformIO + VS Code 进行开发

PlatformIO 是 VS Code 的一个扩展, 用于嵌入式项目的开发. 在开发*STC12*项目时, HML_FwLib_STC12可以作为库直接引用. 下面是一个典型的PlatformIO项目目录结构:
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
编译和烧录的工具都由PlatformIO自动安装和管理, 需要在platformio.ini中配置相应的编译参数
* `-D__CONF_FRE_CLKIN`, 必填, 用于指定晶振频率
* `-D__CONF_MCU_MODEL`, 必填, 用于指定单片机型号
* `upload_speed` and `upload_flags`, 选填, 用于ISP提速

配置示例
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

# 附录

## STC单片机版本历史

| 时间  | 版本                     |
| ---- | -----------------       |
| 2004 | STC89                   |
| 2007 | STC90 STC10 STC11 STC12 |
| 2010 | STC15                   |
| 2014 | IAP15                   |
| 2017 | STC8F/STC8A/STC8G/STC8H |

