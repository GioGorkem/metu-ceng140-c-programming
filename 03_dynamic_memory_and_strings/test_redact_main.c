#include <stdio.h>
#include <stdlib.h>
#include "questions.h"


char* custom_strdup(const char* src) {
    int len = 0;
    int i;
    char *dest;
    while (src[len] != '\0') len++;
    dest = (char*)malloc((len + 1) * sizeof(char));
    for (i = 0; i <= len; i++) {
        dest[i] = src[i];
    }
    return dest;
}

void print_document(char **doc, int count) {
    int i;
    printf("Word count: %d\nDocument: ", count);
    if (count == 0 || doc == NULL) {
        printf("EMPTY\n");
        return;
    }
    for (i = 0; i < count; i++) {
        printf("[%s] ", doc[i]);
    }
    printf("\n");
}

int main() {
    
    
    char **doc;
    int word_count = 6;
    int b, r, c;
    int ***input_matrix;
    int ***output_matrix;
    int B = 1, R = 3, C = 3, k = 3;
    int val_counter = 1;

    printf("======================================\n");
    printf("TESTING Q1: DYNAMIC REDACTOR & SHIFTER\n");
    printf("======================================\n");
    
    doc = (char**)malloc(word_count * sizeof(char*));
    doc[0] = custom_strdup("this");
    doc[1] = custom_strdup("is");
    doc[2] = custom_strdup("a");
    doc[3] = custom_strdup("bad");
    doc[4] = custom_strdup("bad");
    doc[5] = custom_strdup("world");

    printf("Original: ");
    print_document(doc, word_count);

    printf("\n--> Test 1: Deleting consecutive 'bad' (replacement=NULL)\n");
    redact_and_shift(&doc, &word_count, "bad", NULL);
    print_document(doc, word_count);

    printf("\n--> Test 2: Replacing 'world' with 'universe'\n");
    redact_and_shift(&doc, &word_count, "world", "universe");
    print_document(doc, word_count);

    printf("\n--> Test 3: Attempting to find non-existent 'alien'\n");
    redact_and_shift(&doc, &word_count, "alien", "human");
    print_document(doc, word_count);

    printf("\n--> Test 4: Nuking the document (Deleting all remaining words)\n");
    redact_and_shift(&doc, &word_count, "this", NULL);
    redact_and_shift(&doc, &word_count, "is", NULL);
    redact_and_shift(&doc, &word_count, "a", NULL);
    redact_and_shift(&doc, &word_count, "universe", NULL);
    print_document(doc, word_count);

    if (doc != NULL) {
        free(doc); 
    }
    
    printf("\n======================================\n");
    printf("TESTING Q2: PADDING & OVERLAPPING FILTER\n");
    printf("======================================\n");


    input_matrix = (int***)malloc(B * sizeof(int**));
    for (b = 0; b < B; b++) {
        input_matrix[b] = (int**)malloc(R * sizeof(int*));
        for (r = 0; r < R; r++) {
            input_matrix[b][r] = (int*)malloc(C * sizeof(int));
            for (c = 0; c < C; c++) {
                input_matrix[b][r][c] = val_counter++;
            }
        }
    }

    printf("Input Matrix (1x3x3):\n");
    for (r = 0; r < R; r++) {
        for (c = 0; c < C; c++) {
            printf("%d\t", input_matrix[0][r][c]);
        }
        printf("\n");
    }

    printf("\nApplying Filter (k=3)...\n");
    output_matrix = apply_overlapping_filter(B, R, C, k, input_matrix);

    if (output_matrix != NULL) {
        printf("\nOutput Matrix:\n");
        for (r = 0; r < R; r++) {
            for (c = 0; c < C; c++) {
                printf("%d\t", output_matrix[0][r][c]);
            }
            printf("\n");
        }

  
        for (b = 0; b < B; b++) {
            for (r = 0; r < R; r++) free(output_matrix[b][r]);
            free(output_matrix[b]);
        }
        free(output_matrix);
    } else {
        printf("ERROR: Output matrix is NULL. Not implemented or allocation failed.\n");
    }


    for (b = 0; b < B; b++) {
        for (r = 0; r < R; r++) free(input_matrix[b][r]);
        free(input_matrix[b]);
    }
    free(input_matrix);

    printf("\nTesting complete. Run through Valgrind to ensure your doom is not sealed by memory leaks.\n"); 
    return 0;
}