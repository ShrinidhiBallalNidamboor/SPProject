#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/kmod.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CS158");
MODULE_DESCRIPTION("List contents");

static char *binary_name = "/home/shrinidhi/LS/a.out";
static char *binary_arg = "Text";

module_param(binary_arg, charp, S_IRUGO); // Define module parameter for filename
MODULE_PARM_DESC(binary_arg, "Argument for a.out");

static int __init ls_init(void) {
    char *argv[] = {binary_name, NULL};
    char *envp[] = {
        "HOME=/",
        "PATH=/sbin:/bin:/usr/sbin:/usr/bin", NULL};
    char buffer[256]; // Buffer to store read data
    ssize_t bytes_read;
    struct file *file;
    int result = call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);
    printk(KERN_ERR "Failed to execute usermode program: %d\n", result);
    file = filp_open("file.txt", O_RDONLY, 0);
    if (IS_ERR(file)) {
        printk(KERN_ERR "Failed to open file: %ld\n", PTR_ERR(file));
        return PTR_ERR(file);
    }
    bytes_read = kernel_read(file, buffer, sizeof(buffer), 0);
    if (bytes_read < 0) {
        printk(KERN_ERR "Failed to read from file: %zd\n", bytes_read);
        filp_close(file, NULL);
        return bytes_read;
    }
    printk(KERN_INFO "List Files:\n");
    printk(KERN_INFO "%s", buffer);
    filp_close(file, NULL);
    return 0;
}

static void __exit ls_cleanup(void) {
    printk(KERN_INFO "Exiting execute_binary module\n");
}

module_init(ls_init);
module_exit(ls_cleanup);
