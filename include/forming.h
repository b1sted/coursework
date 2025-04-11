#ifndef FORMING_H
#define FORMING_H

void forming_time(int n, float *t, float *dt);
void forming_Uvx(int n, float *t, float *Uvx, float t1, float t2, float t3, float a, float b, float c);
void forming_Uvix(int n, float *Uvx, float *Uvix, float Uvx1, float a, float b);

#endif // FORMING_H
