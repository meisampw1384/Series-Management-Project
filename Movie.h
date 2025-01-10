#ifndef MOVIE_H
#define MOVIE_H
#include <iostream>
#include "Media.h"
using namespace std;

class Movie : public Media
{
private:
    int duration;

public:
    Movie();
    ~Movie();
    Movie(string name, int year, int dur, string country, string gen, string lang, float rate, string plot);
    int getDuration();
    void setDuration(int &value);
};

#endif // MOVIE_H
