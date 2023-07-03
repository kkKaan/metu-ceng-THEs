#ifndef __MUSIC_BAND_H__
#define __MUSIC_BAND_H__

#include<list>
#include<vector>
#include<iostream>

using namespace std;


class MusicBand {
public:
    MusicBand(const char name[], int energy, int talent, int fans) 
        : name(name), talent(talent), energy(energy), fans(fans) {}

    // name getter setter
    virtual const std::string& get_name() final { return name; }
    virtual const void rename(const std::string& name_) final { name = name_; }
    
    // fan getter setter
    virtual int get_fan_count() final { return fans; }
    virtual void set_fan_count(int fans_) final { fans = fans_; }

    // energy getter setter
    virtual void set_energy(int n) final { energy = n; } 
    virtual int get_energy() final { return energy; }
    
    // talent getter setter
    virtual void set_talent(int n) final { talent = n; } 
    virtual int get_talent() final { return talent; }

    // pure functions
    virtual int play(MusicBand *other) = 0; // may increase fans, decrease energy
    virtual void rehearse(void) = 0; // increase talent, decrease energy

private:
    std::string name;
    int talent, energy, fans;
};


#endif
