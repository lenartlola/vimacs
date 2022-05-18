/*
 * WUBBA LUBBA DUB DUB
 */

#include "Vimacs.hpp"

struct t_term g_term;

int	main(int argc, char *argv[])
{
	enter_raw_mode();
	initTerm();

	if (argc >= 2)
		editorOpen(argv[1]);

	while (1) {
		refreshScreen();
		keyPressProcess();
	}
	return 0;
}
