#ifndef MEDIA_H
#define MEDIA_H
#include <iostream>
using namespace std;

class Media
{
protected:
    string name;
    int releaseYear;
    string countryOfOrigin;
    string genre;
    string language;
    float rating;
    string plotSummary;

public:
    Media();
    Media(string _name, int year, string country, string gen, string lang, float rate, string plot);
    virtual ~Media();
    string getName();
    void setName(string &value);
    int getReleaseYear();
    void setReleaseYear(int &value);
    string getCountryOfOrigin();
    void setCountryOfOrigin(string &value);
    string getGenre();
    void setGenre(string &value);
    string getLanguage();
    void setLanguage(string &value);
    float getRating();
    void setRating(float &value);
    string getPlotSummary();
    void setPlotSummary(string &value);
    virtual void displayInfo() = 0;
};

#endif
