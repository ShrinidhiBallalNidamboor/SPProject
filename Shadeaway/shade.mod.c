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
	{ 0x570ce3ef, "filp_open" },
	{ 0x833f6a95, "kmalloc_caches" },
	{ 0xe0e093c4, "kmalloc_trace" },
	{ 0xb65bf686, "iterate_dir" },
	{ 0x37a0cba, "kfree" },
	{ 0xab2e2714, "kernel_write" },
	{ 0x55bbf72f, "filp_close" },
	{ 0x754d539c, "strlen" },
	{ 0x69acdf38, "memcpy" },
	{ 0xf9c0b663, "strlcat" },
	{ 0xcbd4898c, "fortify_panic" },
	{ 0xc4f0da12, "ktime_get_with_offset" },
	{ 0x65929cae, "ns_to_timespec64" },
	{ 0x9ec6ca96, "ktime_get_real_ts64" },
	{ 0xfff5afc, "time64_to_tm" },
	{ 0xa916b694, "strnlen" },
	{ 0xd0da656b, "__stack_chk_fail" },
	{ 0x87a21cb3, "__ubsan_handle_out_of_bounds" },
	{ 0x5b34092f, "param_ops_charp" },
	{ 0xb6924ec5, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "822434DCAA516202B82C6E2");
