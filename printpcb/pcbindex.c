#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/fdtable.h>
#include <linux/fs_struct.h>
#include <linux/mm_types.h>
#include <linux/init_task.h>
#include <linux/atomic.h>

MODULE_LICENSE("GPL");

static int __init print_pcb(void)
{
	struct task_struct *task, *p;
	struct list_head *pos;

	int count = 0;

	printk("begin \r\n");

	task = &init_task;

	list_for_each(pos, &task->tasks) {
		p = list_entry(pos, struct task_struct, tasks);
		count++;
		printk("\r\n");
		printk("pid : %d; state : %lx; prio : %d; static_prio : %d; parent : %d;  count : %d; umask : %d;   \r\n", p->pid, p->state, p->prio, p->static_prio, (p->parent)->pid, atomic_read(&((p->files)->count)), (p->fs)->umask);

		if(p->mm){
			printk("total_vm : %ld \r\n", (p->mm)->total_vm);
		}
	}

	printk("process number : %d \r\n", count);

	return 0;
}

static void __exit exit_pcb(void)
{
	printk("exiting... \r\n");
}

module_init(print_pcb);
module_exit(exit_pcb);
