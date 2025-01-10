#include "Series.h"

Series::Series() {
    
}

Series::Series(string name, int year, int episodeDur, string country, string gen, string lang, float rate, string plot, int seasons, int episodes)
    : Media(name, year, country, gen, lang, rate, plot), episodeDuration(episodeDur), numberOfSeasons(seasons), numberOfEpisodes(episodes) {}

Series::~Series() {
    
}

int Series::getEpisodeDuration() {
    return episodeDuration;
}
void Series::setEpisodeDuration(int& value) {
    episodeDuration = value;
}
int Series::getNumberOfSeasons() {
    return numberOfSeasons;
}
void Series::setNumberOfSeasons(int& value) {
    numberOfSeasons = value;
}
int Series::getNumberOfEpisodes() {
    return numberOfEpisodes;
}
void Series::setNumberOfEpisodes(int& value) {
    numberOfEpisodes = value;
}
