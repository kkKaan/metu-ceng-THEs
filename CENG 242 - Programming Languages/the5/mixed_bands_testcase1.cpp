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
    
    std::cout << band1.get_name().c_str() << ".play(" << band1.get_name().c_str() << ") returns " << band1.play(&band1) << std::endl;
    std::cout << band1.get_name().c_str() << ".energy " << band1.get_energy() << std::endl;
    std::cout << band1.get_name().c_str() << ".talent " << band1.get_talent() << std::endl;
    std::cout << band1.get_name().c_str() << ".fans " << band1.get_fan_count() << std::endl;
    
    std::cout << band1.get_name().c_str() << ".play(" << band2.get_name().c_str() << ") returns " << band1.play(&band2) << std::endl;
    std::cout << band1.get_name().c_str() << ".energy " << band1.get_energy() << std::endl;
    std::cout << band1.get_name().c_str() << ".talent " << band1.get_talent() << std::endl;
    std::cout << band1.get_name().c_str() << ".fans " << band1.get_fan_count() << std::endl;
    
    
    std::cout << band1.get_name().c_str() << ".play(" << band3.get_name().c_str() << ") returns " << band1.play(&band3) << std::endl;
    std::cout << band1.get_name().c_str() << ".energy " << band1.get_energy() << std::endl;
    std::cout << band1.get_name().c_str() << ".talent " << band1.get_talent() << std::endl;
    std::cout << band1.get_name().c_str() << ".fans " << band1.get_fan_count() << std::endl;
    
    
    std::cout << band1.get_name().c_str() << ".play(" << band4.get_name().c_str() << ") returns " << band1.play(&band4) << std::endl;
    std::cout << band1.get_name().c_str() << ".energy " << band1.get_energy() << std::endl;
    std::cout << band1.get_name().c_str() << ".talent " << band1.get_talent() << std::endl;
    std::cout << band1.get_name().c_str() << ".fans " << band1.get_fan_count() << std::endl;
    
    
    /*************************************************************************************/
    
    std::cout << band2.get_name().c_str() << ".play(" << band1.get_name().c_str() << ") returns " << band2.play(&band1) << std::endl;
    std::cout << band2.get_name().c_str() << ".energy " << band2.get_energy() << std::endl;
    std::cout << band2.get_name().c_str() << ".talent " << band2.get_talent() << std::endl;
    std::cout << band2.get_name().c_str() << ".fans " << band2.get_fan_count() << std::endl;
    
    std::cout << band2.get_name().c_str() << ".play(" << band2.get_name().c_str() << ") returns " << band2.play(&band2) << std::endl;
    std::cout << band2.get_name().c_str() << ".energy " << band2.get_energy() << std::endl;
    std::cout << band2.get_name().c_str() << ".talent " << band2.get_talent() << std::endl;
    std::cout << band2.get_name().c_str() << ".fans " << band2.get_fan_count() << std::endl;
    
    
    std::cout << band2.get_name().c_str() << ".play(" << band3.get_name().c_str() << ") returns " << band2.play(&band3) << std::endl;
    std::cout << band2.get_name().c_str() << ".energy " << band2.get_energy() << std::endl;
    std::cout << band2.get_name().c_str() << ".talent " << band2.get_talent() << std::endl;
    std::cout << band2.get_name().c_str() << ".fans " << band2.get_fan_count() << std::endl;
    
    
    std::cout << band2.get_name().c_str() << ".play(" << band4.get_name().c_str() << ") returns " << band2.play(&band4) << std::endl;
    std::cout << band2.get_name().c_str() << ".energy " << band2.get_energy() << std::endl;
    std::cout << band2.get_name().c_str() << ".talent " << band2.get_talent() << std::endl;
    std::cout << band2.get_name().c_str() << ".fans " << band2.get_fan_count() << std::endl;
    
    /*************************************************************************************/
    
    std::cout << band3.get_name().c_str() << ".play(" << band1.get_name().c_str() << ") returns " << band3.play(&band1) << std::endl;
    std::cout << band3.get_name().c_str() << ".energy " << band3.get_energy() << std::endl;
    std::cout << band3.get_name().c_str() << ".talent " << band3.get_talent() << std::endl;
    std::cout << band3.get_name().c_str() << ".fans " << band3.get_fan_count() << std::endl;
    
    std::cout << band3.get_name().c_str() << ".play(" << band2.get_name().c_str() << ") returns " << band3.play(&band2) << std::endl;
    std::cout << band3.get_name().c_str() << ".energy " << band3.get_energy() << std::endl;
    std::cout << band3.get_name().c_str() << ".talent " << band3.get_talent() << std::endl;
    std::cout << band3.get_name().c_str() << ".fans " << band3.get_fan_count() << std::endl;
    
    
    std::cout << band3.get_name().c_str() << ".play(" << band3.get_name().c_str() << ") returns " << band3.play(&band3) << std::endl;
    std::cout << band3.get_name().c_str() << ".energy " << band3.get_energy() << std::endl;
    std::cout << band3.get_name().c_str() << ".talent " << band3.get_talent() << std::endl;
    std::cout << band3.get_name().c_str() << ".fans " << band3.get_fan_count() << std::endl;
    
    
    std::cout << band3.get_name().c_str() << ".play(" << band4.get_name().c_str() << ") returns " << band3.play(&band4) << std::endl;
    std::cout << band3.get_name().c_str() << ".energy " << band3.get_energy() << std::endl;
    std::cout << band3.get_name().c_str() << ".talent " << band3.get_talent() << std::endl;
    std::cout << band3.get_name().c_str() << ".fans " << band3.get_fan_count() << std::endl;
    
    /*************************************************************************************/
    
    std::cout << band4.get_name().c_str() << ".play(" << band1.get_name().c_str() << ") returns " << band4.play(&band1) << std::endl;
    std::cout << band4.get_name().c_str() << ".energy " << band4.get_energy() << std::endl;
    std::cout << band4.get_name().c_str() << ".talent " << band4.get_talent() << std::endl;
    std::cout << band4.get_name().c_str() << ".fans " << band4.get_fan_count() << std::endl;
    
    std::cout << band4.get_name().c_str() << ".play(" << band2.get_name().c_str() << ") returns " << band4.play(&band2) << std::endl;
    std::cout << band4.get_name().c_str() << ".energy " << band4.get_energy() << std::endl;
    std::cout << band4.get_name().c_str() << ".talent " << band4.get_talent() << std::endl;
    std::cout << band4.get_name().c_str() << ".fans " << band4.get_fan_count() << std::endl;
    
    
    std::cout << band4.get_name().c_str() << ".play(" << band3.get_name().c_str() << ") returns " << band4.play(&band3) << std::endl;
    std::cout << band4.get_name().c_str() << ".energy " << band4.get_energy() << std::endl;
    std::cout << band4.get_name().c_str() << ".talent " << band4.get_talent() << std::endl;
    std::cout << band4.get_name().c_str() << ".fans " << band4.get_fan_count() << std::endl;
    
    
    std::cout << band4.get_name().c_str() << ".play(" << band4.get_name().c_str() << ") returns " << band4.play(&band4) << std::endl;
    std::cout << band4.get_name().c_str() << ".energy " << band4.get_energy() << std::endl;
    std::cout << band4.get_name().c_str() << ".talent " << band4.get_talent() << std::endl;
    std::cout << band4.get_name().c_str() << ".fans " << band4.get_fan_count() << std::endl;
    
    
    return 0;
}