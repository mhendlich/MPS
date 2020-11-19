//*----------------------------------------------------------------------------
//* File Name           : ser_io.h
//* Object              : Standard C Header File
//*
//* 1.0 27/10/02 GR     : Creation
//*----------------------------------------------------------------------------

#ifndef ser_io_h
#define ser_io_h

void putchar(int);
unsigned char getchar(void);
void init_ser(void);
void puts(char*);
unsigned int gets(char*,int);
unsigned int getpw(char*,int);

#endif /* ser_io_h */
