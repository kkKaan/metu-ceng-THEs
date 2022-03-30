#include "Profile.h"

Profile::Profile(const std::string &email, const std::string &username, SubscriptionPlan plan) {
    this->email = email;
    this->username = username;
    this->plan = plan;
}

const std::string &Profile::getUsername() const {
    return this->username;
}

const std::string &Profile::getEmail() const {
    return this->email;
}

SubscriptionPlan Profile::getPlan() const {
    return this->plan;
}

LinkedList<Playlist> &Profile::getPlaylists() {
    return this->playlists;
}

LinkedList<Profile *> &Profile::getFollowings() {
    return this->following;
}

LinkedList<Profile *> &Profile::getFollowers() {
    return this->followers;
}

void Profile::setPlan(SubscriptionPlan plan) 
{
    this->plan = plan;
}

void Profile::followProfile(Profile *profile) 
{
    /* TODO */

    (this->getFollowings()).insertAtTheEnd(profile);
    (profile->getFollowers()).insertAtTheEnd(this);
}

void Profile::unfollowProfile(Profile *profile) 
{
    /* TODO */

    (this->getFollowings()).removeNode(profile);
    (profile->getFollowers()).removeNode(this);
}

void Profile::createPlaylist(const std::string &playlistName) 
{
    /* TODO */

    Playlist p(playlistName);
    (this->getPlaylists()).insertAtTheEnd(p);
}

void Profile::deletePlaylist(int playlistId) 
{
    /* TODO */

    (this->getPlaylists()).removeNode(*(this->getPlaylist(playlistId)));
}

void Profile::addSongToPlaylist(Song *song, int playlistId) 
{
    /* TODO */

    Playlist *p = this->getPlaylist(playlistId);
    p->addSong(song);
}

void Profile::deleteSongFromPlaylist(Song *song, int playlistId) 
{
    /* TODO */

    Playlist *p = this->getPlaylist(playlistId);
    p->dropSong(song);
}

Playlist *Profile::getPlaylist(int playlistId) /////
{
    /* TODO */

    Node<Playlist>* p = (this->playlists).getFirstNode();

    do
    {
        if((p->data).getPlaylistId() == playlistId){break;}
        p = p->next;

    } while (p != (this->playlists).getFirstNode());

    return &(p->data);
}

LinkedList<Playlist *> Profile::getSharedPlaylists()  //////
{
    /* TODO */

    LinkedList<Playlist *> pl;
    LinkedList<Profile *> fol = this->getFollowings();
    Node<Profile *> *profs = fol.getFirstNode();

    do
    {
        LinkedList<Playlist> lst = profs->data->getPlaylists();
        Node<Playlist> *iter = lst.getFirstNode();

        do
        {
            if((iter->data).isShared()){pl.insertAtTheEnd(&(iter->data));}
            iter = iter->next;
        } while (iter != lst.getFirstNode());
        
        profs = profs->next;

    } while (profs != fol.getFirstNode());
    
    return pl;
}

void Profile::shufflePlaylist(int playlistId, int seed) 
{
    /* TODO */

    Playlist* p = this->getPlaylist(playlistId);
    p->shuffle(seed);
}

void Profile::sharePlaylist(int playlistId) 
{
    /* TODO */

    Playlist* p = this->getPlaylist(playlistId);
    p->setShared(true);
}

void Profile::unsharePlaylist(int playlistId) 
{
    /* TODO */
    Playlist* p = this->getPlaylist(playlistId);
    p->setShared(false);
}

bool Profile::operator==(const Profile &rhs) const {
    return this->email == rhs.email && this->username == rhs.username && this->plan == rhs.plan;
}

bool Profile::operator!=(const Profile &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Profile &profile) {
    os << "email: " << profile.email << " |";
    os << " username: " << profile.username << " |";
    if (profile.plan == free_of_charge) {
        os << " plan: " << "free_of_charge" << " |";
    } else if (profile.plan == premium) {
        os << " plan: " << "premium" << " |";
    } else {
        os << " plan: " << "undefined" << " |";
    }

    os << " playlists: [";
    Node<Playlist> *firstPlaylistNode = profile.playlists.getFirstNode();
    Node<Playlist> *playlistNode = firstPlaylistNode;
    if (playlistNode) {
        do {
            os << playlistNode->data;
            if (playlistNode->next != firstPlaylistNode) os << ", ";
            playlistNode = playlistNode->next;
        } while (playlistNode != firstPlaylistNode);
    }
    os << "] |";
    os << " following: [";
    Node<Profile *> *firstProfileNode = profile.following.getFirstNode();
    Node<Profile *> *profileNode = firstProfileNode;
    if (profileNode) {
        do {
            os << profileNode->data->getEmail();
            if (profileNode->next != firstProfileNode) os << ", ";
            profileNode = profileNode->next;
        } while (profileNode != firstProfileNode);
    }
    os << "] |";
    os << " followers: [";
    firstProfileNode = profile.followers.getFirstNode();
    profileNode = firstProfileNode;
    if (profileNode) {
        do {
            os << profileNode->data->getEmail();
            if (profileNode->next != firstProfileNode) os << ", ";
            profileNode = profileNode->next;
        } while (profileNode != firstProfileNode);
    }
    os << "]";

    return os;
}
