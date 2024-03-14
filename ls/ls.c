#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CS316");
MODULE_DESCRIPTION("LS Command");

static char *directory = "default";

module_param(directory, charp, S_IRUGO);
MODULE_PARM_DESC(directory, "directory");

static bool print_dir_entry(struct dir_context *ctx, const char *name,
                             int namlen, loff_t offset, u64 ino,
                             unsigned int d_type) {
  printk(KERN_INFO "  - %.*s (type: %u)\n", namlen, name, d_type);
  return true;
}

static int __init my_init(void)
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

  return ret;
}

static void __exit my_exit(void)
{
  // No specific cleanup required for this example
  printk(KERN_INFO "Exiting Linux Kernel Module!\n");
}

module_init(my_init);
module_exit(my_exit);
