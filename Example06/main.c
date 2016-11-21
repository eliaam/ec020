/*
    FreeRTOS V6.1.1 - Copyright (C) 2011 Real Time Engineers Ltd.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    ***NOTE*** The exception to the GPL is included to allow you to distribute
    a combined work that includes FreeRTOS without being obliged to provide the
    source code for proprietary components outside of the FreeRTOS kernel.
    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public
    License and the FreeRTOS license exception along with FreeRTOS; if not it
    can be viewed here: http://www.freertos.org/a00114.html and also obtained
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

    http://www.FreeRTOS.org - Documentation, latest information, license and
    contact details.

    http://www.SafeRTOS.com - A version that is certified for use in safety
    critical systems.

    http://www.OpenRTOS.com - Commercial support, development, porting,
    licensing and training services.
*/

/* FreeRTOS.org includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "sensor.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_i2c.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_ssp.h"
#include "lpc17xx_timer.h"
#include "oled.h"
#include "acc.h"
#include "light.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "basic_io.h"

static void vSenderTask( void *pvParameters );
static void vReceiverTask( void *pvParameters );

xQueueHandle xQueue;

int main( void )
{
	 xQueue = xQueueCreate( 5, sizeof( int ) );

		if( xQueue != NULL )
		{

			xTaskCreate( vSenderTask, "Sender1", 240, ( void * ) 100, 1, NULL );

			xTaskCreate( vReceiverTask, "Receiver", 240, NULL, 2, NULL );

			vTaskStartScheduler();
		}
		else
		{

		}

	for( ;; );
	return 0;
}

/*-----------------------------------------------------------*/
void delay (int x){
	int i,j;
	for(i=0;i<x;i++){
		for(j=0;j<x;j++);
	}

}

static void vSenderTask( void *pvParameters )
{
	long lValueToSend;
	portBASE_TYPE xStatus;
	int luz;
	SensorLuz_new();

	lValueToSend = ( long ) pvParameters;

	for( ;; )
	{
		luz=SensorLuz_read();
		xStatus = xQueueSendToBack( xQueue, &luz, 0 );

		if( xStatus != pdPASS )
		{
			vPrintString( "Could not send to the queue.\r\n" );
		}

		taskYIELD();
	}
}

static void vReceiverTask( void *pvParameters )
{
	/* Declare the variable that will hold the values received from the queue. */
	long lReceivedValue;
	portBASE_TYPE xStatus;
	const portTickType xTicksToWait = 100 / portTICK_RATE_MS;

	DisplayOled_new();
	init_ssp();

	for( ;; )
	{
		if( uxQueueMessagesWaiting( xQueue ) != 0 )
		{
			vPrintString( "Queue should have been empty!\r\n" );
		}
		xStatus = xQueueReceive( xQueue, &lReceivedValue, xTicksToWait );
		delay(2000);
		if( xStatus == pdPASS )
		{
			//vPrintStringAndNumber( "Received = ", lReceivedValue );
			DisplayOled_write(lReceivedValue);
		}
		else
		{
			vPrintString( "Could not receive from the queue.\r\n" );
		}
	}
}

void vApplicationMallocFailedHook( void )
{
	/* This function will only be called if an API call to create a task, queue
	or semaphore fails because there is too little heap RAM remaining. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName )
{
	/* This function will only be called if a task overflows its stack.  Note
	that stack overflow checking does slow down the context switch
	implementation. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	/* This example does not use the idle hook to perform any processing. */
}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
	/* This example does not use the tick hook to perform any processing. */
}


