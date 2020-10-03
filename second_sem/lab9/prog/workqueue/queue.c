#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/workqueue.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ilya Levushkin");

#define SHARED_IRQ 1
static int irq = SHARED_IRQ, my_dev_id, irq_counter = 0;
module_param( irq, int, S_IRUGO );

struct workqueue_struct *my_wq;
void hardwork_function(struct work_struct *work);

DECLARE_WORK(hardwork, hardwork_function);


void hardwork_function(struct work_struct *work)
{
    printk(KERN_INFO "[WQ] data: %d", work->data);
    return;
}

static irqreturn_t my_interrupt(int irq, void *dev_id)
{
  if (irq == SHARED_IRQ) {
    irq_counter++;
    printk(KERN_INFO "[INTERRUPT] In the ISR: counter = %d\n", irq_counter);
    queue_work(my_wq, &hardwork);
    return IRQ_HANDLED;
  }
  else return IRQ_NONE;
}

static int __init my_workqueue_init(void)
{
  if(request_irq(irq, my_interrupt, IRQF_SHARED, "my_interrupt2ß", &my_dev_id))
        return -1;
  
  printk(KERN_INFO 
        "[INTERRUPT] Successfully loading ISR handler on IRQ %d\n", irq);


  if (my_wq = create_workqueue("my_queue"))
  {
      printk(KERN_INFO "[MODULE] Workqueue created.\n");
  }

	printk(KERN_INFO "[MODULE] Module is now loaded.\n");
	return 0;
}

static void __exit my_workqueue_exit(void)
{
  flush_workqueue(my_wq);
  destroy_workqueue(my_wq);
	synchronize_irq(irq);
  free_irq(irq, &my_dev_id);
  printk(KERN_INFO 
    "[INTERRUPT] Successfully unloading, irq_counter = %d\n", irq_counter);
	printk(KERN_INFO "[MODULE] Module is now unloaded.\n");
  return;
}

module_init(my_workqueue_init);
module_exit(my_workqueue_exit);
