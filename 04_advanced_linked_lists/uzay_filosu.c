#include <stdio.h>
#include <stdlib.h>
#include "uzay_filosu.h"

/* TODO: Task 1 - Yeni Gemi Uret (mknode)
 * Heap bellekte yeni bir struct Gemi yarat.
 * id ve kalkanGucu'nu yerlestir, next'ini NULL yap ve dondur.
 */
Filo gemiUret(int id, int kalkanGucu)
{
    Filo yeniGemi;
    /* Kodlarini buraya yaz */
    yeniGemi = (Filo)malloc(sizeof(struct Gemi));
    yeniGemi->id = id;
    yeniGemi->kalkan = kalkanGucu;
    yeniGemi->next = NULL;

    return yeniGemi;
}

/* TODO: Task 2 - Filoya Kat (Sirali Ekleme)
 * Yeni gemiyi filoya ekle. Kural su:
 * Filodaki gemiler kalkan gucune gore BUYUKTEN KUCUGE (Azalan) siralanmalidir.
 * En guclu kalkan en basta olmali. Eger kalkanlar esitse, id'si kucuk olan onde olsun.
 * Ipuclari: Liste bossa, yeni gemi basa gececekse Double Pointer (**anaKarargah) gucunu kullan!
 */
void filoyaKat(Filo *anaKarargah, int id, int kalkanGucu)
{
    Filo yeniGemi;
    Filo gecici;
    Filo prev;
    /* Kodlarini buraya yaz */
    yeniGemi = gemiUret(id, kalkanGucu);

    if (yeniGemi == NULL)
    {
        return;
    }

    if (*anaKarargah == NULL ||
        kalkanGucu > (*anaKarargah)->kalkan ||
        (kalkanGucu == (*anaKarargah)->kalkan && id < (*anaKarargah)->id))
    {

        yeniGemi->next = *anaKarargah;
        (*anaKarargah) = yeniGemi;
    }
    else
    {
        gecici = *anaKarargah;
        prev = NULL;

        while (gecici != NULL)
        {

            if (kalkanGucu > gecici->kalkan ||
                (kalkanGucu == gecici->kalkan && id < gecici->id))
            {
                break;
            }
            prev = gecici;
            gecici = gecici->next;
        }

        prev->next = yeniGemi;
        yeniGemi->next = gecici;
    }
}

/* TODO: Task 3 - BOMBA GOREV: Meteor Yagmuru (Eleman Guncelleme ve Silme)
 * Filodaki TUM gemilerin kalkan gucunden 'hasarMiktari'ni cikar.
 * Eger bir geminin kalkani 0 veya daha eksi bir degere duserse, o gemi PATLAMISTIR.
 * O gemiyi listeden tamamen cikar (Shift yap) ve free ile bellekten sil!
 * DİKKAT: Bastaki gemi de patlayabilir, aradaki gemi de!
 * Aradaki gemiyi silerken koptugu yeri dikmeyi (prev->next = silinecek->next) unutma!
 */
void meteorYagmuru(Filo *anaKarargah, int hasarMiktari)
{
    Filo gecici;
    Filo onceki = NULL;
    Filo silinecek = NULL;

    if (anaKarargah == NULL || *anaKarargah == NULL) {
        return;
    }

    gecici = *anaKarargah;
    while (gecici != NULL) {
        gecici->kalkan -= hasarMiktari;
        if (gecici->kalkan <= 0) {
            silinecek = gecici;
            if (onceki == NULL) {
                *anaKarargah = gecici->next;
                gecici = *anaKarargah;
            } else {
                onceki->next = gecici->next;
                gecici = onceki->next;
            }
            free(silinecek);
        } else {
            onceki = gecici;
            gecici = gecici->next;
        }
    }
}

void filoyuYokEt(Filo *anaKarargah)
{
    Filo gecici;
    Filo silinecek;

    if (anaKarargah == NULL || *anaKarargah == NULL) {
        return;
    }

    gecici = *anaKarargah;
    while (gecici != NULL) {
        silinecek = gecici;
        gecici = gecici->next;
        free(silinecek);
    }
    *anaKarargah = NULL;
}
