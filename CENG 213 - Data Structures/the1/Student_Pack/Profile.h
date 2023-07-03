#ifndef PROFILE_H
#define PROFILE_H

// DO NOT CHANGE THIS FILE.

#include <iostream>

#include "Playlist.h"

enum SubscriptionPlan {free_of_charge, premium};

class Profile {
public:
    Profile() {}
    Profile(const std::string &email, const std::string &username, SubscriptionPlan plan);

    const std::string &getUsername() const;
    const std::string &getEmail() const;
    SubscriptionPlan getPlan() const;
    LinkedList<Playlist> &getPlaylists();
    LinkedList<Profile *> &getFollowings();
    LinkedList<Profile *> &getFollowers();

    void setPlan(SubscriptionPlan plan);

    void followProfile(Profile *profile);
    void unfollowProfile(Profile *profile);

    void createPlaylist(const std::string &playlistName);
    void deletePlaylist(int playlistId);
    void addSongToPlaylist(Song *song, int playlistId);
    void deleteSongFromPlaylist(Song *song, int playlistId);
    Playlist *getPlaylist(int playlistId);
    LinkedList<Playlist *> getSharedPlaylists();
    void shufflePlaylist(int playlistId, int seed);
    void sharePlaylist(int playlistId);
    void unsharePlaylist(int playlistId);

    bool operator==(const Profile &rhs) const;
    bool operator!=(const Profile &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Profile &profile);

private:
    std::string email;
    std::string username;
    SubscriptionPlan plan;

    LinkedList<Playlist> playlists;
    LinkedList<Profile *> following;
    LinkedList<Profile *> followers;
};

#endif //PROFILE_H
