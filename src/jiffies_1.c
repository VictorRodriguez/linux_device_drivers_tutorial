/*  
 *  hello-1.c - The simplest kernel module.
 */
#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/jiffies.h>

#define DELAY 3

int init_module(void)
{
	int n = 10;

	printk(KERN_INFO "Hello world 1.\n");
	unsigned long j, stamp_1, stamp_half, stamp_n,jifdone;
	j = jiffies;                      /* read the current value */
	stamp_1    = j + HZ;              /* 1 second in the future */
	stamp_half = j + HZ/2;            /* half a second */
	stamp_n    = j + n * HZ / 1000;   /* n milliseconds */

	printk(KERN_INFO "Current time = %lu \n",j);
	printk(KERN_INFO "1 second in the future = %lu \n",stamp_1 );
	printk(KERN_INFO "half a second= %lu \n",stamp_half );
	printk(KERN_INFO "n milliseconds = %lu \n",stamp_n );

/*
	jifdone = jiffies + DELAY * HZ;
	
	while ( time_before( jiffies,jifdone))
	{
		printk(KERN_INFO "Waiting for Nothing .\n");
	}
*/	
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "Goodbye world 1.\n");
}
