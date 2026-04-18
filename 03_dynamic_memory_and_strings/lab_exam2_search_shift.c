#include <stdio.h>
#include <math.h>
#include "lab_2.h"

int findCityIndex(char cityNames[], char target, int count)
{
    /* TODO: Implement with a loop. */
    int i;
    for (i = 0; i < count; i++)
    {
        if (cityNames[i] == target)
        {
            return i;
        }
    }
    return -1;
}

double cumulativeSunsetShift(double dailyChanges[], int day)
{
    /* TODO: Implement with a loop. */
    int i;
    double cumulative_shift = 0.0;
    for (i = 0; i < day; i++)
    {
        cumulative_shift += dailyChanges[i];
    }
    return cumulative_shift; /* I changed 0.0 with cumulative_shift since I define its first value 0.0 */
}

int citySunsetMinutes(int cityMeridian, int cityLatitude,
                      int refMeridian,  int refLatitude,
                      int baseSunsetMins,
                      double dailyChanges[], int day,
                      double timeDifference)
{
    /* TODO: Implement using floor() and computeDaytime(). */
    int refSunset = baseSunsetMins + floor(cumulativeSunsetShift(dailyChanges, day));
    int refSolarNoon = refSunset - ((computeDaytime(refLatitude, timeDifference)/2)*60);
    int citySolarNoon = refSolarNoon - ((cityMeridian - refMeridian)*4);
    int citySunset = citySolarNoon + ((computeDaytime(cityLatitude, timeDifference)/2)*60);
    return citySunset; /* I deleted 0 from return */
}

double computeDaytime(int latitude, double timeDifference)
{
    /* TODO: Implement the daytime formula and clamp to [0, 24]. */
    double daytime = 0.0;
    int l_90 = latitude / 90;
    double diff_time = timeDifference * l_90;
    daytime = 12-diff_time;
    if (daytime < 0)
    {
        return daytime + 24;
    }
    else
    {
        return daytime;
    }
    return daytime; /* I also changed 0.0 with daytime */
}

int atToMinutesAfterSunset(int atHour, int atMinute)
{
    /* TODO: Convert the AT reading to minutes after sunset. */
    return 60*atHour + atMinute;
}

int normalizeAT(int minutes)
{
    /* TODO: Normalize with while loops into [0, 1439]. */
    if (minutes < 0)
    {
        while (minutes < 0)
        {
            minutes += 1440;
        }
    }
    else if (minutes > 1439)
    {
        while (minutes > 1439)
        {
            minutes -= 1444;
        }
    }
    return minutes; /* I also deleted 0 */
}

int minutesToATHour(int normalizedMinutes)
{
    /* TODO: Extract the hour component. */
    return normalizedMinutes / 60;
}

int minutesToATMinute(int normalizedMinutes)
{
    /* TODO: Extract the minute component. */
    
    return (normalizedMinutes-((normalizedMinutes/60)*60));
}

void printATTime(int normalizedMinutes)
{
    /* TODO: Print HH:MM using minutesToATHour() and minutesToATMinute(). */
    printf("%02d:%02d", minutesToATHour(normalizedMinutes), minutesToATMinute(normalizedMinutes));
}

void printClockTime(int absoluteMinutes)
{
    /* TODO: Print an absolute clock time as HH:MM. */
    printf("%02d:%02d", minutesToATHour(absoluteMinutes), minutesToATMinute(absoluteMinutes)); /* !!! I DONT GET WHAT SHOULD I DO */
}

void printSunsetTable(char cityNames[], int meridians[], int latitudes[],
                      int cityCount,
                      int refMeridian,  int refLatitude, int baseSunsetMins,
                      double dailyChanges[], double timeDifferences[],
                      int dayCount)
{
    /* TODO: Print the sunset table with nested loops. */
    int i, j, k, l;
    printf("           %c", cityNames[0]); /* First 11 spaces and first letter */
    
    for (i = 1; i < cityCount; i++)
    {
        if (i == cityCount - 1)
        {
            printf("      %c\n", cityNames[i]);
            break;
        }
        else
        {
            printf("        %c", cityNames[i]); /* second to the last with 8 spaces */
        }
    }
    printf("         ---");
    for (j = 1; j < cityCount; j ++)
    {
        printf("---------");
    }
    printf("------\n");
    
    for (k = 1; k <= dayCount; k++)
    {
        printf("Day%3d:   ", k);
        for (l = 0; l < cityCount; l++)
        {
            int cityMeridian = meridians[l];
            int cityLatitude = latitudes[l];
            int sunset_min = citySunsetMinutes(cityMeridian, cityLatitude, refMeridian, refLatitude, baseSunsetMins, dailyChanges, k, timeDifferences[l]);
            
            if (l == cityCount-1)
            {
                printf("%02d:%02d  \n",minutesToATHour(sunset_min), minutesToATMinute(sunset_min));
                break;
            }
            else
            {
                printf("%02d:%02d    ",minutesToATHour(sunset_min), minutesToATMinute(sunset_min));
            }
        }
    }
    
}

void printDaytimeTable(char cityNames[], int latitudes[], int cityCount,
                       double timeDifferences[], int dayCount)
{
    /* TODO: Print the daytime table with nested loops. */
    int i, j, k, l;
    printf("           %c", cityNames[0]); /* First 11 spaces and first letter */
    
    for (i = 1; i < cityCount; i++)
    {
        if (i == cityCount - 1)
        {
            printf("      %c\n", cityNames[i]);
            break;
        }
        else
        {
            printf("        %c", cityNames[i]); /* second to the last with 8 spaces */
        }
    }
    printf("         ---");
    for (j = 1; j < cityCount; j ++)
    {
        printf("---------");
    }
    printf("------\n");
    
    for (k = 1; k <= dayCount; k++)
    {
        printf("Day%3d:    ", k);
        for (l = 0; l < cityCount; l++)
        {
            int daytime = computeDaytime(latitudes[l], timeDifferences[l]);
            
            if (l == cityCount-1)
            {
                printf("%02dh \n",daytime);
                break;
            }
            else
            {
                printf("%02dh   ",daytime);
            }
        }
    }
    
}

void processQuery(int day, char srcCity, char tgtCity,
                  int atHour, int atMinute,
                  char cityNames[], int meridians[], int latitudes[],
                  int cityCount,
                  int refMeridian, int refLatitude, int baseSunsetMins,
                  double dailyChanges[], double timeDifferences[])
{
    /* TODO: Implement the query conversion and print the result line. */
    int source_city_offset = atToMinutesAfterSunset(atHour, atMinute);
    int source_city_sunset, tgt_city_sunset;
    int i, j;
    int absolute_moment;
    int raw_offset;
    
    
    
    for (i = 0; i < cityCount; i++)
    {
        if (cityNames[i] == srcCity)
        {
            break;
        }
    }
    for (j = 0; j < cityCount; j++)
    {
        if (cityNames[j] == tgtCity)
        {
            break;
        }
    }
    source_city_sunset = citySunsetMinutes(meridians[i], latitudes[i], refMeridian, refLatitude, baseSunsetMins, dailyChanges, day, timeDifferences[i]);
    tgt_city_sunset = citySunsetMinutes(meridians[j], latitudes[j], refMeridian, refLatitude, baseSunsetMins, dailyChanges, day, timeDifferences[j]);
    absolute_moment = source_city_sunset + source_city_offset;
    raw_offset = absolute_moment - tgt_city_sunset;
    raw_offset = normalizeAT(raw_offset);
    printf("Day  %d: City %c AT %02d:%02d  -->  City %c AT %02d:%02d\n", day, srcCity, atHour, atMinute, tgtCity, minutesToATHour(raw_offset), minutesToATMinute(raw_offset));
    
    
}
