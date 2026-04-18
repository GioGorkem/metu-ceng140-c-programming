#include "questions.h"

/*
 * Implementation of 2D overlapping window filter over a B x R x C tensor.
 * Applies a k x k spatial filter centered at (r, c) with zero-padding at boundaries.
 */
int*** apply_overlapping_filter(int B, int R, int C, int k, int ***input) {
    int b, r, c, dr, dc;
    int pad = k / 2;
    int ***output;

    if (input == NULL || B <= 0 || R <= 0 || C <= 0 || k <= 0) {
        return NULL;
    }

    output = (int***)malloc(B * sizeof(int**));
    if (output == NULL) {
        return NULL;
    }

    for (b = 0; b < B; b++) {
        output[b] = (int**)malloc(R * sizeof(int*));
        if (output[b] == NULL) {
            return NULL;
        }

        for (r = 0; r < R; r++) {
            output[b][r] = (int*)malloc(C * sizeof(int));
            if (output[b][r] == NULL) {
                return NULL;
            }

            for (c = 0; c < C; c++) {
                int sum = 0;
                for (dr = -pad; dr <= pad; dr++) {
                    for (dc = -pad; dc <= pad; dc++) {
                        int nr = r + dr;
                        int nc = c + dc;
                        if (nr >= 0 && nr < R && nc >= 0 && nc < C) {
                            sum += input[b][nr][nc];
                        }
                    }
                }
                output[b][r][c] = sum;
            }
        }
    }

    return output;
}
