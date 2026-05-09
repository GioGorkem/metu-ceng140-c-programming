#include <stdio.h>
#include <stdlib.h>
#include "lab_ring.h"

/* TODO: Task 1 - mknode Felsefesi 
 * 'durakYarat' fonksiyonu, Heap bellekte yepyeni bir 'struct Durak' adasi yaratmalidir.
 * Parametre olarak gelen id ve yolcu sayisini yerlestir.
 * next pusulasini NULL ile muhurle ve adanin baslangic adresini dondur.
 * malloc basarisiz olursa NULL dondur.
 */
RingGuzergahi durakYarat(int id, int yolcu) {
    /* ANSI C Kurali: Degiskenler her zaman blogun en ustunde tanimlanir! */
    RingGuzergahi yeniAda;
    
    /* Kodlarini buraya yaz */
    yeniAda = (RingGuzergahi)malloc(sizeof(NodeElem));
    if (yeniAda != NULL){
        yeniAda->durakID = id;
        yeniAda->bekleyenYolcu = yolcu;
        yeniAda->next = NULL;
        return yeniAda;
    }


    return NULL; 
}

/* TODO: Task 2 - Sona Eleman Ekleme ve Double Pointer 
 * 'guzergahaEkle' fonksiyonu, mevcut ring guzergahinin EN SONUNA yeni bir durak ekler.
 * Gelen 'baslangicAdresi' bir Double Pointer'dir.
 * Liste bossa yeni duragi dogrudan baslangic (Head) yap.
 * Liste doluysa, listenin sonuna kadar yuruyup sona ekle.
 */
void guzergahaEkle(RingGuzergahi *baslangicAdresi, int id, int yolcu) {
    /* ANSI C Kurali: Degiskenler her zaman blogun en ustunde tanimlanir! */
    RingGuzergahi yeniAda;

    
    /* Kodlarini buraya yaz */
    if (*baslangicAdresi == NULL){
        yeniAda = (RingGuzergahi)malloc(sizeof(NodeElem));
        (*baslangicAdresi) = yeniAda;
        yeniAda->bekleyenYolcu = yolcu;
        yeniAda->durakID = id;
        yeniAda->next = NULL;
    }
    else{
        guzergahaEkle(&((*baslangicAdresi)->next),id,yolcu);
    }
}

/* TODO: Task 3 - Heap Temizligi ve Dangling Pointer
 * Tum bagli listeyi dugum dugum gezip 'free' ile isletim sistemine iade et.
 * Islem bittiginde ana baslangic pointer'ini kalici olarak NULL yap.
 */
void guzergahiTemizle(RingGuzergahi *baslangicAdresi) {
    /* ANSI C Kurali: Degiskenler her zaman blogun en ustunde tanimlanir! */
    RingGuzergahi gecici;
    RingGuzergahi silinecek;
    
    /* Kodlarini buraya yaz */
    gecici = *baslangicAdresi;
    while (gecici != NULL){
        silinecek = gecici;
        gecici = gecici->next;
        free(silinecek);
        silinecek = NULL;
    }
    (*baslangicAdresi) = NULL;
}