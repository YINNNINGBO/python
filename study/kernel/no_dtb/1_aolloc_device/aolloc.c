#include "user.h" // #include "user.h"

int major = 11;
int minor = 0;
int mychar_num = 1;

struct cdev mydev;

int mychar_open(struct inode *pnode, struct file *pfile)
{
    printk("mychar_open is called\n");
    return 0;
}

int mychar_close(struct inode *pnode, struct file *pfile)
{
    printk("mychar_close is called\n");
    return 0;
}

struct file_operations myops = {
    .owner = THIS_MODULE,
    .open = mychar_open,
    .release = mychar_close,
};

int mychar_init(void)
{
    int ret = 0;
    dev_t devno = MKDEV(major, minor);

    /* 申请设备号 */
    ret = register_chrdev_region(devno, mychar_num, "mychar");
    if (ret)
    {
        ret = alloc_chrdev_region(&devno, minor, mychar_num, "mychar");
        if (ret)
        {
            printk("get devno failed\n");
            return -1;
        }
        major = MAJOR(devno); // 容易遗漏，注意
    }

    /* 给struct cdev对象指定操作函数集 */
    cdev_init(&mydev, &myops);

    /* 将 struct cdev对象添加到内核对应的数据结构里 */
    mydev.owner = THIS_MODULE;
    cdev_add(&mydev, devno, mychar_num);

    return 0;
}

void __exit mychar_exit(void)
{
    dev_t devno = MKDEV(major, minor);

    cdev_del(&mydev);

    unregister_chrdev_region(devno, mychar_num);
}

// 表示支持GPL的开源协议
MODULE_LICENSE("GPL");

module_init(mychar_init);
module_exit(mychar_exit);
