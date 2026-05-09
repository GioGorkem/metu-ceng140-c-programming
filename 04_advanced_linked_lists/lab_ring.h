#ifndef LAB_RING_H
#define LAB_RING_H

struct Durak {
    int durakID;
    int bekleyenYolcu;
    struct Durak *next;
};

typedef struct Durak NodeElem;
typedef struct Durak *RingGuzergahi;

/* Fonksiyon Imzalari */
RingGuzergahi durakYarat(int id, int yolcu);
void guzergahaEkle(RingGuzergahi *baslangicAdresi, int id, int yolcu);
void guzergahiTemizle(RingGuzergahi *baslangicAdresi);

#endif