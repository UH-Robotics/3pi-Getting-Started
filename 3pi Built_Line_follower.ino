/*
 * http://www.pololu.com/docs/0J21
 * http://www.pololu.com
 * http://forum.pololu.com
 *
 */

// The 3pi include file must be at the beginning of any program that
// uses the Pololu AVR library and 3pi.
#include <pololu/3pi.h>
#include <math.h>
#include <stdlib.h> //used for the abs function
double ABS (double input)
 {
   return (input > 0) ? input : (0 - input);
 }
#include <stdio.h>
#include <avr/pgmspace.h>
const char welcome[] PROGMEM = ">g32>>c32"; //sound used for debugging...
#include <stdbool.h>

void rotate_cw(); //function to turn clock-wise...
void rotate_ccw();
void display_battery(); //displays battery voltage...

int main()
{

	//bool seen_whiteline = 1; //automatically set to it has detected "whiteness"
	//int dark_threshold = 1000; //black line be seen with more than this
	//int light_threshold = 300; //white line should be seen with less than this...
	int l_counter = 0; //counter for the line...
	//int sq_counter = 0; //counter for the square...
	pololu_3pi_init(2000); //initialize the max value on the 3pi @ 2000...
	lcd_init_printf();	// required if we want to use printf()
	unsigned int sensor_values[5]; //initialize the array for the sensors...

	display_battery();

	wait_for_button_release(BUTTON_B);
	delay_ms(1000);

	while(1)
	{

		read_line_sensors(sensor_values,IR_EMITTERS_ON); //function to turn onthe IR sensors...
		printf("%d\n",l_counter);
		//bool sees_blackline = 0; //has not yet detected black...
		delay_ms(100);

		int leftsum = sensor_values[0] + sensor_values[1]; //variables for sensors 0 and 1...
		int rightsum = sensor_values[3] + sensor_values[4]; //variables for sensors 3 and 4...
		printf("%d\n",abs(leftsum-rightsum)); //display the value for the computation of their difference...
		delay_ms(100); //delay the reading
		clear(); //clear the reading from the display

		int threshold = 600; //if above the threshold rotate...because you would be off the line...
		//otherwise if threshold is met or under met then keep moving forward...

		if(((leftsum-rightsum) > 0) && (abs(leftsum-rightsum) > threshold))
		//check if the computation of the difference is greater than zero and if it's greater than the threshold...
		{
			rotate_ccw();
			//turn counter-clockwise if sensor 0 and 1 see to much black...
		}


		else if(((rightsum - leftsum) > 0) && ((abs(rightsum - leftsum)) > threshold))
		{
			rotate_cw();
			//turn clockwise if sensor 3 and 4 see to much black...
		}

		/* //remove the comment lines...
		else if(((sensor_values[0] > dark_threshold) && (sensor_values[1] > dark_threshold) && (sensor_values[2] > dark_threshold) && (sensor_values[3] > dark_threshold) && (sensor_values[4] > dark_threshold)) && (!sees_blackline && seen_whiteline))
		{
			red_led(1);
			delay_ms(500);
			red_led(0);

			sees_blackline = 1;
			seen_whiteline = 0; //hasn't seen a new white line...
			l_counter += 1;

				//robot gets stuck over here...convert to an if statement instead???
				while((((sensor_values[0] > dark_threshold) && (sensor_values[1] > dark_threshold)) || ((sensor_values[3] > dark_threshold) && (sensor_values[4] > dark_threshold))) && (sees_blackline && !seen_whiteline))
				//(while sensors 0 & 1 OR sensors 3 & 4 see black) AND the robot has not yet detected a new white line...execute...
				{
					set_motors(10,10);
					delay_ms(500);
				}
				//reset the booleans back...
				seen_whiteline = 1; //it saw the white line...
		}
		//remove the comment lines...
		*/
		else
		{
			set_motors(20,20);
			delay_ms(100);
			//set_motors(0,0);
		}



	}
}

void rotate_cw()
{
	set_motors(15,-15);
	delay_ms(100);
	//set_motors(0,0);
}
void rotate_ccw()
{
	set_motors(-15,15);
	delay_ms(100);
	//set_motors(0,0);
}

void display_battery()
{
	while(!button_is_pressed(BUTTON_B))
	{
		int bat = read_battery_millivolts();

		clear();
		print_long(bat);
		print("mV");
		lcd_goto_xy(0,1);
		print("Press B");


		delay_ms(100);

	}
}