#ifndef FILE_H
#define FILE_H

void open_output_files(FILE **f1, FILE **f2, FILE **f3);
void close_output_files(FILE *f1, FILE *f2, FILE *f3);
long get_file_size(FILE *f);

#endif // FILE_H
