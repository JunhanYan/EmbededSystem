#include <linux/cpumask.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/kernel_stat.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/seq_file.h>
#include <linux/slab.h>
#include <linux/time.h>
#include <asm/cputime.h>
#include <linux/tick.h>



static int show_stat(struct seq_file *p, void *v)
{
	int i;
	u64 user, nice, system, idle, iowait, irq, softirq, steal;
	u64 guest, guest_nice;

	user = nice = system = idle = iowait =
		irq = softirq = steal = 0;
	guest = guest_nice = 0;
	

	for_each_possible_cpu(i) {
		user += kcpustat_cpu(i).cpustat[CPUTIME_USER];
		nice += kcpustat_cpu(i).cpustat[CPUTIME_NICE];
		system += kcpustat_cpu(i).cpustat[CPUTIME_SYSTEM];
		
		
		irq += kcpustat_cpu(i).cpustat[CPUTIME_IRQ];
		softirq += kcpustat_cpu(i).cpustat[CPUTIME_SOFTIRQ];
		steal += kcpustat_cpu(i).cpustat[CPUTIME_STEAL];
		guest += kcpustat_cpu(i).cpustat[CPUTIME_GUEST];
		guest_nice += kcpustat_cpu(i).cpustat[CPUTIME_GUEST_NICE];
	}
	

	seq_puts(p, "cpu ");
	seq_puts(p, " user");
	seq_put_decimal_ull(p, ' ', cputime64_to_clock_t(user));
	seq_puts(p, " nice");
	seq_put_decimal_ull(p, ' ', cputime64_to_clock_t(nice));
	seq_puts(p, " sys");
	seq_put_decimal_ull(p, ' ', cputime64_to_clock_t(system));
	seq_puts(p, " irq");
	seq_put_decimal_ull(p, ' ', cputime64_to_clock_t(irq));
	seq_puts(p, " sirq");
	seq_put_decimal_ull(p, ' ', cputime64_to_clock_t(softirq));
	seq_puts(p, " steal");
	seq_put_decimal_ull(p, ' ', cputime64_to_clock_t(steal));
	seq_puts(p, " guest");
	seq_put_decimal_ull(p, ' ', cputime64_to_clock_t(guest));
	seq_puts(p, " gnice");
	seq_put_decimal_ull(p, ' ', cputime64_to_clock_t(guest_nice));
	seq_putc(p, '\n');
	for_each_online_cpu(i) {
		/* Copy values here to work around gcc-2.95.3, gcc-2.96 */
		user = kcpustat_cpu(i).cpustat[CPUTIME_USER];
		nice = kcpustat_cpu(i).cpustat[CPUTIME_NICE];
		system = kcpustat_cpu(i).cpustat[CPUTIME_SYSTEM];
		
		irq = kcpustat_cpu(i).cpustat[CPUTIME_IRQ];
		softirq = kcpustat_cpu(i).cpustat[CPUTIME_SOFTIRQ];
		steal = kcpustat_cpu(i).cpustat[CPUTIME_STEAL];
		guest = kcpustat_cpu(i).cpustat[CPUTIME_GUEST];
		guest_nice = kcpustat_cpu(i).cpustat[CPUTIME_GUEST_NICE];
		seq_printf(p, "cpu%d ", i);
		seq_puts(p, " user");
		seq_put_decimal_ull(p, ' ', cputime64_to_clock_t(user));
		seq_puts(p, " nice");
		seq_put_decimal_ull(p, ' ', cputime64_to_clock_t(nice));
		seq_puts(p, " sys");
		seq_put_decimal_ull(p, ' ', cputime64_to_clock_t(system));
		seq_puts(p, " irq");
		seq_put_decimal_ull(p, ' ', cputime64_to_clock_t(irq));
		seq_puts(p, " sirq");
		seq_put_decimal_ull(p, ' ', cputime64_to_clock_t(softirq));
		seq_puts(p, " steal");
		seq_put_decimal_ull(p, ' ', cputime64_to_clock_t(steal));
		seq_puts(p, " guest");
		seq_put_decimal_ull(p, ' ', cputime64_to_clock_t(guest));
		seq_puts(p, " gnice");
		seq_put_decimal_ull(p, ' ', cputime64_to_clock_t(guest_nice));
		seq_putc(p, '\n');
	}
	


	return 0;
}

static int stat_open(struct inode *inode, struct file *file)
{
	int res;

	

	res = single_open(file, show_stat, NULL);
	
	return res;
}

static const struct file_operations proc_stat_operations = {
	.open		= stat_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int __init proc_stat_init(void)
{
	proc_create("mystat", 0, NULL, &proc_stat_operations);
	return 0;
}

static void __exit my_exit(void) 
{  
    remove_proc_entry("mystat",NULL);
    printk("exit module mymemoryinfo\n");  
}
module_init(proc_stat_init);
module_exit(my_exit); 
