/*
 * app.h
 *
 *  Created on: Jul 15, 2023
 *      Author: HAZEM-PC
 */

#ifndef APP_APP_H_
#define APP_APP_H_

/*============= FILE INCLUSION =============*/
#include "util/delay.h"
#include "../HAL/Button/button.h"
#include "../HAL/Led/led.h"
#include "../HAL/LCD/lcd_config.h"
#include "app_config.h"

/*============= TYPE DEFINITION =============*/
typedef enum{
	RIGHT_EVENT,
	LEFT_EVENT,
	WAIT_EVENT,
	MAX_EVENT
}enu_btn_event_t;

typedef enum{
	RIGHT_SIGNAL,
	LEFT_SIGNAL,
	FLASH_SIGNAL,
	NO_SIGNAL,
	FLASH_RHT_SIGNAL,
	FLASH_LFT_SIGNAL,
	MAX_SIGNAL
}enu_light_state_t;


/*============= FUNCTION PROTOTYPE =============*/

/**
 * @brief       app_init	    :   Function used to initialize Led , button and LCD
 *
 * @param[in]   void			:	
 *
 * @return      void			:
 */
void app_init(void);

/*===========================================================================*/

/**
 * @brief       get_event	    :   Function used to read buttons states and determine the event
 *
 * @param[in]   void			:	
 *
 * @return      RIGHT_EVENT		:   in case of right button pressed
 *              LEFT_EVENT 		:   in case of left button pressed
 *				WAIT_EVENT		:	in case of wait button pressed
 *				MAX_EVENT		:	in case of no button pressed
 */
enu_btn_event_t get_event (void);

/*===========================================================================*/

/**
 * @brief       light_stateMachine	:   Function used to read buttons states and determine the event
 *
 * @param[in]   enu_btn_event		:	type of event
 *
 * @return      RIGHT_SIGNAL		:   in case of right led on
 *              LEFT_SIGNAL 		:   in case of left led on
 *				FLASH_SIGNAL		:	in case of both led on
 *				NO_SIGNAL			:	in case of both led off
 *				FLASH_RHT_SIGNAL	:	in case of right led on and flash mode
 *				FLASH_LFT_SIGNAL	:	in case of left led on and flash mode
 *				MAX_SIGNAL			:	Max states of led
 */
enu_light_state_t light_stateMachine (enu_btn_event_t enu_btn_event);

/*===========================================================================*/
/**
 * @brief       light_action		:   Function used to set led according to mode
 *
 * @param[in]   RIGHT_SIGNAL		:   in case of right led on
 *              LEFT_SIGNAL 		:   in case of left led on
 *				FLASH_SIGNAL		:	in case of both led on
 *				NO_SIGNAL			:	in case of both led off
 *				FLASH_RHT_SIGNAL	:	in case of right led on and flash mode
 *				FLASH_LFT_SIGNAL	:	in case of left led on and flash mode
 *				MAX_SIGNAL			:	Max states of led
 * @return		void		
 */
void light_action (enu_light_state_t enu_light_state);

/*===========================================================================*/

/**
 * @brief       screen_update		:   Function used to update the LCD with car signal state
 *
 * @param[in]   RIGHT_SIGNAL		:   in case of right led on
 *              LEFT_SIGNAL 		:   in case of left led on
 *				FLASH_SIGNAL		:	in case of both led on
 *				NO_SIGNAL			:	in case of both led off
 *				FLASH_RHT_SIGNAL	:	in case of right led on and flash mode
 *				FLASH_LFT_SIGNAL	:	in case of left led on and flash mode
 *				MAX_SIGNAL			:	Max states of led
 * @return		void		
 */
void screen_update (enu_light_state_t enu_light_state);

/*===========================================================================*/

/**
 * @brief       app_start	    :   Function used to start application run in infinity loop
 *
 * @param[in]   void				
 *
 * @return      void			
 */
void app_start(void);


#endif /* APP_APP_H_ */
