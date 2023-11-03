/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * Configuration for Phytium D2000
 * Copyright (c) 2021-2023 Phytium Technology Co., Ltd
 *
 * Authors:
 *  shixiaofeng <shixiaofeng@phytium.com.cn>
 *  Shaojun Yang <yangshaojun@phytium.com.cn>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.
 * See the COPYING file in the top-level directory.
 */

#include <jailhouse/types.h>
#include <jailhouse/cell-config.h>

struct {
	struct jailhouse_system header;
	__u64 cpus[1];
	struct jailhouse_memory mem_regions[28];
	struct jailhouse_irqchip irqchips[1];
	struct jailhouse_pci_device pci_devices[1];
} __attribute__((packed)) config = {
	.header = {
		.signature = JAILHOUSE_SYSTEM_SIGNATURE,
		.revision = JAILHOUSE_CONFIG_REVISION,
		.flags = JAILHOUSE_SYS_VIRTUAL_DEBUG_CONSOLE,
		.hypervisor_memory = {
			.phys_start = 0xb0000000,
			.size =       0x01000000,
		},
		.debug_console = {
			.address = 0x28001000,
			.size = 0x1000,
			.type = JAILHOUSE_CON_TYPE_PL011,
			.flags = JAILHOUSE_CON_ACCESS_MMIO |
				 JAILHOUSE_CON_REGDIST_4,
		},
		.platform_info = {
			.pci_mmconfig_base = 0x40000000,
			.pci_mmconfig_end_bus = 0xff,
			.pci_is_virtual = 0,
			.pci_domain = 0,

			.arm = {
				.gic_version = 3,
				.gicd_base = 0x29a00000, /* GICD */
				.gicr_base = 0x29b00000, /* GICR */
				.gicc_base = 0x29c00000, /* GICC */
				.gich_base = 0x29c10000, /* GICH */
				.gicv_base = 0x29c20000, /* GICV */
				.maintenance_irq = 25,
			},
		},
		.root_cell = {
			.name = "d2000",

			.cpu_set_size = sizeof(config.cpus),
			.num_memory_regions = ARRAY_SIZE(config.mem_regions),
			.num_irqchips = ARRAY_SIZE(config.irqchips),
			.num_pci_devices = ARRAY_SIZE(config.pci_devices),

			.vpci_irq_base = 100,
		},
	},

	.cpus = {
		0xff,
	},

	.mem_regions = {
		/* IVSHMEM shared memory regions */
		{
			.phys_start = 0xb1000000,
			.virt_start = 0xb1000000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ,
		},
		{
			.phys_start = 0xb1001000,
			.virt_start = 0xb1001000,
			.size = 0x9000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		{
			.phys_start = 0xb100a000,
			.virt_start = 0xb100a000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		{
			.phys_start = 0xb100c000,
			.virt_start = 0xb100c000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ,
		},
		{
			.phys_start = 0xb100e000,
			.virt_start = 0xb100e000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ,
		},
		/* Main memory */
		{
			.phys_start = 0x80000000,
			.virt_start = 0x80000000,
			.size =	      0x80000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE,
		},
		/* Main memory */
		{
			.phys_start = 0x2000000000,
			.virt_start = 0x2000000000,
			.size =	      0x2000000000, //Maximum support 128G
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE,
		},
		/* UART 0-3 */
		{
			.phys_start = 0x28000000,
			.virt_start = 0x28000000,
			.size = 0x4000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* GPIO 0-1 */
		{
			.phys_start = 0x28004000,
			.virt_start = 0x28004000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* I2C 0-1 */
		{
			.phys_start = 0x28006000,
			.virt_start = 0x28006000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* Watchdog 0 */
		{
			.phys_start = 0x2800a000,
			.virt_start = 0x2800a000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* Watchdog 1 */
		{
			.phys_start = 0x28016000,
			.virt_start = 0x28016000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* SPI 0 */
		{
			.phys_start = 0x2800c000,
			.virt_start = 0x2800c000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* SPI 1 */
		{
			.phys_start = 0x28013000,
			.virt_start = 0x28013000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* QSPI */
		{
			.phys_start = 0x28014000,
			.virt_start = 0x28014000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* rtc */
		{
			.phys_start = 0x2800d000,
			.virt_start = 0x2800d000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* HDA */
		{
			.phys_start = 0x28206000,
			.virt_start = 0x28206000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* CAN 0-2 and SDCI*/
		{
			.phys_start = 0x28207000,
			.virt_start = 0x28207000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* ETH0 */
		{
			.phys_start = 0x2820c000,
			.virt_start = 0x2820c000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* ETH1 */
		{
			.phys_start = 0x28210000,
			.virt_start = 0x28210000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* ixic */
		{
			.phys_start = 0x29000000,
			.virt_start = 0x29000000,
			.size = 0x102000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},        
		/* Mailbox */
		{
			.phys_start = 0x2a000000,
			.virt_start = 0x2a000000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* SRAM */
		{
			.phys_start = 0x2a006000,
			.virt_start = 0x2a006000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* GIC ITS */
		{
			.phys_start = 0x29a20000,
			.virt_start = 0x29a20000,
			.size = 0x20000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* PCIe ECAM */
		{
			.phys_start = 0x40000000,
			.virt_start = 0x40000000,
			.size = 0x10000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* PCIe IO */
		{
			.phys_start = 0x50000000,
			.virt_start = 0x50000000,
			.size = 0x8000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* PCIe Mem32 */
		{
			.phys_start = 0x58000000,
			.virt_start = 0x58000000,
			.size = 0x28000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* PCIe Mem64 */
		{
			.phys_start = 0x1000000000,
			.virt_start = 0x1000000000,
			.size = 0x1000000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
	},

	.irqchips = {
		/* GIC */ 
		{
			.address = 0x29a00000,
			.pin_base = 32,
			.pin_bitmap = {
				0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
			},
		},
	},
	
	.pci_devices = {
		{
			.type = JAILHOUSE_PCI_TYPE_IVSHMEM,
			.domain = 1,
			.bdf = 0 << 3,
			.bar_mask = JAILHOUSE_IVSHMEM_BAR_MASK_INTX,
			.shmem_regions_start = 0,
			.shmem_dev_id = 0,
			.shmem_peers = 3,
			.shmem_protocol = JAILHOUSE_SHMEM_PROTO_UNDEFINED,
		},
	},
};
