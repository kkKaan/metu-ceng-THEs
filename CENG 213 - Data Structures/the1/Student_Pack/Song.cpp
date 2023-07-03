#include "Song.h"

// DO NOT CHANGE THIS FILE.

Song Song::ADVERTISEMENT_SONG = Song("advertisement", 30);

Song::Song(const std::string &name, int duration) {
    static int songId = 1;

    this->name = name;
    this->duration = duration;
    this->songId = songId;

    songId += 1;
}

int Song::getSongId() const {
    return this->songId;
}

const std::string &Song::getName() const {
    return this->name;
}

int Song::getDuration() const {
    return this->duration;
}

bool Song::operator==(const Song &rhs) const {
    return this->songId == rhs.songId && this->name == rhs.name && this->duration == rhs.duration;
}

bool Song::operator!=(const Song &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Song &song) {
    os << "songId: " << song.songId << " |";
    os << " name: " << song.name << " |";
    os << " duration: " << song.duration;

    return os;
}
