/* GETCHLIKE.C
 *
 * this funtion is to imitate the non-standard getch() function for use on
 * a linux platform.
 */
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

#include "include/getchlike.h"

int getch_like(void)
{
	int ch;
	struct termios oldt;
	struct termios newt;

	/* store old settings */
	tcgetattr(STDIN_FILENO, &oldt);
	/* copy old settings to new settings */
	newt = oldt;
	/* make one change to old settings in new settings */
	newt.c_lflag &= ~(ICANON | ECHO);
	/* apply the new settings immediately */
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	ch = getchar();

	/* reapply the old settings */
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

	return ch;
}
