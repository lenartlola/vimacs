//
// Created by Hajar Sabir on 5/15/22.
//

#include "Vimacs.hpp"

//Stylize to c++
void editorOpen(char *filename) {
	std::fstream	fp;
	std::string		line;

	fp.open(filename);
	if (!fp.is_open()) {
		die("Failed to open file");
	}
	while (std::getline(fp, line, '\n')) {
//		write(STDOUT_FILENO, line.c_str(), line.length());
//		write(STDOUT_FILENO, "\n", 1);
		g_term.buf.append(std::to_string(g_term.n_line));
		g_term.buf.append(": ");
		g_term.buf.append(line);
		g_term.buf.append("\r\n");
		g_term.n_rows = 1;
		g_term.n_line++;
	}
	fp.close();
}