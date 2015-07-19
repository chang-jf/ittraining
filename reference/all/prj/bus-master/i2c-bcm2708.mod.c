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
	{ 0x149c7752, __VMLINUX_SYMBOL_STR(param_ops_uint) },
	{ 0x60ee9172, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0xc586db14, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0xe6354fda, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x81111746, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x514a1236, __VMLINUX_SYMBOL_STR(clk_get_rate) },
	{ 0xcef3d529, __VMLINUX_SYMBOL_STR(i2c_add_numbered_adapter) },
	{ 0xd6b8e852, __VMLINUX_SYMBOL_STR(request_threaded_irq) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0xc6c7cbbf, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x3f151a5a, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xfb961d14, __VMLINUX_SYMBOL_STR(__arm_ioremap) },
	{ 0x87024868, __VMLINUX_SYMBOL_STR(clk_enable) },
	{ 0xd27b2591, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0xdd2706e8, __VMLINUX_SYMBOL_STR(clk_prepare) },
	{ 0xf6152744, __VMLINUX_SYMBOL_STR(clk_get) },
	{ 0x309f8007, __VMLINUX_SYMBOL_STR(platform_get_irq) },
	{ 0xcc435e6e, __VMLINUX_SYMBOL_STR(platform_get_resource) },
	{ 0xb64c6159, __VMLINUX_SYMBOL_STR(of_property_read_u32_array) },
	{ 0xf6325cbe, __VMLINUX_SYMBOL_STR(of_alias_get_id) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xff178f6, __VMLINUX_SYMBOL_STR(__aeabi_idivmod) },
	{ 0xac230ff2, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x7cf9099, __VMLINUX_SYMBOL_STR(wait_for_completion_timeout) },
	{ 0x3bd1b1f6, __VMLINUX_SYMBOL_STR(msecs_to_jiffies) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0xd4669fad, __VMLINUX_SYMBOL_STR(complete) },
	{ 0x5fc56a46, __VMLINUX_SYMBOL_STR(_raw_spin_unlock) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x2e1ca751, __VMLINUX_SYMBOL_STR(clk_put) },
	{ 0xcf036bd3, __VMLINUX_SYMBOL_STR(clk_unprepare) },
	{ 0x6fee290c, __VMLINUX_SYMBOL_STR(clk_disable) },
	{ 0xc2165d85, __VMLINUX_SYMBOL_STR(__arm_iounmap) },
	{ 0xf20dabd8, __VMLINUX_SYMBOL_STR(free_irq) },
	{ 0xe30add01, __VMLINUX_SYMBOL_STR(i2c_del_adapter) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("of:N*T*Cbrcm,bcm2708-i2c*");

MODULE_INFO(srcversion, "0ACD78A7932FB3F3042F78B");
