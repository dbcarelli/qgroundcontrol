#include "LandingSequence.h"

LandingSequence::LandingSequence(const LandingSequence& other)
{
    this->loiter = other.getLoiter();
    this->touchdown = other.getTouchdown();
    this->waypoints = other.getWaypoints();
    this->id = other.getID();
    this->description = other.getDescription();
}

LandingSequence& LandingSequence::operator =(const LandingSequence& other)
{
    this->loiter = other.getLoiter();
    this->touchdown = other.getTouchdown();
    this->waypoints = other.getWaypoints();
    this->id = other.getID();
    this->description = other.getDescription();
}

