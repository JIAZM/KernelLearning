#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/interrupt.h>

static int irq;
static char *devname;

module_param(irq, int, 0644);
module_param(devname, charp, 0644);

struct myirqdev{
	int devid;
};

struct myirqdev mydev = {1119};

static struct tasklet_struct mytasklet;

static void mytasklet_handler(unsigned long data)
{
	printk("I am a tasklet handler \r\n");
	printk("Get into down handler by tasklet \r\n");

	return ;
}

static irqreturn_t myirq_handler(int irq, void *dev)
{
	struct myirqdev mydev;
	static int count = 1;

	mydev = *(struct myirqdev *)dev;
	printk("key count: %d ... \r\n", count++);
	printk("devid: %d ISR is working ... \r\n", mydev.devid);
	printk("ISE is leaving ...\r\n");

	// tasklet ...
	tasklet_init(&mytasklet, mytasklet_handler, 0);
	tasklet_schedule(&mytasklet);

	return IRQ_HANDLED;
	// IRQ_HANDLED means received interrupt signal and has made handle
}


static int __init myirq_init(void)
{
	printk("Module is workign ... \r\n");

	if(request_irq(irq, myirq_handler, IRQF_SHARED, devname, &mydev) != 0){
		printk("%s request IRQ: %d failed ... \r\n", devname, irq);
		return -1;
	}
	printk("%s request IRQ: %d success... \r\n", devname, irq);

	return 0;
}

static void __exit myirq_exit(void)
{
	printk("Module is leaving... \r\n");

	free_irq(irq, &mydev);
	tasklet_kill(&mytasklet);

	printk("Free irq: %d \r\n", irq);
}

MODULE_LICENSE("GPL");
module_init(myirq_init);
module_exit(myirq_exit);
