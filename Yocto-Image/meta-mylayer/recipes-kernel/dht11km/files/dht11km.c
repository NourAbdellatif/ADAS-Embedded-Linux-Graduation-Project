#include <linux/err.h>
#include <linux/gpio.h>
#include <linux/of_gpio.h>
#include <linux/gpio/consumer.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/property.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/init.h>
#include <asm/uaccess.h>

typedef unsigned char u8;
typedef unsigned short u16;

static int dht11_major = 0;
static int dht11_gpio = 4;
static struct class *dht11_class;
static struct device *dht11_dev;
static const char* dht11_name = "dht11km";


typedef struct	DHT11_SENSOR_DATA
{
	u16 temp;
	u16 hum;
}dht11_data;

#define DHT11_DQ_High    gpio_direction_output(dht11_gpio, 1)
#define DHT11_DQ_Low     gpio_direction_output(dht11_gpio, 0)
#define DHT11_IO_IN		 gpio_direction_input(dht11_gpio)


#define delay_us(x)		udelay(x)
#define delay_ms(x)		msleep(x)

static u8 DHT11_Read_DQ(void)    
{
	DHT11_IO_IN;
	return gpio_get_value(dht11_gpio);
}


static void DHT11_Rst(void)   
{                 
	DHT11_DQ_Low;
	msleep (20);  
	DHT11_DQ_High; 
	delay_us (30); 
}


static u8 DHT11_Check(void)    
{   
	u8 retry=0;
	DHT11_IO_IN;
	while ((DHT11_Read_DQ()==1)&&retry<100)
	{
		retry++;
		delay_us(1);
	}; 
	if(retry>=100)return 1;
	else retry=0;
	while ((DHT11_Read_DQ()==0)&&retry<100)
	{
		retry++;
		delay_us(1);
	};
	if(retry>=100)return 1;    
	return 0;
}


static u8 DHT11_Read_Bit(void)  
{
	u8 retry=0;
	while((DHT11_Read_DQ()==1)&&retry<100)
	{
		retry++;
		delay_us(1);
	}
	retry=0;
	while((DHT11_Read_DQ()==0)&&retry<100)
	{
		retry++;
		delay_us(1);
	}
	delay_us(40);
	if(DHT11_Read_DQ()==1)
	return 1;
	else 
	return 0;   
}

static u8 DHT11_Read_Byte(void)    
{        
    u8 i,dat;
    dat=0;
	for (i=0;i<8;i++) 
	{
		dat<<=1; 
		dat|=DHT11_Read_Bit();
	}    
	return dat;
}
 

static u8 DHT11_Read_Data(u16 *temp,u16 *humi)    
{        
	u8 buf[5];
	u8 i;
	DHT11_Rst();
	if(DHT11_Check()==0)
	{
		for(i=0;i<5;i++)
		{
			buf[i]=DHT11_Read_Byte();
		}
		if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
		{
			*humi=buf[0];
			*temp=buf[2];
			//printk("buf=%d,%d,%d,%d,%d\n",buf[0],buf[1],buf[2],buf[3],buf[4]);

			printk("Temperature: %u.%u degrees Celsius, Humidity: %u%%\n", buf[2], buf[3], buf[0]);
		}
	}else return 1;
	return 0;    
}
  
static void DHT11_Init(void)
{     
	DHT11_Rst();
	DHT11_Check();
}

int DHT11_open(struct inode *inode, struct file *flips)
{
	printk("--------------%s--------------\n",__FUNCTION__);
	return 0;
}

static ssize_t DHT11_read(struct file *file, char __user *buf, size_t nbytes, loff_t *ppos)
{	
    	char str_temp[16], str_hum[16];
    	char data_str[35];
	printk("--------------%s--------------\n",__FUNCTION__);
	
	dht11_data Last_dht11_data;
	if(DHT11_Read_Data(&Last_dht11_data.temp,&Last_dht11_data.hum) == 0)
	{
	
		sprintf(str_temp, "%d", Last_dht11_data.temp);
    		sprintf(str_hum, "%d", Last_dht11_data.hum);
    		snprintf(data_str, sizeof(data_str), "Temperature: %s°C, Humidity: %s%%\n", str_temp, str_hum);
    		
		/* we need to check if the user wants more that the size or not */
    		/* This if condition guarantees that the count never exceeds the size of the buffer */
    		if (nbytes + (*ppos) > 35)
    		{
    		    nbytes = 35 - (*ppos);
    		}
    		
		if ( copy_to_user(buf, data_str, strlen(data_str) + 1) )
		{
			return EFAULT ;
		}
		*ppos = nbytes; 
		return nbytes;
	}
	else
	{
		return 0;
	}
	
}

static int DHT11_close(struct inode *inode, struct file *flip)
{
	printk("--------------%s--------------\n",__FUNCTION__);
	return 0;
}

static struct file_operations dht11_fops = {
	.owner = THIS_MODULE,
	.read = DHT11_read,
	.open = DHT11_open,
	.release = DHT11_close,
};

static const struct of_device_id of_dht11_match[] = {
	{ .compatible = "mygpio-leds", },
	{},
};

MODULE_DEVICE_TABLE(of, of_dht11_match);



static int __init dht11_init(void)
{
	int ret;  
	enum of_gpio_flags flag;

	printk("-------%s-------------\n", __FUNCTION__);
	

	if (!gpio_is_valid(dht11_gpio)) 
	{
    	printk("dht11-gpio: %d is invalid\n", dht11_gpio); 
		return -ENODEV;
        goto err_0;
    }
	else
		printk("dht11-gpio: %d is valid!\n", dht11_gpio);
	if (gpio_request(dht11_gpio, "dht11-gpio")) 
	{ 
        printk("gpio %d request failed!\n", dht11_gpio); 
        gpio_free(dht11_gpio); 
        return -ENODEV;
        goto err_0;
    }
	else
		printk("gpio %d request success!\n", dht11_gpio); 
	dht11_major = register_chrdev(0, "dht11km",&dht11_fops);
	if(dht11_major <0)
	{
		printk(KERN_ERR "reg error!\n");
		goto err_0;		
	}
	else 
		printk("dht11_major =%d\n",dht11_major);
	
	dht11_class = class_create(THIS_MODULE,"dht11_class");//creat class
	if( IS_ERR(dht11_class))
	{
		printk(KERN_ERR "fail create class\n");
		ret = PTR_ERR(dht11_class);
		goto err_1;
	}
	
	//creat dht11_dev--->>/dev/dht11_dev
	dht11_dev = device_create(dht11_class, NULL,MKDEV(dht11_major,0), NULL, dht11_name);
	if(IS_ERR(dht11_dev))
	{
		printk(KERN_ERR "fail create device!\n");
		ret = PTR_ERR(dht11_dev);
		goto err_2;		
	}
	
	//init dht11
	DHT11_Init();
	printk("dht11 Initing...\n");
	return 0;
	
err_2:
		device_destroy(dht11_class,MKDEV(dht11_major,0));
err_1:
		class_destroy(dht11_class);
err_0:
		unregister_chrdev(dht11_major,dht11_name);	
		return -1;
}

static void __exit dht11_exit(void)
{
	printk("-------%s-------------\n", __FUNCTION__);
	device_destroy(dht11_class,MKDEV(dht11_major,0));
	class_destroy(dht11_class);
	unregister_chrdev(dht11_major,dht11_name);
}




module_init(dht11_init);
module_exit(dht11_exit);
MODULE_AUTHOR("jackeyt,bbs.elecfans.com");
MODULE_DESCRIPTION("DHT11 Sensor driver");
MODULE_LICENSE("GPL");

