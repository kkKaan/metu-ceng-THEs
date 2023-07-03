#ifndef MUSICSTREAMINGSERVICE_H
#define MUSICSTREAMINGSERVICE_H

#include "LinkedList.h"
#include "Album.h"
#include "Artist.h"
#include "Profile.h"
#include "Song.h"

class MusicStream {
public: // DO NOT CHANGE THIS PART.
    MusicStream() {}

    void addProfile(const std::string &email, const std::string &username, SubscriptionPlan plan);
    void deleteProfile(const std::string &email);

    void addArtist(const std::string &artistName);
    void addAlbum(const std::string &albumName, int artistId);
    void addSong(const std::string &songName, int songDuration, int albumId);

    void followProfile(const std::string &email1, const std::string &email2);
    void unfollowProfile(const std::string &email1, const std::string &email2);

    void createPlaylist(const std::string &email, const std::string &playlistName);
    void deletePlaylist(const std::string &email, int playlistId);
    void addSongToPlaylist(const std::string &email, int songId, int playlistId);
    void deleteSongFromPlaylist(const std::string &email, int songId, int playlistId);
    LinkedList<Song *> playPlaylist(const std::string &email, Playlist *playlist);
    Playlist *getPlaylist(const std::string &email, int playlistId);
    LinkedList<Playlist *> getSharedPlaylists(const std::string &email);
    void shufflePlaylist(const std::string &email, int playlistId, int seed);
    void sharePlaylist(const std::string &email, int playlistId);
    void unsharePlaylist(const std::string &email, int playlistId);

    void subscribePremium(const std::string &email);
    void unsubscribePremium(const std::string &email);

    void print() const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    LinkedList<Profile> profiles;
    LinkedList<Artist> artists;
    LinkedList<Album> albums;
    LinkedList<Song> songs;
};

#endif //MUSICSTREAMINGSERVICE_H
