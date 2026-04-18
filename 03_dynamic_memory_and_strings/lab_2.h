#ifndef LAB_2_H
#define LAB_2_H

int findCityIndex(char cityNames[], char target, int count);
double cumulativeSunsetShift(double dailyChanges[], int day);
int citySunsetMinutes(int cityMeridian, int cityLatitude,
                      int refMeridian,  int refLatitude,
                      int baseSunsetMins,
                      double dailyChanges[], int day,
                      double timeDifference);
double computeDaytime(int latitude, double timeDifference);
int atToMinutesAfterSunset(int atHour, int atMinute);
int normalizeAT(int minutes);
int minutesToATHour(int normalizedMinutes);
int minutesToATMinute(int normalizedMinutes);
void printATTime(int normalizedMinutes);
void printClockTime(int absoluteMinutes);
void printSunsetTable(char cityNames[], int meridians[], int latitudes[],
                      int cityCount,
                      int refMeridian,  int refLatitude, int baseSunsetMins,
                      double dailyChanges[], double timeDifferences[],
                      int dayCount);
void printDaytimeTable(char cityNames[], int latitudes[], int cityCount,
                       double timeDifferences[], int dayCount);
void processQuery(int day, char srcCity, char tgtCity,
                  int atHour, int atMinute,
                  char cityNames[], int meridians[], int latitudes[],
                  int cityCount,
                  int refMeridian, int refLatitude, int baseSunsetMins,
                  double dailyChanges[], double timeDifferences[]);

#endif
