#ifndef PLAYLIST_H
#define PLAYLIST_H

// DO NOT CHANGE THIS FILE.

#include <iostream>

#include "LinkedList.h"
#include "Song.h"

class Playlist {
public:
    Playlist() {}
    Playlist(const std::string &name);

    int getPlaylistId() const;
    const std::string &getName() const;
    bool isShared() const;
    LinkedList<Song *> &getSongs();

    void setShared(bool shared);

    void addSong(Song *song);
    void dropSong(Song *song);

    void shuffle(int seed);

    bool operator==(const Playlist &rhs) const;
    bool operator!=(const Playlist &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Playlist &playlist);

private:
    int playlistId;
    std::string name;
    bool shared;

    LinkedList<Song *> songs;
};


#endif //PLAYLIST_H
