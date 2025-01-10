#ifndef SERIES_H
#define SERIES_H
#include "Media.h"

class Series : public Media
{
private:
    int episodeDuration;
    int numberOfSeasons;
    int numberOfEpisodes;

public:
    Series();
    Series(string name, int year, int episodeDur, string country, string gen, string lang, float rate, string plot, int seasons, int episodes);
    int getEpisodeDuration();
    void setEpisodeDuration(int &value);
    int getNumberOfSeasons();
    void setNumberOfSeasons(int &value);
    int getNumberOfEpisodes();
    void setNumberOfEpisodes(int &value);
    ~Series();
};

#endif // SERIES_H
