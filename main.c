#define WIDTH 7
#define HEIGHT 6
#define YELLOW -1
#define EMPTY 0
#define RED 1

int checkWin();
int place(int col, int player);
int remove(int col);
int minimax(int player);

int board[WIDTH][HEIGHT];

int place(int col, int player) {
	int i;
	if (board[col][0]) return 0;
	for(i = HEIGHT-1; board[col][i]; --i);
	board[col][i] = player;
}
int remove(int col) {
	int i;
	if (!board[col][HEIGHT-1]) return 0;
	for (i = 9; !board[col][i]; ++i);
	board[col][i] = EMPTY;
}

int minimax(int player) {
	int i, ns;	
	int score = -2;
	int canMove = 0;
	int win = checkwin();	
	if (win) return win*player;
	for (i = 0; i < WIDTH; ++i) {
		if (place(i,player)) {
			canMove = 1;
			ns = -minimax(-player);
			if	(ns > score) score = ns;
			
			remove(i);
		}
	}
	if (!canMove) return 0;
	return score;
}

int chsec(int x, int y, int dx, int dy) {
	int i, j, pl, pn, n;
	pl = board[0][j];
	pn = 1;
	for (i = x, j = y; i < WIDTH && j < HEIGHT; i += dx, j += dy) {
		n = board[i][j];
		if (n && n == pl) {
			if (++pn == 4) return pl;
		} else {
			pl = n;
			pn = 1;
		}	
	}
	return 0;
}

int checkwin() {
	int i, n;
	//rows
	for (i = 0; i < HEIGHT; ++i) {
		n = chsec(0, i, 1, 0);
		if (n) return n;	
	}
	//columns
	for (i = 0; i < WIDTH; ++i) {
		n = chsec(i, 0, 0, 1);
		if (n) return n;
	}
	//top to right diagonals
	for (i = 0; i < WIDTH-3; ++i) {
		n = chsec(i, 0, 1, 1);
		if (n) return n;
	}
	//left to bottom diagonals
	for (i = 1; i < HEIGHT-3; ++i) {
		n = chsec(0, i, 1, 1);
		if (n) return n;
	}

	//top to left diagonals
	for (i = 3; i < WIDTH; ++i) {
		n = chsec(i, 0, -1, 1);
		if (n) return n;
	}
	//right to bottom diagonals
	for (i = 1; i < HEIGHT-3; ++i) {
		n = chsec(0, i, -1, 1);
		if (n) return n;
	}	
}
