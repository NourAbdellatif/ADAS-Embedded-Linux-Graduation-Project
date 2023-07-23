#include <linux/module.h>


static int __init mydriver_init(void)
{
    printk("Driver init\n");
    return 0; 
}

static void __exit mydriver_exit(void)
{
    printk("Driver exit\n");
}


module_init(mydriver_init);
module_exit(mydriver_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hussam");
MODULE_DESCRIPTION("This is a test driver");
MODULE_VERSION("1.0");
