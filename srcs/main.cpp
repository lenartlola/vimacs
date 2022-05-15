/*
 * WUBBA LUBBA DUB DUB
 */

#include "Vimacs.hpp"

struct t_term g_term;

int	main()
{
	enter_raw_mode();
	char	c;

	while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
		if (iscntrl(c))
			printf("%d\r\n", c);
		else
			printf("%d ('%c')\r\n", c, c);
	}
	return 0;
}
