//
// Created by Hajar Sabir on 5/15/22.
//

#include "Vimacs.hpp"

//TODO : Provide  a fallback support of getting widows size to all the system

static int	getWindowSize(int *rows, int *cols) {
	struct winsize	ws;

	if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0)
		return -1;
	*cols = ws.ws_col;
	*rows = ws.ws_row;
	return 0;
}

void	initTerm() {
    g_term.cursor_x = 0;
    g_term.cursor_y = 0;
    g_term.n_rows = 0;
	if (getWindowSize(&g_term.screenrows, &g_term.screencols) == -1)
		die("vimacs: failed to get the window size\n");
}

static void	exit_raw_mode(void) {
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_term.o_mode) == -1)
		die("vimacs: failed to reset the terminal attributes to the original.\n");
}

void	enter_raw_mode(void) {


	// Get terminal attributes
	tcgetattr(STDIN_FILENO, &g_term.o_mode);
	atexit(exit_raw_mode);

    //TODO it crush on linux
	//g_term.r_mode = g_term.o_mode;

	/*
	 * Remove the echo,
	 * canonical mode: in order to read byte by byte instead of line by line,
	 * Ctrl-C && Ctrl-Z && Ctrl-(S, Q) && Ctrl-V signals
	 * Ctrl-M "Carriage return newline CRNL"
	*/
	 // (~) bitwise-NOT operator to inverse the echo bits
	g_term.r_mode.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
	g_term.r_mode.c_iflag &= ~(IXON | ICRNL);
	// Turn of all output processing
	g_term.r_mode.c_oflag &= ~(OPOST);

	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_term.r_mode) == -1)
		die("vimacs: failed to set the terminal attributes to the raw mode.\n");
}

