

/*
 * Filename: swc_button_read.c
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 */

#include "project.h"
#include "global.h"
#include "rte.h"
#include "rte_types.h"
#include "swc_button_read.h"



/* USER CODE START SWC_BUTTON_READ_INCLUDE */

/* USER CODE END SWC_BUTTON_READ_INCLUDE */


#include "sp_common_signal.h"

/* USER CODE START SWC_BUTTON_READ_USERDEFINITIONS */

/* USER CODE END SWC_BUTTON_READ_USERDEFINITIONS */



/*
* component: swc_Button_Read
* cycletime: 50
* description: This runnable reads the data out of the buttons and send the event to the Clock control runnable
* events: 
* name: BUTTON_READ__run
* shortname: 
* signalIN: 
* signalOUT: so_Event_Signal
* task: tsk_IO
*/
void BUTTON_READ__run(RTE_event ev){
	
	/* USER CODE START BUTTON_READ__run */

    SC_EVENT_SIGNAL_data_t Button_Signal = SC_EVENT_SIGNAL_INIT_DATA;
    
    // Read Joystick signal from the joystick driver.
    if ( RC_SUCCESS == RTE_SC_EVENT_SIGNAL_pullPort(&SO_EVENT_SIGNAL_signal))
    {
        
    }
    else
    {
         UART_LOG_PutString("Event Data Not updated ");        
    }
  
    /* USER CODE END BUTTON_READ__run */
}

/* USER CODE START SWC_BUTTON_READ_FUNCTIONS */

/* USER CODE END SWC_BUTTON_READ_FUNCTIONS */

