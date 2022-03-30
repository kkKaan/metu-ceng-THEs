#include "MusicStream.h"

#include <iostream>

void MusicStream::addProfile(const std::string &email, const std::string &username, SubscriptionPlan plan) 
{
    /* TODO */

    Profile user(email,username,plan);
    (this->profiles).insertAtTheEnd(user);
}

void MusicStream::deleteProfile(const std::string &email) /////
{
    /* TODO */
    
    Node<Profile>* user1 = (this->profiles).getFirstNode();
    Profile* pr1;

    do // Finding the profile.
    {
        if((user1->data).getEmail() == email)
        {
            pr1 = &(user1->data);
            break;
        }
        user1 = user1->next;

    } while (user1 != (this->profiles).getFirstNode());
    
    LinkedList<Profile *> *follng = &(pr1->getFollowings()); // That profile's following list.
    int size1 = follng->getSize();
    
    if(size1)
    {
        Node<Profile *> *ndFllng = follng->getFirstNode();
        for(int i = 0; i < size1; ++i)
        {
            pr1->unfollowProfile(ndFllng->data);
            ndFllng = ndFllng->next;
        }
    }
    
    LinkedList<Profile *> *follwr = &(pr1->getFollowers()); // That profile's follower list.
    int size2 = follwr->getSize();
        
    if(size2)
    {
        
        Node<Profile *> *ndFllwr = follwr->getFirstNode();
        for(int a=0; a<size2; ++a)
        {
            (ndFllwr->data)->unfollowProfile(pr1);
            ndFllwr = ndFllwr->next;
        }
    }
    
    LinkedList<Playlist>* plst = &(pr1->getPlaylists()); // That profile's playlists.
    int size3 = plst->getSize();
    
    if(size3)
    {
        Node<Playlist>* y = plst->getFirstNode();
        for(int k = 0; k < size3; ++k)
        {
            LinkedList<Song *> *sngs = &((y->data).getSongs());
            int size4 = sngs->getSize();
            
            if(size4){sngs->removeAllNodes();}
            y = y->next;
        }
        (pr1->getPlaylists()).removeAllNodes();
    }
    
    (this->profiles).removeNode(*pr1);
}

void MusicStream::addArtist(const std::string &artistName) 
{
    /* TODO */
    
    Artist art(artistName);
    (this->artists).insertAtTheEnd(art);
}

void MusicStream::addAlbum(const std::string &albumName, int artistId) 
{
    /* TODO */
    
    Album alb(albumName);
    (this->albums).insertAtTheEnd(alb);

    Node<Artist>* art = (this->artists).getFirstNode();

    do // Finding the artist with the Id to add album to it.
    {
        if((art->data).getArtistId() == artistId)
        {
            (art->data).addAlbum(&((this->albums).getLastNode())->data);
            return;
        }
        art = art->next;

    } while (art != (this->artists).getFirstNode());
}

void MusicStream::addSong(const std::string &songName, int songDuration, int albumId)
{
    /* TODO */

    Song son(songName, songDuration);
    (this->songs).insertAtTheEnd(son);

    Node<Album>* alb = (this->albums).getFirstNode();

    do // Finding the album to add the song. These finding loops should be functions by themselves.
    {
        if((alb->data).getAlbumId() == albumId)
        {
            (alb->data).addSong(&((this->songs).getLastNode())->data);
            return;
        }
        alb = alb->next;

    } while (alb != (this->albums).getFirstNode());
}

void MusicStream::followProfile(const std::string &email1, const std::string &email2) 
{
    /* TODO */

    Node<Profile>* user1 = (this->profiles).getFirstNode();
    Node<Profile>* user2 = (this->profiles).getFirstNode();
    Profile* pr1;
    Profile* pr2;

    do // * Finding the user with e mail, this could be a helper function by itself, that would reduce the number of lines of code. Also, it would be easier to see the errors, but I had realized that after I wrote many of them. 
    {
        if((user1->data).getEmail() == email1)
        {
            pr1 = &(user1->data);
            break;
        }
        user1 = user1->next;

    } while (user1 != (this->profiles).getFirstNode());

    do // * Finding the users.
    {
        if((user2->data).getEmail() == email2)
        {
            pr2 = &(user2->data);
            break;
        }
        user2 = user2->next;

    } while (user2 != (this->profiles).getFirstNode());

    pr1->followProfile(pr2);
}

void MusicStream::unfollowProfile(const std::string &email1, const std::string &email2) // The same logic with the follow.
{
    /* TODO */

    Node<Profile>* user1 = (this->profiles).getFirstNode();
    Node<Profile>* user2 = (this->profiles).getFirstNode();
    Profile* pr1;
    Profile* pr2;

    do 
    {
        if((user1->data).getEmail() == email1)
        {
            pr1 = &(user1->data);
            break;
        }
        user1 = user1->next;

    } while (user1 != (this->profiles).getFirstNode());

    do
    {
        if((user2->data).getEmail() == email2)
        {
            pr2 = &(user2->data);
            break;
        }
        user2 = user2->next;

    } while (user2 != (this->profiles).getFirstNode());

    pr1->unfollowProfile(pr2);
}

void MusicStream::createPlaylist(const std::string &email, const std::string &playlistName) 
{
    /* TODO */

    Node<Profile>* user1 = (this->profiles).getFirstNode();
    Profile* pr1;

    do
    {
        if((user1->data).getEmail() == email)
        {
            pr1 = &(user1->data);
            break;
        }
        user1 = user1->next;

    } while (user1 != (this->profiles).getFirstNode());

    pr1->createPlaylist(playlistName);
}

void MusicStream::deletePlaylist(const std::string &email, int playlistId) 
{
    /* TODO */

    Node<Profile>* user1 = (this->profiles).getFirstNode();
    Profile* pr1;

    do
    {
        if((user1->data).getEmail() == email)
        {
            pr1 = &(user1->data);
            break;
        }
        user1 = user1->next;

    } while (user1 != (this->profiles).getFirstNode());

    pr1->deletePlaylist(playlistId);
}

void MusicStream::addSongToPlaylist(const std::string &email, int songId, int playlistId) 
{
    /* TODO */

    Node<Profile>* user1 = (this->profiles).getFirstNode();
    Node<Song>* sng = (this->songs).getFirstNode();
    Song* sn1;
    Profile* pr1;

    do
    {
        if((user1->data).getEmail() == email)
        {
            pr1 = &(user1->data);
            break;
        }
        user1 = user1->next;

    } while (user1 != (this->profiles).getFirstNode());

    Playlist* plist = pr1->getPlaylist(playlistId);

    do
    {
        if((sng->data).getSongId() == songId)
        {
            sn1 = &(sng->data);
            break;
        }
        sng = sng->next;

    } while (sng != (this->songs).getFirstNode());
    
    plist->addSong(sn1);
}

void MusicStream::deleteSongFromPlaylist(const std::string &email, int songId, int playlistId) 
{
    /* TODO */

    Node<Profile>* user1 = (this->profiles).getFirstNode();
    Node<Song>* sng = (this->songs).getFirstNode();
    Song* sn1;
    Profile* pr1;

    do
    {
        if((user1->data).getEmail() == email)
        {
            pr1 = &(user1->data);
            break;
        }
        user1 = user1->next;

    } while (user1 != (this->profiles).getFirstNode());

    Playlist* plist = pr1->getPlaylist(playlistId);

    do
    {
        if((sng->data).getSongId() == songId)
        {
            sn1 = &(sng->data);
            break;
        }
        sng = sng->next;

    } while (sng != (this->songs).getFirstNode());
    
    plist->dropSong(sn1);
}

LinkedList<Song *> MusicStream::playPlaylist(const std::string &email, Playlist *playlist) 
{
    /* TODO */

    Node<Profile>* user1 = (this->profiles).getFirstNode();
    Profile* pr1;
    LinkedList<Song *> returnList = playlist->getSongs();

    do
    {
        if((user1->data).getEmail() == email)
        {
            pr1 = &(user1->data);
            break;
        }
        user1 = user1->next;

    } while (user1 != (this->profiles).getFirstNode());

    if(pr1->getPlan() == premium){return playlist->getSongs();}

    Song* s = &(Song::ADVERTISEMENT_SONG); 

    returnList.insertAsEveryKthNode(s, 2);

    return  returnList;
}

Playlist *MusicStream::getPlaylist(const std::string &email, int playlistId) 
{
    /* TODO */

    Node<Profile>* user1 = (this->profiles).getFirstNode();
    Profile* pr1;

    do
    {
        if((user1->data).getEmail() == email)
        {
            pr1 = &(user1->data);
            break;
        }
        user1 = user1->next;

    } while (user1 != (this->profiles).getFirstNode());

    return pr1->getPlaylist(playlistId);
}

LinkedList<Playlist *> MusicStream::getSharedPlaylists(const std::string &email) 
{
    /* TODO */

    Node<Profile>* user1 = (this->profiles).getFirstNode();
    Profile* pr1;

    do
    {
        if((user1->data).getEmail() == email)
        {
            pr1 = &(user1->data);
            break;
        }
        user1 = user1->next;

    } while (user1 != (this->profiles).getFirstNode());

    return pr1->getSharedPlaylists();
}

void MusicStream::shufflePlaylist(const std::string &email, int playlistId, int seed) 
{
    /* TODO */

    Playlist* pl = this->getPlaylist(email, playlistId);
    pl->shuffle(seed);
}

void MusicStream::sharePlaylist(const std::string &email, int playlistId) 
{
    /* TODO */

    Playlist* pl = this->getPlaylist(email, playlistId);
    pl->setShared(true);
}

void MusicStream::unsharePlaylist(const std::string &email, int playlistId) 
{
    /* TODO */

    Playlist* pl = this->getPlaylist(email, playlistId);
    pl->setShared(false);
}

void MusicStream::subscribePremium(const std::string &email) 
{
    /* TODO */

    Node<Profile>* user1 = (this->profiles).getFirstNode();
    Profile* pr1;

    do
    {
        if((user1->data).getEmail() == email)
        {
            pr1 = &(user1->data);
            break;
        }
        user1 = user1->next;

    } while (user1 != (this->profiles).getFirstNode());

    pr1->setPlan(premium);
}

void MusicStream::unsubscribePremium(const std::string &email) 
{
    /* TODO */

    Node<Profile>* user1 = (this->profiles).getFirstNode();
    Profile* pr1;

    do
    {
        if((user1->data).getEmail() == email)
        {
            pr1 = &(user1->data);
            break;
        }
        user1 = user1->next;

    } while (user1 != (this->profiles).getFirstNode());

    pr1->setPlan(free_of_charge);
}

void MusicStream::print() const {
    std::cout << "# Printing the music stream ..." << std::endl;

    std::cout << "# Number of profiles is " << this->profiles.getSize() << ":" << std::endl;
    this->profiles.print();

    std::cout << "# Number of artists is " << this->artists.getSize() << ":" << std::endl;
    this->artists.print();

    std::cout << "# Number of albums is " << this->albums.getSize() << ":" << std::endl;
    this->albums.print();

    std::cout << "# Number of songs is " << this->songs.getSize() << ":" << std::endl;
    this->songs.print();

    std::cout << "# Printing is done." << std::endl;
}
