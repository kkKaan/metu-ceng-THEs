#ifndef __KPOP_H__
#define __KPOP_H__
#include "music_band.h"


class KPopBand : public MusicBand {
public:
    KPopBand(const char name[], int energy, int talent, int fans) 
        : MusicBand(name, talent, energy, fans) {}

    virtual int play(MusicBand *other) override;
    virtual void rehearse(void) override;
};

#endif