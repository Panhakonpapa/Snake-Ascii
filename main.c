#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <time.h>
#include <stdbool.h>

#define WIDTH 20 
#define HEIGHT 20 
#define MAX_SNAKE_LENGHT 100 

/* Board layout */
char board[HEIGHT][WIDTH];

/* Snake */
int snakeX, snakeY; 
int snakeBodyX[MAX_SNAKE_LENGHT]; 
int snakeBodyy[MAX_SNAKE_LENGHT]; 

/* direction */
int dx = 0, dy = 0;  

/* Food */
int foodX, foodY; 
int snakeLenght = 1; 

void initializeBorad() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1) {
				board[i][j] = '#'; /* wall */
			} 
			else {
				board[i][j] = ' '; /* Empty space */ 
			}
		}
	}
}
void drawBoard() {
	system("clear"); 
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			printf("%c", board[i][j]); 
		}
		printf("\n"); 
	}
}
void initializeSnake() {
	snakeX = WIDTH / 2;
	snakeY = HEIGHT /2; 
	board[snakeX][snakeY] = 'O'; 
	snakeBodyX[0] = snakeX; 
	snakeBodyy[0] = snakeY;  
}
void moveSnake()  {
	board[snakeBodyX[snakeLenght - 1]][snakeBodyy[snakeLenght - 1]] = ' ';
	
	for (int i = snakeLenght - 1; i > 0; i--) {
		snakeBodyX[i] = snakeBodyX[i - 1]; 
		snakeBodyy[i] = snakeBodyy[i - 1]; 
	}

	snakeX += dx; 
	snakeY += dy;

	snakeBodyX[0] = snakeX; 	
	snakeBodyy[0] = snakeY;  

	board[snakeX][snakeY] = 'O'; 

	for (int i = 1 ; i < snakeLenght; i++) {
		board[snakeBodyX[i]][snakeBodyy[i]] = '0'; 
	}
}
void processInput() {
	char key = getchar(); 
	switch (key) {
		case 'w': dy = -1; dx = 0; break;  // Move up
		case 's': dy = 1; dx = 0; break;   // Move down
		case 'a': dx = -1; dy = 0; break;  // Move left
		case 'd': dx = 1; dy = 0; break;   // Move right
	}
}	

void placeFood() {
	do {
		foodX = rand() % (WIDTH - 2) + 1;
		foodY = rand() % (HEIGHT - 2) + 1; 
	} while (board[foodX][foodY] == 'O'); 

	board[foodX][foodY] = '*'; 
}
void cheakFoodCollision() {
	if (snakeX == foodX && snakeY == foodY) {
		snakeLenght++; 
		placeFood(); 
	}
}
bool cheakCollision() {
	if (snakeX <= 0 || snakeX >= WIDTH - 1 || snakeY <= 0 || snakeX >= HEIGHT - 1)	 {
		return true; /* hit wall */  
	}
	for (int i = 1; i < snakeLenght; i++) {
		if (snakeBodyX[i] == snakeX && snakeBodyy[i] == snakeY) {
			return true; 
		}
	}
	return false; 
}
int main() {
	srand(time(NULL));
	initializeBorad(); 
	initializeSnake(); 
	placeFood(); 
	while (1) {
		drawBoard(); 
		processInput(); 
		moveSnake(); 
		cheakFoodCollision(); 
		if (cheakCollision()) {
			printf("Game Over "); 
		}
		usleep(200000);
	}

	return 0; 
}
