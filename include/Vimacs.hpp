//
// Created by Hajar Sabir on 5/15/22.
//

#ifndef VIMACS_VIMACS_HPP
#define VIMACS_VIMACS_HPP

#include <unistd.h>
#include <ncurses.h>
#include <git2.h>
#include <termios.h>
#include <cctype>
#include <iostream>

/* Data structures */

struct t_term {
	struct termios o_mode;
	struct termios r_mode;
};
extern struct t_term g_term;

/* Prototypes */

// Terminal
void	enter_raw_mode(void);

#endif //VIMACS_VIMACS_HPP
