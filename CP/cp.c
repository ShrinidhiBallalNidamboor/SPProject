#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/kmod.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CS158");
MODULE_DESCRIPTION("List contents");

static char *from = "default1";
static char *to = "default2";

char buffer[2000]; // Buffer to store read data

module_param(from, charp, S_IRUGO);
MODULE_PARM_DESC(from, "from");

module_param(to, charp, S_IRUGO);
MODULE_PARM_DESC(to, "to");

static int __init ls_init(void) {
    ssize_t bytes_read;
    ssize_t bytes_written;
    struct file *file;
    
    file = filp_open(from, O_RDONLY, 0);
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
    filp_close(file, NULL);
    
    file = filp_open(to, O_WRONLY|O_CREAT, 0644);
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

static void __exit ls_cleanup(void) {
    printk(KERN_INFO "Exiting execute_binary module\n");
}

module_init(ls_init);
module_exit(ls_cleanup);
