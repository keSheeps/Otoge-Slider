/*
             LUFA Library
     Copyright (C) Dean Camera, 2017.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2017  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  Main source file for the Joystick demo. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */

#include "Joystick.h"

/** Buffer to hold the previously generated HID report, for comparison purposes inside the HID class driver. */
static uint8_t PrevJoystickHIDReportBuffer[sizeof(USB_JoystickReport_Data_t)];
int thresholds[16];
/** LUFA HID Class driver interface configuration and state information. This structure is
 *  passed to all HID Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_HID_Device_t Joystick_HID_Interface =
	{
		.Config =
			{
				.InterfaceNumber              = INTERFACE_ID_Joystick,
				.ReportINEndpoint             =
					{
						.Address              = JOYSTICK_EPADDR,
						.Size                 = JOYSTICK_EPSIZE,
						.Banks                = 1,
					},
				.PrevReportINBuffer           = PrevJoystickHIDReportBuffer,
				.PrevReportINBufferSize       = sizeof(PrevJoystickHIDReportBuffer),
			},
	};


/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
	SetupHardware();
	
	GlobalInterruptEnable();

	for(int i=0;i<10;i++){
		DDRC=0b11111111;PORTC=0b00000000;
		Delay_MS(1);
		DDRC=0b00000000;while(!(PINC & _BV(PC7))){thresholds[0]++;}
		//PC6
		DDRC=0b11111111;PORTC=0b00000000;
		Delay_MS(1);
		DDRC=0b00000000;while(!(PINC & _BV(PC6))){thresholds[1]++;}
		//PB3
		DDRB=0b11111111;PORTB=0b00000000;
		Delay_MS(1);
		DDRB=0b00000000;while(!(PINB & _BV(PB3))){thresholds[2]++;}
		//PB2
		DDRB=0b11111111;PORTB=0b00000000;
		Delay_MS(1);
		DDRB=0b00000000;while(!(PINB & _BV(PB2))){thresholds[3]++;}
		//PB1
		DDRB=0b11111111;PORTB=0b00000000;
		Delay_MS(1);
		DDRB=0b00000000;while(!(PINB & _BV(PB1))){thresholds[4]++;}
		//PB0
		DDRB=0b11111111;PORTB=0b00000000;
		Delay_MS(1);
		DDRB=0b00000000;while(!(PINB & _BV(PB0))){thresholds[5]++;}
		//PF1
		DDRF=0b11111111;PORTF=0b00000000;
		Delay_MS(1);
		DDRF=0b00000000;while(!(PINF & _BV(PF1))){thresholds[6]++;}
		//PF0
		DDRF=0b11111111;PORTF=0b00000000;
		Delay_MS(1);
		DDRF=0b00000000;while(!(PINF & _BV(PF0))){thresholds[7]++;}
		//PD3
		DDRD=0b11111111;PORTD=0b00000000;
		Delay_MS(1);
		DDRD=0b00000000;while(!(PIND & _BV(PD3))){thresholds[8]++;}
		//PD5
		DDRD=0b11111111;PORTD=0b00000000;
		Delay_MS(1);
		DDRD=0b00000000;while(!(PIND & _BV(PD5))){thresholds[9]++;}
		//PD6
		DDRD=0b11111111;PORTD=0b00000000;
		Delay_MS(1);
		DDRD=0b00000000;while(!(PIND & _BV(PD6))){thresholds[10]++;}
		//PD4
		DDRD=0b11111111;PORTD=0b00000000;
		Delay_MS(1);
		DDRD=0b00000000;while(!(PIND & _BV(PD4))){thresholds[11]++;}
		//PB4
		DDRB=0b11111111;PORTB=0b00000000;
		Delay_MS(1);
		DDRB=0b00000000;while(!(PINB & _BV(PB4))){thresholds[12]++;}
		//PD7
		DDRD=0b11111111;PORTD=0b00000000;
		Delay_MS(1);
		DDRD=0b00000000;while(!(PIND & _BV(PD7))){thresholds[13]++;}
		//PB6
		DDRB=0b11111111;PORTB=0b00000000;
		Delay_MS(1);
		DDRB=0b00000000;while(!(PINB & _BV(PB6))){thresholds[14]++;}
		//PB5
		DDRB=0b11111111;PORTB=0b00000000;
		Delay_MS(1);
		DDRB=0b00000000;while(!(PINB & _BV(PB5))){thresholds[15]++;}
	}
		
	for(int i=0;i<16;i++){
		thresholds[i]=thresholds[i]/10;
	}
		
	for (;;)
	{
		HID_Device_USBTask(&Joystick_HID_Interface);
		USB_USBTask();
	}
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware(void)
{
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);

	/* Hardware Initialization */
	USB_Init();
}

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void)
{
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void)
{
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	bool ConfigSuccess = true;

	ConfigSuccess &= HID_Device_ConfigureEndpoints(&Joystick_HID_Interface);

	USB_Device_EnableSOFEvents();
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void)
{
	HID_Device_ProcessControlRequest(&Joystick_HID_Interface);
}

/** Event handler for the USB device Start Of Frame event. */
void EVENT_USB_Device_StartOfFrame(void)
{
	HID_Device_MillisecondElapsed(&Joystick_HID_Interface);
}

int count,num=0;
/** HID class driver callback function for the creation of HID reports to the host.
 *
 *  \param[in]     HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in,out] ReportID    Report ID requested by the host if non-zero, otherwise callback should set to the generated report ID
 *  \param[in]     ReportType  Type of the report to create, either HID_REPORT_ITEM_In or HID_REPORT_ITEM_Feature
 *  \param[out]    ReportData  Pointer to a buffer where the created report should be stored
 *  \param[out]    ReportSize  Number of bytes written in the report (or zero if no report is to be sent)
 *
 *  \return Boolean \c true to force the sending of the report, \c false to let the library determine if it needs to be sent
 */
#define THRESH_DIFF 3
bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                         uint8_t* const ReportID,
                                         const uint8_t ReportType,
                                         void* ReportData,
                                         uint16_t* const ReportSize)
{
	USB_JoystickReport_Data_t* JoystickReport = (USB_JoystickReport_Data_t*)ReportData;
	
	switch(num){
		case 0://PC7
			DDRC=0b11111111;PORTC=0b00000000;count=0;
			Delay_MS(1);
			DDRC=0b00000000;while(!(PINC & _BV(PC7))){count++;}
			if(count-thresholds[num]<-THRESH_DIFF||THRESH_DIFF<count-thresholds[num]){JoystickReport->Button |= 0b00000001;}
			//break;
  		case 1://PC6
  			DDRC=0b11111111;PORTC=0b00000000;count=0;
  			Delay_MS(1);
  			DDRC=0b00000000;while(!(PINC & _BV(PC6))){count++;}
  			if(count-thresholds[num]<-THRESH_DIFF||THRESH_DIFF<count-thresholds[num]){JoystickReport->Button |= 0b00000010;}
			//break;
 		case 2://PB3
 			DDRB=0b11111111;PORTB=0b00000000;count=0;
			Delay_MS(1);
			DDRB=0b00000000;while(!(PINB & _BV(PB3))){count++;}
			if(count-thresholds[num]<-THRESH_DIFF||THRESH_DIFF<count-thresholds[num]){JoystickReport->Button |= 0b00000100;}
			//break;
		case 3://PB2
			DDRB=0b11111111;PORTB=0b00000000;count=0;
			Delay_MS(1);
			DDRB=0b00000000;while(!(PINB & _BV(PB2))){count++;}
			if(count-thresholds[num]<-THRESH_DIFF||THRESH_DIFF<count-thresholds[num]){JoystickReport->Button |= 0b00001000;}
			//break;
		case 4://PB1
			DDRB=0b11111111;PORTB=0b00000000;count=0;
			Delay_MS(1);
			DDRB=0b00000000;while(!(PINB & _BV(PB1))){count++;}
			if(count-thresholds[num]<-THRESH_DIFF||THRESH_DIFF<count-thresholds[num]){JoystickReport->Button |= 0b00010000;}
			//break;
		case 5://PB0
			DDRB=0b11111111;PORTB=0b00000000;count=0;
			Delay_MS(1);
   			DDRB=0b00000000;while(!(PINB & _BV(PB0))){count++;}
			if(count-thresholds[num]<-THRESH_DIFF||THRESH_DIFF<count-thresholds[num]){JoystickReport->Button |= 0b00100000;}
			//break;
  		case 6://PF1
   			DDRF=0b11111111;PORTF=0b00000000;count=0;
   			Delay_MS(1);
   			DDRF=0b00000000;while(!(PINF & _BV(PF1))){count++;}
   			if(count-thresholds[num]<-THRESH_DIFF||THRESH_DIFF<count-thresholds[num]){JoystickReport->Button |= 0b01000000;}
   			//break;
   		case 7://PF0
   			DDRF=0b11111111;PORTF=0b00000000;count=0;
   			Delay_MS(1);
   			DDRF=0b00000000;while(!(PINF & _BV(PF0))){count++;}
   			if(count-thresholds[num]<-THRESH_DIFF||THRESH_DIFF<count-thresholds[num]){JoystickReport->Button |= 0b10000000;}
			//break;
		case 8://PD3
  			DDRD=0b11111111;PORTD=0b00000000;count=0;
  			Delay_MS(1);
  			DDRD=0b00000000;while(!(PIND & _BV(PD3))){count++;}
 			if(count-thresholds[num]<-THRESH_DIFF||THRESH_DIFF<count-thresholds[num]){JoystickReport->Button2 |= 0b0000001;}
			//break;
 		case 9://PD5
  			DDRD=0b11111111;PORTD=0b00000000;count=0;
  			Delay_MS(1);
  			DDRD=0b00000000;while(!(PIND & _BV(PD5))){count++;}
  			if(count-thresholds[num]<-THRESH_DIFF||THRESH_DIFF<count-thresholds[num]){JoystickReport->Button2 |= 0b00000010;}
			//break;
  		case 10://PD6
  			DDRD=0b11111111;PORTD=0b00000000;count=0;
  			Delay_MS(1);
  			DDRD=0b00000000;while(!(PIND & _BV(PD6))){count++;}
  			if(count-thresholds[num]<-THRESH_DIFF||THRESH_DIFF<count-thresholds[num]){JoystickReport->Button2 |= 0b00000100;}
			//break;
  		case 11://PD4
  			DDRD=0b11111111;PORTD=0b00000000;count=0;
  			Delay_MS(1);
  			DDRD=0b00000000;while(!(PIND & _BV(PD4))){count++;}
  			if(count-thresholds[num]<-THRESH_DIFF||THRESH_DIFF<count-thresholds[num]){JoystickReport->Button2 |= 0b00001000;}
			//break;
  		case 12://PB4
  			DDRB=0b11111111;PORTB=0b00000000;count=0;
  			Delay_MS(1);
  			DDRB=0b00000000;while(!(PINB & _BV(PB4))){count++;}
  			if(count-thresholds[num]<-THRESH_DIFF||THRESH_DIFF<count-thresholds[num]){JoystickReport->Button2 |= 0b00010000;}
			//break;
  		case 13://PD7
  			DDRD=0b11111111;PORTD=0b00000000;count=0;
  			Delay_MS(1);
  			DDRD=0b00000000;while(!(PIND & _BV(PD7))){count++;}
  			if(count-thresholds[num]<-THRESH_DIFF||THRESH_DIFF<count-thresholds[num]){JoystickReport->Button2 |= 0b00100000;}
			//break;
  		case 14://PB6
  			DDRB=0b11111111;PORTB=0b00000000;count=0;
  			Delay_MS(1);
  			DDRB=0b00000000;while(!(PINB & _BV(PB6))){count++;}
  			if(count-thresholds[num]<-THRESH_DIFF||THRESH_DIFF<count-thresholds[num]){JoystickReport->Button2 |= 0b01000000;}
			//break;
  		case 15://PB5
  			DDRB=0b11111111;PORTB=0b00000000;count=0;
  			Delay_MS(1);
  			DDRB=0b00000000;while(!(PINB & _BV(PB5))){count++;}
  			if(count-thresholds[num]<-THRESH_DIFF||THRESH_DIFF<count-thresholds[num]){JoystickReport->Button2 |= 0b10000000;}
			//break;
	}
	//num++;
	//if(num>=16)num=0;
	*ReportSize = sizeof(USB_JoystickReport_Data_t);
	return false;
}

/** HID class driver callback function for the processing of HID reports from the host.
 *
 *  \param[in] HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in] ReportID    Report ID of the received report from the host
 *  \param[in] ReportType  The type of report that the host has sent, either HID_REPORT_ITEM_Out or HID_REPORT_ITEM_Feature
 *  \param[in] ReportData  Pointer to a buffer where the received report has been stored
 *  \param[in] ReportSize  Size in bytes of the received HID report
 */
void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                          const uint8_t ReportID,
                                          const uint8_t ReportType,
                                          const void* ReportData,
                                          const uint16_t ReportSize)
{
	// Unused (but mandatory for the HID class driver) in this demo, since there are no Host->Device reports
}

