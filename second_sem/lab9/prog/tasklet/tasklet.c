#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/timex.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ilya Levushkin");

#define SHARED_IRQ 1
static int irq = SHARED_IRQ, my_dev_id, irq_counter = 0;

module_param(irq, int, S_IRUGO);

char my_tasklet_data[] = "my_tasklet_function was called";

void my_tasklet_function(unsigned long data);

DECLARE_TASKLET(my_tasklet, my_tasklet_function, 
                 (unsigned long)&my_tasklet_data);



void my_tasklet_function(unsigned long data)
{
	printk(KERN_INFO "[TASKLET] state: %ld, count: %d, data: %ld",
					my_tasklet.state, my_tasklet.count, my_tasklet.data);
    return;
}

static irqreturn_t my_interrupt( int irq, void *dev_id)
{
  if (irq == SHARED_IRQ)
  {
    irq_counter++;
    printk(KERN_INFO "[INTERRUPT] In the ISR: counter = %d\n", irq_counter);
    tasklet_schedule(&my_tasklet);
    return IRQ_HANDLED;
  }
  else
    return IRQ_NONE;
}

static int __init my_tasklet_init(void)
{
	if (request_irq(irq, my_interrupt, IRQF_SHARED, "my_interrupt", &my_dev_id))
    		return -1;
    printk(KERN_INFO 
    	"[INTERRUPT] Successfully loading ISR handler on IRQ %d\n", irq);
	printk(KERN_INFO "[MODULE] Module is now loaded.\n");
	return 0;
}

static void __exit my_tasklet_exit(void)
{
  	tasklet_kill(&my_tasklet);
	synchronize_irq(irq);
   	free_irq(irq, &my_dev_id);
   	printk(KERN_INFO 
   		"[INTERRUPT] Successfully unloading, irq_counter = %d\n", irq_counter);
	printk(KERN_INFO "[MODULE] Module is now unloaded.\n");
  	return;
}

module_init(my_tasklet_init);
module_exit(my_tasklet_exit);
