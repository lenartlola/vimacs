//
// Created by Hajar Sabir on 5/15/22.
//

#include "Vimacs.hpp"

void editorOpen() {
	// TODO - fix it bordel
    std::string str;
	str.append("Hello, world!");
    ssize_t linelen = 13;
    g_term.t_row.size = linelen;
    g_term.t_row.buf = malloc(linelen + 1);
    memcpy(g_term.t_row.buf, str, linelen);
    g_term.t_row.buf[linelen] = '\0';
    g_term.n_rows = 1;
}