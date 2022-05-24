use termios::*;

pub struct Gterm
{
	pub     screenrows: usize,
    pub 	screencols: usize,
	pub     buf:		String,
	pub     termios:	Termios,
	pub     o_term:		Termios,
    pub     n_rows:     usize,
}
