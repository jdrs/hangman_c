#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "include/dictionary.h" 
#include "include/stkfgr.h"

/* If compiling for Windows include and define the following: */
#ifdef WIN32
#include <conio.h>
#define CLEARSCREEN "cls"
#else /* If compiling for Linux */
#include "include/getchlike.h"
#define CLEARSCREEN "clear"
#endif

#define PROGRAM_NAME "HANGMAN"
#define PROGRAM_VERSION	"0.4"

#define MAX_LEN 25	/* max length of a word */
#define MAX_LIFE 7	/* maximum number of miss guesses */
#define MAX_TRIVIA_LEN 240 /* maximum length of trivia */
#define RESET ' '
#define BLANK '_'

/* define my own boolean type */
#define TRUE 1
#define FALSE 0
typedef int boolean;

/* function prototypes */
void game_init(void);
void print_headings(void);
int play_game(char *s, char *t, char *r);
void update(char c, int word_size, int index, char *guess_word, int rem_lives);
int check(char *s);
void lives(int lives_left);
void show_stat(char c);
void print_trivia(char *trivia);

int game;	/* will count the game played */
int alphabet[26];

int main(void)
{
	char word[MAX_LEN + 1], category[MAX_LEN + 1], trivia[MAX_TRIVIA_LEN + 1],
		 			again;
	int games_played;

	game_init(); /* initialize the game with 7 lives */
	
	for (;;) {
		get_word(word, category, trivia); /* generated a new word from the dictionary */
		games_played = play_game(word, category, trivia); /* play the game */
		printf("\nGames played: %d\n", games_played);
		printf("Play again? (y/n): ");
		again = getchar();
		getchar();
		
		if (again == 'n' || again == 'N') {
			system(CLEARSCREEN);
			break;
		}

		game_init();
	}

	return 0;
}

/******************************************************************************
 * GAME_INIT																  *
 *																			  *
 * This function will print the game version and game title.				  *
 * It will set the life to MAX_LIFE (7) and reset the stick man.			  *
 ******************************************************************************/
void game_init(void)
{
	print_headings();
	printstkfgr(MAX_LIFE);
	show_stat(RESET);
	lives(MAX_LIFE);
}

void print_headings(void)
{
	system(CLEARSCREEN);
	printf("%s %s\n", PROGRAM_NAME, PROGRAM_VERSION);
printf("\t\tH  H    A    NN  N   GGG    MM   MM    A    NN  N\n"
       "\t\tHHHH   A A   N N N  G   GG  M M M M   A A   N N N\n"
       "\t\tH  H  AA AA  N  NN   GGGG   M  M  M  AA AA  N  NN\n");
}

/******************************************************************************
 * PLAY_GAME																  *
 *																			  *
 * play_game takes a pointer to the generated word as an argument and returns *
 * an integer that counts the games played.							  		  *
 ******************************************************************************/
int play_game(char *s, char *t, char *r)
{
	int guess;
	boolean correct = FALSE;
	char new_word[strlen(s)];
	int i, remaining_lives = MAX_LIFE;

	/* initialize all elements of new word to a BLANK ('_') character */
	for (i = 0; i < strlen(s); i++) {
		new_word[i] = BLANK;
		printf("%c ", new_word[i]);
	}
	printf("\n");

	for (;;) {
		printf("\nCategory: %s ", t);

#ifdef WIN32
		guess = getch();
#else
		guess = getch_like();
#endif
		/* if character is in lowercase convert to uppercase */
		if (guess >= 97 && guess <= 122)
			guess -= 32;

		/* compare the character input if it matches to any letter in the
		 * generated word. If we find a match then we update the with the
		 * blank word (new_word) with that letter.
		 */
		for (i = 0; i < strlen(s); i++)
			if (guess == s[i]) {
				update(guess, strlen(s), i, new_word, remaining_lives);
				correct = TRUE;
			}

		/* if we didn't find a match then store the letter in the last element
		 * of the array and update,  decrementing the life.
		 */
		if (!correct)
			update(guess, strlen(s), i, new_word, --remaining_lives);

		correct = FALSE;

		/* check if game is over */
		if (remaining_lives == 0) {
			print_trivia(r);
			printf("\nGAME OVER\n");
			return ++game;
		} else if (check(new_word)) {
			update(guess, strlen(s), i, new_word, -1);
			print_trivia(r);
			return ++game;
		}
	}
}

/******************************************************************************
 * UPDATE																	  *
 *																			  *
 * Update the word with the character input then re print the headings		  *
 ******************************************************************************/
void update(char c, int word_size, int index, char *guess_word, int rem_lives)
{
	int i;

	print_headings();
	printstkfgr(rem_lives);
	show_stat(c);
	lives(rem_lives);
	guess_word[index] = c;
	for (i = 0; i < word_size; i++)
		printf("%c ", guess_word[i]);

	printf("\n");
}

/******************************************************************************
 * CHECK																	  *
 * 																			  *
 * We keep playing as long as we find a BLANK ('_') character, or until we    *
 * run out of lives.														  *
 ******************************************************************************/
int check(char *s)
{
	int i;
	for (i = 0; i < strlen(s); i++)
		if (s[i] == BLANK)
			return 0;

	return 1;
}

void lives(int lives_left)
{
	int i;

	printf("Lives left: ");	
	for (i = 1; i <= lives_left; i++)
		printf("X");
	puts("\n");
}

/******************************************************************************
 * SHOW_STAT																  *
 *																		      *
 * Print the letters of the alphabet.										  *
 * Change the letter into an empty space if it matches a letter in the        *
 * generated word.														   	  *
 * If the argument is an empty space then re-initialize alphabet array with   *
 * all the letters of the alphabet.											  *
 ******************************************************************************/
void show_stat(char c)
{
	int i, a = 65;

	if (c == RESET) {
		for (i = 0; i < 26; i++)
			alphabet[i] = a++;

		for (i = 0; i < 26; i++)
			printf("%c", alphabet[i]);

		puts("\n");

		return ;
	}	

	for (i = 0; i < 26; i++)
		if (alphabet[i] == c) {
			alphabet[i] = ' ';
			printf(" ");
		} else {
			printf("%c", alphabet[i]);
		}

	puts("\n");
}

void print_trivia(char *trivia)
{
	printf("\n%s\n", trivia);
}

