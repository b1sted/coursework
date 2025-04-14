#ifndef OUTPUT_H
#define OUTPUT_H

void print_banner();
void forming_table(int n, float *t, float *Uvx, float *Uvix);
void output_in_file(FILE *f1, FILE *f2, FILE *f3, int n, float *t, float *Uvx, float *Uvix);

#endif // BANNER_H
