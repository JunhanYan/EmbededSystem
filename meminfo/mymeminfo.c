#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h> 
#include <linux/mm.h>
#include <linux/mman.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/atomic.h>
#include <asm/page.h> 

 MODULE_AUTHOR("yanjunhan");
 MODULE_LICENSE("GPL"); 

static int meminfo_proc_show(struct seq_file *m, void *v)
{
	struct sysinfo i;

/*
 * display in kilobytes.
 */
#define K(x) ((x) << (PAGE_SHIFT - 10))
	si_meminfo(&i);

	seq_printf(m,
		"MemTotal:       %8lu kB\n"
		"MemFree:        %8lu kB\n"
		"MemShared:      %8lu kB\n"
		"Buffers:        %8lu kB\n"
		"HighMemoryTotal:        %8lu kB\n"
		"HighMemoryRree:        %8lu kB\n"	
		,
		K(i.totalram),
		K(i.freeram),
		K(i.sharedram),
		K(i.bufferram),
		K(i.totalhigh),
		K(i.freehigh)
		);
	return 0;
#undef K
}

static int meminfo_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, meminfo_proc_show, NULL);
}

static const struct file_operations meminfo_proc_fops = {
	.open		= meminfo_proc_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int __init proc_meminfo_init(void)
{
	proc_create("mymeminfo", 0, NULL, &meminfo_proc_fops);
	return 0;
}
static void __exit my_exit(void) 
{  
    remove_proc_entry("mymeminfo",NULL);
    printk("exit module mymemoryinfo\n");  
}  
module_init(proc_meminfo_init);
module_exit(my_exit); 
