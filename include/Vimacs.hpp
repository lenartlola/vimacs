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
#include <string>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <cstring>

/* Defines */

#define CTRL_KEY(k) ((k) & 0x1f)
#define VIMACS_VERSION "0.0.1"

/* Data structures */

//TODO : Change char * to str
typedef struct text_row {
    int size;
    char *buf;
} text_row;

//TODO - may we don't even need a struct for str
struct t_term {
	int				screenrows;
	int				screencols;
    int             cursor_x;
    int             cursor_y;
    int             n_rows;
    text_row        t_row;
	struct termios	o_mode;
	struct termios	r_mode;
};
extern struct t_term g_term;

struct t_buffer {
	std::string buffer;
};

enum keyBinding {
    ARROW_LEFT = 100,
    ARROW_RIGHT,
    ARROW_UP,
    ARROW_DOWN
};

/* Prototypes */

// Terminal
void	initTerm();
void	enter_raw_mode(void);

// Utils
void	die(const char *s);

// IO handlers
void	keyPressProcess();
void	refreshScreen();

// Buffer handler
void    editorOpen();

#endif //VIMACS_VIMACS_HPP
