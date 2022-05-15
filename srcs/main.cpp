/*
 * WUBBA LUBBA DUB DUB
 */

#include "Vimacs.hpp"

struct t_term g_term;

int	main()
{
	enter_raw_mode();
	initTerm();

	while (1) {
		refreshScreen();
		keyPressProcess();
	}
	return 0;
}
