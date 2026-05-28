#include <stdio.h>
#include <stdlib.h>
#include "sensor_network.h"

/* --- YARDIMCI TEST FONKSIYONLARI --- */
void print_test_result(int task_num, int passed, const char* msg) {
    if (passed) {
        printf("[TASK %d] BASARILI: %s\n", task_num, msg);
    } else {
        printf("[TASK %d] BASARISIZ: %s\n", task_num, msg);
    }
}

int check_task1() {
    int passed = 1;
    int out_count = 0;
    SensorRead* result;
    
    SensorRead raw[5];
    raw[0].timestamp = 10; raw[0].sensor_id = 1; raw[0].value = 50; raw[0].zone = 'A';
    raw[1].timestamp = -5; raw[1].sensor_id = 2; raw[1].value = 40; raw[1].zone = 'B'; /* Gecersiz timestamp */
    raw[2].timestamp = 20; raw[2].sensor_id = 3; raw[2].value = -10; raw[2].zone = 'A'; /* Gecersiz value */
    raw[3].timestamp = 30; raw[3].sensor_id = 4; raw[3].value = 0; raw[3].zone = 'C';
    raw[4].timestamp = 0;  raw[4].sensor_id = 5; raw[4].value = 10; raw[4].zone = 'B'; /* Gecersiz timestamp */
    
    printf("--- TASK 1 TESTI BASLIYOR ---\n");
    result = filter_valid_reads(raw, 5, &out_count);
    
    if (out_count != 2) {
        print_test_result(1, 0, "Gecerli eleman sayisi yanlis hesaplandi (Beklenen: 2).");
        passed = 0;
    } else if (result == NULL) {
        print_test_result(1, 0, "NULL pointer dondu.");
        passed = 0;
    } else {
        if (result[0].sensor_id != 1 || result[1].sensor_id != 4) {
            print_test_result(1, 0, "Dizideki elemanlar yanlis veya sirasi bozulmus.");
            passed = 0;
        } else {
            print_test_result(1, 1, "Filtreleme ve dinamik bellek tahsisi dogru.");
        }
    }
    
    if (result) free(result);
    return passed;
}

int check_task2() {
    int passed = 1;
    SystemSnapshot snap;
    SensorRead data[6];
    
    /* Karisik veriler */
    data[0].timestamp = 10; data[0].sensor_id = 2; data[0].value = 100; data[0].zone = 'B';
    data[1].timestamp = 20; data[1].sensor_id = 1; data[1].value = 200; data[1].zone = 'A';
    data[2].timestamp = 10; data[2].sensor_id = 1; data[2].value = 300; data[2].zone = 'B';
    data[3].timestamp = 30; data[3].sensor_id = 3; data[3].value = 400; data[3].zone = 'C';
    data[4].timestamp = 30; data[4].sensor_id = 4; data[4].value = 500; data[4].zone = 'A';
    data[5].timestamp = 30; data[5].sensor_id = 2; data[5].value = 600; data[5].zone = 'A';
    
    printf("--- TASK 2 TESTI BASLIYOR ---\n");
    snap = create_snapshot(data, 6);
    
    if (snap.num_zones != 3) {
        print_test_result(2, 0, "Zone sayisi yanlis (Beklenen: 3).");
        passed = 0;
    } else if (snap.zones == NULL) {
        print_test_result(2, 0, "Zones dizisi icin bellek ayrilmamis.");
        passed = 0;
    } else {
        /* Bolgeler Buyukten Kucuge (Desc) Sirali mi? C, B, A olmali */
        if (snap.zones[0].zone != 'C' || snap.zones[1].zone != 'B' || snap.zones[2].zone != 'A') {
            print_test_result(2, 0, "Bolgeler (Zone) harf sirasina gore ters (Z-A) siralanmamis.");
            passed = 0;
        } else {
            /* Bolge A icindeki siralamayi kontrol et. Beklenen sensor_id sirasi: 2, 4, 1 
               (Cunku ts=30 (id=2), ts=30 (id=4), ts=20 (id=1). 
               Ayni ts'de sensor id'si KUCUK olan once gelir.) */
            ZoneData zoneA = snap.zones[2];
            if (zoneA.num_reads != 3) {
                print_test_result(2, 0, "A bolgesinin okuma sayisi yanlis.");
                passed = 0;
            } else if (zoneA.reads[0].sensor_id != 2 || 
                       zoneA.reads[1].sensor_id != 4 || 
                       zoneA.reads[2].sensor_id != 1) {
                print_test_result(2, 0, "Bolge icindeki siralama hatali! (Zaman buyukten kucuge, esitse sensor_id kucukten buyuge olmali).");
                passed = 0;
            } else {
                print_test_result(2, 1, "Snapshot olusturma, gruplama ve coklu siralama harika!");
            }
        }
    }
    
    /* Task 4 burada test ediliyor, memory leak olmamasi icin q.c de dogru yazilmis olmali */
    free_snapshot(&snap);
    return passed;
}

int check_task3() {
    int passed = 1;
    SystemSnapshot s1, s2, merged;
    /* Elle Manuel Snapshot S1 Olusturma */
    s1.num_zones = 1;
    s1.zones = (ZoneData*)malloc(sizeof(ZoneData) * 1);
    s1.zones[0].zone = 'A';
    s1.zones[0].num_reads = 2;
    s1.zones[0].reads = (SensorRead*)malloc(sizeof(SensorRead) * 2);
    s1.zones[0].reads[0].timestamp = 50; s1.zones[0].reads[0].sensor_id = 1; s1.zones[0].reads[0].value = 10;
    s1.zones[0].reads[1].timestamp = 40; s1.zones[0].reads[1].sensor_id = 2; s1.zones[0].reads[1].value = 20;
    
    /* Elle Manuel Snapshot S2 Olusturma */
    s2.num_zones = 2;
    s2.zones = (ZoneData*)malloc(sizeof(ZoneData) * 2);
    s2.zones[0].zone = 'B';
    s2.zones[0].num_reads = 1;
    s2.zones[0].reads = (SensorRead*)malloc(sizeof(SensorRead) * 1);
    s2.zones[0].reads[0].timestamp = 100; s2.zones[0].reads[0].sensor_id = 5; s2.zones[0].reads[0].value = 55;
    
    s2.zones[1].zone = 'A';
    s2.zones[1].num_reads = 2;
    s2.zones[1].reads = (SensorRead*)malloc(sizeof(SensorRead) * 2);
    /* Cakisik veri (Duplicate) - S1'de de var */
    s2.zones[1].reads[0].timestamp = 50; s2.zones[1].reads[0].sensor_id = 1; s2.zones[1].reads[0].value = 99; 
    /* Yeni veri */
    s2.zones[1].reads[1].timestamp = 60; s2.zones[1].reads[1].sensor_id = 3; s2.zones[1].reads[1].value = 30; 

    printf("--- TASK 3 TESTI BASLIYOR ---\n");
    merged = merge_snapshots(s1, s2);
    
    if (merged.num_zones != 2) {
        print_test_result(3, 0, "Merge sonrasi zone sayisi hatali (Beklenen: 2 -> A ve B).");
        passed = 0;
    } else {
        /* B ve A olmali (Ters Sirali) */
        if (merged.zones[0].zone != 'B' || merged.zones[1].zone != 'A') {
            print_test_result(3, 0, "Merge sonrasi zone sirasi hatali (B, sonra A gelmeli).");
            passed = 0;
        } else {
            ZoneData zoneA = merged.zones[1];
            if (zoneA.num_reads != 3) { /* Duplicate silinmeli, toplam 4 veri vardi 3 kalmali */
                print_test_result(3, 0, "Cakisan (Duplicate) veriler dogru temizlenmemis veya eksik kopyalanmis.");
                passed = 0;
            } else if (zoneA.reads[0].timestamp != 60 || 
                       zoneA.reads[1].timestamp != 50 || 
                       zoneA.reads[2].timestamp != 40) {
                print_test_result(3, 0, "Merge edilmis bolge icerisindeki siralama kurali bozulmus.");
                passed = 0;
            } else {
                print_test_result(3, 1, "Zorlu Merge operasyonu basarili!");
            }
        }
    }
    
    /* Temizlik */
    free(s1.zones[0].reads); free(s1.zones);
    free(s2.zones[0].reads); free(s2.zones[1].reads); free(s2.zones);
    free_snapshot(&merged); /* Senin fonksiyonunla temizle */
    
    return passed;
}

int main() {
    int score = 0;
    printf("==========================================\n");
    printf("  CENG 140 - ADVANCED PRELIM SIMULATION   \n");
    printf("==========================================\n\n");
    
    if (check_task1()) score += 20;
    printf("\n");
    
    if (check_task2()) score += 40;
    printf("\n");
    
    if (check_task3()) score += 40;
    printf("\n");
    
    /* Task 4 ayri puanlanmiyor, memory leak yapmamasi Valgrind ile olculecek */
    printf("Note: Task 4 (free_snapshot) verified inside test suites.\n");
    printf("Core dumps indicate issues in pointer management or dynamic allocation.\n");
    printf("Run with 'valgrind --leak-check=full' for memory leak validation.\n\n");
    
    printf("Test Suite Score: %d / 100\n", score);
    printf("==========================================\n");
    
    return 0;
}