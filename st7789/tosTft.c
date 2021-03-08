/*
 * tosTft.c
 *
 *  Created on: Dec 4, 2020
 *      Author: neset
 */
#include "tosTft.h"
#include "st7789.h"
#include "main.h"

#if DMA_ACTIVE
static lv_disp_drv_t * st7789disp_p;
#endif

static void st7789_flush_cb(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);
void tos_Tft_init(void){
	  ST7789_Init();
	  lv_init();

	 static lv_disp_buf_t disp_buf;
	 static lv_color_t buf[LV_HOR_RES_MAX * LV_VER_RES_MAX / 10];
	 lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * LV_VER_RES_MAX / 10);

	  lv_disp_drv_t disp_drv;
	  lv_disp_drv_init(&disp_drv);
	  disp_drv.buffer = &disp_buf;
	  disp_drv.flush_cb = st7789_flush_cb;
	  lv_disp_drv_register(&disp_drv);

}

static void st7789_flush_cb(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
	 	if(area->x2 < 0) return;
	    if(area->y2 < 0) return;
	    if(area->x1 > LV_HOR_RES_MAX - 1) return;
	    if(area->y1 > LV_VER_RES_MAX - 1) return;


#if DMA_ACTIVE
	      ST7789_Send_Data_DMA(area->x1, area->y1, area->x2, area->y2,(uint8_t *)color_p);
	      st7789disp_p=disp_drv;
#else
	ST7789_Send_Data(area->x1, area->y1, area->x2, area->y2,(uint8_t *)color_p);
    lv_disp_flush_ready(disp_drv);
#endif
}
#if DMA_ACTIVE
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	lv_disp_flush_ready(st7789disp_p);
}

void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi){}
#endif
void tos_Lvgl_test(void)
{lv_obj_t * label2;
    label2 = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(label2, "Bismillah\ntest");
    lv_obj_align(label2, NULL, LV_ALIGN_CENTER, 0, 0);
}


