#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/kmod.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CS158");
MODULE_DESCRIPTION("Mkdir");

static char *binary_name = "a.out";
static char *binary_arg = "Text";
module_param(binary_arg, charp, S_IRUGO); // Define module parameter for filename
MODULE_PARM_DESC(binary_arg, "Name of the file to create");

static int __init mkdir_init(void) {
    char *argv[] = {binary_name, binary_arg, NULL};
    char **envp = NULL;
    printk(KERN_INFO "Directory: %s", argv[1]);
    call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);
    return 0;
}

static void __exit mkdir_cleanup(void) {
    printk(KERN_INFO "Exiting execute_binary module\n");
}

module_init(mkdir_init);
module_exit(mkdir_cleanup);
