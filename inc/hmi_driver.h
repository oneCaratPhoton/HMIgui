/*! 
*  \file hmi_driver.h
*  \brief 串口屏驱动文件
*  \version 1.0
*  \date 2012-2018
*  \copyright 广州大彩光电科技有限公司
*/

#ifndef _HMI_DRIVER_
#define _HMI_DRIVER_

#define FIRMWARE_VER 921          // 保持此固件版本号与真实屏幕一致，确保新增功能可用
#define CRC16_ENABLE 0            // 如果需要CRC16校验功能，修改此宏为1(此时需要在VisualTFT工程中配CRC校验)
#define CMD_MAX_SIZE 64           // 单条指令大小，根据需要调整，尽量设置大一些
#define QUEUE_MAX_SIZE 512        // 指令接收缓冲区大小，根据需要调整，尽量设置大一些

#define SD_FILE_EN 0
#include <rtthread.h>

/*! 
*  \brief  检查数据是否符合CRC16校验
*  \param buffer 待校验的数据，末尾存储CRC16
*  \param n 数据长度，包含CRC16
*  \return 校验通过返回1，否则返回0
*/
rt_uint16_t CheckCRC16(rt_uint8_t *buffer,rt_uint16_t n);

/*! 
*  \brief  延时
*  \param  n 延时时间(毫秒单位)
*/
void DelayMS(unsigned int n);

/*! 
*  \brief  锁定设备配置，锁定之后需要解锁，才能修改波特率、触摸屏、蜂鸣器工作方式
*/
void LockDeviceConfig(void);

/*! 
*  \brief  解锁设备配置
*/
void UnlockDeviceConfig(void);

/*! 
*  \brief    修改串口屏的波特率
*  \details  波特率选项范围[0~14]，对应实际波特率
{1200,2400,4800,9600,19200,38400,57600,115200,1000000,2000000,218750,437500,875000,921800,2500000}
*  \param  option 波特率选项
*/
void SetCommBps(rt_uint8_t option);

/*! 
*  \brief  发送握手命令
*/
void SetHandShake(void);

/*! 
*  \brief  设置前景色
*  \param  color 前景色
*/
void SetFcolor(rt_uint16_t color);

/*! 
*  \brief  设置背景色
*  \param  color 背景色
*/
void SetBcolor(rt_uint16_t color);

/*! 
*  \brief  清除画面
*/
void GUI_CleanScreen(void);

/*! 
*  \brief  设置文字间隔
*  \param  x_w 横向间隔
*  \param  y_w 纵向间隔
*/
void SetTextSpace(rt_uint8_t x_w, rt_uint8_t y_w);

/*! 
*  \brief  设置文字显示限制
*  \param  enable 是否启用限制
*  \param  width 宽度
*  \param  height 高度
*/
void SetFont_Region(rt_uint8_t enable,rt_uint16_t width,rt_uint16_t height );

/*! 
*  \brief  设置过滤色
*  \param  fillcolor_dwon 颜色下界
*  \param  fillcolor_up 颜色上界
*/
void SetFilterColor(rt_uint16_t fillcolor_dwon, rt_uint16_t fillcolor_up);

/*! 
*  \brief  设置过滤色
*  \param  x 位置X坐标
*  \param  y 位置Y坐标
*  \param  back 颜色上界
*  \param  font 字体
*  \param  strings 字符串内容
*/
void DisText(rt_uint16_t x, rt_uint16_t y,rt_uint8_t back,rt_uint8_t font,rt_uint8_t *strings );

/*! 
*  \brief    显示光标
*  \param  enable 是否显示
*  \param  x 位置X坐标
*  \param  y 位置Y坐标
*  \param  width 宽度
*  \param  height 高度
*/
void DisCursor(rt_uint8_t enable,rt_uint16_t x, rt_uint16_t y,rt_uint8_t width,rt_uint8_t height );

/*! 
*  \brief      显示全屏图片
*  \param  image_id 图片索引
*  \param  masken 是否启用透明掩码
*/
void DisFull_Image(rt_uint16_t image_id,rt_uint8_t masken);

/*! 
*  \brief      指定位置显示图片
*  \param  x 位置X坐标
*  \param  y 位置Y坐标
*  \param  image_id 图片索引
*  \param  masken 是否启用透明掩码
*/
void DisArea_Image(rt_uint16_t x,rt_uint16_t y,rt_uint16_t image_id,rt_uint8_t masken);

/*! 
*  \brief      显示裁剪图片
*  \param  x 位置X坐标
*  \param  y 位置Y坐标
*  \param  image_id 图片索引
*  \param  image_x 图片裁剪位置X坐标
*  \param  image_y 图片裁剪位置Y坐标
*  \param  image_l 图片裁剪长度
*  \param  image_w 图片裁剪高度
*  \param  masken 是否启用透明掩码
*/
void DisCut_Image(rt_uint16_t x,rt_uint16_t y,rt_uint16_t image_id,rt_uint16_t image_x,rt_uint16_t image_y,
				  rt_uint16_t image_l, rt_uint16_t image_w,rt_uint8_t masken);

/*! 
*  \brief      显示GIF动画
*  \param  x 位置X坐标
*  \param  y 位置Y坐标
*  \param  flashimage_id 图片索引
*  \param  enable 是否显示
*  \param  playnum 播放次数
*/
void DisFlashImage(rt_uint16_t x,rt_uint16_t y,rt_uint16_t flashimage_id,rt_uint8_t enable,rt_uint8_t playnum);

/*! 
*  \brief      画点
*  \param  x 位置X坐标
*  \param  y 位置Y坐标
*/
void GUI_Dot(rt_uint16_t x,rt_uint16_t y);

/*! 
*  \brief      画线
*  \param  x0 起始位置X坐标
*  \param  y0 起始位置Y坐标
*  \param  x1 结束位置X坐标
*  \param  y1 结束位置Y坐标
*/
void GUI_Line(rt_uint16_t x0, rt_uint16_t y0, rt_uint16_t x1, rt_uint16_t y1);

/*! 
*  \brief      画折线
*  \param  mode 模式
*  \param  dot 数据点
*  \param  dot_cnt 点数
*/
void GUI_ConDots(rt_uint8_t mode,rt_uint16_t *dot,rt_uint16_t dot_cnt);

/*! 
*  \brief      画空心圆
*  \param  x0 圆心位置X坐标
*  \param  y0 圆心位置Y坐标
*  \param  r 半径
*/
void GUI_Circle(rt_uint16_t x0, rt_uint16_t y0, rt_uint16_t r);

/*! 
*  \brief      画实心圆
*  \param  x0 圆心位置X坐标
*  \param  y0 圆心位置Y坐标
*  \param  r 半径
*/
void GUI_CircleFill(rt_uint16_t x0, rt_uint16_t y0, rt_uint16_t r);

/*! 
*  \brief      画弧线
*  \param  x0 圆心位置X坐标
*  \param  y0 圆心位置Y坐标
*  \param  r 半径
*  \param  sa 起始角度
*  \param  ea 终止角度
*/
void GUI_Arc(rt_uint16_t x,rt_uint16_t y, rt_uint16_t r,rt_uint16_t sa, rt_uint16_t ea);

/*! 
*  \brief      画空心矩形
*  \param  x0 起始位置X坐标
*  \param  y0 起始位置Y坐标
*  \param  x1 结束位置X坐标
*  \param  y1 结束位置Y坐标
*/
void GUI_Rectangle(rt_uint16_t x0, rt_uint16_t y0, rt_uint16_t x1,rt_uint16_t y1 );

/*! 
*  \brief      画实心矩形
*  \param  x0 起始位置X坐标
*  \param  y0 起始位置Y坐标
*  \param  x1 结束位置X坐标
*  \param  y1 结束位置Y坐标
*/
void GUI_RectangleFill(rt_uint16_t x0, rt_uint16_t y0, rt_uint16_t x1,rt_uint16_t y1 );

/*! 
*  \brief      画空心椭圆
*  \param  x0 起始位置X坐标
*  \param  y0 起始位置Y坐标
*  \param  x1 结束位置X坐标
*  \param  y1 结束位置Y坐标
*/
void GUI_Ellipse (rt_uint16_t x0, rt_uint16_t y0, rt_uint16_t x1,rt_uint16_t y1 );

/*! 
*  \brief      画实心椭圆
*  \param  x0 起始位置X坐标
*  \param  y0 起始位置Y坐标
*  \param  x1 结束位置X坐标
*  \param  y1 结束位置Y坐标
*/
void GUI_EllipseFill (rt_uint16_t x0, rt_uint16_t y0, rt_uint16_t x1,rt_uint16_t y1 );

/*! 
*  \brief      画线
*  \param  x0 起始位置X坐标
*  \param  y0 起始位置Y坐标
*  \param  x1 结束位置X坐标
*  \param  y1 结束位置Y坐标
*/
void SetBackLight(rt_uint8_t light_level);

/*! 
*  \brief   蜂鸣器设置
*  \time  time 持续时间(毫秒单位)
*/
void SetBuzzer(rt_uint8_t time);

/*! 
*  \brief   触摸屏设置
*  \param enable 触摸使能
*  \param beep_on 触摸蜂鸣器
*  \param work_mode 触摸工作模式：0按下就上传，1松开才上传，2不断上传坐标值，3按下和松开均上传数据
*  \param press_calibration 连续点击触摸屏20下校准触摸屏：0禁用，1启用
*/
void SetTouchPaneOption(rt_uint8_t enbale,rt_uint8_t beep_on,rt_uint8_t work_mode,rt_uint8_t press_calibration);

/*! 
*  \brief   校准触摸屏
*/
void	CalibrateTouchPane(void);

/*! 
*  \brief  触摸屏测试
*/
void TestTouchPane(void);

/*! 
*  \brief      设置当前写入图层
*  \details  一般用于实现双缓存效果(绘图时避免闪烁)：
*  \details  rt_uint8_t layer = 0;
*  \details  WriteLayer(layer);   设置写入层
*  \details  ClearLayer(layer);   使图层变透明
*  \details  添加一系列绘图指令
*  \details  DisText(100,100,0,4,"hello hmi!!!");
*  \details  DisplyLayer(layer);  切换显示层
*  \details  layer = (layer+1)%2; 双缓存切换
*  \see DisplyLayer
*  \see ClearLayer
*  \param  layer 图层编号
*/
void WriteLayer(rt_uint8_t layer);

/*! 
*  \brief      设置当前显示图层
*  \param  layer 图层编号
*/
void DisplyLayer(rt_uint8_t layer);

/*! 
*  \brief      清除图层，使图层变成透明
*  \param  layer 图层编号
*/
void ClearLayer(rt_uint8_t layer);

/*! 
*  \brief  写数据到串口屏用户存储区
*  \param  startAddress 起始地址
*  \param  length 字节数
*  \param  _data 待写入的数据
*/
void WriteUserFlash(rt_uint32_t startAddress,rt_uint16_t length,rt_uint8_t *_data);

/*! 
*  \brief  从串口屏用户存储区读取数据
*  \param  startAddress 起始地址
*  \param  length 字节数
*/
void ReadUserFlash(rt_uint32_t startAddress,rt_uint16_t length);

/*! 
*  \brief      拷贝图层
*  \param  src_layer 原始图层
*  \param  dest_layer 目标图层
*/
void CopyLayer(rt_uint8_t src_layer,rt_uint8_t dest_layer);

/*! 
*  \brief      设置当前画面
*  \param  screen_id 画面ID
*/
void SetScreen(rt_uint16_t screen_id);

/*! 
*  \brief      获取当前画面
*/
void GetScreen(rt_uint16_t screen_id);

/*! 
*  \brief     禁用\启用画面更新
*  \details 禁用\启用一般成对使用，用于避免闪烁、提高刷新速度
*  \details 用法：
*	\details SetScreenUpdateEnable(0);//禁止更新
*	\details 一系列更新画面的指令
*	\details SetScreenUpdateEnable(1);//立即更新
*  \param  enable 0禁用，1启用
*/
void SetScreenUpdateEnable(rt_uint8_t enable);

/*! 
*  \brief     设置控件输入焦点
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*  \param  focus 是否具有输入焦点
*/
void SetControlFocus(rt_uint16_t screen_id,rt_uint16_t control_id,rt_uint8_t focus);

/*! 
*  \brief     显示\隐藏控件
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*  \param  visible 是否显示
*/
void SetControlVisiable(rt_uint16_t screen_id,rt_uint16_t control_id,rt_uint8_t visible);

/*! 
*  \brief     设置触摸控件使能
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*  \param  enable 控件是否使能
*/
void SetControlEnable(rt_uint16_t screen_id,rt_uint16_t control_id,rt_uint8_t enable);

/*! 
*  \brief     获取控件值
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*/
void GetControlValue(rt_uint16_t screen_id,rt_uint16_t control_id);

/*! 
*  \brief     设置按钮状态
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*  \param  value 按钮状态
*/
void SetButtonValue(rt_uint16_t screen_id,rt_uint16_t control_id,rt_uint8_t value);
void SetSwitchButtonValue(rt_uint16_t screen_id,rt_uint16_t control_id,rt_uint8_t value);

/*! 
*  \brief     设置文本值
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*  \param  str 文本值
*/
void SetTextValue(rt_uint16_t screen_id,rt_uint16_t control_id,rt_uint8_t *str);

#if FIRMWARE_VER>=908

/*! 
*  \brief     设置文本为整数值，要求FIRMWARE_VER>=908
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*  \param  value 文本数值
*  \param  sign 0-无符号，1-有符号
*  \param  fill_zero 数字位数，不足时左侧补零
*/
void SetTextInt32(rt_uint16_t screen_id,rt_uint16_t control_id,rt_uint32_t value,rt_uint8_t sign,rt_uint8_t fill_zero);

/*! 
*  \brief     设置文本单精度浮点值，要求FIRMWARE_VER>=908
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*  \param  value 文本数值
*  \param  precision 小数位数
*  \param  show_zeros 为1时，显示末尾0
*/
void SetTextFloat(rt_uint16_t screen_id,rt_uint16_t control_id,float value,rt_uint8_t precision,rt_uint8_t show_zeros);

#endif

/*! 
*  \brief      设置进度值
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*  \param  value 数值
*/
void SetProgressValue(rt_uint16_t screen_id,rt_uint16_t control_id,rt_uint32_t value);

/*! 
*  \brief     设置仪表值
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*  \param  value 数值
*/
void SetMeterValue(rt_uint16_t screen_id,rt_uint16_t control_id,rt_uint32_t value);

/*! 
*  \brief     设置仪表值
*  \param  screen_id 画面ID
*  \param  control_id 图片控件ID
*  \param  value 数值
*/
void Set_picMeterValue(rt_uint16_t screen_id,rt_uint16_t control_id,rt_uint16_t value);

/*! 
*  \brief      设置滑动条
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*  \param  value 数值
*/

void SetSliderValue(rt_uint16_t screen_id,rt_uint16_t control_id,rt_uint32_t value);

/*! 
*  \brief      设置选择控件
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*  \param  item 当前选项
*/
void SetSelectorValue(rt_uint16_t screen_id,rt_uint16_t control_id,rt_uint8_t item);

/*! 
*  \brief      开始播放动画
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*/
void AnimationStart(rt_uint16_t screen_id,rt_uint16_t control_id);

/*! 
*  \brief      停止播放动画
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*/
void AnimationStop(rt_uint16_t screen_id,rt_uint16_t control_id);

/*! 
*  \brief      暂停播放动画
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*/
void AnimationPause(rt_uint16_t screen_id,rt_uint16_t control_id);

/*! 
*  \brief     播放制定帧
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*  \param  frame_id 帧ID
*/
void AnimationPlayFrame(rt_uint16_t screen_id,rt_uint16_t control_id,rt_uint8_t frame_id);

/*! 
*  \brief     播放上一帧
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*/
void AnimationPlayPrev(rt_uint16_t screen_id,rt_uint16_t control_id);

/*! 
*  \brief     播放下一帧
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*/
void AnimationPlayNext(rt_uint16_t screen_id,rt_uint16_t control_id);

/*! 
*  \brief     曲线控件-添加通道
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*  \param  channel 通道号
*  \param  color 颜色
*/
void GraphChannelAdd(rt_uint16_t screen_id,rt_uint16_t control_id,rt_uint8_t channel,rt_uint16_t color);

/*! 
*  \brief     曲线控件-删除通道
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*  \param  channel 通道号
*/
void GraphChannelDel(rt_uint16_t screen_id,rt_uint16_t control_id,rt_uint8_t channel);

/*! 
*  \brief     曲线控件-添加数据
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*  \param  channel 通道号
*  \param  pData 曲线数据
*  \param  nDataLen 数据个数
*/
void GraphChannelDataAdd(rt_uint16_t screen_id,rt_uint16_t control_id,rt_uint8_t channel,rt_uint8_t *pData,rt_uint16_t nDataLen);

/*! 
*  \brief     曲线控件-清除数据
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*  \param  channel 通道号
*/
void GraphChannelDataClear(rt_uint16_t screen_id,rt_uint16_t control_id,rt_uint8_t channel);

/*! 
*  \brief     曲线控件-设置视图窗口
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*  \param  x_offset 水平偏移
*  \param  x_mul 水平缩放系数
*  \param  y_offset 垂直偏移
*  \param  y_mul 垂直缩放系数
*/
void GraphSetViewport(rt_uint16_t screen_id,rt_uint16_t control_id,rt_int16_t x_offset,rt_uint16_t x_mul,rt_int16_t y_offset,rt_uint16_t y_mul);

/*! 
*  \brief     开始批量更新
*  \param  screen_id 画面ID
*/
void BatchBegin(rt_uint16_t screen_id);

/*! 
*  \brief     批量更新按钮控件
*  \param  control_id 控件ID
*  \param  value 数值
*/
void BatchSetButtonValue(rt_uint16_t control_id,rt_uint8_t state);

/*! 
*  \brief     批量更新进度条控件
*  \param  control_id 控件ID
*  \param  value 数值
*/
void BatchSetProgressValue(rt_uint16_t control_id,rt_uint32_t value);

/*! 
*  \brief     批量更新滑动条控件
*  \param  control_id 控件ID
*  \param  value 数值
*/
void BatchSetSliderValue(rt_uint16_t control_id,rt_uint32_t value);

/*! 
*  \brief     批量更新仪表控件
*  \param  control_id 控件ID
*  \param  value 数值
*/
void BatchSetMeterValue(rt_uint16_t control_id,rt_uint32_t value);

/*! 
*  \brief      计算字符串长度
*/
rt_uint32_t GetStringLen(rt_uint8_t *str);

/*! 
*  \brief     批量更新文本控件
*  \param  control_id 控件ID
*  \param  strings 字符串
*/
void BatchSetText(rt_uint16_t control_id,rt_uint8_t *strings);

/*! 
*  \brief     批量更新动画\图标控件
*  \param  control_id 控件ID
*  \param  frame_id 帧ID
*/
void BatchSetFrame(rt_uint16_t control_id,rt_uint16_t frame_id);

#if FIRMWARE_VER>=921

/*! 
*  \brief     批量设置控件可见
*  \param  control_id 控件ID
*  \param  visible 帧ID
*/
void BatchSetVisible(rt_uint16_t control_id,rt_uint8_t visible);

/*! 
*  \brief     批量设置控件使能
*  \param  control_id 控件ID
*  \param  enable 帧ID
*/
void BatchSetEnable(rt_uint16_t control_id,rt_uint8_t enable);

#endif

/*! 
*  \brief    结束批量更新
*/
void BatchEnd(void);

/*! 
*  \brief     设置倒计时控件
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*  \param  timeout 倒计时(秒)
*/
void SeTimer(rt_uint16_t screen_id,rt_uint16_t control_id,rt_uint32_t timeout);

/*! 
*  \brief     开启倒计时控件
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*/
void StartTimer(rt_uint16_t screen_id,rt_uint16_t control_id);

/*! 
*  \brief     停止倒计时控件
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*/
void StopTimer(rt_uint16_t screen_id,rt_uint16_t control_id);

/*! 
*  \brief     暂停倒计时控件
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*/
void PauseTimer(rt_uint16_t screen_id,rt_uint16_t control_id);

/*! 
*  \brief     设置控件背景色
*  \details  支持控件：进度条、文本
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*  \param  color 背景色
*/
void SetControlBackColor(rt_uint16_t screen_id,rt_uint16_t control_id,rt_uint16_t color);

/*! 
*  \brief     设置控件前景色
* \details  支持控件：进度条
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*  \param  color 前景色
*/
void SetControlForeColor(rt_uint16_t screen_id,rt_uint16_t control_id,rt_uint16_t color);

/*! 
*  \brief     显示\隐藏弹出菜单控件
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*  \param  show 是否显示，为0时focus_control_id无效
*  \param  focus_control_id 关联的文本控件(菜单控件的内容输出到文本控件)
*/
void ShowPopupMenu(rt_uint16_t screen_id,rt_uint16_t control_id,rt_uint8_t show,rt_uint16_t focus_control_id);

/*! 
*  \brief     显示\隐藏系统键盘
*  \param  show 0隐藏，1显示
*  \param  x 键盘显示位置X坐标
*  \param  y 键盘显示位置Y坐标
*  \param  type 0小键盘，1全键盘
*  \param  option 0正常字符，1密码，2时间设置
*  \param  max_len 键盘录入字符长度限制
*/
void ShowKeyboard(rt_uint8_t show,rt_uint16_t x,rt_uint16_t y,rt_uint8_t type,rt_uint8_t option,rt_uint8_t max_len);

#if FIRMWARE_VER>=914
/*! 
*  \brief     多语言设置
*  \param  ui_lang 用户界面语言0~9
*  \param  sys_lang 系统键盘语言-0中文，1英文
*/
void SetLanguage(rt_uint8_t ui_lang,rt_uint8_t sys_lang);
#endif

#if FIRMWARE_VER>=917
/*! 
*  \brief     开始保存控件数值到FLASH
*  \param  version 数据版本号，可任意指定，高16位为主版本号，低16位为次版本号
*  \param  address 数据在用户存储区的存放地址，注意防止地址重叠、冲突
*/
void FlashBeginSaveControl(rt_uint32_t version,rt_uint32_t address);

/*! 
*  \brief     保存某个控件的数值到FLASH
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*/
void FlashSaveControl(rt_uint16_t screen_id,rt_uint16_t control_id);

/*! 
*  \brief     保存结束
*/
void FlashEndSaveControl(void);

/*! 
*  \brief     从FLASH中恢复控件数据
*  \param  version 数据版本号，主版本号必须与存储时一致，否则会加载失败
*  \param  address 数据在用户存储区的存放地址
*/
void FlashRestoreControl(rt_uint32_t version,rt_uint32_t address);
#endif

#if FIRMWARE_VER>=921
/*! 
*  \brief     设置历史曲线采样数据值(单字节，rt_uint8_t或int8)
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*  \param  value 采样点数据
*  \param  channel 通道数
*/
void HistoryGraph_SetValueInt8(rt_uint16_t screen_id,rt_uint16_t control_id,rt_uint8_t *value,rt_uint8_t channel);

/*! 
*  \brief     设置历史曲线采样数据值(双字节，rt_uint16_t或rt_int16_t)
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*  \param  value 采样点数据
*  \param  channel 通道数
*/
void HistoryGraph_SetValueInt16(rt_uint16_t screen_id,rt_uint16_t control_id,rt_uint16_t *value,rt_uint8_t channel);

/*! 
*  \brief     设置历史曲线采样数据值(四字节，rt_uint32_t或int32)
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*  \param  value 采样点数据
*  \param  channel 通道数
*/
void HistoryGraph_SetValueInt32(rt_uint16_t screen_id,rt_uint16_t control_id,rt_uint32_t *value,rt_uint8_t channel);

/*! 
*  \brief     设置历史曲线采样数据值(单精度浮点数)
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*  \param  value 采样点数据
*  \param  channel 通道数
*/
void HistoryGraph_SetValueFloat(rt_uint16_t screen_id,rt_uint16_t control_id,float *value,rt_uint8_t channel);

/*! 
*  \brief     允许或禁止历史曲线采样
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*  \param  enable 0-禁止，1-允许
*/
void HistoryGraph_EnableSampling(rt_uint16_t screen_id,rt_uint16_t control_id,rt_uint8_t enable);

/*! 
*  \brief     显示或隐藏历史曲线通道
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*  \param  channel 通道编号
*  \param  show 0-隐藏，1-显示
*/
void HistoryGraph_ShowChannel(rt_uint16_t screen_id,rt_uint16_t control_id,rt_uint8_t channel,rt_uint8_t show);


/*! 
*  \brief     设置历史曲线时间长度(即采样点数)
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*  \param  sample_count 一屏显示的采样点数
*/
void HistoryGraph_SetTimeLength(rt_uint16_t screen_id,rt_uint16_t control_id,rt_uint16_t sample_count);

/*! 
*  \brief     历史曲线缩放到全屏
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*/
void HistoryGraph_SetTimeFullScreen(rt_uint16_t screen_id,rt_uint16_t control_id);

/*! 
*  \brief     设置历史曲线缩放比例系数
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*  \param  zoom 缩放百分比(zoom>100%时水平方向缩小，反正放大)
*  \param  max_zoom 缩放限制，一屏最多显示采样点数
*  \param  min_zoom 缩放限制，一屏最少显示采样点数
*/
void HistoryGraph_SetTimeZoom(rt_uint16_t screen_id,rt_uint16_t control_id,rt_uint16_t zoom,rt_uint16_t max_zoom,rt_uint16_t min_zoom);
#endif

#if SD_FILE_EN
/*! 
*  \brief     检测SD卡是否插入
*/
void SD_IsInsert(void);

#define	FA_READ				   0x01  // 可读取
#define	FA_WRITE			   0x02  // 可写入
#define	FA_CREATE_NEW		   0x04  // 创建新文件，如果文件已经存在，则返回失败
#define	FA_CREATE_ALWAYS	   0x08  // 创建新文件，如果文件已经存在，则覆盖
#define	FA_OPEN_EXISTING	   0x00  // 打开文件，如果文件不存在，则返回失败
#define	FA_OPEN_ALWAYS		   0x10  // 打开文件，如果文件不存在，则创建新文件

/*! 
*  \brief     打开或创建文件
*  \param  filename 文件名称(仅ASCII编码)
*  \param  mode 模式，可选组合模式如上FA_XXXX
*/
void SD_CreateFile(rt_uint8_t *filename,rt_uint8_t mode);

/*! 
*  \brief     以当前时间创建文件，例如:20161015083000.txt
*  \param  ext 文件后缀，例如 txt
*/
void SD_CreateFileByTime(rt_uint8_t *ext);

/*! 
*  \brief     在当前文件末尾写入数据
*  \param  buffer 数据
*  \param  dlc 数据长度
*/
void SD_WriteFile(rt_uint8_t *buffer,rt_uint16_t dlc);

/*! 
*  \brief     读取当前文件
*  \param  offset 文件位置偏移
*  \param  dlc 数据长度
*/
void SD_ReadFile(rt_uint32_t offset,rt_uint16_t dlc);

/*! 
*  \brief     获取当前文件长度
*/
void SD_GetFileSize();

/*! 
*  \brief     关闭当前文件
*/
void SD_CloseFile();
#endif

/*! 
*  \brief     记录控件-触发警告
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*  \param  value 告警值
*  \param  time 告警产生的时间，为0时使用屏幕内部时间
*/
void Record_SetEvent(rt_uint16_t screen_id,rt_uint16_t control_id,rt_uint16_t value,rt_uint8_t *time);

/*! 
*  \brief     记录控件-解除警告
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*  \param  value 告警值
*  \param  time 告警解除的时间，为0时使用屏幕内部时间
*/
void Record_ResetEvent(rt_uint16_t screen_id,rt_uint16_t control_id,rt_uint16_t value,rt_uint8_t *time);

/*! 
*  \brief    记录控件- 添加常规记录
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*  \param  record 一条记录(字符串)，子项通过分号隔开，例如：第一项;第二项;第三项;
*/
void Record_Add(rt_uint16_t screen_id,rt_uint16_t control_id,rt_uint8_t *record);

/*! 
*  \brief     记录控件-清除记录数据
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*/
void Record_Clear(rt_uint16_t screen_id,rt_uint16_t control_id);

/*! 
*  \brief     记录控件-设置记录显示偏移
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*  \param  offset 显示偏移，滚动条位置
*/
void Record_SetOffset(rt_uint16_t screen_id,rt_uint16_t control_id,rt_uint16_t offset);

/*! 
*  \brief     记录控件-获取当前记录数目
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*/
void Record_GetCount(rt_uint16_t screen_id,rt_uint16_t control_id);


/*! 
*  \brief     读取屏幕RTC时间
*/
void ReadRTC(void);

/*! 
*  \brief   播放音乐
*  \param   buffer 十六进制的音乐路径及名字
*/
void PlayMusic(rt_uint8_t *buffer);

#endif      //_HMI_DRIVER_
