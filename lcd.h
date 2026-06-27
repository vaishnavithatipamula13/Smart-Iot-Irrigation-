#ifndef LCD_H
#define LCD_H

void Write_LCD(char data);

void Cmd_LCD(char cmd);

void Char_LCD(char ch);

void Init_LCD(void);

void Str_LCD(char *p);

void Uint_LCD(unsigned int n);

void LCD_GotoXY(unsigned int row,unsigned int col);

#endif
