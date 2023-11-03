/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * Configuration for Phytium E2000Q
 * Copyright (c) 2022-2023 Phytium Technology Co., Ltd
 *
 * Authors:
 *  yangshaojun <yangshaojun@phytium.com.cn>
 *  huyuming <huyuming1672@phytium.com.cn>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 */
#include <jailhouse/types.h>
#include <jailhouse/cell-config.h>

struct {
	struct jailhouse_cell_desc cell;
	__u64 cpus[1];
	struct jailhouse_memory mem_regions[6];
	struct jailhouse_irqchip irqchips[1];
#ifdef CONFIG_PCIE_E1000E_TEST
	struct jailhouse_pci_device pci_devices[3];
	struct jailhouse_pci_capability pci_caps[11];
	union jailhouse_stream_id stream_ids[1];
#else
	struct jailhouse_pci_device pci_devices[1];
#endif
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
#ifdef CONFIG_PCIE_E1000E_TEST
		.num_pci_caps = ARRAY_SIZE(config.pci_caps),
		.num_stream_ids = ARRAY_SIZE(config.stream_ids),
#endif
		.cpu_reset_address = 0x0,

		.console = {
			.address = 0x2800d000,
			.type = JAILHOUSE_CON_TYPE_PL011,
			.flags = JAILHOUSE_CON_ACCESS_MMIO | JAILHOUSE_CON_REGDIST_4,
		},
	},

	.cpus = {
		0x3,
	},

	.mem_regions = {
		/* UART 1 */
		{
			.phys_start = 0x2800d000,
			.virt_start = 0x2800d000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_IO | JAILHOUSE_MEM_ROOTSHARED,
		},

		/* PCI bridge @00:02.0 BAR0 */
		{
			.phys_start = 0x1000300000,
			.virt_start = 0x1000300000,
			.size = 0x00010000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},

		/* e1000 BAR0 */
		{
			.phys_start = 0x582c0000,
			.virt_start = 0x582c0000,
			.size = 0x00020000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},

		/* RAM: for linux-loader space */
		{
			.phys_start = 0x2000000000,
			.virt_start = 0x0,
			.size = 0x00010000, /* 64KB */
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_LOADABLE,
		},

		/* RAM */
		{
			.phys_start = 0x2000080000,
			.virt_start = 0x2000080000,
			.size = 0x40000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_LOADABLE | JAILHOUSE_MEM_DMA,
		},

		/* communication region */
		{
			.virt_start = 0x80000000,
			.size = 0x00001000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_COMM_REGION,
		},
	},

	.irqchips = {
		/* GIC */
		{
			.address = 0x30800000,
			.pin_base = 32,
			.pin_bitmap = {
				1 << (36 - 32) | 1 << (37 - 32) | 1 << (38 - 32) | 1 << (39 - 32), /* pcie_inta=36,pcie_intb=37,pcie_intc=38,pcie_intd=39 */
				0,
				1 << (116 - 96), /* UART1=116 */
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
			.shmem_dev_id = 1,
			.shmem_peers = 1,
			.shmem_protocol = JAILHOUSE_SHMEM_PROTO_UNDEFINED,
		},

#ifdef CONFIG_PCIE_E1000E_TEST
		/* PCI bridge @00:02.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_BRIDGE,
			.domain = 0x0000,
			.bdf = 0x0010,
			.caps_start = 0,
			.num_caps = 5,
			.num_msi_vectors = 1,
			.msi_64bits = 1,
		},

		/* Intel e1000e @02:00.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.domain = 0x0000,
			.bdf = 0x0200,
			.bar_mask = {
				0xfffe0000, 0xfffe0000, 0xffffffe0,
				0xffffc000, 0x00000000, 0x00000000,
			},

			.caps_start = 5,
			.num_caps = 6,
			.num_msi_vectors = 1,
			.msi_64bits = 1,
			.num_msix_vectors = 5, /* RxQ0, TxQ0 and other, Message Control for MSI-X: Table Size */
			.msix_region_size = 0x4000,
			.msix_address = 0x582e0000,
		},
#endif
	},

#ifdef CONFIG_PCIE_E1000E_TEST
	.pci_caps = {
		/* PCI bridge @00:02.0 */
		{
			.id = PCI_CAP_ID_EXP,
			.start = 0x80,
			.len = 60,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_MSIX,
			.start = 0xd0,
			.len = 12,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_MSI,
			.start = 0xe0,
			.len = 14,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_PM,
			.start = 0xf8,
			.len = 12,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_EXT_CAP_ID_ERR,
			.start = 0x200,
			.len = 68,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},

		/* Intel e1000e @02:00.0 Power Management Capability Structure */
		{
			.id = PCI_CAP_ID_PM,
			.start = 0xc8,
			.len = 12,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		/* Intel e1000e @02:00.0 --MSI Capability Structures */
		{
			.id = PCI_CAP_ID_MSI,
			.start = 0xd0,
			.len = 14,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		/* Intel e1000e @02:00.0 --PCI Express Capability Structure */
		{
			.id = PCI_CAP_ID_EXP,
			.start = 0xe0,
			.len = 60,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		/* Intel e1000e @02:00.0 --MSI-X Capability Structures */
		{
			.id = PCI_CAP_ID_MSIX,
			.start = 0xa0,
			.len = 12,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		/* Intel e1000e @02:00.0 --Advanced Error Reporting Capability */
		{
			.id = PCI_EXT_CAP_ID_ERR,
			.start = 0x100,
			.len = 68,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		/* Intel e1000e @02:00.0 --Device Serial Number Capability */
		{
			.id = PCI_EXT_CAP_ID_DSN,
			.start = 0x140,
			.len = 12,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
	},
	.stream_ids = {
		/* Intel e1000e @02:00.0 */
		{0x0200},
	},
#endif
};
