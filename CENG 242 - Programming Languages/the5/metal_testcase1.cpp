#include "kpop.h"
#include "jazz.h"
#include "rock.h"
#include "metal.h"

#include "tournament.h"
#include "tournament_round.h"


int main()
{
    MetalBand band1("metal1", 55, 40, 200);
    MetalBand band2("metal2", 50, 100, 25);
    
    std::cout << band1.get_name().c_str() << ".play(" << band2.get_name().c_str() << ") returns " << band1.play(&band2) << std::endl;
    std::cout << band1.get_name().c_str() << ".energy " << band1.get_energy() << std::endl;
    std::cout << band1.get_name().c_str() << ".talent " << band1.get_talent() << std::endl;
    std::cout << band1.get_name().c_str() << ".fans " << band1.get_fan_count() << std::endl;
    
    return 0;
}