#include "Movie.h"

Movie::Movie()
{
}
Movie::Movie(string name, int year, int dur, string country, string gen, string lang, float rate, string plot)
    : Media(name, year, country, gen, lang, rate, plot), duration(dur) {}

Movie::~Movie()
{
}
int Movie::getDuration()
{
    return duration;
}
void Movie::setDuration(int &value)
{
    duration = value;
}
