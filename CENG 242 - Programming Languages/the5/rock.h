#ifndef __ROCK_H__
#define __ROCK_H__
#include "music_band.h"


class RockBand : public MusicBand {
public:
    RockBand(const char name[], int energy, int talent, int fans) 
        : MusicBand(name, talent, energy, fans) {}

    virtual int play(MusicBand *other) override;
    virtual void rehearse(void) override;
};

#endif