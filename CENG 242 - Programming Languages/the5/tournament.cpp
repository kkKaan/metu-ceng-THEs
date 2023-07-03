#include "tournament.h"
#include "music_band.h"
#include "tournament_round.h"

Tournament::Tournament()
{
}

void Tournament::enroll(MusicBand&team) 
{ 
    bands.push_back(&team);
}

void Tournament::make_tournament() 
{
    TournamentRound current_bands(bands);
    TournamentRound rounds;
    int round_number = 1;

    std::cout << "printing round " << round_number++ << std::endl  
                                   << current_bands << std::endl;
    while (current_bands.size() > 1) {
        current_bands = std::move(current_bands.get_next_round());
        std::cout << "printing round " << round_number++ << std::endl 
                                       << current_bands << std::endl;
    }
}