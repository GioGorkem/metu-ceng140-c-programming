#include "questions.h"

/* HELPER FUNCTIONS HERE */
/* Remember: No string.h allowed. Write your own strlen, strcmp, strcpy logic if needed. */
int str_length(char *word)
{
    int i = 0;
    while (word[i])
    {
        i++;
    }
    return i;
}

void redact_and_shift(char ***document, int *word_count, const char *target, const char *replacement) {
    /* YOUR STRICT ANSI C CODE HERE */
    int i, j=0, curr_length = 0, k;
    int target_length = 0;
    int is_correct_length = 0;
    int number_of_targets = 0;
    int *indexs_of_targets;
    int current_target_index = 0;
    int replacement_length = 0;
    /* *document bizim kelimelerin arrayıdır. */
    if ((*document == NULL) || (*word_count == 0)) {return;}
    while(target[target_length])
    {
        target_length++;
    }

    for (i = 0; i < *word_count; i++)
    {
        curr_length = str_length((*document)[i]);
        if (curr_length != target_length) {curr_length = 0; continue;}
        while (((*document)[i][is_correct_length] == target[is_correct_length]) && target[is_correct_length] != '\0')
        {
            is_correct_length++;
        }
        if (is_correct_length == target_length) /*TARGET BULUNDU, şimdi kaç tane target var onu saydıralım. */
        {
            number_of_targets++;
            is_correct_length = 0;
            curr_length = 0;
        }

    }   
    if (number_of_targets == 0) {return;}
    
    /* TARGETLARIN INDEXLERİNİ ARRAYE ATALIM */
    indexs_of_targets = (int*)malloc(number_of_targets*sizeof(int));

    for (i = 0; i < *word_count; i++)
    {
        curr_length = str_length((*document)[i]);
        if (curr_length != target_length) {curr_length = 0; continue;}
        while (((*document)[i][is_correct_length] == target[is_correct_length]) && target[is_correct_length] != '\0')
        {
            is_correct_length++;
        }
        if (is_correct_length == target_length) 
        {
  
            is_correct_length = 0;
            curr_length = 0;
            indexs_of_targets[j] = i;
            j++;
        }

    }  
    /* Elimizde kaç tane target olacağı bilgisi var şimdi buna göre 2 yolumuz var kodu 2ye bölelim */

    if (replacement){ /* TARGET DEĞİŞECEK */

        /* SADECE TARGET DEĞİŞECEKSE YER BOŞALTMAMIZA GEREK YOK */
        /* KELİME SAYISINI DEĞİŞTİRMEMİZE GEREK YOK */
        /* SADECE TARGETIN OLDUĞU İNDEKSLERİN BOYUTUNU DEĞİŞTİRİP, KELİMEYİ DEĞİŞTİRECEĞİZ */
        for (i = 0; i < number_of_targets; i++)
        {
            current_target_index = indexs_of_targets[i];
            while (replacement[replacement_length])
            {
                replacement_length++;
            }
            free((*document)[current_target_index]);
            (*document)[current_target_index] = (char*)malloc((replacement_length+1)*sizeof(char));
            for (k = 0; k <= replacement_length; k++)
            {
                (*document)[current_target_index][k] = replacement[k];
            }
            replacement_length = 0;

            
        }
        free(indexs_of_targets);


    }
    else{ /* TARGETLAR NULL YAPILACAK */
        /* ASIL ZOR KISMA GELDİK: TARGETLAR DİREKT SİLİNCEK */
        /* TARGETTAN SONRAKİ TÜM KELİMELER BİR GERİYE KAYCAK */
        /* HER BİR KAYDIRMADAN SONRA TARGET INDEX ARREYINDAKİ SONRAKİ TÜM INDEXLERİ 1 AZALTARAK YAPABİLİRİM */
        if (number_of_targets == *word_count)
        {
            for (i = 0; i < *word_count; i++)
            {
                free((*document)[i]);
                (*document)[i] = NULL;
            }
            *document = NULL;
            *word_count = 0;
            free(indexs_of_targets);
            return;
        }

        for (i = 0; i < number_of_targets; i++)
        {
            current_target_index = indexs_of_targets[i];
            free((*document)[current_target_index]);
            for (k = current_target_index; k < *word_count - 1; k++)
            {
                (*document)[k] = (*document)[k+1];
            }
            (*word_count)--;
            for (k = i+1; k < number_of_targets; k++)
            {
                indexs_of_targets[k]--;
            }
        }
        *document = (char**)realloc(*document, (*word_count)*sizeof(char*));
        free(indexs_of_targets);





    }
}