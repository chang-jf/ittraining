#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
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
	{ 0xa0db54eb, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x1c53ee2c, __VMLINUX_SYMBOL_STR(cdev_del) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x4056b2aa, __VMLINUX_SYMBOL_STR(device_destroy) },
	{ 0x1766903e, __VMLINUX_SYMBOL_STR(cdev_add) },
	{ 0xd8012408, __VMLINUX_SYMBOL_STR(cdev_init) },
	{ 0x2576947d, __VMLINUX_SYMBOL_STR(class_destroy) },
	{ 0xd81d82c1, __VMLINUX_SYMBOL_STR(device_create) },
	{ 0x7485e15e, __VMLINUX_SYMBOL_STR(unregister_chrdev_region) },
	{ 0xde27be2f, __VMLINUX_SYMBOL_STR(__class_create) },
	{ 0x29537c9e, __VMLINUX_SYMBOL_STR(alloc_chrdev_region) },
	{ 0xfbc74f64, __VMLINUX_SYMBOL_STR(__copy_from_user) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xfe990052, __VMLINUX_SYMBOL_STR(gpio_free) },
	{ 0xb56ecb4b, __VMLINUX_SYMBOL_STR(gpiod_unexport) },
	{ 0x4b71367e, __VMLINUX_SYMBOL_STR(gpiod_direction_output_raw) },
	{ 0xf69727f5, __VMLINUX_SYMBOL_STR(gpiod_export) },
	{ 0x47229b5c, __VMLINUX_SYMBOL_STR(gpio_request) },
	{ 0x52de684a, __VMLINUX_SYMBOL_STR(gpiod_set_raw_value) },
	{ 0x47fb99c6, __VMLINUX_SYMBOL_STR(gpio_to_desc) },
	{ 0x12a38747, __VMLINUX_SYMBOL_STR(usleep_range) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "A162B23A7D4F9FC82A25738");
