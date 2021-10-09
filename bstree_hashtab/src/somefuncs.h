#include <sys/time.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE 200000

double wtime();
int getrand(int min, int max);
void free_some_words(char **words);
void load_some_words(char **words);
double avr(double average_time);