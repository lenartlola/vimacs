//
// Created by Hajar Sabir on 5/15/22.
//

#include "Vimacs.hpp"

void	die(const char *s) {
	// Clear the screen on exit
	write(STDOUT_FILENO, "\x1b[2J", 5);
	write(STDOUT_FILENO, "\x1b[H", 3);

	perror(s);
	exit(127);
}
