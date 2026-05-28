#ifndef Q_H
#define Q_H

#include <stdlib.h>

/* Bir sensörden gelen tekil okuma verisi */
typedef struct {
    int timestamp;   /* Zaman damgası (büyük olan daha güncel) */
    int sensor_id;   /* Sensörün benzersiz numarası */
    int value;       /* Okunan değer */
    char zone;       /* Sensörün bulunduğu bölge (Örn: 'A', 'B', 'Z') */
} SensorRead;

/* Belirli bir bölgeye ait tüm okumaların toplandığı yapı */
typedef struct {
    char zone;           /* Bölge harfi */
    int num_reads;       /* Bu bölgedeki okuma sayısı */
    SensorRead* reads;   /* Bu bölgeye ait dinamik okuma dizisi */
} ZoneData;

/* Tüm sistemin anlık durumunu tutan çatı yapı */
typedef struct {
    int num_zones;       /* Sistemdeki toplam benzersiz bölge sayısı */
    ZoneData* zones;     /* Dinamik bölgeler dizisi */
} SystemSnapshot;

/* UYGULAMAN GEREKEN FONKSİYONLARIN PROTOTİPLERİ */

/* Task 1 */
SensorRead* filter_valid_reads(SensorRead* raw_data, int raw_count, int* out_valid_count);
SensorRead *zone_sort(SensorRead *data, int count);
/* Task 2 */
SystemSnapshot create_snapshot(SensorRead* valid_data, int valid_count);

/* Task 3 */
SystemSnapshot merge_snapshots(SystemSnapshot s1, SystemSnapshot s2);

/* Task 4 */
void free_snapshot(SystemSnapshot* snapshot);

#endif