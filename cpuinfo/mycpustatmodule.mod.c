#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x15b2dc7b, "module_layout" },
	{ 0x8f0610f, "single_open" },
	{ 0x2d37342e, "cpu_online_mask" },
	{ 0xa3a57f57, "single_release" },
	{ 0x96a592f6, "seq_puts" },
	{ 0xc0a3d105, "find_next_bit" },
	{ 0x96c7e43b, "seq_printf" },
	{ 0x1975faaf, "seq_read" },
	{ 0xfe7c4287, "nr_cpu_ids" },
	{ 0x50eedeb8, "printk" },
	{ 0xb4390f9a, "mcount" },
	{ 0xb863e8df, "seq_putc" },
	{ 0x579fbcd2, "cpu_possible_mask" },
	{ 0x7ecb001b, "__per_cpu_offset" },
	{ 0xd2555f19, "jiffies_64_to_clock_t" },
	{ 0x90079988, "proc_create_data" },
	{ 0xe41a8077, "seq_lseek" },
	{ 0xb4d6e420, "seq_put_decimal_ull" },
	{ 0x5567c227, "kernel_cpustat" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "14DE91D22418AF0CB887F16");
