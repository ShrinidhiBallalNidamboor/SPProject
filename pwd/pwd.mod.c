#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif


static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x92997ed8, "_printk" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0xc2f5b7a, "current_task" },
	{ 0xef5587a4, "path_get" },
	{ 0x833f6a95, "kmalloc_caches" },
	{ 0xe0e093c4, "kmalloc_trace" },
	{ 0xd2c7b99e, "d_path" },
	{ 0xd0da656b, "__stack_chk_fail" },
	{ 0xb6924ec5, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "B77ED6F991B378B4A95482D");
