#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/timer.h>
#include <linux/fs.h>
#include <linux/sched.h> 
#include <linux/uaccess.h>

void my_timer_callback(struct timer_list * my_timer);


#define TIMER 5000

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Levushkin Ilya");

static struct timer_list my_timer;

int init_timer(void)
{
	int ret;
	timer_setup(&my_timer, my_timer_callback, 0);

	ret = mod_timer(&my_timer, jiffies + msecs_to_jiffies(TIMER));
	if (ret)
	{
		printk("Error in mod_timer\n");
	}
	return 0;
}

void delete_timer(void)
{
	int ret;
	ret = del_timer(&my_timer);
}

int print_new_load_proc_module_info(void)
{
	char *argv[] = { "/home/ilalevuskin/Desktop/example/proc_modules", NULL};
	static char *envp[] = {
	        "HOME=/",
	        "TERM=linux",
	        "PATH=/home/ilalevuskin/Desktop/example", NULL};
	call_usermodehelper(argv[0], argv, envp, UMH_NO_WAIT);
	return 0;
}


void my_timer_callback(struct timer_list * my_timer)
{
	delete_timer();
	print_new_load_proc_module_info();
	init_timer();
}

static int __init monitoring_init(void)
{
	printk("Monitoring module was installed\n");
	printk("Kernel modules info update every (%d)ms (%ld)\n", TIMER, jiffies);

	return init_timer();
}

static void __exit monitoring_exit(void)
{
	delete_timer();
	printk("Monitoring module uninstalled\n");
}
module_init(monitoring_init);
module_exit(monitoring_exit); 