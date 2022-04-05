/*! 
*  \file hmi_driver.h
*  \brief 指令分类处理
*  \version 1.0
*  \date 2012-2018
*  \copyright 广州大彩光电科技有限公司
*/


#ifndef _CMD_PROCESS_H
#define _CMD_PROCESS_H
#include "hmi_driver.h"

#define NOTIFY_TOUCH_PRESS         0X01  //触摸屏按下通知
#define NOTIFY_TOUCH_RELEASE       0X03  //触摸屏松开通知
#define NOTIFY_WRITE_FLASH_OK      0X0C  //写FLASH成功
#define NOTIFY_WRITE_FLASH_FAILD   0X0D  //写FLASH失败
#define NOTIFY_READ_FLASH_OK       0X0B  //读FLASH成功
#define NOTIFY_READ_FLASH_FAILD    0X0F  //读FLASH失败
#define NOTIFY_MENU                0X14  //菜单事件通知
#define NOTIFY_TIMER               0X43  //定时器超时通知
#define NOTIFY_CONTROL             0XB1  //控件更新通知
#define NOTIFY_READ_RTC            0XF7  //读取RTC时间
#define MSG_GET_CURRENT_SCREEN     0X01  //画面ID变化通知
#define MSG_GET_DATA               0X11  //控件数据通知
#define NOTIFY_HandShake           0X55  //握手通知

#define PTR2U16(PTR) ((((rt_uint8_t *)(PTR))[0]<<8)|((rt_uint8_t *)(PTR))[1])  //从缓冲区取16位数据
#define PTR2U32(PTR) ((((rt_uint8_t *)(PTR))[0]<<24)|(((rt_uint8_t *)(PTR))[1]<<16)|(((rt_uint8_t *)(PTR))[2]<<8)|((rt_uint8_t *)(PTR))[3])  //从缓冲区取32位数据


enum CtrlType
{
    kCtrlUnknown=0x0,
    kCtrlButton=0x10,                     //按钮
    kCtrlText,                            //文本
    kCtrlProgress,                        //进度条
    kCtrlSlider,                          //滑动条
    kCtrlMeter,                            //仪表
    kCtrlDropList,                        //下拉列表
    kCtrlAnimation,                       //动画
    kCtrlRTC,                             //时间显示
    kCtrlGraph,                           //曲线图控件
    kCtrlTable,                           //表格控件
    kCtrlMenu,                            //菜单控件
    kCtrlSelector,                        //选择控件
    kCtrlQRCode,                          //二维码
};

#pragma pack(push)
#pragma pack(1)                           //按字节对齐

typedef struct
{
    rt_uint8_t    cmd_head;                    //帧头

    rt_uint8_t    cmd_type;                    //命令类型(UPDATE_CONTROL)    
    rt_uint8_t    ctrl_msg;                    //CtrlMsgType-指示消息的类型
    rt_uint16_t   screen_id;                   //产生消息的画面ID
    rt_uint16_t   control_id;                  //产生消息的控件ID
    rt_uint8_t    control_type;                //控件类型

    rt_uint8_t    param[256];                  //可变长度参数，最多256个字节

    rt_uint8_t  cmd_tail[4];                   //帧尾
}CTRL_MSG,*PCTRL_MSG;

#pragma pack(pop)

/*! 
*  \brief  握手通知
*/
void NOTIFYHandShake(void);

/*! 
*  \brief  消息处理流程
*  \param msg 待处理消息
*  \param size 消息长度
*/
void ProcessMessage( PCTRL_MSG msg, rt_uint16_t size );
/*! 
*  \brief  画面切换通知
*  \details  当前画面改变时(或调用GetScreen)，执行此函数
*  \param screen_id 当前画面ID
*/
void NotifyScreen(rt_uint16_t screen_id);
/*! 
*  \brief  触摸坐标事件响应
*  \param press 1按下触摸屏，3松开触摸屏
*  \param x x坐标
*  \param y y坐标
*/
void NotifyTouchXY(rt_uint8_t press,rt_uint16_t x,rt_uint16_t y);

/*! 
*  \brief  按钮控件通知
*  \details  当按钮状态改变(或调用GetControlValue)时，执行此函数
*  \param screen_id 画面ID
*  \param control_id 控件ID
*  \param state 按钮状态：0弹起，1按下
*/
void NotifyButton(rt_uint16_t screen_id, rt_uint16_t control_id, rt_uint8_t state);
/*! 
*  \brief  文本控件通知
*  \details  当文本通过键盘更新(或调用GetControlValue)时，执行此函数
*  \details  文本控件的内容以字符串形式下发到MCU，如果文本控件内容是浮点值，
*  \details  则需要在此函数中将下发字符串重新转回浮点值。
*  \param screen_id 画面ID
*  \param control_id 控件ID
*  \param str 文本控件内容
*/
void NotifyText(rt_uint16_t screen_id, rt_uint16_t control_id, rt_uint8_t *str);
/*!                                                                              
*  \brief  进度条控件通知                                                       
*  \details  调用GetControlValue时，执行此函数                                  
*  \param screen_id 画面ID                                                      
*  \param control_id 控件ID                                                     
*  \param value 值                                                              
*/   
void NotifyProgress(rt_uint16_t screen_id, rt_uint16_t control_id, rt_uint32_t value);
/*!                                                                              
*  \brief  滑动条控件通知                                                       
*  \details  当滑动条改变(或调用GetControlValue)时，执行此函数                  
*  \param screen_id 画面ID                                                      
*  \param control_id 控件ID                                                     
*  \param value 值                                                              
*/    
void NotifySlider(rt_uint16_t screen_id, rt_uint16_t control_id, rt_uint32_t value);
/*! 
*  \brief  仪表控件通知
*  \details  调用GetControlValue时，执行此函数
*  \param screen_id 画面ID
*  \param control_id 控件ID
*  \param value 值
*/
void NotifyMeter(rt_uint16_t screen_id, rt_uint16_t control_id, rt_uint32_t value);
/*! 
*  \brief  菜单控件通知
*  \details  当菜单项按下或松开时，执行此函数
*  \param screen_id 画面ID
*  \param control_id 控件ID
*  \param item 菜单项索引
*  \param state 按钮状态：0松开，1按下
*/
void NotifyMenu(rt_uint16_t screen_id, rt_uint16_t control_id, rt_uint8_t  item, rt_uint8_t  state);

/*! 
*  \brief  选择控件通知
*  \details  当选择控件变化时，执行此函数
*  \param screen_id 画面ID
*  \param control_id 控件ID
*  \param item 当前选项
*/
void NotifySelector(rt_uint16_t screen_id, rt_uint16_t control_id, rt_uint8_t  item);
/*! 
*  \brief  定时器超时通知处理
*  \param screen_id 画面ID
*  \param control_id 控件ID
*/
void NotifyTimer(rt_uint16_t screen_id, rt_uint16_t control_id);
/*! 
*  \brief  读取用户FLASH状态返回
*  \param status 0失败，1成功
*  \param _data 返回数据
*  \param length 数据长度
*/
void NotifyReadFlash(rt_uint8_t status,rt_uint8_t *_data,rt_uint16_t length);

/*! 
*  \brief  写用户FLASH状态返回
*  \param status 0失败，1成功
*/
void NotifyWriteFlash(rt_uint8_t status);
/*! 
*  \brief  读取RTC时间，注意返回的是BCD码
*  \param year 年（BCD）
*  \param month 月（BCD）
*  \param week 星期（BCD）
*  \param day 日（BCD）
*  \param hour 时（BCD）
*  \param minute 分（BCD）
*  \param second 秒（BCD）
*/
void NotifyReadRTC(rt_uint8_t year,rt_uint8_t month,rt_uint8_t week,rt_uint8_t day,rt_uint8_t hour,rt_uint8_t minute,rt_uint8_t second);

#endif
