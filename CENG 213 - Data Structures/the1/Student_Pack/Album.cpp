#include "Album.h"

Album::Album(const std::string &name) {
    static int albumId = 1;

    this->name = name;
    this->albumId = albumId;

    albumId += 1;
}

int Album::getAlbumId() const {
    return this->albumId;
}

const std::string &Album::getName() const {
    return this->name;
}

const LinkedList<Song *> &Album::getSongs() const {
    return this->songs;
}

void Album::addSong(Song *song) 
{
    /* TODO */

    (this->songs).insertAtTheEnd(song);
}

void Album::dropSong(Song *song) 
{
    /* TODO */

    (this->songs).removeNode(song);
}

bool Album::operator==(const Album &rhs) const {
    return this->albumId == rhs.albumId && this->name == rhs.name;
}

bool Album::operator!=(const Album &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Album &album) {
    os << "aldumId: " << album.albumId << " |";
    os << " name: " << album.name << " |";

    os << " songs: [";
    Node<Song *> *firstSongNode = album.songs.getFirstNode();
    Node<Song *> *songNode = firstSongNode;
    if (songNode) {
        do {
            os << *(songNode->data);
            if (songNode->next != firstSongNode) os << ", ";
            songNode = songNode->next;
        } while (songNode != firstSongNode);
    }
    os << "]";

    return os;
}
