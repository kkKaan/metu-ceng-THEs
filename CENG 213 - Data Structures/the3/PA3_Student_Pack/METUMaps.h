#ifndef __METU_MAPS_H__
#define __METU_MAPS_H__

#include "Graph.h"
#include "HashTable.h"

class METUMaps
{
    private:
        Graph           map;
        KeyedHashTable  cachedPaths;
        // How many paths should be provided
        // by the maps array
        int             potentialPathCount;

        // States
        bool                inJourney;
        std::string         startingLoc;
        std::string         currentLoc;
        std::string         destination;
        std::vector<int>    currentRoute;

        // Print Functions
        // You may want to use these functions in terms of consistency
        void                PrintNotInJourney() const;
        void                PrintUnableToChangeDestination() const;
        void                PrintUnableToChangeStartingLoc() const;
        void                PrintAlreadyInJourney() const;
        void                PrintJourneyIsAlreadFinished() const;
        void                PrintLocationNotFound() const;
        void                PrintJourneyCompleted() const;
        void                PrintCachedLocationFound(const std::string& location0,
                                                     const std::string& location1) const;
        void                PrintCalculatingRoutes(const std::string& location0,
                                                   const std::string& location1) const;

        //
        static std::string  GenerateKey(const std::string& location0,
                                        const std::string& location1);

        // Friend class that will access your private members etc.
        // This will be used for testing. Do not remove/edit this
        // statement.
        friend class    PA3_MAPS_TEST_CASE;

    public:
        // Constructors
                        METUMaps(int potentialPathCount,
                                 const std::string& mapFilePath);
        // No need for rule of 3 here
        // "Graph" & "KeyedHashTable" classes define their
        // copy constructor, destructor, copy assignment operator
        // properly

        // Methods
        void            SetDestination(const std::string& name);
        void            SetStartingLocation(const std::string& name);
        // Start/End the journey
        void            StartJourney();
        void            EndJourney();
        // Functions that will be called during journey
        void            UpdateLocation(const std::string& name);
        void            Display();
};
#endif // __METU_MAPS_H__