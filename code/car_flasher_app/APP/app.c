/*
 * app.c
 *
 *  Created on: Jul 15, 2023
 *      Author: HAZEM-PC
 */

/*============= FILE INCLUSION =============*/
#include "app.h"

/*============= Global Variables =============*/
enu_light_state_t gl_enu_light_state	= NO_SIGNAL;
uint8 left_btn_value					= LOGIC_LOW;
uint8 right_btn_value					= LOGIC_LOW;
uint8 flash_btn_value					= LOGIC_LOW;
BOOLEAN left_btn_flag					= TRUE;
BOOLEAN right_btn_flag					= TRUE;
BOOLEAN flash_btn_flag					= TRUE;

/*============= FUNCTION DEFINITIONS =============*/

void app_init(void)
{
	LCD_init();
	button_init(LEFT_BTN_PORT, LEFT_BTN_PIN);
	button_init(RIGHT_BTN_PORT, RIGHT_BTN_PIN);
	button_init(FLASH_BTN_PORT, FLASH_BTN_PIN);
	led_init(LEFT_LED_PORT, LEFT_LED_PIN);
	led_init(RIGHT_LED_PORT, RIGHT_LED_PIN);
}


/*===========================================================================*/

/*
enu_btn_event_t get_event (void)
{
	enu_btn_event_t enu_btn_event = MAX_EVENT;
	button_read(LEFT_BTN_PORT, LEFT_BTN_PIN, &left_btn_value);
	button_read(RIGHT_BTN_PORT, RIGHT_BTN_PIN, &right_btn_value);
	button_read(FLASH_BTN_PORT, FLASH_BTN_PIN, &flash_btn_value);

	if (left_btn_value == LOGIC_HIGH)
	{
		if(left_btn_flag == FALSE)
		{
			left_btn_flag = TRUE;
			enu_btn_event = LEFT_EVENT;
		}
	}
	else if(right_btn_value == LOGIC_HIGH)
	{
		if(right_btn_flag == FALSE)
		{
			right_btn_flag = TRUE;
			enu_btn_event = RIGHT_EVENT;
		}
	}
	else if(flash_btn_value == LOGIC_HIGH)
	{	
		if(flash_btn_flag == FALSE)
		{
			flash_btn_flag = TRUE;
			enu_btn_event = WAIT_EVENT;
		}	
	}
	else
	{
		left_btn_flag = FALSE;
		right_btn_flag = FALSE;
		flash_btn_flag = FALSE;	
	}
	return enu_btn_event;
}
*/

/*===========================================================================*/

enu_btn_event_t get_event (void)
{
	enu_btn_event_t enu_btn_event = MAX_EVENT;
	button_read(LEFT_BTN_PORT, LEFT_BTN_PIN, &left_btn_value);
	button_read(RIGHT_BTN_PORT, RIGHT_BTN_PIN, &right_btn_value);
	button_read(FLASH_BTN_PORT, FLASH_BTN_PIN, &flash_btn_value);

	if (left_btn_value == LOGIC_HIGH)
	{
		_delay_ms(BTN_DEBOUNCE_MS);
		button_read(LEFT_BTN_PORT, LEFT_BTN_PIN, &left_btn_value);
		if(left_btn_value == LOGIC_HIGH)
		{
			if(left_btn_flag == FALSE)
			{
				enu_btn_event = LEFT_EVENT;
				left_btn_flag = TRUE;
			}
		}
	}
	else if(right_btn_value == LOGIC_HIGH)
	{
		_delay_ms(BTN_DEBOUNCE_MS);
		button_read(RIGHT_BTN_PORT, RIGHT_BTN_PIN, &right_btn_value);
		if(right_btn_value == LOGIC_HIGH)
		{
			if(right_btn_flag == FALSE)
			{
				enu_btn_event = RIGHT_EVENT;
				right_btn_flag = TRUE;
			}
		}
	}
	else if(flash_btn_value == LOGIC_HIGH)
	{
		_delay_ms(BTN_DEBOUNCE_MS);
		button_read(FLASH_BTN_PORT, FLASH_BTN_PIN, &flash_btn_value);
		if(flash_btn_value == LOGIC_HIGH)
		{
			if(flash_btn_flag == FALSE)
			{
			
				enu_btn_event = WAIT_EVENT;
				flash_btn_flag = TRUE;
			}
		}
	}
	else
	{
		left_btn_flag = FALSE;
		right_btn_flag = FALSE;
		flash_btn_flag = FALSE;	
	}

	return enu_btn_event;
}

/*===========================================================================*/

void light_action (enu_light_state_t enu_light_state)
{
	if(enu_light_state == RIGHT_SIGNAL)
	{
		led_write(RIGHT_LED_PORT, RIGHT_LED_PIN, PIN_HIGH);
		led_write(LEFT_LED_PORT, LEFT_LED_PIN, PIN_LOW);
	}
	else if(enu_light_state == LEFT_SIGNAL)
	{
		led_write(RIGHT_LED_PORT, RIGHT_LED_PIN, PIN_LOW);
		led_write(LEFT_LED_PORT, LEFT_LED_PIN, PIN_HIGH);
	}
	else if((enu_light_state == FLASH_SIGNAL) || (enu_light_state == FLASH_LFT_SIGNAL) || (enu_light_state == FLASH_RHT_SIGNAL))
	{
		led_write(RIGHT_LED_PORT, RIGHT_LED_PIN, PIN_HIGH);
		led_write(LEFT_LED_PORT, LEFT_LED_PIN, PIN_HIGH);
		_delay_ms(FLASH_TIME_MS);
		led_write(RIGHT_LED_PORT, RIGHT_LED_PIN, PIN_LOW);
		led_write(LEFT_LED_PORT, LEFT_LED_PIN, PIN_LOW);
		_delay_ms(FLASH_TIME_MS);
	}
	else if(enu_light_state == NO_SIGNAL)
	{
		led_write(RIGHT_LED_PORT, RIGHT_LED_PIN, PIN_LOW);
		led_write(LEFT_LED_PORT, LEFT_LED_PIN, PIN_LOW);
	}
	else
	{
		//do nothing
	}

}

/*===========================================================================*/

enu_light_state_t light_stateMachine (enu_btn_event_t enu_btn_event)
{
	static enu_btn_event_t st_enu_btn_event = MAX_EVENT;
	if(enu_btn_event != st_enu_btn_event)
	{
		st_enu_btn_event = enu_btn_event;
		switch(gl_enu_light_state)
		{
			case RIGHT_SIGNAL:
			{
				switch(enu_btn_event)
				{
					case RIGHT_EVENT:
					{
						gl_enu_light_state = RIGHT_SIGNAL;
					}
					break;
					case LEFT_EVENT:
					{
						gl_enu_light_state = NO_SIGNAL;
					}
					break;
					case WAIT_EVENT:
					{
						gl_enu_light_state = FLASH_RHT_SIGNAL;
					}
					break;
					default:
					{
					//do nothing
					}
					break;
				}
			}
			break;
			case LEFT_SIGNAL:
			{
				switch(enu_btn_event)
				{
					case RIGHT_EVENT:
					{
						gl_enu_light_state = NO_SIGNAL;
					}
					break;
					case LEFT_EVENT:
					{
						gl_enu_light_state = LEFT_SIGNAL;
					}
					break;
					case WAIT_EVENT:
					{
						gl_enu_light_state = FLASH_LFT_SIGNAL;
					}
					break;
					default:
					{
					
					}
					break;
				}
			}
			break;
			case FLASH_SIGNAL:
			{
				switch(enu_btn_event)
				{
					case RIGHT_EVENT:
					{
						gl_enu_light_state = FLASH_RHT_SIGNAL;
					}
					break;
					case LEFT_EVENT:
					{
						gl_enu_light_state = FLASH_LFT_SIGNAL;
					}
					break;
					case WAIT_EVENT:
					{
						gl_enu_light_state = NO_SIGNAL;
					}
					break;
					default:
					{
									
					}
					break;
				}
			}
			break;
			case NO_SIGNAL:
			{
				switch(enu_btn_event)
				{
					case RIGHT_EVENT:
					{
						gl_enu_light_state = RIGHT_SIGNAL;
					}
					break;
					case LEFT_EVENT:
					{
						gl_enu_light_state = LEFT_SIGNAL;
					}
					break;
					case WAIT_EVENT:
					{
						gl_enu_light_state = FLASH_SIGNAL;
					}
					break;
					default:
					{
									
					}
					break;
				}
			}
			break;
			case FLASH_RHT_SIGNAL:
			{
				switch(enu_btn_event)
				{
					case RIGHT_EVENT:
					{
						gl_enu_light_state = FLASH_RHT_SIGNAL;
					}
					break;
					case LEFT_EVENT:
					{
						gl_enu_light_state = FLASH_SIGNAL;
					}
					break;
					case WAIT_EVENT:
					{
						gl_enu_light_state = RIGHT_SIGNAL;
					}
					break;
					default:
					{
					}
					break;
				}
			}
			break;
			case FLASH_LFT_SIGNAL:
			{
				switch(enu_btn_event)
				{
					case RIGHT_EVENT:
					{
						gl_enu_light_state = FLASH_SIGNAL;
					}
					break;
					case LEFT_EVENT:
					{
						gl_enu_light_state = FLASH_LFT_SIGNAL;
					}
					break;
					case WAIT_EVENT:
					{
						gl_enu_light_state = LEFT_SIGNAL;
					}
					break;
					default:
					{
					}
					break;
				}
			}
			break;
			default:
			{
				//do nothing
			}
			break;
		}
	}
	return gl_enu_light_state;
}

/*===========================================================================*/
void screen_update (enu_light_state_t enu_light_state)
{
	static enu_light_state_t st_enu_light_state = MAX_SIGNAL;
	if(enu_light_state != st_enu_light_state)
	{
		st_enu_light_state = enu_light_state;
		LCD_clearScreen();
		if(enu_light_state == RIGHT_SIGNAL)
		{
			LCD_displayString("right signal");
		}
		else if(enu_light_state == LEFT_SIGNAL)
		{
			LCD_displayString("left signal");
		}
		else if(enu_light_state == FLASH_SIGNAL) 
		{
			LCD_displayString("wait signal");
		}
		else if(enu_light_state == NO_SIGNAL)
		{
			LCD_displayString("no signal");
		}
		else if (enu_light_state == FLASH_LFT_SIGNAL)
		{
			LCD_displayString("left signal");
			LCD_displayStringRowColumn(1,0,"wait signal");
		}
		else if (enu_light_state == FLASH_RHT_SIGNAL)
		{
			LCD_displayString("right signal");
			LCD_displayStringRowColumn(1,0,"wait signal");
		}
		else
		{
			//do nothing
		}
	}
}


/*===========================================================================*/

void app_start(void)
{
	enu_btn_event_t enu_btn_event = MAX_EVENT;
	LCD_clearScreen();
	LCD_displayString("CAR IS READY");
	_delay_ms(5000);
	while(1)
	{
		enu_btn_event = get_event();
		gl_enu_light_state=light_stateMachine(enu_btn_event);
		light_action(gl_enu_light_state);
		screen_update(gl_enu_light_state);
	}
}
