/*
 * app_config.h
 *
 * Created: 2023-07-18 1:33:59 AM
 *  Author: HAZEM-PC
 */ 


#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_


/*============= configuration set =============*/
#define LEFT_BTN_PORT		PORTD_ID
#define RIGHT_BTN_PORT		PORTD_ID
#define FLASH_BTN_PORT		PORTD_ID
#define LEFT_BTN_PIN		PIN2_ID
#define RIGHT_BTN_PIN		PIN0_ID
#define FLASH_BTN_PIN		PIN1_ID
#define LEFT_LED_PORT		PORTD_ID
#define RIGHT_LED_PORT		PORTD_ID
#define LEFT_LED_PIN		PIN7_ID
#define RIGHT_LED_PIN		PIN5_ID
#define BTN_DEBOUNCE_MS 	100
#define FLASH_TIME_MS		500

#endif /* APP_CONFIG_H_ */