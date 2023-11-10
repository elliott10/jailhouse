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
	struct jailhouse_cell_desc cell;
	__u64 cpus[1];
	struct jailhouse_memory mem_regions[10];
	struct jailhouse_irqchip irqchips[1];
	struct jailhouse_pci_device pci_devices[3];
	struct jailhouse_pci_capability pci_caps[14];
} __attribute__((packed)) config = {
	.cell = {
		.signature = JAILHOUSE_CELL_DESC_SIGNATURE,
		.revision = JAILHOUSE_CONFIG_REVISION,
		.name = "linux-demo",
		.flags = JAILHOUSE_CELL_PASSIVE_COMMREG | JAILHOUSE_CON_REGDIST_4,

		.cpu_set_size = sizeof(config.cpus),
		.num_memory_regions = ARRAY_SIZE(config.mem_regions),
		.num_irqchips = ARRAY_SIZE(config.irqchips),
		.num_pci_devices = ARRAY_SIZE(config.pci_devices),
		.num_pci_caps = ARRAY_SIZE(config.pci_caps),

		.cpu_reset_address = 0x0,

		.console = {
			.address = 0x28001000,
			.type = JAILHOUSE_CON_TYPE_PL011,
			.flags = JAILHOUSE_CON_ACCESS_MMIO | JAILHOUSE_CON_REGDIST_4,
		},
	},

	.cpus = {
		0xf,
	},

	.mem_regions = {
		/* IVSHMEM shared memory regions */
		{
			.phys_start = 0xb1000000,
			.virt_start = 0xb1000000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_ROOTSHARED,
		},
		{
			.phys_start = 0xb1001000,
			.virt_start = 0xb1001000,
			.size = 0x9000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_ROOTSHARED,
		},
		{
			.phys_start = 0xb100a000,
			.virt_start = 0xb100a000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_ROOTSHARED,
		},
		{
			.phys_start = 0xb100c000,
			.virt_start = 0xb100c000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ  | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_ROOTSHARED,
		},
		{
			.phys_start = 0xb100e000,
			.virt_start = 0xb100e000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ  | JAILHOUSE_MEM_ROOTSHARED,
		},
		/* UART 1 */ {
			.phys_start = 0x28001000,
			.virt_start = 0x28001000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO | JAILHOUSE_MEM_ROOTSHARED,
		},
		/* ETH1 */
		{
			.phys_start = 0x28210000,
			.virt_start = 0x28210000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO | JAILHOUSE_MEM_ROOTSHARED,
		},
		/* RAM */ {
			.phys_start = 0xb1100000,
			.virt_start = 0,
			.size = 0x800000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_LOADABLE,
		},
		/* RAM */ {
			.phys_start = 0xb2000000,
			.virt_start = 0xb2000000,
			.size = 0x1d000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_DMA |
				JAILHOUSE_MEM_LOADABLE,
		},
		/* communication region */ {
			.virt_start = 0x80000000,
			.size = 0x00001000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_COMM_REGION,
		},
	},

	.irqchips = {
		/* GIC */ {
			.address = 0x29a00000,
			.pin_base = 32,
			.pin_bitmap = {
				1 << (39 - 32) | 1 << (60 - 32) | 1 << (61 - 32) | 1 << (62 - 32) | 1 << (63 - 32), /* uart1=39, pcie_inta=60,pcie_intb=61,pcie_intc=62,pcie_intd=63 */
				0,
				0,
				1 << (102 + 32 - 128),
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
			.shmem_dev_id = 2,
			.shmem_peers = 3,
			.shmem_protocol = JAILHOUSE_SHMEM_PROTO_UNDEFINED,
		},

		/* PCI bridge @00:04.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_BRIDGE,
			.domain = 0x0000,
			.bdf = 0x0020,
			.caps_start = 0,
			.num_caps = 8,
		},

		/* Intel e1000e @05:00.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.domain = 0x0000,
			.bdf = 0x0500,
			.bar_mask = {
				0xfffe0000, 0xfffe0000, 0xffffffe0,
				0xffffc000, 0x00000000, 0x00000000,
			},

			.caps_start = 8,
			.num_caps = 6,
		},
	},

	.pci_caps = {
		/* PCI bridge @00:04.0 [0-7] */
		{
			.id = PCI_CAP_ID_EXP, /* PCI Express Capability */
			.start = 0x80,
			.len = 60,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_MSIX, /* MSI-X Capability */
			.start = 0xd0,
			.len = 12,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_MSI, /* MSI Capability Structure */
			.start = 0xe0,
			.len = 14,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_PM, /* Power Management Capability */
			.start = 0xf8,
			.len = 8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_EXT_CAP_ID_VNDR, /* Vendor-Specific Capability */
			.start = 0x100,
			.len = 8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_EXT_CAP_ID_L1SS, /* L1 PM Substates capability */
			.start = 0x110,
			.len = 16,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_EXT_CAP_ID_ERR, /* Advanced Error Reporting Capability */
			.start = 0x200,
			.len = 60,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_EXT_CAP_ID_SECPCI, /* Secondary PCI Express Extended Capability */
			.start = 0x300,
			.len = 28,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},

		/* Intel e1000e @05:00.0 [8-13] */
		{
			.id = PCI_CAP_ID_PM, /* Power Management Capability */
			.start = 0xc8,
			.len = 8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_MSI, /* MSI Capability Structure */
			.start = 0xd0,
			.len = 14,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_MSIX, /* MSI-X Capability */
			.start = 0xa0,
			.len = 12,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_EXP, /* PCI Express Capability */
			.start = 0xe0,
			.len = 60,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_EXT_CAP_ID_ERR, /* Advanced Error Reporting Capability */
			.start = 0x100,
			.len = 60,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_EXT_CAP_ID_DSN, /* Device Serial Number Capability */
			.start = 0x140,
			.len = 12,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
	}
};
