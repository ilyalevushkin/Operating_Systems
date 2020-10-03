#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Levushkin Ilya");

char* export_char = "Hello from md1!";
int export_int = 52;


extern char* md1_str(int n)
{
	printk(KERN_INFO "md1_str() called!\n");
	switch(n)
	{
		case 1:
			return "First message.\n";
			break;
		case 2:
			return "Second message.\n";
			break;
		case 3:
			return "Please, print 1 to get first message or 2 to get second.\n";
			break;
	}
}

extern int md1_fact(int n)
{
	int i, res;
	res = 1;
	printk(KERN_INFO "md1_fact() called!\n");
	for (i = 2; i <= n; i++)
	{
		res *= i;
	}
	return res;
}



EXPORT_SYMBOL(md1_str);
EXPORT_SYMBOL(md1_fact);

EXPORT_SYMBOL(export_char);
EXPORT_SYMBOL(export_int);


static int __init md_init(void)
{
	printk(KERN_INFO "Module md1 loaded!\n");
	return 0;
}

static void __exit md_exit(void)
{
	printk(KERN_INFO "Module md1 unloaded!\n");
}

module_init(md_init);
module_exit(md_exit);


