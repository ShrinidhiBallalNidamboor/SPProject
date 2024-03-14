#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/rcupdate.h>
#include <linux/fdtable.h>
#include <linux/fs.h>
#include <linux/fs_struct.h>
#include <linux/dcache.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("CS316");
MODULE_DESCRIPTION("PWD Command");

static int __init current_init(void)
{

 	char *cwd;
        struct path pwd, root; 
 	pwd = current->fs->pwd;
	path_get(&pwd);
	char *buf = (char *)kmalloc(GFP_KERNEL,100*sizeof(char));
	cwd = d_path(&pwd,buf,100*sizeof(char));
	printk(KERN_INFO "Current Working Directory: %s",cwd);

	return 0;
}

static void __exit current_exit(void)
{
 	printk(KERN_INFO "Exiting Kernel Module!");
}

module_init(current_init);
module_exit(current_exit);



