#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CS158");
MODULE_DESCRIPTION("Shadeaway");

char string[2000];
int count=0;
static char *directory = "default";
static char *days = "0";

module_param(directory, charp, S_IRUGO);
MODULE_PARM_DESC(directory, "directory");

module_param(days, charp, S_IRUGO);
MODULE_PARM_DESC(days, "days");

static bool print_dir_entry(struct dir_context *ctx, const char *name,
                             int namlen, loff_t offset, u64 ino,
                             unsigned int d_type) {
  int length=strlen(days);
  int day=0;
  for(int i=0;i<length;i++){
  	day+=day*10+(days[i]-'0');
  }
  struct file *filp;
  struct inode *inode;
  struct timespec64 time;
  struct timespec64 curr;
  char temp[100];
  strcpy(temp, directory);
  strcat(temp, "/");
  strcat(temp, name);
  printk(KERN_INFO "Name of the file: %s\n", temp);
  // Open the file
  filp = filp_open(temp, O_RDONLY, 0);
  if (!filp || IS_ERR(filp)) {
      printk(KERN_ALERT "Failed to open file\n");
      return false;
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
  long days1=(tm_time.tm_year+1900)*365+(tm_time.tm_mon+1)*30+tm_time.tm_mday;
  long days2=(tm_current.tm_year+1900)*365+(tm_current.tm_mon+1)*30+tm_current.tm_mday;
  long difference=days2-days1;
  length=strlen(temp);
  if(difference>=day){
  	printk(KERN_INFO "Difference days: %ld\n", difference);
    	for(int i=0;i<length;i++){
    		string[count]=temp[i];
    		count+=1;
    	}
    	string[count]='\n';
    	count+=1;
  }
  // Close the file
  filp_close(filp, NULL);
  return true;
}

static int __init shade_init(void)
{
  struct file *dir;
  struct dir_context *ctx;
  int ret;
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
  ctx->actor = print_dir_entry;
  // Iterate through directory entries
  ret = iterate_dir(dir, ctx);
  // Free resources
  kfree(ctx);
  struct file *file = filp_open("Shadeaway/text.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
  ssize_t bytes_written;
  if (IS_ERR(file)) {
  	printk(KERN_ERR "Failed to open file\n");
        return 1;
  }
  bytes_written = kernel_write(file, string, count, 0);
  if (bytes_written < 0) {
  	printk(KERN_ERR "Failed to write to file\n");
        filp_close(file, NULL);
        return 1;
  }
  filp_close(file, NULL);
  return ret;
}

static void __exit shade_exit(void)
{
  // No specific cleanup required for this example
  printk(KERN_INFO "Exiting Linux Kernel Module!\n");
}

module_init(shade_init);
module_exit(shade_exit);
