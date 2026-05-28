#include <stdio.h>
#include <stdlib.h>
/* Gerekirse <string.h> kullanabilirsin, ancak bu lab string degil struct manipulasyonu uzerinedir. */
#include "sensor_network.h"

/*
====================================================================================
 CENG 140 - C Programming Lab Exam - Advanced Simulation
 "Distributed Sensor Network Aggregation"
====================================================================================

 GENERAL INSTRUCTIONS:
 - You must implement the four C functions described below.
 - Your code must compile with: gcc -ansi -Wall -pedantic-errors -g -O0
 - Use ONLY block comments: (no // comments allowed in C89).
 - Do NOT use global variables.
 - Do NOT use the static keyword for the required functions. You may use static 
   for your own helper functions.
 - Memory leaks are strictly forbidden. valgrind will be used for grading.

====================================================================================
 Task 1: Filter Valid Reads (20 Points)
====================================================================================
 Description:
 You are given an array of raw sensor reads. Some reads contain corrupted data.
 A read is considered INVALID and must be discarded if:
   - timestamp is less than or equal to 0
   - value is less than 0
 
 You must create a new dynamically allocated array containing only the VALID reads.
 The valid reads must remain in the same relative order as they appeared in the 
 raw_data array.
 
 Parameters:
   raw_data: A pointer to the array of raw SensorRead structures.
   raw_count: The number of elements in raw_data.
   out_valid_count: A pointer to an integer. You must store the number of valid 
                    reads you found into this address.

 Returns:
   A pointer to the newly allocated array of valid SensorRead structures.
   If no valid reads are found, set *out_valid_count to 0 and return NULL.
*/
SensorRead* filter_valid_reads(SensorRead* raw_data, int raw_count, int* out_valid_count) {
    /* TODO: KODUNU BURAYA YAZ */
    int i, k = 0;
    SensorRead *valid_data;
    *out_valid_count = 0;
    /*şimdi sadece sayıcaz kaç tane valid data var diye */
    for (i = 0; i < raw_count; i++){
        if (raw_data[i].timestamp > 0 && raw_data[i].value >= 0){
            (*out_valid_count)++;
        }
    }
    if (*out_valid_count == 0) {return NULL;}
    /*şimdi arrayimizi malloclayalım*/
    valid_data = (SensorRead*)malloc((*out_valid_count)*sizeof(SensorRead));

    for (i = 0; i < raw_count; i++){
        if(raw_data[i].timestamp>0 && raw_data[i].value >= 0){
            valid_data[k] = raw_data[i];
            k++;
        }
    }
    

    return valid_data;
}

/*
====================================================================================
 Task 2: Create System Snapshot (40 Points)
====================================================================================
 Description:
 Given a flat array of VALID sensor reads (like the one produced in Task 1), 
 group them into a "SystemSnapshot" by their 'zone' character.

 Rules for grouping and sorting:
 1. The 'zones' array inside SystemSnapshot must be dynamically allocated.
    Its size should be exactly the number of unique zones found in the valid_data.
 2. The 'zones' array must be sorted in DESCENDING order by the zone character.
    (e.g., Zone 'Z' comes before Zone 'C', which comes before Zone 'A').
 3. Inside each ZoneData, the 'reads' array must be dynamically allocated to hold 
    exactly the number of reads belonging to that zone.
 4. The 'reads' array inside each ZoneData must be sorted by timestamp in 
    DESCENDING order (newest data first).
 5. IF two reads in the same zone have the EXACT SAME timestamp, they must be 
    sorted by sensor_id in ASCENDING order (smaller ID first).

 Parameters:
   valid_data: Array of valid SensorRead structures.
   valid_count: Number of elements in valid_data.

 Returns:
   A SystemSnapshot structure containing the correctly grouped and sorted data.
*/
SensorRead *zone_sort(SensorRead *data, int count)
{
    SensorRead *zone_sorted_data;
    int i, j;
    SensorRead temp;

    zone_sorted_data = (SensorRead*)malloc(count*sizeof(SensorRead));
    for (i = 0; i < count; i++){
        zone_sorted_data[i] = data[i];
    }

    for (i = 0; i < count-1; i++){
        for (j = 0; j < count - i - 1; j++){
            /*şimdi timestampe göre sıralayalım ilk sonra döndürüz*/
            if (zone_sorted_data[j].timestamp < zone_sorted_data[j+1].timestamp || 
            (zone_sorted_data[j].timestamp == zone_sorted_data[j+1].timestamp && zone_sorted_data[j].sensor_id > zone_sorted_data[j+1].sensor_id)){
                temp = zone_sorted_data[j];
                zone_sorted_data[j] = zone_sorted_data[j+1];
                zone_sorted_data[j+1] = temp;
            }
        }
    }
    /*şimdi elimizde timestampe göre sıralanmış bir dizi var, bunu zonelara göre sıralarsak elimizde bölge bölge her şey sıralanmış olcak flat bir şekilde*/
    for (i = 0; i < count-1; i++){
        for (j = 0; j < count -i -1; j++){
            if (zone_sorted_data[j].zone < zone_sorted_data[j+1].zone){
                temp = zone_sorted_data[j];
                zone_sorted_data[j] = zone_sorted_data[j+1];
                zone_sorted_data[j+1] = temp;
            }
        }
    }
    return zone_sorted_data;

}
SystemSnapshot create_snapshot(SensorRead* valid_data, int valid_count) {
    SystemSnapshot snap;

    SensorRead *zone_sorted_data;
    int i, j = 0, k = 0;
    int *sensor_num;
    char *sensor_names;
    int anchor = 0;
    snap.num_zones = 0;
    snap.zones = NULL;
    if (valid_data == NULL || valid_count <= 0) { return snap; }
    snap.num_zones = 1;
    /* TODO: KODUNU BURAYA YAZ */

    /*şimdi öncelikle bir helper function tanımlayalım, bize yeni bir array versin valid datayı zonea göre descending sıralasın*/
    zone_sorted_data = zone_sort(valid_data, valid_count);
    /*Şu an elimizde mesela A A A B B C C C C var ve Alar Bler Cler kendi içinde timestampe göre sıralı*/
    /*şimdi kaç tane zone olduğunu sayıcaz*/
    for (i = 0; i < valid_count - 1; i++){
        if (zone_sorted_data[i].zone != zone_sorted_data[i+1].zone){
            (snap.num_zones)++;
        }
    }
    /*zone sayısını bulduğumuza göre zones u allocate edebiliriz*/
    snap.zones = (ZoneData*)malloc(snap.num_zones*sizeof(ZoneData));
    /*şimdi zonesın içindeki her bir bölgenin readlarını mı allocate etsek*/
    /*allocate edemem çünkü her bir zonedan kaç tane var bilmem lazım*/
    /*bunu bir array tanımlayarak yapmak istiyorum*/
    sensor_num = (int*)malloc(snap.num_zones*sizeof(int));
    sensor_names = (char*)malloc(snap.num_zones*sizeof(char));


    for (i = 0; i < valid_count; i++){
        if (zone_sorted_data[anchor].zone != zone_sorted_data[i].zone){
            sensor_names[j] = zone_sorted_data[anchor].zone;
            sensor_num[j] = i - anchor;
            anchor = i;
            j++;
        }
    }
    sensor_names[j] = zone_sorted_data[anchor].zone;
    sensor_num[j] = i - anchor;

    /*şimdi her bir zoneda kaç tane sensor var biliyoruz, allocate edebiliriz readsleri*/
    for (i = 0; i < snap.num_zones; i++){
        snap.zones[i].reads = (SensorRead*)malloc(sensor_num[i]*sizeof(SensorRead));
    }
    /*şimdi dizimizi okicaz, okurken farklı zone görünce iç döngü 0lancak ama koşucu kmız 0lanmicak*/
    for (i = 0; i < snap.num_zones; i++){
        for (j = 0; j < sensor_num[i]; j++, k++){
            snap.zones[i].reads[j] = zone_sorted_data[k];
        }
    }
    /*şimdi zoneslarımızın hepsinin içini dolduruyoruz*/
    for (i = 0; i < snap.num_zones; i++){
        snap.zones[i].zone = sensor_names[i];
        snap.zones[i].num_reads = sensor_num[i];
    }

    free(sensor_num);
    free(zone_sorted_data);
    free(sensor_names);
    return snap;
}

/*
====================================================================================
 Task 3: Merge Snapshots (40 Points)
====================================================================================
 Description:
 You are given two separate SystemSnapshot structures representing data gathered 
 from different networks. You need to combine them into a single, unified 
 SystemSnapshot.

 Rules for merging:
 1. The resulting snapshot must contain all unique zones from both s1 and s2.
 2. The resulting 'zones' array must maintain the DESCENDING zone character sorting 
    rule defined in Task 2.
 3. The 'reads' within each merged zone must also maintain the multi-level sorting 
    rule (timestamp DESCENDING, then sensor_id ASCENDING).
 4. DUPLICATE PREVENTION: If both snapshots contain a read in the same zone with 
    the EXACT SAME timestamp AND the EXACT SAME sensor_id, it is a duplicate. 
    You must keep only ONE copy of this read in the merged result. 
    (The 'value' of the duplicate can be taken from either snapshot, assume they 
    are identical for the same timestamp and sensor_id).
 5. The original snapshots (s1 and s2) must NOT be modified or freed inside this 
    function. Create entirely new dynamic arrays for the merged result.

 Parameters:
   s1: The first snapshot.
   s2: The second snapshot.

 Returns:
   A completely new SystemSnapshot containing the merged, sorted, and unique data.
*/
SystemSnapshot merge_snapshots(SystemSnapshot s1, SystemSnapshot s2) {
    SystemSnapshot merged;
    int total_reads_estimate = 0;
    SensorRead* flat_pool = NULL;
    int pool_count = 0;
    int i, j, k;
    int is_duplicate;

    merged.num_zones = 0;
    merged.zones = NULL;

    /* Count total potential reads to allocate a flat buffer */
    for (i = 0; i < s1.num_zones; i++) {
        total_reads_estimate += s1.zones[i].num_reads;
    }
    for (i = 0; i < s2.num_zones; i++) {
        total_reads_estimate += s2.zones[i].num_reads;
    }

    if (total_reads_estimate == 0) {
        return merged;
    }

    flat_pool = (SensorRead*)malloc(total_reads_estimate * sizeof(SensorRead));
    if (flat_pool == NULL) {
        return merged;
    }

    /* Add all reads from s1 */
    for (i = 0; i < s1.num_zones; i++) {
        for (j = 0; j < s1.zones[i].num_reads; j++) {
            flat_pool[pool_count] = s1.zones[i].reads[j];
            flat_pool[pool_count].zone = s1.zones[i].zone;
            pool_count++;
        }
    }

    /* Add reads from s2, avoiding duplicates (same zone, timestamp, sensor_id) */
    for (i = 0; i < s2.num_zones; i++) {
        for (j = 0; j < s2.zones[i].num_reads; j++) {
            SensorRead r2 = s2.zones[i].reads[j];
            r2.zone = s2.zones[i].zone;
            is_duplicate = 0;
            for (k = 0; k < pool_count; k++) {
                if (flat_pool[k].zone == r2.zone &&
                    flat_pool[k].timestamp == r2.timestamp &&
                    flat_pool[k].sensor_id == r2.sensor_id) {
                    is_duplicate = 1;
                    break;
                }
            }
            if (!is_duplicate) {
                flat_pool[pool_count++] = r2;
            }
        }
    }

    /* create_snapshot creates the structured, grouped, and sorted snapshot */
    merged = create_snapshot(flat_pool, pool_count);

    free(flat_pool);
    return merged;
}

void free_snapshot(SystemSnapshot* snapshot) {
    int i;
    if (snapshot == NULL) {
        return;
    }
    if (snapshot->zones != NULL) {
        for (i = 0; i < snapshot->num_zones; i++) {
            if (snapshot->zones[i].reads != NULL) {
                free(snapshot->zones[i].reads);
                snapshot->zones[i].reads = NULL;
            }
        }
        free(snapshot->zones);
        snapshot->zones = NULL;
    }
    snapshot->num_zones = 0;
}
