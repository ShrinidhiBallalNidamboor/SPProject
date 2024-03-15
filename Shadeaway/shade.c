#include <linux/fs.h>
#include <linux/time.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/uaccess.h>
#include <linux/string.h>

static char *directory = "default";
static char *days = "0";

module_param(directory, charp, S_IRUGO);
MODULE_PARM_DESC(directory, "directory");

module_param(days, charp, S_IRUGO);
MODULE_PARM_DESC(days, "days");

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CS158");
MODULE_DESCRIPTION("Shadeaway");

static int print_dir_entry(struct dir_context *ctx, const char *name, int namlen, loff_t offset, u64 ino, unsigned int d_type) {
  	int length=strlen(days);
  	int day=0;
  	for(int i=0;i<length;i++){
  		day+=day*10+(days[i]-'0');
  	}
  	struct file *filp;
    	struct inode *inode;
    	struct timespec64 time;
    	struct timespec64 curr;
    	char *temp;
    	strcpy(temp, directory);
    	strcat(temp, name);
    	// Open the file
    	filp = filp_open(temp, O_RDONLY, 0);
    	if (!filp || IS_ERR(filp)) {
        	printk(KERN_ALERT "Failed to open file\n");
        	return -ENOENT;
    	}
    	// Get the inode
    	inode = file_inode(filp);
    	// Get the creation timestamp
    	time = inode->i_mtime;
    	curr = ktime_to_timespec64(ktime_get_real());
    	struct tm tm_time;
    	struct tm tm_current;
    	ktime_get_real_ts64(&time);
    	ktime_get_real_ts64(&curr);
    	time64_to_tm(time.tv_sec, 0, &tm_time);
    	time64_to_tm(curr.tv_sec, 0, &tm_current);
    	long int days1=(tm_time.tm_year+1900)*365+(tm_time.tm_mon+1)*30+tm_time.tm_mday;
    	long int days2=(tm_current.tm_year+1900)*365+(tm_current.tm_mon+1)*30+tm_current.tm_mday;
    	long int difference=days2-days1;
    	if(difference>=day){
    		struct file *file = filp_open("text.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    		ssize_t bytes_written;
    		char *buffer;
    		strcpy(buffer, name);
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
    	}
    	// Close the file
    	filp_close(filp, NULL);
    	return 0;
}

static int __init shadeaway_init(void) {
  	struct file *dir;
  	struct dir_context *ctx;
  	// Open a directory (replace with your desired path)
  	dir = filp_open(directory, O_RDONLY, 0);
  	if (IS_ERR(dir)) {
    		printk(KERN_ERR "Failed to open directory\n");
    		return PTR_ERR(dir);
  	}
  	// Allocate and initialize dir_context
  	ctx = kzalloc(sizeof(struct dir_context), GFP_KERNEL);
  	if (!ctx) {
    		printk(KERN_ERR "Failed to allocate memory\n");
  	}
  	print_dir_entry;
  	// Free resources
  	kfree(ctx);
    	return 0;
}

static void __exit shadeaway_exit(void) {
  	// No specific cleanup required for this example
  	printk(KERN_INFO "Exiting Linux Kernel Module!\n");
}

module_init(shadeaway_init);
module_exit(shadeaway_exit);
