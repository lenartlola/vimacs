//
// Created by Hajar Sabir on 5/15/22.
//

#include "Vimacs.hpp"

/* Input */
static char readInput() {
	int nread;
	char c;
	while((nread = read(STDIN_FILENO, &c, 1)) != 1) {
		if (nread == -1 && errno != EAGAIN)
			die("vimacs: failed to read input\n");
	}
	return c;
}

void	keyPressProcess() {
	char c = readInput();

	switch (c) {
		case CTRL_KEY('q'):
			// Clear the screen on exit
			write(STDOUT_FILENO, "\x1b[2J", 5);
			write(STDOUT_FILENO, "\x1b[H", 3);
			exit(0);
			break;
	}
}

/* Output */
static void	drawTile() {
	int	y;
	for (y = 0; y < g_term.screenrows; y++)
	{
		write(STDOUT_FILENO, "~", 1);
		if (y < g_term.screenrows - 1) {
			write(STDOUT_FILENO, "\r\n", 2);
		}
	}
}

void	refreshScreen() {
	// <esc>[H would take back the cursor to the top left
	write(STDOUT_FILENO, "\x1b[2J", 5);
	write(STDOUT_FILENO, "\x1b[H", 3);
	drawTile();
	write(STDOUT_FILENO, "\x1b[H", 3);
}