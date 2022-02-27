#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <iostream>
using namespace std;

class Playlist
{
private:
    char * nume=nullptr;
    int nr;
    char **melodii=nullptr;
    float rating;

public:
    Playlist(char *nume = nullptr, int nr = 0, char **melodii = nullptr, float rating = 0);
    virtual ~Playlist();
    Playlist(const Playlist& p);

    char * Getnume() { return nume; };
    int Getnr(){ return nr; };
    int Getrating() { return rating; };

    void Setnr(int nr) { this->nr = nr; };
    void Setrating(int rating) { this->rating = rating; };
    void Setnume(char * nume);
    void new_song(char * mel);
    void delete_song(int pos);
    char * Getsong(int pos) { return melodii[pos]; };

    friend istream & operator >> (istream &, Playlist &);
    friend ostream & operator << (ostream &, const Playlist &);
    Playlist &operator = (const Playlist &);

};


#endif // PLAYLIST_H
