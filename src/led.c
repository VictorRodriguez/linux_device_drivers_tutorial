#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>	/* for put_user */
#include <linux/gpio.h>
#include <mach/mux.h>

#include "led.h"

#define AUTOR 		"Victor Rodriguez"
#define DESCRIPCION 	"Driver  ioctl"
#define MAXIMO		1024

/*Turn On a Led */


//#define PIN_LED		GPIO_TO_PIN(6, 13)
//#define MUX_LED		DA850_GPIO6_13


#define PIN_LED		GPIO_TO_PIN(6, 12)
#define MUX_LED		DA850_GPIO6_12


/*Varaiables */
static int status; 
static int num_mayor; 
static unsigned long procfs_buffer_size = 0;
static char buffer_data[MAXIMO];
static char msg[MAXIMO];	/* The msg the device will give when asked */
static char *msg_Ptr;

/*Metods faile operation*/
static int device_open(struct inode *inode, struct file *file);
static int device_release(struct inode *inode, struct file *file); 	
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);
static int device_ioctl(struct inode *inode,struct file *file,unsigned int ioctl_num,unsigned long ioctl_param); 

/*Metodos to turn on a led*/
static int led_on(void); 
static int led_off(void); 

/*File operation structure */ 
static struct file_operations fops= {
	.open = device_open,
	.release = device_release,
	.read = device_read,
	.write = device_write,
	.ioctl = device_ioctl,
};


static int __init hola_inicio(void)
{


	num_mayor=register_chrdev(MAJOR_NUM, DEVICE_NAME, &fops);
	printk(KERN_INFO "The mayor number is %d \n",MAJOR_NUM); 
	printk(KERN_INFO "The minor number is %s \n",DEVICE_NAME); 
	printk(KERN_INFO "Generete the device driver with mknod %s c %d 0 \n",DEVICE_NAME,MAJOR_NUM);

	return 0 ; 

}

static void __exit hola_fin(void)
{
	unregister_chrdev(num_mayor, DEVICE_NAME);
}

module_init(hola_inicio); 
module_exit(hola_fin); 



/*Metods faile operation*/

static int device_open(struct inode *inode, struct file *file)
{
	sprintf(msg,buffer_data);
	msg_Ptr = msg;
	return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
	return 0;
}

static ssize_t device_read(struct file *filp,	/* see include/linux/fs.h   */
			   char *buf,	/* buffer to fill with data */
			   size_t len,	/* length of the buffer     */
			   loff_t * off)
{
	int bytes_read = 0;
	
	/*Turn on led */
	led_on(); 

	if (*msg_Ptr == 0)
		return 0;


	while (len && *msg_Ptr) {

		/* 
		 * The buffer is in the user data segment, not the kernel 
		 * segment so "*" assignment won't work.  We have to use 
		 * put_user which copies data from the kernel data segment to
		 * the user data segment. 
		 */
		put_user(*(msg_Ptr++), buf++);

		len--;
		bytes_read++;
	}
	
	 /* 
	 * Most read functions return the number of bytes put into the buffer
	 */
	return bytes_read;


}	

static ssize_t device_write(struct file *filp, 
			    const char *buf, 
			    size_t len, 
			    loff_t * off)
{

procfs_buffer_size = len;
	
	if ( copy_from_user(buffer_data, buf, procfs_buffer_size) ) {
		return -EFAULT;
	}
	 *off += len;

	/*Turn of led */
	led_off(); 
	return procfs_buffer_size;
}

int device_ioctl(struct inode *inode,	// see include/linux/fs.h 
		 struct file *file,	// ditto 
		 unsigned int ioctl_num,	// number and param for ioctl 
		 unsigned long ioctl_param)
{


	switch (ioctl_num) 
	{
		case IOCTL_SET_MSG:


			if(ioctl_param == 1)
			{
				led_on(); 				
			}
			
			if (ioctl_param == 0)
			{
				led_off(); 
			}
	
		break;

		case IOCTL_GET_MSG:
			/*Get the value */
			printk(KERN_INFO "Entro en IOCTL_GET_MSG \n");
			status = gpio_get_value(PIN_LED); 
			printk(KERN_INFO "El valor del pin 6,13 es %d \n", status); 
			return status;
		break; 
		
	}

	return 0; 
}

static int led_on(void)
{


	int ret; 
	
	/*Free gpio */
	gpio_free(PIN_LED);
	
	/*Configure in mux.h  */
	ret = davinci_cfg_reg (MUX_LED); 
		if (ret<0)
		{
			printk(KERN_INFO "No es posible configurar el led 1\n"); 
			return ret; 
		}
	
	/*Ask permision to turn it on */
	ret = gpio_request(PIN_LED, "led");
		if (ret) 
		{
			printk(KERN_INFO "No es posible configurar el led 2\n"); 
			return ret;
		}
		
	

	/*Configure as out put */
	gpio_direction_output(PIN_LED, 1); 

	/*TURN ON */
	gpio_set_value(PIN_LED, 1);


	return 0 ; 

}

static int led_off(void)
{
	int ret; 
	
	/*Free gpio */
	gpio_free(PIN_LED);
	
	/*Configure in mux.h  */
	ret = davinci_cfg_reg (MUX_LED); 
		if (ret<0)
		{
			printk(KERN_INFO "No es posible configurar el led 1\n"); 
			return ret;
		}
	
	/*Configure as out put */
	ret = gpio_request(PIN_LED, "led");
		if (ret) 
		{
			printk(KERN_INFO "No es posible configurar el led 2\n"); 
			return ret;
		}
		
	

	/*Configure as out put */
	gpio_direction_output(PIN_LED, 1); 

	/*TURN OFF */
	gpio_set_value(PIN_LED, 0);


	return 0 ; 

}

MODULE_LICENSE("GPL");
MODULE_AUTHOR(AUTOR);	/* Who wrote this module? */
MODULE_DESCRIPTION(DESCRIPCION);	/* What does this module do */
MODULE_SUPPORTED_DEVICE("ioctl-hawkboard");
