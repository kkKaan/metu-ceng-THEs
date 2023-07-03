#include "tournament_round.h"

TournamentRound::TournamentRound() { }

TournamentRound::TournamentRound(std::list<MusicBand*> _bands)
{
    this->bands = _bands;
}

TournamentRound::TournamentRound(std::vector<MusicBand*> _bands)
{
    for(auto band: _bands)
    {
        this->bands.push_back(band);
    }
}

std::size_t TournamentRound::size()
{
    return this->bands.size();
}

// TournamentRound::TournamentRound(TournamentRound& other)
// {
//     this->bands = other.bands;
// }

// TournamentRound::TournamentRound(TournamentRound&& other)
// {
//     this->bands = std::move(other.bands);
// }

TournamentRound& TournamentRound::operator=(TournamentRound&& other)
{
    if (this != &other)
    {
        this->bands = std::move(other.bands);
    }
    return *this;
}

TournamentRound& TournamentRound::get_next_round()
{
    std::list<MusicBand*> new_bands;

    while(this->bands.size() > 1)
    {
        auto front_band = this->bands.front();
        auto back_band = this->bands.back();
        
        int score1 = front_band->play(back_band);
        int score2 = back_band->play(front_band);

        MusicBand* winner;
        MusicBand* loser;

        int fan_change = 0;
        
        if (score1 >= score2)
        {
            winner = front_band;
            loser = back_band;
            fan_change = std::min(loser->get_fan_count(), abs(score1 - score2));

            if(score2 == 0)
            {
                fan_change = back_band->get_fan_count();
            }
        }
        else
        {
            winner = back_band;
            loser = front_band;
            fan_change = std::min(loser->get_fan_count(), abs(score1 - score2));

            if(score1 == 0)
            {
                fan_change = front_band->get_fan_count();
            }
        }

        winner->set_fan_count(winner->get_fan_count() + fan_change);
        loser->set_fan_count(loser->get_fan_count() - fan_change);

        new_bands.push_back(winner);

        this->bands.pop_front();
        this->bands.pop_back();
    }

    if(!bands.empty())
    {
        new_bands.push_back(bands.front());
    }

    TournamentRound* new_round = new TournamentRound(new_bands);
    return *new_round;
}


std::ostream& operator<< (std::ostream &os, TournamentRound &other)
{
    for(auto band: other.bands)
    {
        if(band != other.bands.back())  os << band->get_name() << "\t";
        else os << band->get_name();
    }
    return os;
}
