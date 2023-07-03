#include "Artist.h"

Artist::Artist(const std::string &name) {
    static int artistId = 1;

    this->name = name;
    this->artistId = artistId;

    artistId += 1;
}

int Artist::getArtistId() const {
    return this->artistId;
}

const std::string &Artist::getName() const {
    return this->name;
}

const LinkedList<Album *> &Artist::getAlbums() const {
    return this->albums;
}

void Artist::addAlbum(Album *album) 
{
    /* TODO */

    (this->albums).insertAtTheEnd(album);
}

void Artist::dropAlbum(Album *album) 
{
    /* TODO */

    (this->albums).removeNode(album);
}

bool Artist::operator==(const Artist &rhs) const {
    return this->artistId == rhs.artistId && this->name == rhs.name;
}

bool Artist::operator!=(const Artist &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Artist &artist) {
    os << "artistId: " << artist.artistId << " |";
    os << " name: " << artist.name << " |";

    os << " albums: [";
    Node<Album *> *firstAlbumNode = artist.albums.getFirstNode();
    Node<Album *> *albumNode = firstAlbumNode;
    if (albumNode) {
        do {
            os << *(albumNode->data);
            if (albumNode->next != firstAlbumNode) os << ", ";
            albumNode = albumNode->next;
        } while (albumNode != firstAlbumNode);
    }
    os << "]";

    return os;
}
