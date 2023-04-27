# Aip650 和 Tm1650 的驱动

## 1.简介

**Aip650/Tm1650** 旨在提供一个快捷易用的数码管和按键扫描驱动包。

### 1.1目录结构

`Aip650/Tm1650` 软件包目录结构如下所示：

``` 
aip650
├───examples                    // 例子的目录
│   │───SConscript              // RT-Thread 默认的构建脚本
│   └───test_aip650.c           // 测试例子的文件
├───inc                         // 头文件目录
│   └───aip650.h                // API 接口头文件
├───src                         // 源码目录
│   │───SConscript              // RT-Thread 默认的构建脚本
│   └───aip650.c                // 主模块
│   license                     // 软件包许可证
│   README.md                   // 软件包使用说明
└───SConscript                  // RT-Thread 默认的构建脚本
```

### 1.2许可证

 Aip650/Tm1650 package 遵循 LGPLv2.1 许可，详见 `LICENSE` 文件。

### 1.3依赖

- RT_Thread 4.0

## 2.使用

### 2.1接口函数说明

#### int aip650_init(void);
- 功能 ：初始化aip650/tm1650
- 返回 ：0--成功，其它--错误

#### int aip650_deinit(void);
- 功能 ：卸载aip650/tm1650
- 返回 ：0--成功，其它--错误

#### int aip650_set_segment(E_Segment segment, E_Bright_level level);
- 功能 ：设置数码管的段数及亮度
- 参数 ：segment - 段数
- 参数 ：level - 亮度
- 返回 ：0--成功，其它--错误

#### int aip650_write_number(E_Digit_Bit bit, E_Number number, int is_point);
- 功能 ：显示数字
- 参数 ：bit - 选择数码管位
- 参数 ：number - 显示的数字
- 参数 ：is_point  - 是否显示点
- 返回 ：0--成功，其它--错误

#### 矩阵按键映射表
||SG1|SG2|SG3|SG4|SG5|SG6|SG7|
|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|
|DG1|0x11|0x12|0x13|0x14|0x15|0x16|0x17|
|DG2|0x21|0x22|0x23|0x24|0x25|0x26|0x27|
|DG3|0x31|0x32|0x33|0x34|0x35|0x36|0x37|
|DG4|0x41|0x42|0x43|0x44|0x45|0x46|0x47|

#### char aip650_get_key(void);
- 功能 ：获取按键
- 返回 ：按键的映射值

### 2.2获取组件

- **方式1：**
通过 *Env配置工具* 或 *RT-Thread studio* 开启软件包，根据需要配置各项参数；配置路径为 *RT-Thread online packages -> peripherals packages -> aip650/tm1650* 


### 2.3配置参数说明

| 参数宏 | 说明 |
| ---- | ---- |
| PKG_AIP650_I2C_NAME 		| 使用的I2C的名称
| PKG_USING_AIP650 	    	| 使能aip650/tm1650的驱动

## 3. 联系方式

* 维护：Chasel
* 主页：https://github.com/Maihuanyi/aip650
* 邮箱：m19825309307@163.com

