use crate::lib::Gterm;

fn draw_tile(term: &mut Gterm, buffer: &mut String)
{
    let mut    y = 0;
    while y < term.screenrows
    {
        if y >= term.n_rows
        {
            if y == term.screenrows / 3 && term.n_rows == 0
            {
                let welcome = String::from("Welcome to vimacs it appears to have rusted a bit due to the rain, sorry");
                let mut padding =  (term.screencols - welcome.len()) / 2;
                if padding != 0
                {
                    buffer.push_str("~");
                    padding -= 1;
                }
                while padding != 0
                {
                    buffer.push_str(" ");
                    padding -= 1;
                }
                { buffer.push_str(&welcome); }
            }
        }
            else
            {
                let mut _len = term.buf.len();
                if _len > term.screencols
                {
                    _len = term.screencols;
                }
                buffer.push_str(&term.buf);
            }
            if y < term.screenrows - 1
            {
                buffer.push_str("\r\n");
            }
            y += 1;
    }
}
pub fn test(term: &mut Gterm)
{
    let mut buffer = String::new();

    buffer.push_str("\x1b[?25l");
    draw_tile(term, &mut buffer);
    println!("{}", buffer);
}
