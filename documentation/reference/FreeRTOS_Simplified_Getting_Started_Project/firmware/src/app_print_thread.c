/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_print_thread.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "app_print_thread.h"
#include <stdio.h>
#include "definitions.h"
#include "app_user_input_thread.h"
// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************



// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the app_PRINT_THREAD_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP_PRINT_THREAD_DATA app_printData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************



// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void app_PRINT_THREAD_Initialize ( void )

  Remarks:
    See prototype in app_print_thread.h.
 */

void APP_PRINT_THREAD_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    
    app_printData.isInitDone = false; 
    
    xAPP_PRINT_THREAD_Tasks = NULL;
}


/******************************************************************************
  Function:
    void app_PRINT_THREAD_Tasks ( void )

  Remarks:
    See prototype in app_print_thread.h.
 */

void APP_PRINT_THREAD_Tasks ( void )
{

    uint8_t strlen; 
            
        /* Open the drivers if not already opened */
    if (app_printData.isInitDone == false)
    {
            
        app_printData.usartHandle = DRV_USART_Open(DRV_USART_INDEX_0, 0);
           
        if (app_printData.usartHandle != DRV_HANDLE_INVALID)
        {
            /* All drivers opened successfully */
            app_printData.isInitDone = true;
            strlen = sprintf((char*)app_printData.usartTxBuffer, "***FreeRTOS Simplified*** \r\n Press SW0 on IO1 Xplained board for latest temperature data\r\n"); 
                
            DRV_USART_WriteBuffer(app_printData.usartHandle, app_printData.usartTxBuffer, strlen);
        }
        else
        {
           /* Handle error */
        }
    }        
   
    /* Block to wait for APP_Tasks() to notify this task. */
    xTaskNotifyWait(0,pdTRUE,0,portMAX_DELAY);
    
    xQueueReceive( eventQueue, &app_printData.eventInfo, portMAX_DELAY );
        
    strlen = sprintf((char*)app_printData.usartTxBuffer, "User Input received \r\nTemperature = %d F\r\n", (uint8_t)app_printData.eventInfo.eventData); 
                
    DRV_USART_WriteBuffer(app_printData.usartHandle, app_printData.usartTxBuffer, strlen);
            
}//end of print task        

   

/*******************************************************************************
 End of File
 */
