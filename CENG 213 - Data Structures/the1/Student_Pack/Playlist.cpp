#include "Playlist.h"

Playlist::Playlist(const std::string &name) {
    static int playlistId = 1;

    this->name = name;
    this->shared = false;
    this->playlistId = playlistId;

    playlistId += 1;
}

int Playlist::getPlaylistId() const {
    return this->playlistId;
}

const std::string &Playlist::getName() const {
    return this->name;
}

bool Playlist::isShared() const {
    return this->shared;
}

LinkedList<Song *> &Playlist::getSongs() {
    return this->songs;
}

void Playlist::setShared(bool shared) {
    this->shared = shared;
}

void Playlist::addSong(Song *song) 
{
    /* TODO */

    (this->getSongs()).insertAtTheEnd(song);
}

void Playlist::dropSong(Song *song) 
{
    /* TODO */

    (this->getSongs()).removeNode(song);
}

void Playlist::shuffle(int seed) 
{
    /* TODO */

    (this->getSongs()).shuffle(seed);
}

bool Playlist::operator==(const Playlist &rhs) const {
    return this->playlistId == rhs.playlistId && this->name == rhs.name && this->shared == rhs.shared;
}

bool Playlist::operator!=(const Playlist &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Playlist &playlist) {
    os << "playlistId: " << playlist.playlistId << " |";
    os << " name: " << playlist.name << " |";
    os << " shared: " << (playlist.shared ? "yes" : "no") << " |";

    os << " songs: [";
    Node<Song *> *firstSongNode = playlist.songs.getFirstNode();
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
