#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/kmod.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CS158");
MODULE_DESCRIPTION("Encryption Module");

char buffer[2000];
static char *filepath = "default";
static char *encryption_key = "key";

module_param(filepath, charp, S_IRUGO);
MODULE_PARM_DESC(filepath, "filepath");

module_param(encryption_key, charp, S_IRUGO);
MODULE_PARM_DESC(encryption_key, "key");

static void decrypt_string(char *plaintext, const char *key) {
    size_t key_len = strlen(key);
    size_t str_len = strlen(plaintext);
    size_t i;

    for (i = 0; i < 2000; ++i) {
        if(plaintext[i]!='\n' && plaintext[i]!='\0')
        	plaintext[i] ^= (key[i % key_len]-'a');
        printk(KERN_INFO "%c", plaintext[i]);
    }
}

static int __init string_encrypt_init(void) {
    ssize_t bytes_read;
    ssize_t bytes_written;
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
    filp_close(file, NULL);
    
    decrypt_string(buffer, encryption_key);
    
    file = filp_open(filepath, O_WRONLY|O_CREAT, 0644);
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

static void __exit string_encrypt_exit(void) {
    printk(KERN_INFO "String encryption module unloaded\n");
}

module_init(string_encrypt_init);
module_exit(string_encrypt_exit);
