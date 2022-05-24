use std::fs::File;
use std::io::BufReader;
use std::io::prelude::*;
use std::env;
use std::path::Path;

mod iohandler;
mod lib;
use crate::lib::Gterm as GTerm;
use crate::iohandler::test;
use termios::*;
/*    pub struct GTerm
    {
        screenrows: usize,
        screencols: usize,
        // cursor_x:   isize,
        // cursor_y:   isize,
        // n_rows:     isize,
        buf:        String,
        termios:    Termios,
        o_term:     Termios,
    }

*/
fn enter_raw_mode(term: &mut GTerm)
{
    tcgetattr(0,&mut term.termios).expect("error getting termios");
    term.termios.c_lflag &= !(ECHO | ICANON | ISIG | IEXTEN);
    term.termios.c_lflag &= !(IXON | ICRNL);
    term.termios.c_oflag &= !(OPOST);
    tcsetattr(0, TCSAFLUSH, &mut term.termios).expect("Error setting termios");

}
fn init_term(term: &mut GTerm)
{
    if let Some((w, h)) = term_size::dimensions_stdout()
    {
        term.screenrows = w;
        term.screencols = h;
    }
    else
    {
        println!("Error unable to get terminal size");
    }

}
fn main() -> std::io::Result<()>
{
    let mut term = GTerm {
        screenrows: 0,
        screencols: 0,
      //  cursor_x: 0,
       // cursor_y: 0,
        n_rows: 0,
        buf: String::new(),
        termios: Termios::from_fd(0).unwrap(),
        o_term: Termios::from_fd(0).unwrap(),
    };
    enter_raw_mode(&mut term);
    init_term(&mut term);
    let args: Vec<String> = env::args().collect();
    if args.len() > 1
    {
        if Path::new(&args[1]).is_file() == true
        {
            let file = File::open(&args[1])?;
            let mut buf_reader = BufReader::new(file);
        // let mut contents = String::new();
            buf_reader.read_to_string(&mut term.buf)?;
            println!("{:?}\r", term.buf);
        }
        else
        {
            println!("file doesn't exist F\r");
        }
    }
    else
    {
        test(&mut term);
    }
    tcsetattr(0, TCSAFLUSH, &mut term.o_term).expect("Error resetting terminal to og val");
    Ok(())
}
