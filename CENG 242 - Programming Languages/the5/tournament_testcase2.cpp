#include "kpop.h"
#include "jazz.h"
#include "rock.h"
#include "metal.h"

#include "tournament.h"
#include "tournament_round.h"


int main()
{
    JazzBand band1("jazz", 50, 100, 25);
    
    Tournament tournament;
    
    tournament.enroll(band1);
    
    tournament.make_tournament();
    return 0;
}