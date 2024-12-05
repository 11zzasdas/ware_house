/*
 * @Descripttion: 文件描述
 * @version: 文件版本
 * @Author: jinsc
 * @Date: 2022-09-04 19:24:25
 * @LastEditors: jinsc
 * @LastEditTime: 2022-09-05 21:15:53
 * @FilePath: \lvgl\main\lvgl_main.c
 */
/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp_log.h"
#include "./driver/gpio.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "ui.h"


//C:\Espressif\frameworks\esp-idf-v4.4.6\components\driver\include\driver\gpio.h
//C:\Espressif\frameworks\esp-idf-v4.4.6\components\esp_lcd\include\esp_lcd_panel_vendor.h
/*用定时器给LVGL提供时钟*/
static void lv_tick_task(void *arg)
{
	(void)arg;
	lv_tick_inc(10);
}
void app_main(void)
{
    printf("Hello world!\n");
    lv_init();
    lv_port_disp_init();
    //lv_demo_music();
    ui_init();

    lv_port_indev_init();
    lv_indev_set_group(indev_keypad, group);
    

    /*  esp_register_freertos_tick_hook(lv_tick_task);
    Create and start a periodic timer interrupt to call lv_tick_inc 
    */
    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &lv_tick_task,
        .name = "periodic_gui"};
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, 10 * 1000));



    while(1)
    {

        lv_task_handler();
        /* lv_tick_inc(10); //12/04bug修改 开定时器后就可以关闭了*/
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
