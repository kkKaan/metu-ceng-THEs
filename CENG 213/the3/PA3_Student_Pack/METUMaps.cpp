#include "METUMaps.h"
#include "GraphExceptions.h"

#include <iostream>

void METUMaps::PrintNotInJourney() const
{
    std::cout << "Device is not in a journey!" << std::endl;
}

void METUMaps::PrintUnableToChangeDestination() const
{
    std::cout << "Cannot change Destination during journey!" << std::endl;
}

void METUMaps::PrintUnableToChangeStartingLoc() const
{
    std::cout << "Cannot change Starting Location during journey!" << std::endl;
}

void METUMaps::PrintAlreadyInJourney() const
{
    std::cout << "Device is already in a journey!" << std::endl;
}

void METUMaps::PrintJourneyIsAlreadFinished() const
{
    std::cout << "Journey is already finished!" << std::endl;
}

void METUMaps::PrintLocationNotFound() const
{
    std::cout << "One (or both) of the locations are not found in the maps!" << std::endl;
}

void METUMaps::PrintJourneyCompleted() const
{
    std::cout << "Journey Completed!" << std::endl;
}

void METUMaps::PrintCachedLocationFound(const std::string& location0,
                                        const std::string& location1) const
{
    std::cout << "Route between \""
              << location0 << "\" and \""
              << location1 << "\" is in cache, using that..."
              << std::endl;
}

void METUMaps::PrintCalculatingRoutes(const std::string& location0,
                                      const std::string& location1) const
{
    std::cout << "Calculating Route(s) between \""
              << location0 << "\" and \""
              << location1 << "\"..."
              << std::endl;
}

std::string METUMaps::GenerateKey(const std::string& location0,
                                  const std::string& location1)
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    return location0 + "/" + location1;
}

METUMaps::METUMaps(int potentialPathCount,
                   const std::string& mapFilePath)
{
    // TODO

    Graph g(mapFilePath);
    this->map = g;

    this->potentialPathCount = potentialPathCount;
    this->inJourney = false;
    
    KeyedHashTable h(potentialPathCount * (this->map).TotalVertexCount());
    this->cachedPaths = h;
}

void METUMaps::SetDestination(const std::string& name)
{
    // TODO

    if(inJourney){PrintUnableToChangeDestination();}
    else
    {
        this->destination = name;
    }

}

void METUMaps::SetStartingLocation(const std::string& name)
{
    // TODO

    if(inJourney){PrintUnableToChangeStartingLoc();}
    else
    {
        this->startingLoc = name;
    }
}

void METUMaps::StartJourney()
{
    // TODO

    if(inJourney){PrintAlreadyInJourney(); return;}
    
    bool x = true, y = true;
    for(int a = 0; a < map.TotalVertexCount(); ++a)
    {
        if(map.VertexName(a) == startingLoc){x = false;}
        else if(map.VertexName(a) == destination){y = false;}
    }

    PrintCalculatingRoutes(startingLoc, destination);
    if(x || y){PrintLocationNotFound(); return;}

    std::vector<std::vector<int> > orderedList;
    map.MultipleShortPaths(orderedList, startingLoc, destination, potentialPathCount);

    for(int b = 0; b < orderedList.size(); ++b)
    {
        for(int c = 0; c < orderedList[b].size() - 1; ++c)
        {
            std::vector<int> initPath = orderedList[b];
            std::vector<int> finalPath;
            std::string key = GenerateKey(map.VertexName(initPath[c]), destination);
            
            for(int d = c; d < initPath.size(); ++d)
            {
                finalPath.push_back(initPath[d]);
            }
            cachedPaths.Insert(key, finalPath);
        }
    }
    inJourney = true;
    currentLoc = startingLoc;
    currentRoute = orderedList[0];
}

void METUMaps::EndJourney()
{
    // TODO

    if(!inJourney){PrintJourneyIsAlreadFinished(); return;}

    cachedPaths.ClearTable();
    startingLoc = "";
    destination = "";
    currentLoc = "";
    currentRoute.clear();
    inJourney = false;
}

void METUMaps::UpdateLocation(const std::string& name)
{
    // TODO

    if(!inJourney){PrintNotInJourney(); return;}
    
    bool x = true;
    for(int a = 0; a < map.TotalVertexCount(); ++a)
    {
        if(map.VertexName(a) == name){x = false;}
    }

    if(x){PrintLocationNotFound(); return;}
    if(destination == name){PrintJourneyCompleted(); return;}

    std::vector<int> newPath;
    std::string newKey = GenerateKey(name, destination);
    map.ShortestPath(newPath, name, destination);

    if(cachedPaths.Find(newPath, newKey))
    {
        PrintCachedLocationFound(name, destination);
    }
    else
    {
        PrintCalculatingRoutes(name, destination);
        
        std::vector<std::vector<int> > orderedList;
        map.MultipleShortPaths(orderedList, name, destination, 10000);
        
        for(int b = 0; b < orderedList.size(); ++b)
        {
            for(int c = 0; c < orderedList[b].size() - 1; ++c)
            {
                std::vector<int> initPath = orderedList[b];
                std::vector<int> finalPath;
                std::string key = GenerateKey(map.VertexName(initPath[c]), destination);
                
                for(int d = c; d < initPath.size(); ++d)
                {
                    finalPath.push_back(initPath[d]);
                }
                cachedPaths.Insert(key, finalPath);
            }
        }
    }
    currentRoute = newPath;
    currentLoc = name;
}

void METUMaps::Display()
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    if(!inJourney)
    {
        // We are not in journey, this function
        // shouldn't be called
        PrintNotInJourney();
        return;
    }

    int timeLeft = map.TotalWeightInBetween(currentRoute);

    // Print last known location
    std::cout << "Journey         : " << startingLoc << "->"
              << destination << "\n";
    std::cout << "Current Location: " << currentLoc << "\n";
    std::cout << "Time Left       : " << timeLeft << " minutes\n";
    std::cout << "Current Route   : ";
    map.PrintPath(currentRoute, true);

    std::cout.flush();
}