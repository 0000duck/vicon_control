# Make flags
FLAGS = --no-print-directory -C

default: .FORCE
	@ # Make ARM software
	@ echo "--- Making ARM software ---"

	@ # Make components
	@ echo "Making components"
	@ $(MAKE) $(FLAGS) src/components

	@ # Make tools
	@ echo "Making tools"
	@ $(MAKE) $(FLAGS) src/tools

	@ # Make robot
	@ echo "Making robot"
	@ $(MAKE) $(FLAGS) src/robot

	@ # Make example_robot
	@ echo "Making example_robot"
	@ $(MAKE) $(FLAGS) src/example_robot

	@ # Add additional binaries to make here
	@ # echo "Making <name>"
	@ # $(MAKE) $(FLAGS) src/<project_directory>

	@ # Make PRU firmware
	@ echo "--- Making PRU firmware ---"

	@ # Make pwm_motor
	@ echo "Making pwm_motor"
	@ $(MAKE) $(FLAGS) src/pwm_motor

	@ # Make read_encoders
	@ echo "Making read_encoders"
	@ $(MAKE) $(FLAGS) src/read_encoders

	@ # Add additional PRU firmware to make here
	@ # echo "Making <name>"
	@ # $(MAKE) $(FLAGS) src/<project_directory>
.FORCE: