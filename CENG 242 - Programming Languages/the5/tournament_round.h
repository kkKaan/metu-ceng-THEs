#ifndef __TOURNAMENT_ROUND_H__
#define __TOURNAMENT_ROUND_H__
#include "music_band.h"


class TournamentRound {
    std::list<MusicBand*> bands;
    public:
    TournamentRound();
    TournamentRound(std::vector<MusicBand*>_bands);
    TournamentRound(std::list<MusicBand*>_bands);
    std::size_t size();
    
    TournamentRound(TournamentRound& other) : bands(other.bands) { }
    TournamentRound(TournamentRound&& other) : bands(std::move(other.bands)) { }

    TournamentRound& operator=(TournamentRound&& other);
    TournamentRound& get_next_round(); 

    friend std::ostream& operator<< (std::ostream &os, TournamentRound &other);

};

#endif