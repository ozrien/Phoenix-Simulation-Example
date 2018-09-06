# Phoenix-Simulation-Example
Visual Studio Project x64 linking Phoenix-api and using a Talon SRX in simulation.

## Dependencies
In the dependencies folder the following binaries must be placed.
These will be distributed in future release of Phoenix installer / maven releases.
- CTRE_Phoenix.dll
- CTRE_Phoenix.lib
- CTRE_PhoenixCCI.dll
- CTRE_PhoenixCCI.lib
- CTRE_PhoenixCanutils.dll
- CTRE_PhoenixCanutils.lib
- CTRE_PhoenixPlatform.dll (copy and rename of CTRE_PhoenixPlatform_sim.dll renamed.)
- CTRE_PhoenixPlatform_sim.lib
- TalonSrx-Application.dll

## Building
- Select x64 for the target type as these binaries are built for x86-x64 Windows.
- CTRE_TALON_LIBRARY_PATH environment variable is set in the VS project to path to TalonSrx-Application.dll.
Ensure this is correct or create env var yourself.

Debug/Release run from Visual studio and confirm a similar output...

![image](https://user-images.githubusercontent.com/14191527/45174124-07665780-b1d8-11e8-8fb8-bdac0b503821.png)

Place a breakpoint and confirm watch shows the value of the configured ramp of the Talon SRX.
![image](https://user-images.githubusercontent.com/14191527/45174083-eaca1f80-b1d7-11e8-82e4-df02dcec3b3f.png)
