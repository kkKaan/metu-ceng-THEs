# Music Streaming Service and Linked List Implementation

This project implements a music streaming service called MusicStream and a linked list data structure. It is divided into two main parts: Music Streaming Service and Linked List Implementation.

## Linked List Implementation

The linked list data structure used in this assignment is implemented as the class template `LinkedList` with the template argument `T`, which is used as the type of data stored in the nodes. The node of the linked list is implemented as the class template `Node` with the template argument `T`, which is the type of data stored in nodes. `Node` class is the basic building block of the `LinkedList` class.

### Node

`Node` class represents nodes that constitute linked lists. A `Node` keeps two pointers (namely `prev` and `next`) to its previous and next nodes in the list, and the data variable of type `T` (namely `data`) to hold the data. The class has two constructors and the overloaded output operator (`operator<<`). They are already implemented for you and should not be changed.

### LinkedList

`LinkedList` class implements a circular doubly linked list data structure with the head pointer. Previously, data members of `LinkedList` class have been briefly described. Their use will be elaborated in the context of utility functions discussed in the following subsections. You must provide implementations for the following public member functions that have been declared under indicated portions of `LinkedList.h` file.

#### Public Member Functions

1. `LinkedList();`
   - This is the default constructor.

2. `LinkedList(const LinkedList<T> &obj);`
   - This is the copy constructor. Creates new nodes by copying the nodes in the given `obj`, and insert those new nodes into the linked list.

3. `~LinkedList();`
   - This is the destructor. It deallocates all the memory that were allocated before.

4. `int getSize() const;`
   - This function returns an integer that is the number of nodes in the linked list (i.e., the size of the linked list)

5. `bool isEmpty() const;`
   - This function should return true if the linked list is empty (i.e., there exists no nodes in the linked list). If the linked list is not empty, it should return false.

6. `bool contains(Node<T> *node) const;`
   - This function should return true if the linked list contains the given node (i.e. any next/prev in the list matches with node). Otherwise, it should return false.

7. `Node<T> *getFirstNode() const;`
   - This function should return a pointer to the first node in the linked list. If the linked list is empty, it should return NULL.

8. `Node<T> *getLastNode() const;`
   - This function should return a pointer to the last node in the linked list. If the linked list is empty, it should return NULL.

9. `Node<T> *getNode(const T &data) const;`
   - Searches the linked list for the node that has the same data with the given data and return a pointer to that node. If there exists multiple such nodes in the linked list, return a pointer to the first occurrence. If there exists no such node in the linked list, you should return NULL.

10. `Node<T> *getNodeAtIndex(int index) const;`
    - Searches the linked list for the node at the given zero-based index (i.e., index=0 means first node, index=1 means second node, ..., index=size-1 means last node) and returns a pointer to that node. If there exists no such node in the linked list (i.e., index is out of bounds), it should return NULL.

11. `void insertAtTheFront(const T &data);`
    - Creates a new node with the given data and insert it at the front of the linked list as the first node.

12. `void insertAtTheEnd(const T &data);`
    - Creates a new node with the given data and insert it at the end of the linked list as the last node.

13. `void insertAfterNode(const T &data, Node<T> *node);`
    - Creates a new node with the given data and insert it after the given node as its next node. If the given node is not in the linked list, do nothing.

14. `void insertAsEveryKthNode(const T &data, int k);`
    - Creates new nodes with the given data and insert them at the linked list as every kth node. If the given k is smaller than 2, do nothing.

15. `void removeNode(Node<T> *node);`
    - Deletes the given node from the linked list. If the given node is not in the linked list (i.e. the linked list does not contain the given node), do nothing.

16. `void removeNode(const T &data);`
    - Delete the node that has the same data with the given data from the linked list. If there exists multiple such nodes in the linked list, delete all occurrences. If there exists no such node in the linked list, do nothing.

17. `void removeAllNodes();`
    - Removes all nodes in the linked list so that the linked list becomes empty. 

18. `void removeEveryKthNode(int k);`
    - Removes every kth node from the linked list. If the given k is smaller than 2, do nothing.

19. `void swap(Node<T> *node1, Node<T> *node2);`
    - Swaps the two given nodes `node1` and `node2`. It is not allowed to just swap the data in the nodes. Does the swapping by playing with the pointers in the nodes of the linked list. If either of the given nodes is not in the linked list, do nothing.

20. `void shuffle(int seed);`
    - Shuffles the nodes of the linked list by swapping nodes applying the given algorithm:
      ```
      for "i=0" to "i=size-1":
          swap the node at index i with the node at index (i*i+seed)%size
      ```
      
21. `LinkedList<T> &operator=(const LinkedList<T> &rhs);`
    - This is the overloaded assignment operator. Removes all nodes in the linked list and then create new nodes by copying the nodes in the given `rhs` and inserts those new nodes into the linked list.

## Music Streaming Service Implementation

The music streaming service in this assignment is implemented as the class `MusicStream`. `MusicStream` class has four `LinkedList` objects in its private data field (namely `profiles`, `artists`, `albums`, and `songs`) with the types `Profile`, `Artist`, `Album`, and `Song`, respectively. These four `LinkedList` objects keep the profiles, artists, albums, and songs of the music streaming service. `Profile` class represents the users of the music streaming service. `Artist`, `Album`, and `Song` classes represent the artists, albums, and songs of the music streaming service, respectively.

## Project Structure

The project consists of several classes: `Profile`, `Artist`, `Album`, `Song`, and `MusicStream`. Each of these classes has its definitions in separate header files (e.g., `Profile.h`, `Artist.h`) and their implementations in corresponding source files (e.g., `Profile.cpp`, `Artist.cpp`). These classes are used to build the music streaming service and store user profiles, artists, albums, and songs.

### Song

`Song` objects keep a name variable of type `std::string`, and `duration` and `songId` variables of type `int` to hold the data related to available songs in the music streaming service. All of the functions of `Song` class are already implemented.

### Album

`Album` objects keep a name variable of type `std::string` and an `albumId` variable of type `int` to hold the data related to available albums in the music streaming service. They also keep linked lists of pointers to the songs of the albums (namely `songs`). Most of the functions of the `Album` class are already implemented for you. You need to provide implementations for the following functions declared under `Album.h` header:

1. `void addSong(Song *song);`
   - Adds (appends) the given song to the list of songs of this album.  

2. `void dropSong(Song *song);`
   - Removes the given song from the list of songs of this album. 

### Artist

`Artist` objects keep a name variable of type `std::string` and an `artistId` variable of type `int` to hold the data related to available artists in the music streaming service. They also keep linked lists of pointers to the albums of the artists (namely `albums`). Most of the functions of the `Artist` class are already implemented. 

1. `void addAlbum(Album *album);`
   - Adds (appends) the given album to the list of albums of this artist.  

2. `void dropAlbum(Album *album);`
   - Removes the given album from the list of albums of this artist. 

### Playlist

`Playlist` objects keep a name variable of type `std::string`, a shared variable of type `bool`, and a `playlistId` variable of type `int` to hold the data related to the playlists belonging to the users of the music streaming service. They also keep linked lists of pointers to the songs in the playlists (namely `songs`). Most of the functions of the `Playlist` class are already implemented.
1. `void addSong(Song *song);`
   - Adds (appends) the given song to the list of songs in this playlist. 

2. `void dropSong(Song *song);`
   - Removes the given song from the list of songs in this playlist. 

3. `void shuffle(int seed);`
   - Shuffles the list of songs in this playlist. For shuffling, use `shuffle(int seed)` function of the `LinkedList` class with the given seed.

### Profile

`Profile` objects keep `email` and `username` variables of type `std::string`, and `plan` variable of type `SubscriptionPlan` to hold the data related to the users of the music streaming service. `SubscriptionPlan` is an enumerated type defined in `Profile.h` file with values `freeOfCharge`, which means the user does not pay for the service and will listen to advertisements between songs, and `premium`, which means the user pays for the service and will not listen to any advertisement songs. A `Profile` object also keeps linked lists of pointers to the profiles the user follows (namely `followings`), pointers to the profiles follows the user (namely `followers`), and the playlists belonging to the user (namely `playlists`). Profile pointers in `followings` and `followers` linked lists are pointers to the `Profile` objects stored in the linked lists in `MusicStream` class. Most of the functions of `Profile` class are already implemented.

1. `void followProfile(Profile *profile);`
   - This function makes this user (i.e., profile) follow the given profile. 

2. `void unfollowProfile(Profile *profile);`
   - This function makes this user not follow the given profile. 

3. `void createPlaylist(const std::string &playlistName);`
   - This function creates a new playlist with the given `playlistName` for this user.

4. `void deletePlaylist(int playlistId);`
   - This function deletes the playlist with the given `playlistId` of this user. 

5. `void addSongToPlaylist(Song *song, int playlistId);`
   - This function adds the given song to the playlist with the given `playlistId` of this user.
     
6. `void deleteSongFromPlaylist(Song *song, int playlistId);`
   - This function removes the given song from the playlist with the given `playlistId` of this user. 

7. `Playlist *getPlaylist(int playlistId);`
   - This function gets (i.e., returns a pointer to) the playlist with the given `playlistId` of this user. 

8. `LinkedList<Playlist *> getSharedPlaylists();`
   - This function gets a list of (i.e., returns a linked list of pointers to) playlists shared by the users who are followed by this user.

9. `void shufflePlaylist(int playlistId, int seed);`
   - This function shuffles the songs in the playlist with the given `playlistId`. For shuffling, use `shuffle(int seed)` function of the `LinkedList` class with the given seed. 

10. `void sharePlaylist(int playlistId);`
    - This function marks the playlist with the given `playlistId` of this user as shared. 

11. `void unsharePlaylist(int playlistId);`
    - This function marks the playlist with the given `playlistId` of this user as unshared. 

### MusicStream

In the `MusicStream` class, all member functions should utilize `profiles`, `artists`, `albums`, and `songs` member variables to operate as described in the following subsections. 

1. `void addProfile(const std::string &email, const std::string &username, SubscriptionPlan plan);`
   - This function adds a new profile to the system (i.e., registers a new user). It takes profile information (email, username, and plan) as parameters and inserts (appends) a new `Profile` object to the `profiles` linked list. 

2. `void deleteProfile(const std::string &email);`
   - This function deletes a profile from the system (i.e., deletes an already registered user). It takes the email of the profile (`email`) as a parameter. Deletion of a user includes some steps: deleting the user from its followers' list of followings, deleting the user from its followings' list of followers, deleting content of the user’s `Profile` object, and finally deleting the user’s `Profile` object from the `MusicStream`.
     
3. `void addArtist(const std::string &artistName);`
   - This function adds a new artist to the system. It takes artist information (`artistName`) as a parameter and inserts (appends) a new `Artist` object to the `artists` linked list.

4. `void addAlbum(const std::string &albumName, int artistId);`
   - This function adds a new album to the system. It takes album information (`artistName`) and the id of the artist that this album belongs to (`artistId`) as parameters and inserts (appends) a new `Album` object to the `albums` linked list. Also, remember that the `Artist` object of an artist stores a list of pointers to the `Album` objects of the artist’s albums.  

5. `void addSong(const std::string &songName, int songDuration, int albumId);`
   - This function adds a new song to the system. It takes song information (`songName` and `songDuration`) and the id of the album that this song belongs to (`songId`) as parameters and inserts (appends) a new `Song` object to the `songs` linked list. Also, remember that the `Album` object of an album stores a list of pointers to the `Song` objects of the album’s songs.

6. `void followProfile(const std::string &email1, const std::string &email2);`
   - This function takes emails of two users (`email1` and `email2`) as parameters and makes the user with `email1` (i.e., first user) follow the user with `email2` (i.e., second user) by populating their `Profile` objects’ `followings` and `followers` lists. 

7. `void unfollowProfile(const std::string &email1, const std::string &email2);`
   - This function takes emails of two users (`email1` and `email2`) as parameters and makes the user with `email1` (i.e., first user) not follow the user with `email2` (i.e., second user) by populating their `Profile` objects’ `followings` and `followers` lists. 

8. `void createPlaylist(const std::string &email, const std::string &playlistName);`
   - This function creates a new playlist with name `playlistName` for the user with `email` and inserts (appends) a new `Playlist` object to the playlists linked list of the user’s `Profile` object.  

9. `void deletePlaylist(const std::string &email, int playlistId);`
   - This function deletes a playlist with the given `playlistId` for the user with `email`. Deletion of a playlist includes some steps: deleting the playlist from the followers' list of followings (i.e., users who are followed by) of this user’s `Profile` object and finally deleting the `Playlist` object from the user’s `Profile` object.  

10. `void addSongToPlaylist(const std::string &email, int playlistId, int songId);`
    - This function adds the song with the given `songId` to the playlist with the given `playlistId` of the user with `email`.  

11. `void deleteSongFromPlaylist(const std::string &email, int playlistId, int songId);`
    - This function deletes the song with the given `songId` from the playlist with the given `playlistId` of the user with `email`.  

12. `void sharePlaylist(const std::string &email, int playlistId);`
    - This function marks the playlist with the given `playlistId` of the user with `email` as shared.  

13. `void unsharePlaylist(const std::string &email, int playlistId);`
    - This function marks the playlist with the given `playlistId` of the user with `email` as unshared. 

### Main Program

Finally, you should create a main program (`main.cpp`) that tests your `MusicStream` class and its functionalities. In the main program, you can create instances of the `MusicStream` class and use its member functions to simulate user registrations, music additions, playlist management, and more.

This README provides an overview of the project structure and the main classes involved. It outlines the functions you need to implement within each class. You can follow this structure to organize your project and start implementing the required functionality. Make sure to thoroughly test your code to ensure it works correctly.
