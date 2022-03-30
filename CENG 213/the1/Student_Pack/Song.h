#ifndef SONG_H
#define SONG_H

// DO NOT CHANGE THIS FILE.

#include <iostream>

class Song {
public:
    static Song ADVERTISEMENT_SONG;

public:
    Song() {}
    Song(const std::string &name, int duration);

    int getSongId() const;
    const std::string &getName() const;
    int getDuration() const;

    bool operator==(const Song &rhs) const;
    bool operator!=(const Song &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Song &song);

private:
    int songId;
    std::string name;
    int duration;
};

#endif //SONG_H
