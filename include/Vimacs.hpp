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
#include <sys/ioctl.h>

/* Defines */

#define CTRL_KEY(k) ((k) & 0x1f)

/* Data structures */

struct t_term {
	int				screenrows;
	int				screencols;
	struct termios	o_mode;
	struct termios	r_mode;
};
extern struct t_term g_term;

/* Prototypes */

// Terminal
void	initTerm();
void	enter_raw_mode(void);

// Utils
void	die(const char *s);

// IO handlers
void	keyPressProcess();
void	refreshScreen();

#endif //VIMACS_VIMACS_HPP
