#include "LandingSequence.h"

LandingSequence::LandingSequence(const LandingSequence& other)
{
    this->loiter = other.getLoiter();
    this->touchdown = other.getTouchdown();
    this->waypoints = other.getWaypoints();
}

LandingSequence& LandingSequence::operator =(const LandingSequence& other)
{
    this->loiter = other.getLoiter();
    this->touchdown = other.getTouchdown();
    this->waypoints = other.getWaypoints();
}
