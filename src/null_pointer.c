#include <linux/init.h>
#include <linux/module.h>
#include <linux/version.h>

static int test_module_init(void)
{
        int *p = 1;
	printk("%d\n", *p);
        return 0;
}
static void test_module_exit(void)
{
        return;
}

module_init(test_module_init);
module_exit(test_module_exit);
