// TestApplication.cpp : Defines the entry point for the console application.
//
#include <Windows.h>
#include <iostream>
/* normal Phoenix include */
#include "ctre/Phoenix.h"

/* additional include for sim */
#include "ctre/phoenix/cci/Platform_CCI.h" // c_SimCreate
#include "ctre/phoenix/cci/Unmanaged_CCI.h" // c_FeedEnable

/* additional include for direct CAN access */
#include "ctre/phoenix/platform/Platform.h"

/* bring in the x86-64 libs for simulation */
#pragma comment(lib, "CTRE_PhoenixCCI.lib")
#pragma comment(lib, "CTRE_Phoenix.lib")
#pragma comment(lib, "CTRE_PhoenixCanutils.lib")
#pragma comment(lib, "CTRE_PhoenixPlatform_sim.lib")

int main()
{
	/* build simulate robot and wait for init processes */	
	printf("Setting up simulated robot\n");
	c_SimCreate(DeviceType::TalonSRXType, 7); /* wire up a Talon with ID 7 */
	/* for now we need a delay so backend can properly setup device properties before we attempt creating API objects*/
	Sleep(1000); /* this may not be necessary anymore */

	TalonSRX talon(7);
	VictorSPX victor(0);
	PigeonIMU pigeon(0);
	CANifier canif(0);

	/* produce a on/off waveform */
	int loops  = 0;
	int bToggle = 0;
	
	while (true)
	{
		/* calc motor output for this loop */
		double motorOutput = 0;

		/* count loops */
		if (++loops > 400) {
			loops = 0;
			bToggle = 0;
		} else if (loops > 200) {
			bToggle = 1;
		}

		/* change Set output every few seconds. */
		if (bToggle)
			talon.Set(ControlMode::PercentOutput, -1.00);
		else
			talon.Set(ControlMode::PercentOutput, +1.00);

		/* simple set and get test */
		ErrorCode err = talon.ConfigOpenloopRamp(0.080, 50);

		/* loop yield */
		Sleep(10);
		c_FeedEnable(500); /* stay enabled for another half-second*/

		/* print the motor output */
		double appliedOut = talon.GetMotorOutputPercent();
		printf("appliedOut = %f\n", appliedOut);

		/* send a test frame every loop, create a "vs3logs" subfolder, 
			and CAN frames will be logged there. */
		ctre::phoenix::platform::can::CANbus_SendFrame(0x217, 0, 0);
	}
	return 0;
}
