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
	{ 0xa3a57f57, "single_release" },
	{ 0x96c7e43b, "seq_printf" },
	{ 0x1975faaf, "seq_read" },
	{ 0x40c7247c, "si_meminfo" },
	{ 0x50eedeb8, "printk" },
	{ 0xb4390f9a, "mcount" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x90079988, "proc_create_data" },
	{ 0xe41a8077, "seq_lseek" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "F94EED44D15AA7F0543A554");
