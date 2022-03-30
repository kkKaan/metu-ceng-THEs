#ifndef ALBUM_H
#define ALBUM_H

// DO NOT CHANGE THIS FILE.

#include <iostream>

#include "LinkedList.h"
#include "Song.h"

class Album {
public:
    Album() {}
    Album(const std::string &name);

    int getAlbumId() const;
    const std::string &getName() const;
    const LinkedList<Song *> &getSongs() const;

    void addSong(Song *song);
    void dropSong(Song *song);

    bool operator==(const Album &rhs) const;
    bool operator!=(const Album &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Album &album);

private:
    int albumId;
    std::string name;

    LinkedList<Song *> songs;
};

#endif //ALBUM_H
