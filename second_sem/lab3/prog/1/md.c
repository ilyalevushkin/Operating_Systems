#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>

#include <linux/init_task.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Levushkin Ilya");

static int __init my_module_init(void)
{
	printk(KERN_INFO "Module is now loaded.\n");
	struct task_struct *task = &init_task;

	do
	{
		printk(KERN_INFO "---%s-%d, parent %s-%d", task->comm, 
			task->pid, task->parent->comm, task->parent->pid);
	} while ((task = next_task(task)) != &init_task);

	printk(KERN_INFO "---%s-%d, parent %s-%d", current->comm, 
		current->pid, current->parent->comm, current->parent->pid);
	return 0;
}


static void __exit my_module_cleanup(void) {
	printk(KERN_INFO "Module is now unloaded.\n");
}


module_init(my_module_init);
module_exit(my_module_cleanup);
