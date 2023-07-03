#ifndef ARTIST_H
#define ARTIST_H

// DO NOT CHANGE THIS FILE.

#include <iostream>

#include "LinkedList.h"
#include "Album.h"

class Artist {
public:
    Artist() {}
    Artist(const std::string &name);

    int getArtistId() const;
    const std::string &getName() const;
    const LinkedList<Album *> &getAlbums() const;

    void addAlbum(Album *album);
    void dropAlbum(Album *album);

    bool operator==(const Artist &rhs) const;
    bool operator!=(const Artist &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Artist &artist);

private:
    int artistId;
    std::string name;

    LinkedList<Album *> albums;
};

#endif //ARTIST_H
