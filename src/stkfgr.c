#include <stdio.h>

#include "include/stkfgr.h"

void printstkfgr(int rem_lives)
{
	switch (rem_lives) {
	case 7:
		puts(" __________ ");
		puts(" |/      |  ");
		puts(" |	      ");
		puts(" |	      ");
		puts(" |	      ");
		puts("_|__________");
		puts("");
		break;
	case 6:
		puts(" __________ ");
		puts(" |/      |  ");
		puts(" |       O  ");
		puts(" |          ");
		puts(" |	      ");
		puts("_|__________");
		puts("");
		break;
	case 5:
		puts(" __________ ");
		puts(" |/      |  ");
		puts(" |       O  ");
		puts(" |       |  ");
		puts(" |	      ");
		puts("_|__________");
		puts("");
		break;
	case 4:
		puts(" __________ ");
		puts(" |/      |  ");
		puts(" |       O  ");
		puts(" |      /|  ");
		puts(" |	      ");
		puts("_|__________");
		puts("");
		break;
	case 3:
		puts(" __________ ");
		puts(" |/      |  ");
		puts(" |       O  ");
		puts(" |      /|\\");
		puts(" |	      ");
		puts("_|__________");
		puts("");
		break;
	case 2:	
		puts(" __________ ");
		puts(" |/      |  ");
		puts(" |       O  ");
		puts(" |      /|\\");
		puts(" |      /   ");
		puts("_|__________");
		puts("");
		break;
	case 1:
		puts(" __________ ");
		puts(" |/      |  ");
		puts(" |       O  ");
		puts(" |      /|\\");
		puts(" |      / \\");
		puts("_|__________");
		puts("");
		break;
	case 0:
		puts(" __________ ");
		puts(" |/      |  ");
		puts(" |      \\O/");
		puts(" |       |  ");
		puts(" |      / \\");
		puts("_|__________");
		puts("");
		break;
	default:
		puts(" __________      ");
		puts(" |/      |       ");
		puts(" |	           ");
		puts(" |           \\O/");
		puts(" |            |  ");
		puts("_|__________ / \\");
		puts("");
	}
}

