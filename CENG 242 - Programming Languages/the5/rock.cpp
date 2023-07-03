#include "rock.h"
#include "kpop.h"
#include "metal.h"
#include "jazz.h"

int RockBand::play(MusicBand *other)
{
    if(this->get_energy() < 0.1 * this->get_energy())
    {
        return 0;
    }

    double con = 0;

    if (dynamic_cast<KPopBand*>(other) != nullptr)
    {
        con = 0.5;
    }
    else if (dynamic_cast<MetalBand*>(other) != nullptr)
    {
        con = 1.4;
    }
    else if (dynamic_cast<RockBand*>(other) != nullptr)
    {
        con = 1;
    }
    else if (dynamic_cast<JazzBand*>(other) != nullptr)
    {
        con = 0.8;
    }

    int score = (this->get_fan_count() + 0.1 * this->get_talent() * this->get_energy()) * con;

    int remNrg = this->get_energy() - this->get_energy() * 0.1;
    this->set_energy(remNrg);

    return score;
}

void RockBand::rehearse(void) 
{
    if(this->get_energy() < 0.5 * 0.1 *this->get_energy())
    {
        return;
    }

    int remNrg = this->get_energy() - this->get_energy() * 0.5 * 0.1;
    this->set_energy(remNrg);

    int remTal = this->get_talent() + 10;
    this->set_talent(remTal);
}