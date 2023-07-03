#ifndef __METAL_H__
#define __METAL_H__
#include "music_band.h"


class MetalBand : public MusicBand {
public:
    MetalBand(const char name[], int energy, int talent, int fans) 
        : MusicBand(name, talent, energy, fans) {}

    virtual int play(MusicBand *other) override;
    virtual void rehearse(void) override;
};

#endif