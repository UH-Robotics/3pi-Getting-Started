#include <pololu/3pi.h>
int main()
{	
	clear();
	unsigned int sv[5];
	// sensor value array that the robot uses for steering on a line, finding intersections and turns, and determining what kind of intersection it is.
	unsigned int svAI[5];
	// sensor value array after an intersection to determine what kind of intersection the robot is is.
	pololu_3pi_init(2000);
	//Initiation the values that the sensor array will have.
	
	//These symbols are later used to build they arrays of the maze path and maze solution.
	int U = 'U';
	// U turn
	int L = 'L';
	//left turn
	int R = 'R';
	//right turn
	int S = 'S';
	//going straight through the intersection
	int STOP = 'Z';
	//STOP the root has found the end of the maze
	int n= -1;
	// n is used to build the path that the robot makes as is goes through the maze
	int abc = 0;
	unsigned int ms[200];
	//This array records the path of the robot as it goes through the maze for the first time
	int thr = 500;
	//the robot uses this to determine whether or not a line is underneath one of its sensors.
	
	
	void calibration(); 
	calibration();
	//the robot is calibrating its sensors.
	read_line_sensors_calibrated(sv,IR_EMITTERS_ON);
	clear();

	unsigned int status= 1;
	//used for the first while loop as the robot goes through the maze
	unsigned int status2= 1;
	//used for the second time the robot goes though the maze that it has already saved.
	char robotstatus = 'm';
	char robot2 = 'n';
	//these are used for the case sructures for the two main while loops.
	while (status==1)
{
	switch(robotstatus)
{

	
	case 'm':
	read_line_sensors_calibrated(sv,IR_EMITTERS_ON);
	clear();
	
	//this is the robots steering mechanism. This structure is used to find intersections and corners.
	
	if (((sv[0]>thr)||(sv[4]>thr))&&((sv[1]>thr)||(sv[2]>thr)||(sv[3]>thr)||(sv[1]<thr)||(sv[2]<thr)||(sv[3]<thr)))
	robotstatus = 'a';
	// a = intersection found
	//the robot found an intersection or a corner.
	if ((sv[1]<thr)&&(sv[2]>thr)&&(sv[3]<thr)&&(sv[0]<thr)&&(sv[4]<thr))
	robotstatus = 'f';
	// f = forward
	else if ((sv[1]<thr)&&(sv[2]<thr)&&(sv[3]<thr)&&(sv[0]<thr)&&(sv[4]<thr))
	robotstatus = 'c';
	//c = turn around
	else if ((sv[1]>thr)&&(sv[2]<thr)&&(sv[3]<thr)&&(sv[0]<thr)&&(sv[4]<thr))
	robotstatus = 'd';
	//d = steer left hard
	else if ((sv[1]>thr)&&(sv[2]>thr)&&(sv[3]<thr)&&(sv[0]<thr)&&(sv[4]<thr))
	robotstatus = 'e';
	//e = steer left
	else if ((sv[1]<thr)&&(sv[2]<thr)&&(sv[3]>thr)&&(sv[0]<thr)&&(sv[4]<thr))
	robotstatus = 'g';
	//g = steer right hard
	else if ((sv[1]<thr)&&(sv[2]>thr)&&(sv[3]>thr)&&(sv[0]<thr)&&(sv[4]<thr))
	robotstatus = 'h';
	// h = steer right
	break;
	
	case 'a' :
	//intersection found
	print("IF");
	delay_ms(10);
	read_line_sensors_calibrated(sv,IR_EMITTERS_ON);
	set_motors(80,80);
	delay_ms(100);
	read_line(svAI,IR_EMITTERS_ON);
	
	delay_ms(2);
	clear();
	//this is the robot choosing mechanism once it has found an intersection. It is using a left hand on the wall stratagy. 
	if ((sv[0]>thr)&&(sv[4]<thr)&&(svAI[0]<thr)&&(svAI[1]<thr)&&(svAI[2]<thr)&&(svAI[3]<thr)&&(svAI[4]<thr))
	robotstatus = 'b';
	//left turn no save
	else if ((sv[0]<thr)&&(sv[4]>thr)&&(svAI[0]<thr)&&(svAI[1]<thr)&&(svAI[2]<thr)&&(svAI[3]<thr)&&(svAI[4]<thr))
	robotstatus = 'i';
	//right turn no save
	else if ((sv[0]>thr)&&(sv[4]>thr)&&(svAI[0]<thr)&&(svAI[1]<thr)&&(svAI[2]<thr)&&(svAI[3]<thr)&&(svAI[4]<thr))
	robotstatus = 'j';
	//left turn with save. T intersection
	else if ((sv[0]>thr)&&(sv[4]<thr)&&(svAI[0]<thr)&&((svAI[1]>thr)||(svAI[2]>thr)||(svAI[3]>thr)))
	robotstatus = 'j';
	//left turn with save. 3 way intersection.
	else if ((sv[0]>thr)&&(sv[4]>thr)&&(svAI[0]<thr)&&((svAI[1]>thr)||(svAI[2]>thr)||(svAI[3]>thr)))
	robotstatus = 'j';
	//left turn with save. 4 way intersection.
	else if ((sv[0]<thr)&&(sv[4]>thr)&&(svAI[0]<thr)&&((svAI[1]>thr)||(svAI[2]>thr)||(svAI[3]>thr)))
	robotstatus = 'k';
	//robot goes straight through intersection
	else if ((sv[0]>thr)&&(sv[4]>thr)&&(svAI[0]>thr))
	robotstatus = 'l';
	// robot will stop it has found the end of the maze
	break;
	
	case 'b' :
	//left turn no save
	print("L no save");
	play_frequency(800, 500, 15);
	set_motors(-70,70);
	read_line(sv,IR_EMITTERS_ON);
	while(sv[0]<thr)
	{
		read_line_sensors_calibrated(sv,IR_EMITTERS_ON);
		delay_ms(10);
	}
	while(sv[2]<thr)
	{
		read_line_sensors_calibrated(sv,IR_EMITTERS_ON);
		delay_ms(10);
	}
	set_motors(0,0);
	robotstatus = 'm';
	stop_playing();
	clear();
	break;
	
	case 'j' :
	//left turn with save
	n= n+1;
	ms[n]= L;
	set_motors(-70,70);
	read_line_sensors_calibrated(sv,IR_EMITTERS_ON);
	while(sv[0]<thr)
	{
		read_line_sensors_calibrated(sv,IR_EMITTERS_ON);
		delay_ms(10);
	}
	while(sv[2]<thr)
	{
		read_line_sensors_calibrated(sv,IR_EMITTERS_ON);
		delay_ms(10);
	}
	set_motors(0,0);
	robotstatus = 'm';
	break;
	
	case 'i' :
	//right turn no save
	play_frequency(800, 500, 15);
	set_motors(70,-70);
	read_line_sensors_calibrated(sv,IR_EMITTERS_ON);
	while(sv[4]<thr)
	{
		read_line_sensors_calibrated(sv,IR_EMITTERS_ON);
		delay_ms(10);
	}
	while(sv[2]<thr)
	{
		read_line_sensors_calibrated(sv,IR_EMITTERS_ON);
		delay_ms(10);
	}
	set_motors(0,0);
	robotstatus = 'm';
	stop_playing();
	break;
	
	case 'k' :
	// going straight
	n= n+1;
	ms[n]=S;
	robotstatus = 'm';
	break;
	
	case 'l' :
	//solved maze
	n= n+1;
	
	ms[n]=STOP;
	clear();
	print("found");
	lcd_goto_xy(0,1);
	print("end!");
	play_frequency(800, 4000, 15);
	set_motors(0,0);
	delay_ms(4000);
	status = 0;
	stop_playing();
	clear();
	break;
	
	case 'f' :
	//forward
	set_motors(80,80);
	delay_ms(20);
	robotstatus = 'm';
	break;
	
	case 'd' :
	// steer left hard
	set_motors(20,80);
	delay_ms(10);
	robotstatus = 'm';
	break;
	
	case 'e':
	//steer left
	set_motors(40,80);
	delay_ms(10);
	robotstatus = 'm';
	break;
	
	case 'g':
	//steer right hard
	set_motors(80,20);
	delay_ms(10);
	robotstatus = 'm';
	break;
	
	case 'h':
	//steer right
	set_motors(80,40);
	delay_ms(10);
	robotstatus = 'm';
	break;
	
	case 'c' :
	// turning around
	n= n+1;
	
	ms[n]=U;
	set_motors(80,80);
	delay_ms(135);
	set_motors(-70,70);
	read_line_sensors_calibrated(sv,IR_EMITTERS_ON);
	while (sv[2]<thr)
	{
	read_line_sensors_calibrated(sv,IR_EMITTERS_ON);
	delay_ms(10);
	}
	set_motors(0,0);
	clear();
	robotstatus = 'm';
	break;
}

}
clear();
print("comput");
lcd_goto_xy(0,1);
print("ing");
delay_ms(1000);
clear();
//Now the robot is simplifying the maze.It use the use the below variables and the previously made array ms[200] to make a 
//new array and the solution to the maze msSIM[200].
int a=0;
int cd=0;
int de=0;
int xyz=0;
int q=1;
unsigned int msSIM[200];

while(cd<25)
{
	//print_unsigned_long(cd);
	//delay_ms(20);
	clear();

	if( (ms[de]==L) && (ms[(de+1)]==U) && (ms[(de+2)]==L) )
	{
		de=de+3;
		msSIM[a]= S;
		a=a+1;

	}

	else if( (ms[de]==S) && (ms[(de+1)]==U) && (ms[(de+2)]==L) )
	{
		de=de+3;
		msSIM[a]= R;
		a=a+1;
	}
	else if( (ms[de]==R) && (ms[(de+1)]==U) && (ms[(de+2)]==R) )
	{
		de=de+3;
		msSIM[a]= S;
		a=a+1;
		
	}
	else if( (ms[(de)]==S) && (ms[(de+1)]==U) && (ms[(de+2)]==S) )
	{
		de=de+3;
		msSIM[a]= U;
		a=a+1;
	}
	else if( (ms[de]==L) && (ms[(de+1)]==U) && (ms[(de+2)]==S) )
	{
		de=de+3;
		msSIM[a]= R;
		a=a+1;
	}
	else if( (ms[de]==S) && (ms[(de+1)]==U) && (ms[(de+2)]==R) )
	{
		de=de+3;
		msSIM[a]= L;
		a=a+1;
	}
	else if( (ms[de]==R) && (ms[(de+1)]==U) && (ms[(de+2)]==L) )
	{
		de=de+3;
		msSIM[a]= U;
		a=a+1;
	}
	else if(ms[de]==STOP)
	{
		msSIM[a]=STOP;
		a=a+1;
		q=a;
		//this value is used when displaying the simplified solution on the lcd screen when the process is done.
		cd=cd+1;
		de=0;
		xyz=0;
		while(xyz<(q))
		{	ms[xyz]=msSIM[xyz];
			delay_ms(1);
			xyz = xyz +1;
		}
		a=0;
		//ms = msSIM;
		//the code is now reconstructing the array ms the be put int another round of simplification because its mostly likely that the
		// way my code is written that one round of simplification was not enough for the solution to the maze to be made. it will but the ms 
		// array through the simplification process 25 times. this is an arbitrary amount of times.
	}

	else
	{
		msSIM[a]= ms[de];
		a=a+1;
		de=de+1;
	}


}

clear();
print("solution");
delay_ms(1000);
xyz = 0;
clear();
while(xyz<(q))
{
	print_character(msSIM[xyz]);
	delay_ms(10);
	xyz = xyz +1;
}
lcd_goto_xy(0,1);
print("press go");
wait_for_button_press(ANY_BUTTON);
clear();
delay_ms(1000);
print("GO");
abc = 0;
//Now the robot is solving the maze. This code is a repeat from early in the code but its focus is using the newly made array to get to the
//end of the maze as quickly as possible. 
while(status2==1)
{
	switch(robot2)
	{

		
		case 'n':
		read_line_sensors_calibrated(sv,IR_EMITTERS_ON);
		
		clear();
		//this is the robots steering mechanism
		
		if (((sv[0]>thr)||(sv[4]>thr))&&((sv[1]>thr)||(sv[2]>thr)||(sv[3]>thr)||(sv[1]<thr)||(sv[2]<thr)||(sv[3]<thr)))
		robot2 = 'o';
		// a = intersection found
		//the robot found an intersection
		if ((sv[1]<thr)&&(sv[2]>thr)&&(sv[3]<thr)&&(sv[0]<thr)&&(sv[4]<thr))
		robot2 = 'p';
		// f = forward
		else if ((sv[1]<thr)&&(sv[2]<thr)&&(sv[3]<thr)&&(sv[0]<thr)&&(sv[4]<thr))
		robot2 = 'q';
		//c = turn around
		else if ((sv[1]>thr)&&(sv[2]<thr)&&(sv[3]<thr)&&(sv[0]<thr)&&(sv[4]<thr))
		robot2 = 'r';
		//d = steer left hard
		else if ((sv[1]>thr)&&(sv[2]>thr)&&(sv[3]<thr)&&(sv[0]<thr)&&(sv[4]<thr))
		robot2 = 's';
		//e = steer left
		else if ((sv[1]<thr)&&(sv[2]<thr)&&(sv[3]>thr)&&(sv[0]<thr)&&(sv[4]<thr))
		robot2 = 't';
		//g = steer right hard
		else if ((sv[1]<thr)&&(sv[2]>thr)&&(sv[3]>thr)&&(sv[0]<thr)&&(sv[4]<thr))
		robot2 = 'u';
		// h = steer right
		break;
		
		case 'o' :
		//intersection found
		print("IF");
		delay_ms(10);
		read_line_sensors_calibrated(sv,IR_EMITTERS_ON);
		set_motors(80,80);
		delay_ms(100);
		read_line_sensors_calibrated(svAI,IR_EMITTERS_ON);
		delay_ms(2);
		clear();
		//this is the robot choosing mechanism once it has found an intersection. It is using a left hand on the wall stratagy.
		if ((sv[0]>thr)&&(sv[4]<thr)&&(svAI[0]<thr)&&(svAI[1]<thr)&&(svAI[2]<thr)&&(svAI[3]<thr)&&(svAI[4]<thr))
		robot2 = 'v';
		//left turn 
		else if ((sv[0]<thr)&&(sv[4]>thr)&&(svAI[0]<thr)&&(svAI[1]<thr)&&(svAI[2]<thr)&&(svAI[3]<thr)&&(svAI[4]<thr))
		robot2 = 'w';
		//right turn 
		else if (msSIM[abc]== R)
		{
		abc= abc +1;
		robot2 = 'w';
		}
		//right turn 
		else if (msSIM[abc]== L)
		{
		abc= abc+1;
		robot2 = 'v';
		}
		//left turn.
		else if (msSIM[abc]== S)
		{
		abc=abc+1;
		robot2 = 'y';
		}
		//robot goes straight through intersection
		else if (msSIM[abc]== STOP)
		robot2 = 'x';
		// robot will stop it has found the end of the maze
		break;
		
		case 'v' :
		//left turn 
		
		play_frequency(800, 500, 15);
		set_motors(-70,70);
		read_line_sensors_calibrated(sv,IR_EMITTERS_ON);
		while(sv[0]<thr)
		{
			read_line_sensors_calibrated(sv,IR_EMITTERS_ON);
			delay_ms(10);
		}
		while(sv[2]<thr)
		{
			read_line_sensors_calibrated(sv,IR_EMITTERS_ON);
			delay_ms(10);
		}
		set_motors(0,0);
		robot2 = 'n';
		stop_playing();
		clear();
		break;
		
		
		case 'w' :
		//right turn
		play_frequency(800, 500, 15);
		set_motors(70,-70);
		read_line_sensors_calibrated(sv,IR_EMITTERS_ON);
		while(sv[4]<thr)
		{
			read_line_sensors_calibrated(sv,IR_EMITTERS_ON);
			delay_ms(10);
		}
		while(sv[2]<thr)
		{
			read_line_sensors_calibrated(sv,IR_EMITTERS_ON);
			delay_ms(10);
		}
		set_motors(0,0);
		robot2 = 'n';
		clear();
		stop_playing();
		break;
		
		case 'y' :
		// going straight
		
		print("S");
		robot2 = 'n';
		break;
		
		case 'x' :
		//solved maze
		clear();
		print("solved!");
		set_motors(0,0);
		play_frequency(800, 4000, 15);
		delay_ms(4000);
		stop_playing();
		clear();
		status2=0;
		break;
		
		case 'p' :
		//forward
		set_motors(80,80);
		delay_ms(20);
		robot2 = 'n';
		break;
		
		case 'r' :
		// steer left hard
		set_motors(20,80);
		delay_ms(10);
		robot2 = 'n';
		break;
		
		case 's':
		//steer left
		set_motors(40,80);
		delay_ms(10);
		robot2 = 'n';
		break;
		
		case 't':
		//steer right hard
		set_motors(80,20);
		delay_ms(10);
		robot2 = 'n';
		break;
		
		case 'u':
		//steer right
		set_motors(80,40);
		delay_ms(10);
		robot2 = 'n';
		break;
}

}
	
}
	

void calibration()
{
	
unsigned int c;
clear();
print("Maze");
lcd_goto_xy(0, 1);
print("Solver");
delay_ms(2000);
clear();
print("PressAny");
lcd_goto_xy(0,1);
print("to Calibrate");
wait_for_button_press(ANY_BUTTON);
clear();
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
print("PressAny");
lcd_goto_xy(0,1);
print("toSolve");
wait_for_button_press(ANY_BUTTON);
clear();
print("Solv");
lcd_goto_xy(0, 1);
print("ing...");
delay_ms(1000);

}


		
			
		
			
			
	
		


	



