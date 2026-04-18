#ifndef QUESTIONS_H
#define QUESTIONS_H

#include <stdlib.h>

/* BANNED: #include <string.h> */

void redact_and_shift(char ***document, int *word_count, const char *target, const char *replacement);
int*** apply_overlapping_filter(int B, int R, int C, int k, int ***input);

#endif /* QUESTIONS_H */