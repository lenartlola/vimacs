//
// Created by Hajar Sabir on 5/15/22.
//

#include "Vimacs.hpp"

/* Input */
static int readInput() {
	int nread;
	char c;
	while((nread = read(STDIN_FILENO, &c, 1)) != 1) {
		if (nread == -1 && errno != EAGAIN)
			die("vimacs: failed to read input\n");
	}

    if (c == '\x1b') {
        char seq[3];
        if (read(STDIN_FILENO, &seq[0], 1) != 1) return '\x1b';
        if (read(STDIN_FILENO, &seq[1], 1) != 1) return '\x1b';
        if (seq[0] == '[') {
            switch (seq[1]) {
                case 'A':
                    return ARROW_UP;
                case 'B':
                    return ARROW_DOWN;
                case 'C':
                    return ARROW_RIGHT;
                case 'D':
                    return ARROW_LEFT;
            }
        }
        return '\x1b';
    }
    else
        return c;
}

void    movexy(int c) {
    switch (c) {
        case ARROW_LEFT:
            if (g_term.cursor_x != 0)
                g_term.cursor_x--;
            break;
        case ARROW_RIGHT:
            if (g_term.screencols -1 != g_term.cursor_x)
                g_term.cursor_x++;
            break;
        case ARROW_UP:
            if (g_term.cursor_y != 0)
                g_term.cursor_y--;
            break;
        case ARROW_DOWN:
            if (g_term.screenrows -1 != g_term.cursor_y)
                g_term.cursor_y++;
            break;
    }
}

void	keyPressProcess() {
	int c = readInput();

	switch (c) {
		case CTRL_KEY('q'):
			// Clear the screen on exit
			write(STDOUT_FILENO, "\x1b[2J", 5);
			write(STDOUT_FILENO, "\x1b[H", 3);
			exit(0);
        case ARROW_UP:
        case ARROW_DOWN:
        case ARROW_LEFT:
        case ARROW_RIGHT:
            movexy(c);
            break;
    }
}

/* Output */
// TODO - tiles bug on moving cursor
static void	drawTile(std::string *buffer) {
	int y = 0;
	for (y = 0; y < g_term.screenrows; y++) {
		if (y >= g_term.n_rows) {
			if (y == g_term.screenrows / 3 && g_term.n_rows == 0) {
				std::string welcome = "Welcome to vimacs --version " VIMACS_VERSION;
				int padding = (g_term.screencols - welcome.length()) / 2;
				if (padding) {
					buffer->append("~");
					padding--;
				}
				while (padding--)
					buffer->append(" ");
				buffer->append(welcome);
			}
			else {
				//TODO add number of line
				if (y >= g_term.n_line)
					buffer->append("~");
			}
		}
		// clear lines at a time
		buffer->append("\x1b[K");
		if (y < g_term.screenrows - 1)
			buffer->append("\r\n");
	}
	buffer->append("\x1b[H");
	buffer->append(g_term.buf);
	buffer->append("\x1b[H");
}


#include <cstring>

void	refreshScreen() {
	std::string buffer;

	buffer.append("\x1b[?25l");
	drawTile(&buffer);
	// <esc>[H would take back the cursor to the top left
//	buffer.append("\x1b[H");

	// Hide the cursor
	char buf[32];
	snprintf(buf, sizeof(buf), "\x1b[%d;%dH", g_term.cursor_y + 1, g_term.cursor_x + 1);
	buffer.append(buf, strlen(buf));
	buffer.append("\x1b[?25h");
//	std::cout << buffer.length() << "\n";
//	write(STDOUT_FILENO, g_term.buf.c_str(), g_term.buf.length());
	write(STDOUT_FILENO, buffer.c_str(), buffer.length());
}