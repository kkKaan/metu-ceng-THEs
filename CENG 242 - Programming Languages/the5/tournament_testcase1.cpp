#include "kpop.h"
#include "jazz.h"
#include "rock.h"
#include "metal.h"

#include "tournament.h"
#include "tournament_round.h"


int main()
{
    JazzBand band1("jazz", 50, 100, 25);
    RockBand band2("rock", 50, 100, 25);
    MetalBand band3("metal", 50, 100, 25);
    KPopBand band4("kpop", 50, 100, 25);
    
    Tournament tournament;
    
    tournament.enroll(band1);
    tournament.enroll(band2);
    tournament.enroll(band3);
    tournament.enroll(band4);
    
    tournament.make_tournament();
    return 0;
}