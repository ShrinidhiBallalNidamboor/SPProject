#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CS158");
MODULE_DESCRIPTION("Touch");

static char *filename = "default.txt"; // Default filename
module_param(filename, charp, S_IRUGO); // Define module parameter for filename
MODULE_PARM_DESC(filename, "filename");

static int __init touch_init(void){
	struct file *fp = (struct file *) NULL;
	fp = filp_open(filename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    	if (IS_ERR(fp)) {
        	printk(KERN_ERR "Failed to open file\n");
        	return PTR_ERR(fp);
    	}
	filp_close(fp, NULL);
	return 0;
}

static void __exit touch_cleanup(void){
	printk(KERN_INFO "Exiting linked list Code!\n");
}

module_init(touch_init);
module_exit(touch_cleanup);
