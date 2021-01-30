#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE( "GPL" );
MODULE_AUTHOR("Levushkin Ilya");

static int __init test_init(void)
{
	printk("Test module was installed\n");
	return 0;
}

static void __exit test_exit(void)
{
	printk("Test module uninstalled\n");
}
module_init(test_init);
module_exit(test_exit); 