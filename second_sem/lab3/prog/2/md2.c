#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Levushkin Ilya");

extern char* export_char;
extern int export_int;

extern char* md1_str(int n);
extern int md1_fact(int n);

static int __init md_init(void)
{
    printk(KERN_INFO "Module md2 is now loaded!\n");
    printk(KERN_INFO "+ md2: Число экспортированное из md1: %d\n", export_int);
    printk(KERN_INFO "+ md2: Строка экспортированная из md1: %s\n", export_char);
    printk(KERN_INFO "+ md2: Результат работы функции md1_str(1): %s\n", md1_str(1));
    printk(KERN_INFO "+ md2: Результат работы функции md1_str(2): %s\n", md1_str(2));
    printk(KERN_INFO "+ md2: Результат работы функции md1_str(3): %s\n", md1_str(3));
    printk(KERN_INFO "+ md2: Результат работы функции md1_fact(5): %d\n", md1_fact(5));
    return 0;
}

static void __exit md_exit(void)
{
    printk(KERN_INFO "Module md2 is unloaded!\n");
}

module_init(md_init);
module_exit(md_exit);
