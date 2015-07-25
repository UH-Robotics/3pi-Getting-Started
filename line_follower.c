#include <pololu/3pi.h>
int main()
{	unsigned int c;
	unsigned int sv[5];
	// sensor array. sv=sensor values
	int thr = 500;
	//Threshold value used in steering mechanism. 
	pololu_3pi_init(2000);
	print("Line");
	lcd_goto_xy(0, 1);
	print("Follower");
	delay_ms(3000);
	clear();
	// displaying "Line follower" on lcd screen
	print("Press Any");
	lcd_goto_xy(0,1);
	print("to Calibrate");
	wait_for_button_press(ANY_BUTTON);
	clear();
	//This next bit of code calibrates the 3pi 
	lcd_goto_xy(0, 0);
	print("calibrat");
	lcd_goto_xy(0, 1);
	print("ing...");
	delay_ms(1000);
	for(c=0;c<80;c=c+1)
	{
		if(c < 20 || c >= 60)
		set_motors(40, -40);
		else
		set_motors(-40,40);
		calibrate_line_sensors(IR_EMITTERS_ON);
		delay_ms(20);
	}
	clear();
	set_motors(0,0);
	
	print("Press Any");
	lcd_goto_xy(0,1);
	print("toFollow");
	wait_for_button_press(ANY_BUTTON);
	clear();
	print("Follow");
	lcd_goto_xy(0, 1);
	print("ing...");
	delay_ms(1000);
	int x =1;
	//The 3pi has begun to follow the 3pi.
	//This is the steering mechanism for the 3pi.
	while (x==1)
	{
		
	read_line_sensors_calibrated(sv, IR_EMITTERS_ON);
	
	if		((sv[0]<thr)&&(sv[1]<thr)&&(sv[2]>thr)&&(sv[3]<thr)&&(sv[4]<thr))
	set_motors(120,120);
	// 3pi is moving forward
	
	if		((sv[0]<thr)&&(sv[1]<thr)&&(sv[2]<thr)&&(sv[3]<thr)&&(sv[4]<thr))
	{
		set_motors(0,0);
		clear();
		print("STOP");
		delay_ms(2000);
		clear();
		x=0;
	}
	// 3pi has stopped. There is no line underneath it,
	
	else if ((sv[0]<thr)&&(sv[1]>thr)&&(sv[2]>thr)&&(sv[3]<thr)&&(sv[4]<thr))
	set_motors(90,130);
	// 3pi is moving left
	
	else if ((sv[0]<thr)&&(sv[1]>thr)&&(sv[2]<thr)&&(sv[3]<thr)&&(sv[4]<thr))
	set_motors(60,120);
	// 3pi is moving left hard.
	
	else if ((sv[0]>thr)&&(sv[1]>thr)&&(sv[2]<thr)&&(sv[3]<thr)&&(sv[4]<thr))
	set_motors(40,120);
	// 3pi is moving left really hard.
	
	else if ((sv[0]>thr)&&(sv[1]<thr)&&(sv[2]<thr)&&(sv[3]<thr)&&(sv[4]<thr))
	set_motors(0,120);
	// 3pi is moving left really  really hard.
	
	else if ((sv[0]<thr)&&(sv[1]<thr)&&(sv[2]>thr)&&(sv[3]>thr)&&(sv[4]<thr))
	set_motors(130,90);
	// 3pi is moving right.
	
	else if ((sv[0]<thr)&&(sv[1]<thr)&&(sv[2]<thr)&&(sv[3]>thr)&&(sv[4]<thr))
	set_motors(120,60);
	// 3pi is moving right hard.
	
	else if ((sv[0]<thr)&&(sv[1]<thr)&&(sv[2]<thr)&&(sv[3]>thr)&&(sv[4]>thr))
	set_motors(120,40);
	// 3pi is moving right really hard.
	
	else if ((sv[0]<thr)&&(sv[1]<thr)&&(sv[2]<thr)&&(sv[3]<thr)&&(sv[4]>thr))
	set_motors(120,0);
	// 3pi is moving right really really hard.
	else
	
	delay_ms(5);
	}
	
}
