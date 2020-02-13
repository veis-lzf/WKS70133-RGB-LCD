/**
  *********************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   RT-Thread 3.0 + STM32 固件库例程
  *********************************************************************
  * @attention
  *
  * 实验平台:野火 STM32F429挑战者 开发板
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  **********************************************************************
  */

/*
*************************************************************************
*                             包含的头文件
*************************************************************************
*/
#include "board.h"
#include "rtthread.h"


/*
*************************************************************************
*                               变量
*************************************************************************
*/
/* 定义线程控制块 */
static rt_thread_t test_thread = RT_NULL;

/*
*************************************************************************
*                             函数声明
*************************************************************************
*/
static void test_thread_entry(void* parameter);

void LCD_Test(void);

/*
*************************************************************************
*                             main 函数
*************************************************************************
*/
/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
    /*
     * 开发板硬件初始化，RTT系统初始化已经在main函数之前完成，
     * 即在component.c文件中的rtthread_startup()函数中完成了。
     * 所以在main函数中，只需要创建线程和启动线程即可。
     */

    test_thread =                          /* 线程控制块指针 */
        rt_thread_create( "test",              /* 线程名字 */
                          test_thread_entry,   /* 线程入口函数 */
                          RT_NULL,             /* 线程入口函数参数 */
                          512,                 /* 线程栈大小 */
                          3,                   /* 线程的优先级 */
                          20);                 /* 线程时间片 */

    /* 启动线程，开启调度 */
    if (test_thread != RT_NULL)
        rt_thread_startup(test_thread);
    else
        return -1;
}

/*
*************************************************************************
*                             线程定义
*************************************************************************
*/

static void test_thread_entry(void* parameter)
{
    while (1)
    {
        LCD_Test();
    }
}




/*用于测试各种液晶的函数*/
void LCD_Test(void)
{
    /*演示显示变量*/
    static uint8_t testCNT = 0;
    char dispBuff[100];

    testCNT++;

    /*使用不透明前景层*/
    LCD_SetLayer(LCD_FOREGROUND_LAYER);
    LCD_SetTransparency(0xff);

    LCD_Clear(LCD_COLOR_BLACK);	/* 清屏，显示全黑 */

    /*设置字体颜色及字体的背景颜色(此处的背景不是指LCD的背景层！注意区分)*/
    LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);

    /*选择字体*/
    LCD_SetFont(&Font16x24);

    LCD_DisplayStringLine(LINE(1), (uint8_t* )"BH 5.0 inch LCD para:");
    LCD_DisplayStringLine(LINE(2), (uint8_t* )"Image resolution:800x480 px");
    LCD_DisplayStringLine(LINE(3), (uint8_t* )"Touch pad:5 point touch supported");
    LCD_DisplayStringLine(LINE(4), (uint8_t* )"Use STM32-LTDC directed driver,");
    LCD_DisplayStringLine(LINE(5), (uint8_t* )"no extern lcd driver needed,RGB888,24bits data bus");
    LCD_DisplayStringLine(LINE(6), (uint8_t* )"Touch pad use IIC to communicate");

    /*使用c标准库把变量转化成字符串*/
    sprintf(dispBuff, "Display value demo: testCount = %d ", testCNT);
    LCD_ClearLine(LINE(7));

    /*然后显示该字符串即可，其它变量也是这样处理*/
    LCD_DisplayStringLine(LINE(7), (uint8_t* )dispBuff);


    /* 画直线 */
    LCD_SetTextColor(LCD_COLOR_BLUE);

    LCD_ClearLine(LINE(8));
    LCD_DisplayStringLine(LINE(8), (uint8_t* )"Draw line:");

    LCD_SetColors(LCD_COLOR_RED, LCD_COLOR_BLACK);
    LCD_DrawUniLine(50, 250, 750, 250);
    LCD_DrawUniLine(50, 300, 750, 300);

    LCD_SetColors(LCD_COLOR_GREEN, LCD_COLOR_BLACK);
    LCD_DrawUniLine(300, 250, 400, 400);
    LCD_DrawUniLine(600, 250, 600, 400);

    rt_thread_delay(500);   /* 延时500个tick */

    LCD_SetColors(LCD_COLOR_BLACK, LCD_COLOR_BLACK);
    LCD_DrawFullRect(0, 200, LCD_PIXEL_WIDTH, LCD_PIXEL_HEIGHT - 200);


    /*画矩形*/
    LCD_SetTextColor(LCD_COLOR_BLUE);
    LCD_ClearLine(LINE(8));
    LCD_DisplayStringLine(LINE(8), (uint8_t* )"Draw Rect:");

    LCD_SetColors(LCD_COLOR_RED, LCD_COLOR_BLACK);
    LCD_DrawRect(200, 250, 200, 100);

    LCD_SetColors(LCD_COLOR_GREEN, LCD_COLOR_BLACK);
    LCD_DrawRect(350, 250, 200, 50);

    LCD_SetColors(LCD_COLOR_BLUE, LCD_COLOR_BLACK);
    LCD_DrawRect(200, 350, 50, 200);

    rt_thread_delay(500);   /* 延时500个tick */


    LCD_SetColors(LCD_COLOR_BLACK, LCD_COLOR_BLACK);
    LCD_DrawFullRect(0, 200, LCD_PIXEL_WIDTH, LCD_PIXEL_HEIGHT - 200);


    /*填充矩形*/
    LCD_SetTextColor(LCD_COLOR_BLUE);
    LCD_ClearLine(LINE(8));
    LCD_DisplayStringLine(LINE(8), (uint8_t* )"Draw Full Rect:");

    LCD_SetColors(LCD_COLOR_RED, LCD_COLOR_BLACK);
    LCD_DrawFullRect(200, 250, 200, 100);

    LCD_SetColors(LCD_COLOR_GREEN, LCD_COLOR_BLACK);
    LCD_DrawFullRect(350, 250, 200, 50);

    LCD_SetColors(LCD_COLOR_BLUE, LCD_COLOR_BLACK);
    LCD_DrawFullRect(200, 350, 50, 200);

    rt_thread_delay(500);   /* 延时500个tick */

    LCD_SetColors(LCD_COLOR_BLACK, LCD_COLOR_BLACK);
    LCD_DrawFullRect(0, 200, LCD_PIXEL_WIDTH, LCD_PIXEL_HEIGHT - 200);

    /* 画圆 */
    LCD_SetTextColor(LCD_COLOR_BLUE);
    LCD_ClearLine(LINE(8));
    LCD_DisplayStringLine(LINE(8), (uint8_t* )"Draw circle:");

    LCD_SetColors(LCD_COLOR_RED, LCD_COLOR_RED);
    LCD_DrawCircle(200, 350, 50);

    LCD_SetColors(LCD_COLOR_GREEN, LCD_COLOR_GREEN);
    LCD_DrawCircle(350, 350, 75);

    rt_thread_delay(500);   /* 延时500个tick */

    LCD_SetColors(LCD_COLOR_BLACK, LCD_COLOR_BLACK);
    LCD_DrawFullRect(0, 200, LCD_PIXEL_WIDTH, LCD_PIXEL_HEIGHT - 200);


    /*填充圆*/
    LCD_SetTextColor(LCD_COLOR_BLUE);
    LCD_ClearLine(LINE(8));
    LCD_DisplayStringLine(LINE(8), (uint8_t* )"Draw full circle:");

    LCD_SetColors(LCD_COLOR_RED, LCD_COLOR_BLACK);
    LCD_DrawFullCircle(300, 350, 50);

    LCD_SetColors(LCD_COLOR_GREEN, LCD_COLOR_BLACK);
    LCD_DrawFullCircle(450, 350, 75);

    rt_thread_delay(500);   /* 延时500个tick */

    LCD_SetColors(LCD_COLOR_BLACK, LCD_COLOR_BLACK);
    LCD_DrawFullRect(0, 200, LCD_PIXEL_WIDTH, LCD_PIXEL_HEIGHT - 200);

    LCD_ClearLine(LINE(8));

//这种操作效果会有花屏现象，不推荐使用。一般背景混合使用ARGB格式的颜色来混合
//	/*透明效果 前景层操作*/
//	{
//		LCD_SetTextColor(LCD_COLOR_BLUE);
//		LCD_ClearLine(LINE(8));
//		LCD_DisplayStringLine(LINE(8),(uint8_t* )"Transparency effect:");
//
//		/*设置前景层不透明度*/
//		LCD_SetLayer(LCD_FOREGROUND_LAYER);
//		LCD_SetTransparency(200);
//
//		/*在前景画一个红色圆*/
//		LCD_SetColors(LCD_COLOR_RED,LCD_COLOR_BLACK);
//		LCD_DrawFullCircle(400,350,75);
//
//	}
//
//	/*透明效果 背景层操作*/
//	{
//		/*设置背景层不透明*/
//		LCD_SetLayer(LCD_BACKGROUND_LAYER);
//		LCD_SetTransparency(0xff);
//		LCD_Clear(LCD_COLOR_BLACK);

//		/*在背景画一个绿色圆*/
//		LCD_SetColors(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
//		LCD_DrawFullCircle(450,350,75);
//
//		/*在背景画一个蓝色圆*/
//		LCD_SetColors(LCD_COLOR_BLUE,LCD_COLOR_BLACK);
//		LCD_DrawFullCircle(350,350,75);
//	}

    rt_thread_delay(500);   /* 延时500个tick */

    LCD_SetColors(LCD_COLOR_BLACK, LCD_COLOR_BLACK);
    LCD_DrawFullRect(0, 200, LCD_PIXEL_WIDTH, LCD_PIXEL_HEIGHT - 200);


}


/********************************END OF FILE****************************/
