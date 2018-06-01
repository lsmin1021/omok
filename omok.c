// Created by S.M

#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>

#define KEY_SPACE ' ' // not defined in ncurses.h
#define KEY_Enter 10
#define START_ROW 5
#define START_COL 5

int HEIGHT, WIDTH;

void saveGame(int **board, int row, int col, int turn){
	/*
		Save current game with given name 
	*/
	// TODO 
}

int** readSavedGame(int **board, int *row, int *col, int *turn){
	/*
		Read the existing game
	*/
	// TODO 
}

int** initBoard(int **board, int *row, int *col, int *turn, int load){
	int i=0;
	board = (int**)malloc(sizeof(int*)*HEIGHT);

	for(i=0; i<HEIGHT; i++){
		board[i] = (int*)malloc(sizeof(int)*WIDTH);
	}

	printf("%d %d\n", HEIGHT, WIDTH);
	board[0][0] = ACS_ULCORNER;//'┌'
	for (i=1; i < WIDTH-1; i++)
		board[0][i] = ACS_TTEE;//'┬'
	board[0][WIDTH-1] = ACS_URCORNER; //'┐'

	for (i=1; i<HEIGHT-1; i++){
		int j=0;
		board[i][0] = ACS_LTEE; // '├'
		for (j=1; j < WIDTH-1; j++)
			board[i][j] = ACS_PLUS; //'┼'
		board[i][WIDTH-1] = ACS_RTEE; //'┤'
	}

	board[HEIGHT-1][0] = ACS_LLCORNER; //'└'
	for (i=1; i < WIDTH-1; i++)
		board[HEIGHT-1][i] = ACS_BTEE; //'┴'
	board[HEIGHT-1][WIDTH-1] = ACS_LRCORNER; // '┘'

	return board;
}

void paintBoard(int **board, WINDOW *win, int row, int col){
	
	int i,j;
	/*
		Print the board to the given WINDOW 
		using functions of the ncurses library.
	*/
	initscr();
	noecho();
	wprintw(win,"WOW\n");
	for(i=0;i<HEIGHT;i++){
		for(j=0;j<WIDTH;j++){
			addch(board[i][j]);
		}
		printw("\n");
	}
	
	endwin();
	
	return ;
	// TODO
}

int checkWin(){ // parameters and return type can be modified with any form. 
	/*
		Check if the game is over. 
	*/
	// TODO
}

int Action(WINDOW *win, int **board, int keyin, int *row, int *col, int *turn, int players){
	/*
		following right after the keyboard input,
		perform a corresponding action. 
	*/
	switch(keyin){
		case KEY_DOWN:
			*row++;
			break;
		case KEY_RIGHT:
			*col++;
			break;
		case KEY_LEFT:
			*col--;
			break;
		case KEY_UP:
			*row--;
			break;
		case KEY_Enter:
			if(*turn%2==0){
				board[*row][*col]='O';
			}
			else if(*turn%2==1){
				board[*row][*col]='X';
			}
			*turn++;			
			break;
		case KEY_SPACE:
			if(*turn%2==0){
				board[*row][*col]='O';
			}
			else if(*turn%2==1){
				board[*row][*col]='X';
			}
			*turn++;
			break;

	}
	move(*row,*col);
	refresh();
	return 0;
	// TODO 
}


void gameStart(WINDOW *win, int load, int players){
	int **board;
	int row = 0;
	int col = 0;
	int keyin,turn=0;
	wmove(win, row, col); 
	int a=0;
	board = initBoard(board, &row, &col, &turn, load); // Initiating the board

	while(1){
		
		/* 
			This While loop constantly loops in order to 
			draw every frame of the WINDOW.
		*/

		// TODO LIST
		paintBoard(board , win, row, col);  // PAINT THE BOARD
		
		
		initscr();
		noecho();
		cbreak();
		keypad(stdscr,TRUE);

		printw("Current Turn : ");// PAINT MENU
		if(turn%players == 0){
			printw("O\n");
		}
		else if(turn%players == 1){
			printw("X\n");
		}
		else if(turn%players == 2){
			printw("Y\n");
		}
		printw("1. press 1 to save\n2. Exit without save\n");
		printw("%d %d\n",row,col);	
		move(row,col);  // MOVE CURSOR TO THE LAST POINT 
		refresh();
		keyin=getch();  // GET KEYBOARD INPUT
		Action(win,board,keyin,&row,&col,&turn,players);  // DO ACTION ACCORDING TO THAT INPUT
		
		wrefresh(win);
		refresh();// update WINDOW 
		
		
		
			
	}

	return;
}

int main(){
	char load;
	int nload;
	int players;

	// TODO 
		printf("Want to load the game?[y/n] : ");
	scanf("%c",&load);
	if(load == 'y'){
		nload = 0;
	} else {
		nload = 1;
	}

	printf("Enter the HEIGHT of the board : ");
	scanf("%d",&HEIGHT);
	printf("Enter the WIDTH of the board : ");
	scanf("%d",&WIDTH);
	printf("Enter the number of players[2/3] : ");
	scanf("%d",&players);
	//	Prompts to ask options of the game
	

	// TODO LIST
	initscr();
	WINDOW *win = newwin(HEIGHT,WIDTH, 10, 10);  // define a window
	endwin();
	
	// terminate the window safely so that the terminal settings can be restored safely as well. 

	gameStart(win, nload, players); 

	return 0;
}
