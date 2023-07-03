#ifndef __JAZZ_H__
#define __JAZZ_H__
#include "music_band.h"


class JazzBand : public MusicBand {
public:
    JazzBand(const char name[], int energy, int talent, int fans) 
        : MusicBand(name, talent, energy, fans) {}

    virtual int play(MusicBand *other) override;
    virtual void rehearse(void) override;
};

#endif