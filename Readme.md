# 1 概述

Jailhouse是一个基于Linux的分区虚拟机管理器，一旦激活就完全控制硬件。Jailhouse使用被称为cell的方式来配置CPU等硬件的虚拟化特性，cell是系统硬件资源的描述，使用C语言语法来描述。Cell分为root cell和non-root cell，root cell接管系统硬件资源，只有一个；non-root cell可以有多个，并且从root cell中获取系统资源，可独占或与root cell共享。

Jailhouse编译完成后，生成文件分为三部分：第一部分，Jailhouse驱动和hypervisor固件，这部分提供用户态接口并初始化hypervisor；第二部分，cell和guest镜像，cell是镜像运行所需的系统资源的描述；guest镜像运行在cell之上，包括裸机，RTOS和Linux内核镜像等；第三部分，用户态工具，通过这些工具加载cell，运行镜像，查看Jailhouse状态等。


# 2 编译
配置好如下aarch64交叉编译环境：

	$ export PATH=/opt/gcc-linaro-7.5.0-2019.12-x86_64_aarch64-linux-gnu/bin:$PATH
	$ export ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu-

之后通过环境变量KDIR指定内核源码树目录，DESTDIR指定安装目录，最后使用make编译编译安装到/jailhouse-bin目录，将安装目录下的子目录拷贝到开发板的根目录：
	
	$ make DESTDIR=/jailhouse-bin KDIR=/linux install
	$ cp -r /jailhouse-bin/* /

编译后的cell文件在configs/arm64目录下，裸机程序在inmates/demos/arm64目录下。


# 3 运行
## 3.1 裸机程序

首先加载jailhouse驱动模块，之后再加载root cell和non-root cell，在FT2000/4板卡上，ft2004.cell为root cell，主要接管整个系统，ft2004-inmate-demo.cell为non-root cell，从root cell中获取一部分系统资源（共享或者独占），给后续加载的裸机程序；之后加载并运行的裸机程序，命令序列和运行效果如下图所示。

	# modprobe jailhouse;
	# jailhouse enable ft2004.cell;
	# jailhouse cell create ft2004-inmate-demo.cell;
	# jailhouse cell load 1 uart-demo.bin;
	# jailhouse cell start 1;

![](https://gitee.com/phytium_embedded/phytium-jailhouse/raw/master/pic/uart.png)

## 3.2 RTOS
RTOS的运行需要根据系统特性来适配，目前已经可以运行VxWorks（配置串口和网卡），运行效果如下图所示：

![](https://gitee.com/phytium_embedded/phytium-jailhouse/raw/master/pic/vxworks.png)


## 3.3 Linux

运行non-root Linux除加载Jailhouse驱动和root cell外，还需要提供内核镜像，设备树和根文件系统（目前为Ramdisk），还需要设定合适的启动参数，命令序列和运行效果如下图所示。

	# modprobe jailhouse
	# jailhouse enable ft2004.cell
	# jailhouse cell linux -i initrd.ext2 -d ft2004.dtb ft2004-linux-demo.cell /boot/Image -c "console=ttyAMA0,115200 root=/dev/ram0  ramdisk_size=0x1000000"

![](https://gitee.com/phytium_embedded/phytium-jailhouse/raw/master/pic/linux.png)


# 4 其他

如有需要，联系飞腾嵌入式软件部,联系邮箱：

	lizongjun@phytium.com.cn
	shixiaofeng@phytium.com.cn
