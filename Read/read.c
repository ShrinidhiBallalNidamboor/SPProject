#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/kmod.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CS158");
MODULE_DESCRIPTION("List contents");

static char *filepath = "default";

char buffer[2000]; // Buffer to store read data

module_param(filepath, charp, S_IRUGO);
MODULE_PARM_DESC(filepath, "filename");

static int __init ls_init(void) {
    ssize_t bytes_read;
    struct file *file;
    
    file = filp_open(filepath, O_RDONLY, 0);
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
    printk(KERN_INFO "Contents of the file\n");
    printk(KERN_INFO "%s\n", buffer);
    filp_close(file, NULL);
    return 0;
}

static void __exit ls_cleanup(void) {
    printk(KERN_INFO "Exiting execute_binary module\n");
}

module_init(ls_init);
module_exit(ls_cleanup);
