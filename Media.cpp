
#include "Media.h"

Media::Media()
{
}

Media::~Media()
{
}

Media::Media(string _name, int year, string country, string gen, string lang, float rate, string plot)
    : name(_name), releaseYear(year), countryOfOrigin(country), genre(gen), language(lang), rating(rate), plotSummary(plot) {}

string Media::getName()
{
    return name;
}
void Media::setName(string &value)
{
    name = value;
}
int Media::getReleaseYear()
{
    return releaseYear;
}
void Media::setReleaseYear(int &value)
{
    releaseYear = value;
}
string Media::getCountryOfOrigin()
{
    return countryOfOrigin;
}
void Media::setCountryOfOrigin(string &value)
{
    countryOfOrigin = value;
}
string Media::getGenre()
{
    return genre;
}
void Media::setGenre(string &value)
{
    genre = value;
}
string Media::getLanguage()
{
    return language;
}
void Media::setLanguage(string &value)
{
    language = value;
}
float Media::getRating()
{
    return rating;
}
void Media::setRating(float &value)
{
    rating = value;
}
string Media::getPlotSummary()
{
    return plotSummary;
}
void Media::setPlotSummary(string &value)
{
    plotSummary = value;
}
