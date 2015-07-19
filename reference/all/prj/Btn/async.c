// Simple Character Device Driver Module for Raspberry Pi.
/*
 * DESCRIIPT:
 *     Perform the async notification mechanism.
 *     press the button to triggle an interrupt to send a signal
 *     to registered opened file .
 *
 * */

#include <linux/module.h>
#include <linux/string.h>    
#include <linux/fs.h>      
#include <asm/uaccess.h>
#include <linux/init.h>
#include <linux/cdev.h>

#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/io.h>
#include <linux/sched.h>
#include <linux/interrupt.h>

#include <linux/list.h>
#include <linux/irq.h>
#include <linux/slab.h>
#include <linux/gpio.h>
#include <linux/time.h>
#include <linux/delay.h>
#include <linux/version.h>
#include <linux/jiffies.h>



#define MY_BUTTON       23 
#define MY_BUTTON2       27 

#define MY_MAJOR	200
#define MY_MINOR	0


// text below will be seen in 'cat /proc/interrupt' command
#define MY_INT_NAME "MyInterrupt"

// below is optional, used in more complex code, in our case, this could be
// NULL
#define MY_DEV_COUNT 1 
#define MY_CLASS_NAME "myBtn_class"
#define MY_NODE_NAME   "myBtn"

#define MY_DEV_NAME "myBtn"

volatile unsigned int val;


static int     my_open( struct inode *, struct file *);
static int     my_close(struct inode *, struct file *);
static ssize_t my_read( struct file *, char *      , size_t, loff_t *);
static ssize_t my_write(struct file *, const char *, size_t, loff_t *);
static int     my_fasync(int fd, struct file * flip, int mode);
static struct fasync_struct * my_async_list = NULL;


/////////////////////////////////////////////
static void my_tasklet_handler(unsigned long );
/////////////////////////////////////////////

static char   *msg=NULL;
unsigned long flags;
unsigned long jfs_Btn1,jfs_Btn2;

struct file_operations my_fops = {
        read    :       my_read,
        write   :       my_write,
        open    :       my_open,
        release :       my_close,
		fasync  :       my_fasync,
        owner   :       THIS_MODULE,
        };

struct cdev my_cdev;
static struct class *my_class;

/****************************************************************************/
/* Interrupts variables block                                               */
/****************************************************************************/
short int my_int_num    = 0;


////////////////////////////////////////////////////////////////
DECLARE_TASKLET(mytasklet, my_tasklet_handler, 0);

static void my_tasklet_handler(unsigned long flag)
{

   printk("==== TASKLET HANDLER : \n");

	msg[0] = 'H';
	msg[1] = 'E';
	msg[2] = 'L';
	msg[3] = 'L';
	msg[4] = 'O';
	msg[5] = '\0';
   tasklet_disable_nosync(&mytasklet);
   kill_fasync(&my_async_list , SIGIO, POLL_IN);
   tasklet_enable(&mytasklet);   
}

/****************************************************************************/
/* IRQ handler - fired on interrupt                                         */
/***************************************************************************/

static irqreturn_t r_irq_handler(int irq, void *dev_id, struct pt_regs *regs) 
{
unsigned long j;

   printk("==== INT HANDLER : schedule mytasklet \n");
   // disable hard interrupts (remember them in flag 'flags')
   j = jiffies;
   if(time_before(j,jfs_Btn1))
           {
           printk("debounce\n");

           return IRQ_HANDLED;
	   }
   if(my_async_list != 0){
		local_irq_save(flags);
		tasklet_schedule(&mytasklet);
		local_irq_restore(flags);
                jfs_Btn1 =jiffies+(20*HZ/1000);
		return IRQ_HANDLED;
   }else{
	   return IRQ_HANDLED;
   }
}

/****************************************************************************/
/* This function configures interrupts.                                     */
/****************************************************************************/

void r_int_config(void) 
{
   if (gpio_request(MY_BUTTON, MY_INT_NAME)) {
      printk("GPIO request failure: %s\n", MY_INT_NAME);
      return;
   }

   if ( (my_int_num = gpio_to_irq(MY_BUTTON)) < 0 ) {
      printk("GPIO to IRQ mapping failure %s\n", MY_INT_NAME);
      return;
   }

   printk(KERN_NOTICE "Mapped int %d\n", my_int_num);

   jfs_Btn1 =jiffies+(20*HZ/1000);
   //////////////////////////////////////////////////////////
   // REQUEST IRQ
   //////////////////////////////////////////////////////////
   if (request_irq(my_int_num,
                   (irq_handler_t ) r_irq_handler,
                   IRQF_TRIGGER_RISING,
                   MY_INT_NAME,
                   MY_DEV_NAME)) {
      printk("Irq Request failure\n");
      return;
   }
   //////////////////////////////////////////////////////////

   return;
}


/****************************************************************************/
/* This function releases interrupts.                                       */
/****************************************************************************/
void r_int_release(void) {

   printk("==== INT RELEASE : \n");
   free_irq(my_int_num, MY_DEV_NAME);
   gpio_free(MY_BUTTON);

   return;
}


/*
 * MODULE: INIT 
 * */
int init_module(void)
{

	dev_t devno;
	unsigned int count;
	int err;


	devno = MKDEV(MY_MAJOR, MY_MINOR);
	register_chrdev_region(devno, 1, "mydevice");

        cdev_init(&my_cdev, &my_fops);

	my_cdev.owner = THIS_MODULE;
        count = 1;
	err = cdev_add(&my_cdev, devno, count);

	
	if (err < 0)
	{
		printk("Device Add Error\n");
		return -1;
	}

	my_class = class_create(THIS_MODULE, MY_CLASS_NAME); 
	if(IS_ERR(my_class)){
			printk("error at class_create()\n");
				return -1;
				}

	device_create(my_class, NULL, MKDEV(MY_MAJOR, MY_MINOR), NULL, MY_NODE_NAME); 
	printk("system auto make node : /dev/%s\n", MY_NODE_NAME);

	msg 	     = (char *)kmalloc(32, GFP_KERNEL);
	if (msg !=NULL)
		printk("malloc allocator address: 0x%p\n", msg);
	
	
	printk("==== BUTTON GPIO %d,Init \n", MY_BUTTON );
	// -- interrupt configure
	printk("==== INTERRUPT INIT !\n");
	r_int_config();
        return 0;
}


/*
 * MODULE: EXIT
 * */
void cleanup_module(void)
{
	dev_t devno;
	devno = MKDEV(MY_MAJOR, MY_MINOR);
	r_int_release();
	if (msg){
        /* release the malloc */
        kfree(msg);
	}
	tasklet_kill(&mytasklet);
	device_destroy(my_class,MKDEV(MY_MAJOR,MY_MINOR));
//	device_destroy(my_class,MKDEV(MY_MAJOR,MY_MINOR +1 ));
	class_destroy(my_class);

	unregister_chrdev_region(devno, 1);
	cdev_del(&my_cdev);
}




/*************************************************/
/* FILE OPERATION : OPEN READ WRITE CLOSE FASYNC */
/*************************************************/

/*
 * FILE OPERATION: OPEN
 * */
static int my_open(struct inode *inod, struct file *fil)
{

	int major;
	int minor;

	major = imajor(inod);
	minor = iminor(inod);
	printk("\n*****Some body is opening me at major %d  minor %d*****\n",major, minor);
	return 0;
}




/*
 * FILE OPERATION: READ
 * */
static ssize_t my_read(struct file *filp, char *buff, size_t len, loff_t *off)
{
	printk("==== FILE OPERATION: READ \n");
	printk("copy_to_user: %s\n", msg);
	return copy_to_user(buff, msg, 5);
}




/*
 * FILE OPERATION: WRITE
 * */
static ssize_t my_write(struct file *filp, const char *buff, size_t len, loff_t *off)
{
	
	int major,minor;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,19,0)
	major = MAJOR(filp->f_inode->i_rdev);
	minor = MINOR(filp->f_inode->i_rdev);
#else
	major = MAJOR(filp->f_dentry->d_inode->i_rdev);
	minor = MINOR(filp->f_dentry->d_inode->i_rdev);
#endif
	copy_from_user(msg ,buff,3);
	printk("copy from user %d,%d,%d",msg[0],msg[1],msg[2]);
	memset(msg, 0, 32);
        printk("==== FILE OPERATION: WRITE : major=%d\n",major);

	return len;
}




/*
 * FILE OPERATION: CLOSE
 * */
static int my_close(struct inode *inod, struct file *filp)
{
	
	int major,minor;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,19,0)
	major = MAJOR(filp->f_inode->i_rdev);
	minor = MINOR(filp->f_inode->i_rdev);
#else
	major = MAJOR(filp->f_dentry->d_inode->i_rdev);
	minor = MINOR(filp->f_dentry->d_inode->i_rdev);
#endif
	printk("*****Some body is closing me at major %d*****\n",major);

	// -- remove the pid of current process from my_async_list
	my_fasync(-1, filp, 0);

		return 0;
}




/*
 * FILE OPERATION: FASYNC
 * */
static int my_fasync(int fd, struct file * flip, int mode)
{
	printk("FILE OPERATION: FASYNC \n" );
	return fasync_helper(fd, flip, mode, &my_async_list); 
}


MODULE_LICENSE("GPL");
MODULE_AUTHOR("ITtraining.com.tw");
MODULE_DESCRIPTION("A Simple GPIO Device Driver module for RaspPi");
