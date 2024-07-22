
/*
 * Filename: swc_clock_control.h
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 */

#ifndef _H_DEFINE_SWC_CLOCK_CONTROL
#define _H_DEFINE_SWC_CLOCK_CONTROL

#include "project.h"
#include "global.h"
#include "rte_types.h"



/* USER CODE START SWC_CLOCK_CONTROL_USERDEFINITIONS */
void Clock_Auto_Run();
/* USER CODE END SWC_CLOCK_CONTROL_USERDEFINITIONS */


/*
* component: swc_Clock_Control
* cycletime: 1000
* description: This Runnable is oprating the state machine of the clock.
* events: ev_event_signal_onData
* name: CLOCK_CONTROL__run
* shortname: 
* signalIN: so_Event_Signal
* signalOUT: so_Clock_Signal
* task: tsk_Clock_Control
*/
void CLOCK_CONTROL__run(RTE_event ev);


#endif