/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * Configuration for Phytium e2000q
 *
 */

#include <jailhouse/types.h>
#include <jailhouse/cell-config.h>

struct {
	struct jailhouse_system header;
	__u64 cpus[1];
	struct jailhouse_memory mem_regions[52];
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
			.address = 0x2800d000,
			.size = 0x1000,
			.type = JAILHOUSE_CON_TYPE_PL011,
			.flags = JAILHOUSE_CON_ACCESS_MMIO |
				 JAILHOUSE_CON_REGDIST_4,
		},
		.platform_info = {
			.pci_mmconfig_base = 0x40000000,
			.pci_mmconfig_end_bus = 0,
			.pci_is_virtual = 1,
			.pci_domain = 1,

			.arm = {
				.gic_version = 3,
				.gicd_base = 0x30800000,
				.gicr_base = 0x30880000,
				.gicc_base = 0x30960000,
				.maintenance_irq = 25,
			},
		},
		.root_cell = {
			.name = "e2000q",

			.cpu_set_size = sizeof(config.cpus),
			.num_memory_regions = ARRAY_SIZE(config.mem_regions),
			.num_irqchips = ARRAY_SIZE(config.irqchips),
			.num_pci_devices = ARRAY_SIZE(config.pci_devices),

			.vpci_irq_base = 100,
		},
	},

	.cpus = {
		0x0f,
	},

	.mem_regions = {
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
		/* LPC */
		{
			.phys_start = 0x20000000,
			.virt_start = 0x20000000,
			.size = 0x8000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* MMC 0-1 */
		{
			.phys_start = 0x28000000,
			.virt_start = 0x28000000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* NAND Controler*/
		{
			.phys_start = 0x28002000,
			.virt_start = 0x28002000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* DMA 0-1*/
		{
			.phys_start = 0x28003000,
			.virt_start = 0x28003000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* DDMA 1*/
		{
			.phys_start = 0x28005000,
			.virt_start = 0x28005000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* HDA */
		{
			.phys_start = 0x28006000,
			.virt_start = 0x28006000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* LBC */
		{
			.phys_start = 0x28007000,
			.virt_start = 0x28007000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* QSPI */
		{
			.phys_start = 0x28008000,
			.virt_start = 0x28008000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* I2S */
		{
			.phys_start = 0x28009000,
			.virt_start = 0x28009000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* CAN 0-1*/
		{
			.phys_start = 0x2800a000,
			.virt_start = 0x2800a000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* UART 0-3 */
		{
			.phys_start = 0x2800c000,
			.virt_start = 0x2800c000,
			.size = 0x4000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* PMBBUS 0 - 1*/
		{
			.phys_start = 0x28011000,
			.virt_start = 0x28011000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* SMBBUS*/
		{
			.phys_start = 0x28013000,
			.virt_start = 0x28013000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* MMIO 0-15*/
		{
			.phys_start = 0x28014000,
			.virt_start = 0x28014000,
			.size = 0x20000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* GPIO 0-5 */
		{
			.phys_start = 0x28034000,
			.virt_start = 0x28034000,
			.size = 0x6000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* SPIM 0-3 */
		{
			.phys_start = 0x2803A000,
			.virt_start = 0x2803A000,
			.size = 0x4000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* Onewrite*/
		{
			.phys_start = 0x2803F000,
			.virt_start = 0x2803F000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* Watchdog 0-1 */
		{
			.phys_start = 0x28040000,
			.virt_start = 0x28040000,
			.size = 0x4000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* JTAG Master */
		{
			.phys_start = 0x28044000,
			.virt_start = 0x28044000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* I3C 0-3 */
		{
			.phys_start = 0x28045000,
			.virt_start = 0x28045000,
			.size = 0x4000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* eSPI Slave*/
		{
			.phys_start = 0x28049000,
			.virt_start = 0x28049000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* PWM 0-7 */
		{
			.phys_start = 0x2804a000,
			.virt_start = 0x2804a000,
			.size = 0x8000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* IACC */
		{
			.phys_start = 0x28052000,
			.virt_start = 0x28052000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* Tacho 0-37 */
		{
			.phys_start = 0x28054000,
			.virt_start = 0x28054000,
			.size = 0x26000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* keypad*/
		{
			.phys_start = 0x2807a000,
			.virt_start = 0x2807a000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* ADC 0-1 */
		{
			.phys_start = 0x2807B000,
			.virt_start = 0x2807B000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* SGPIO */
		{
			.phys_start = 0x2807D000,
			.virt_start = 0x2807D000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* USB_vhub 0-2 */
		{
			.phys_start = 0x31800000,
			.virt_start = 0x31800000,
			.size = 0x180000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* USB3 0-1 */
		{
			.phys_start = 0x31A00000,
			.virt_start = 0x31A00000,
			.size = 0x40000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* SATA0 */
		{
			.phys_start = 0x31A40000,
			.virt_start = 0x31A40000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* DC */
		{
			.phys_start = 0x32000000,
			.virt_start = 0x32000000,
			.size = 0x4000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* DP 0-1 */
		{
			.phys_start = 0x32004000,
			.virt_start = 0x32004000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* I2S0_DMA */
		{
			.phys_start = 0x32008000,
			.virt_start = 0x32008000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* I2S0 */
		{
			.phys_start = 0x32009000,
			.virt_start = 0x32009000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* I2S1_DMA */
		{
			.phys_start = 0x3200A000,
			.virt_start = 0x3200A000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* I2S1 */
		{
			.phys_start = 0x3200B000,
			.virt_start = 0x3200B000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* GMU 0-3 */
		{
			.phys_start = 0x3200c000,
			.virt_start = 0x3200c000,
			.size = 0x8000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* SATA1 */
		{
			.phys_start = 0x32014000,
			.virt_start = 0x32014000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* USB2 */
		{
			.phys_start = 0x32800000,
			.virt_start = 0x32800000,
			.size = 0x200000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* JPEG_ENCODER */
		{
			.phys_start = 0x32B32000,
			.virt_start = 0x32B32000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* DMAC 0-1 */
		{
			.phys_start = 0x32B34000,
			.virt_start = 0x32B34000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* HW Spinlock */
		{
			.phys_start = 0x32B36000,
			.virt_start = 0x32B36000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* Mailbox */
		{
			.phys_start = 0x32a00000,
			.virt_start = 0x32a00000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_IO,
		},
		/* SRAM */
		{
			.phys_start = 0x32a10000,
			.virt_start = 0x32a10000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE,
		},
		/* GIC ITS */
		{
			.phys_start = 0x30820000,
			.virt_start = 0x30820000,
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
			.address = 0x30800000,
			.pin_base = 32,
			.pin_bitmap = {
				0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
			},
		},
	},
};
