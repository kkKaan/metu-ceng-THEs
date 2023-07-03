#ifndef __TOURNAMENT_H__
#define __TOURNAMENT_H__
#include <vector>
#include "music_band.h"

class Tournament {
    private:
        std::vector<MusicBand *>bands;

    public:
        Tournament();
        void enroll(MusicBand&team);
        void make_tournament();
};

#endif