// NAME: Haritima Manchanda CISC 210 (HONORS) LAB 6 
// DESCRIPTION: The program creates a binary clock which displays time in 24 hour time
// 		notation.

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sense/sense.h>
#include <time.h>
#include <unistd.h>

#define MAX 8 // maximum size of array to store an 8 bit number.

/*GLOBAL VARIABLE
 * run: to check the program is running.
 */
int run = 1;

/*handler: function that exits the program cleanly on pressing ctrl C 
 */
void handler(int sig)
{
	printf("\n Exiting \n");
	run = 0;
}

/* drawClock: function to draw the 8 bit number on the SenseHat
 * binaryNumStore[]: array which stores the binary number.
 * lengthOfArray: stores the size of binaryNumStore
 * rowNum: draws the hour, minute, and seconds part of time on a separate row.
 */
void drawClock(sense_fb_bitmap_t *screen, int binaryNumStore[], int lengthOfArray, int rowNum, int color)
{
	for(int j = lengthOfArray-1; j >= 0; j--)
	{
		if(binaryNumStore[j] == 1)
		{
			setPixel(screen,rowNum,j,color);
		}
		else
		{
			setPixel(screen,rowNum,j, getColor(0,0,0));
		}
	}
}

/* convertTimeToBinary: converts the time passed in either hours, minutes or seconds into binary 
 * and stores in an array.
 */
void convertTimeToBinary(sense_fb_bitmap_t *screen, int currentTimePart, int rowNum, int color)
{
	int binaryNumStore[MAX];
	int i = 0;

	while(currentTimePart > 0)
	{
		binaryNumStore[i] = currentTimePart % 2;
		currentTimePart = currentTimePart / 2;
		i++;
	}

	drawClock(screen, binaryNumStore, i, rowNum, color);
}

int main(int argc,char* argv[])
{	
	signal(SIGINT, handler);
	int hours, minutes, seconds;
	pi_framebuffer_t *fb = getFBDevice();

	int rowNumSeconds = 5;
	int rowNumMinutes = 3;
	int rowNumHours = 1;

	int red = getColor(255,0,0);
	int blue = getColor(0,0,255);
	int green = getColor(0,255,0);

	if(!fb)
	{
		return 0;
	}

	clearBitmap(fb->bitmap,getColor(0,0,0));

	while(run)
	{
		
		time_t currentTime;
		time(&currentTime);
		struct tm *myTime = localtime(&currentTime);
		
		hours = myTime->tm_hour;
		minutes = myTime->tm_min;
		seconds = myTime->tm_sec;
		
		convertTimeToBinary(fb->bitmap,hours,rowNumHours,blue);
		convertTimeToBinary(fb->bitmap,minutes,rowNumMinutes,green);
		convertTimeToBinary(fb->bitmap,seconds,rowNumSeconds,red);
		if(seconds == 0)
		{
			clearBitmap(fb->bitmap,getColor(0,0,0)); //After every 60 th second the bitmap is cleared. So that time start from the zeroth second again.
		}
	}

	freeFrameBuffer(fb); // Clear the frambuffer after the program exits.
	return 0;
}
