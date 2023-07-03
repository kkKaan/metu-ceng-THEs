#include "kpop.h"
#include "metal.h"
#include "rock.h"
#include "jazz.h"

int KPopBand::play(MusicBand *other)
{
    if(this->get_energy() < 0.2 * this->get_energy())
    {
        return 0;
    }

    double con = 0;

    // relative constant definitions table
    
    //          KPopBand  MetalBand RockBand JazzBand
    // KPopBand  2.0         0.5      0.5       0.5
    // MetalBand 0.5         1.0      1.5       1.1
    // RockBand  0.5         1.4      1.0       0.8
    // JazzBand  0.5         1.3      0.7       0.7

    if (dynamic_cast<KPopBand*>(other) != nullptr)
    {
        con = 2;
    }
    else if (dynamic_cast<MetalBand*>(other) != nullptr)
    {
        con = 0.5;
    }
    else if (dynamic_cast<RockBand*>(other) != nullptr)
    {
        con = 0.5;
    }
    else if (dynamic_cast<JazzBand*>(other) != nullptr)
    {
        con = 0.5;
    }

    int score = (this->get_fan_count() + 0.1 * this->get_talent() * this->get_energy()) * con;

    int remNrg = this->get_energy() - this->get_energy() * 0.2;
    this->set_energy(remNrg);

    return score;
}

void KPopBand::rehearse(void) 
{
    if(this->get_energy() < 0.5 * 0.2 *this->get_energy())
    {
        return;
    }

    //          Talent Change
    // KPopBand       0
    // MetalBand     -5
    // RockBand      10
    // JazzBand      5
    // Table 3: Talent Change After Rehearse

    int remNrg = this->get_energy() - this->get_energy() * 0.5 * 0.2;
    this->set_energy(remNrg);

    int remTal = this->get_talent() + 0;
    this->set_talent(remTal);
}