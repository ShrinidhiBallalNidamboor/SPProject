#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/kmod.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CS158");
MODULE_DESCRIPTION("remove");

char buffer[200];

static char *directory = "default";

module_param(directory, charp, S_IRUGO);
MODULE_PARM_DESC(directory, "directory");

static int __init mkdir_init(void) {
    ssize_t bytes_written;
    struct file *file;
    file = filp_open("Mkdir/text.txt", O_WRONLY|O_CREAT, 0644);
    strcpy(buffer, directory);
    strcat(buffer, "\n");
    if (IS_ERR(file)) {
        printk(KERN_ERR "Failed to open file\n");
        return PTR_ERR(file);
    }
    bytes_written = kernel_write(file, buffer, sizeof(buffer), 0);
    if (bytes_written < 0) {
        printk(KERN_ERR "Failed to write to file\n");
        filp_close(file, NULL);
        return bytes_written;
    }
    filp_close(file, NULL);
    return 0;
}

static void __exit mkdir_exit(void) {
    printk(KERN_INFO "String encryption module unloaded\n");
}

module_init(mkdir_init);
module_exit(mkdir_exit);
