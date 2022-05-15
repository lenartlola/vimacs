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
static void	drawTile(std::string *buffer) {
	for (int y = 0; y < g_term.screenrows; y++)
	{
		if (y == g_term.screenrows /3) {
			std::string welcome = "Welcome to vimacs --version " VIMACS_VERSION;
//			if (wlen > g_term.screencols)
//				wlen = g_term.screencols;
			int padding = (g_term.screencols - welcome.length()) / 2;
			if (padding) {
				buffer->append("~");
				padding--;
			}
			while (padding--)
				buffer->append(" ");
			buffer->append(welcome);
		}
		else
			buffer->append("~");
		buffer->append("\x1b[K");
		if (y < g_term.screenrows - 1)
			buffer->append("\r\n");
	}
}

void	refreshScreen() {
	std::string buffer;

	buffer.append("\x1b[?25l");
	drawTile(&buffer);
	// <esc>[H would take back the cursor to the top left
	buffer.append("\x1b[H");
	// Hide the cursor
	buffer.append("\x1b[?25h");
	write(STDOUT_FILENO, buffer.c_str(), buffer.length());
}