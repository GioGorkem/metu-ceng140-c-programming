#ifndef UZAY_FILOSU_H
#define UZAY_FILOSU_H

struct Gemi {
    int id;
    int kalkan;
    struct Gemi *next;
};

typedef struct Gemi NodeGemi;
typedef struct Gemi *Filo;

/* Fonksiyon Imzalari */
Filo gemiUret(int id, int kalkanGucu);
void filoyaKat(Filo *anaKarargah, int id, int kalkanGucu);
void meteorYagmuru(Filo *anaKarargah, int hasarMiktari);
void filoyuYokEt(Filo *anaKarargah);

#endif