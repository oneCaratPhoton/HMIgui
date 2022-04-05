
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "hmigui.uart"
#define DBG_LVL         DBG_LOG
#include <rtdbg.h>

#define HMIGUI_DEBUG
//#define SAMPLE_UART_NAME       "uart2"

/* 用于接收消息的信号量 */
static struct rt_semaphore rx_sem;
static rt_device_t serial;

/* 接收数据回调函数 */
static rt_err_t uart_input(rt_device_t dev, rt_size_t size)
{
    /* 串口接收到数据后产生中断，调用此回调函数，然后发送接收信号量 */
    rt_sem_release(&rx_sem);

    return RT_EOK;
}

static void serial_thread_entry(void *parameter)
{
    rt_uint8_t ch;
#ifdef HMIGUI_DEBUG
    static rt_uint32_t cmd_state = 0;                                           //队列帧尾检测状态
#endif
    while (1)
    {
        /* 从串口读取一个字节的数据，没有读取到则等待接收信号量 */
        while (rt_device_read(serial, -1, &ch, 1) != 1)
        {
            /* 阻塞等待接收信号量，等到信号量后再次读取数据 */
            rt_sem_take(&rx_sem, RT_WAITING_FOREVER);
        }
        queue_push(ch);
        
    #ifdef HMIGUI_DEBUG
        rt_kprintf("%02X ",ch);
        cmd_state = ((cmd_state<<8) | ch);                           //拼接最后4个字节，组成一个32位整数
        //最后4个字节与帧尾匹配，得到完整帧
        if(cmd_state == 0XFFFCFFFF)
        {
        //    rt_kprintf("\r\n");
            LOG_D("\r\n%s", DBG_TAG);
        }
    #endif
    }
}

void uart_sample_put_char(rt_uint8_t ch)
{
    rt_device_write(serial, 0, &ch, 1);
    rt_kprintf("%02X ",ch);
}

static void hmi_uart(void *param)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;  /* 初始化配置参数 */

    /* 初始化信号量 */
    rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);
    
    /* step1：查找串口设备 */
    serial = rt_device_find(param);
    if (!serial)
    {
        rt_kprintf("find %s failed!\n", param);
        return;
    }

    /* step2：修改串口配置参数 */
    config.baud_rate = BAUD_RATE_19200;        //修改波特率为 19200
    config.data_bits = DATA_BITS_8;           //数据位 8
    config.stop_bits = STOP_BITS_1;           //停止位 1
    config.bufsz     = 128;                   //修改缓冲区 buff size 为 128
    config.parity    = PARITY_NONE;           //无奇偶校验位

    /* step3：控制串口设备。通过控制接口传入命令控制字，与控制参数 */
    rt_device_control(serial, RT_DEVICE_CTRL_CONFIG, &config);

    /* step4：打开串口设备。以中断接收及轮询发送模式打开串口设备 */
    rt_device_open(serial, RT_DEVICE_FLAG_INT_RX);
        
    /* 设置接收回调函数 */
    rt_device_set_rx_indicate(serial, uart_input);

    /* 创建 serial 线程 */
    rt_thread_t thread = rt_thread_create("serial", serial_thread_entry, RT_NULL, 1024, 25, 10);
    /* 创建成功则启动线程 */
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }

}

///* 导出到 msh 命令列表中 */
//MSH_CMD_EXPORT(uart_data_sample, uart device sample);

static int hmi_uart_create(void)
{
    rt_thread_t tid1;

    tid1 = rt_thread_create("thread0_HMIgui",
                                      hmi_uart,
                                      HMIGUI_DEVICE_NAME,
                                      1024,
                                      RT_THREAD_PRIORITY_MAX / 2,
                                      20);
    if (tid1 != RT_NULL)
    {
        rt_thread_startup(tid1);
    }

    return RT_EOK;
}
INIT_APP_EXPORT(hmi_uart_create);

