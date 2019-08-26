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
	FILE*savefile;
	char f_name[100];
	echo();
	mvprintw(row+5,col+5,"ENTER FILE NAME : ");
	scanw("%s",&f_name);
	
	savefile=fopen(f_name,"w");
	fprintf(savefile,"%d %d %d ",row,col,turn);
	for(int i=0;i<HEIGHT;i++){
		for(int j=0;j<WIDTH;j++){
			fprintf(savefile,"%d ",board[i][j]);
		}
	}
	fclose(savefile);
	
	// TODO 
}

int** readSavedGame(int **board, int *row, int *col, int *turn){
	/*
		Read the existing game
	*/
	FILE*readfile;
	char f_name[100],x;
	int r,c,t;

	echo();
	printw("ENTER FILE NAME : ");
	scanw("%s",&f_name);
	
	readfile=fopen(f_name,"r");
	fscanf(readfile,"%d %d %d",&r,&c,&t);
	for(int i=0;i<HEIGHT;i++){
		for(int j=0;j<WIDTH;j++){
			fscanf(readfile,"%d",&board[i][j]);
		}
	}
	fclose(readfile);
	(*row)=r;
	(*col)=c;
	(*turn)=t;
	return board;
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
	for(i=0;i<HEIGHT;i++){
		for(j=0;j<WIDTH;j++){
			mvwaddch(win, i, j, board[i][j]);
		}
	}
	wrefresh(win);
	return ;
	// TODO
}

int checkWin(int row,int col,int **board,int players){ // parameters and return type can be modified with any form. 
	/*
		Check if the game is over. 
	*/
	int i,x;
	int fin_num=7-players;
	int check=board[row][col];
	for(row=0;row<HEIGHT;row++){
		for(col=0;col<WIDTH;col++){
			if(check==board[row][col]){
				x=1;
				for(i=1;i<fin_num && x<9;i++){
					if(row>3 && board[row][col]==board[row-i][col] && x==1){
						continue;
					}
					else if(row<HEIGHT-4 && board[row][col]==board[row+i][col] && x==2){
						continue;
					}
					else if(col>3 &&  board[row][col]==board[row][col-i] && x==3){
						continue;
					}
					else if(col<WIDTH-4 && board[row][col]==board[row][col+i] && x==4){
						continue;
					}
					else if(row>3 && col>3 && board[row][col]==board[row-i][col-i] && x==5){
						continue;
					}
					else if(row<HEIGHT-4 && col<WIDTH-4 && board[row][col]==board[row+i][col+i] && x==6){
						continue;
					}
					else if(col>3 && row<HEIGHT-4 && board[row][col]==board[row+i][col-i] && x==7){
						continue;
					}
					else if(col<WIDTH-4 && row>3 && board[row][col]==board[row-i][col+i] && x==8){
						continue;
					}
					else{
						i=0;
						x++;
					}
				}
			if(i==fin_num) return 1;
			}
		}
	}

	/*for(i=1;i<5;i++){
		if(board[row][col]==board[row+i][col]){
			continue;
		}
		else break;
	}
	if(i==5) return 1;

	for(i=1;i<5;i++){
		if(board[row][col]==board[row][col-i]){
			continue;
		}
		else break;
	}
	if(i==5) return 1;

	for(i=1;i<5;i++){
		if(board[row][col]==board[row][col+i]){
			continue;
		}
		else break;
	}
	if(i==5) return 1;

	for(i=1;i<5;i++){
		if(board[row][col]==board[row-i][col-i]){
			continue;
		}
		else break;
	}
	if(i==5) return 1;

	for(i=1;i<5;i++){
		if(board[row][col]==board[row+i][col+i]){
			continue;
		}
		else break;
	}
	if(i==5) return 1;

	for(i=1;i<5;i++){
		if(board[row][col]==board[row-i][col+i]){
			continue;
		}
		else break;
	}
	if(i==5) return 1;

	for(i=1;i<5;i++){
		if(board[row][col]==board[row+i][col-i]){
			continue;
		}
		else break;
	}
	if(i==5) return 1;*/

	return 0;
	// TODO
	
}

int Action(WINDOW *win, int **board, int keyin, int *row, int *col, int *turn, int players,int* save){
	/*
		following right after the keyboard input,
		perform a corresponding action. 
	*/
	int result=0;
	switch(keyin){
		case KEY_DOWN:
			if(*row < HEIGHT-1){
				(*row)++;
			}
			break;
		case KEY_RIGHT:
			if(*col < WIDTH-1){
				(*col)++;
			}
			break;
		case KEY_LEFT:
			if(*col > 0){
				(*col)--;
			}
			break;
		case KEY_UP:
			if(*row > 0)
				(*row)--;
			break;
		case '1':
			saveGame(board,*row,*col,*turn);
			(*save)=1;
			break;
		case '2':
			(*save)=2;
			break;
		case KEY_Enter:
			/*if(board[*row][*col] == 'O' || board[*row][*col] == 'X' || board[*row][*col] == 'Y'){
				break;
			}
			if((*turn) % players == 0){
				board[*row][*col]='O';
			}
			else if((*turn) % players == 1){
				board[*row][*col]='X';
			}
			else if((*turn) % players == 2){
				board[*row][*col]='Y';
			}
			(*turn)++;
			result=checkWin(*row,*col,board,players);
			break;*/
		case KEY_SPACE:
			if(board[*row][*col] == 'O' || board[*row][*col] == 'X'|| board[*row][*col] == 'Y'){
				break;
			}
			if((*turn) % players == 0){
				board[*row][*col]='O';
			}
			else if((*turn) % players == 1){
				board[*row][*col]='X';
			}
			else if((*turn) % players == 2){
				board[*row][*col]='Y';
			}
			(*turn)++;
			result=checkWin(*row,*col,board,players);
			break;
	}
	if(result==1){
		(*turn)--;
	}
	return result;
	// TODO 
}


void gameStart(WINDOW *win, int load, int players){
	int **board;
	int row = 0;
	int col = 0;
	int keyin,turn=0;
	int save=0,result;
	wmove(win, row, col);
	board = initBoard(board, &row, &col, &turn, load); // Initiating the board
	if(load==1){
		board = readSavedGame(board,&row,&col,&turn);
	}	
	while(1){
		
		/* 
			This While loop constantly loops in order to 
			draw every frame of the WINDOW.
		*/

		// TODO LIST
		noecho();
		paintBoard(board , win, row, col);  // PAINT THE BOARD

		mvprintw(HEIGHT + 8, 8, "Current Turn : ");// PAINT MENU
		if(turn%players == 0){
			printw("O\n");
		}
		else if(turn%players == 1){
			printw("X\n");
		}
		else if(turn%players == 2){
			printw("Y\n");
		}
		mvprintw(HEIGHT+9,8,"1. press 1 to save");
		mvprintw(HEIGHT+10,8,"2. Exit without save\n");
		
		move(row+5, col+5);
		keyin = getch();  // GET KEYBOARD INPUT
		result=Action(win,board,keyin,&row,&col,&turn,players,&save);
		if(result==1){
			paintBoard(board,win,row,col);
			mvprintw(HEIGHT+7 ,8,"PLAYER%d WIN !! Press any button to terminate the program",turn%players+1);
			getch();
			wrefresh(win);
			break;
		}   // DO ACTION ACCORDING TO THAT INPUT
		if(save==1){
			break;
		}
		if(save==2){
			break;
		}
		wrefresh(win);// update WINDOW 
	}

	delwin(win);
	endwin();

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
		nload = 1;
	} else {
		nload = 0;
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
	cbreak();
	noecho();
	keypad(stdscr,TRUE);
	WINDOW *win = newwin(HEIGHT,WIDTH, 5, 5);  // define a window
	
	refresh();// terminate the window safely so that the terminal settings can be restored safely as well. 
	endwin();
	
	gameStart(win, nload, players); 

	return 0;
}
