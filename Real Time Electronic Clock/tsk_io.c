

/*
 * Filename: tsk_io.c
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 */

#include "project.h"
#include "global.h"
#include "rte.h"
#include "rte_types.h"
#include "tsk_io.h"



/* USER CODE START TSK_IO_INCLUDE */

/* USER CODE END TSK_IO_INCLUDE */

#include "swc_button_read.h"



/* USER CODE START TSK_IO_USERDEFINITIONS */

/* USER CODE END TSK_IO_USERDEFINITIONS */

/*******************************************************************************
 * Runnable Tables from Activation Engine
 *******************************************************************************/

/* Cyclic Table */

const RTE_cyclicTable_t RTE_cyclicActivationTable_tsk_io[] = {
	{ BUTTON_READ__run, 50 },	//This runnable reads the data out of the buttons and send the event to the Clock control runnable
};
const uint16_t RTE_cyclicActivation_tsk_io_size = sizeof (RTE_cyclicActivationTable_tsk_io) / sizeof(RTE_cyclicTable_t); 


/*******************************************************************************
 * Task Body
 *******************************************************************************/


/*
* description: This task Handles all the Input and output events
* events: 
* mode: Cyclic
* name: tsk_IO
* shortname: IO
* signalpoolsRO: sp_Common_Signal
* signalpoolsRW: sp_Common_Signal
* tickEvent: 0
* timertickperiod: 1
*/
TASK(tsk_IO)
{
	/* ticktime of the task */
	static uint32_t ticktime = 0;

	/* USER CODE START TSK_IO_TASKBOBY_PRE */

	/* USER CODE END TSK_IO_TASKBODY_PRE */
    
    //Process all cyclic runnables which are due
    RTE_ProcessCyclicTable(RTE_cyclicActivationTable_tsk_io, RTE_cyclicActivation_tsk_io_size, ticktime);
	
	/* USER CODE START TSK_IO_TASKBODY_POST */

	/* USER CODE END TSK_IO_TASKBODY_POST */

	ticktime += 1;
	if (ticktime > 0xFFFFFF00) ticktime = 0;
    TerminateTask();
}


/*******************************************************************************
 * Interrupt Service Routines
 *******************************************************************************/

/* USER CODE START TSK_IO_ISR */

/* USER CODE END TSK_IO_ISR */
