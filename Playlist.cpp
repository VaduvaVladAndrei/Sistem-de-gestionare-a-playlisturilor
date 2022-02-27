#include "Playlist.h"
#include <string.h>
#include <iostream>
using namespace std;

Playlist::Playlist(char *nume, int nr, char **melodii, float rating)
{
    int i;
    if(nume!=nullptr){
        this->nume = new char[strlen(nume)+1];
        strcpy(this->nume, nume);
    }
    this->nr = nr;
    if(melodii!=nullptr){
        this->melodii = new char*[nr+1];
        for(i = 0; i<nr; i++){
            this->melodii[i] = new char[strlen(melodii[i])+1];
            strcpy(this->melodii[i], melodii[i]);
        }
    }
    this->rating = rating;
}

Playlist::~Playlist()
{
    int i;
    if(nume!=nullptr){
        delete []nume;
    }
    if(melodii){
        for(i=0; i<this->nr; i++)
            delete []melodii[i];
        delete []melodii;
    }
}

Playlist::Playlist(const Playlist& p)
{
    int i;
    this->nume = new char[strlen(p.nume)+1];
    strcpy(this->nume, p.nume);
    this->nr = p.nr;
    this->melodii = new char*[p.nr+1];
    for(i = 0; i<p.nr; i++){
        this->melodii[i] = new char[strlen(p.melodii[i])+1];
        strcpy(this->melodii[i], p.melodii[i]);
    }
    this->rating = p.rating;
}

void Playlist::Setnume (char *nume){
    if(this->nume)
        delete []this->nume;
    if(nume){
        this->nume = new char[strlen(nume)+1];
        strcpy(this->nume, nume);
    }
}

istream &operator >> (istream &st, Playlist &p){
    cout<<"Playlist:";
    char nume[50];
    st.getline(nume,50);
    p.nume= new char[strlen(nume)+1];
    strcpy(p.nume,nume);

    cout<<"Numarul de melodii:";
    st>>p.nr;
    st.ignore();

    p.melodii=new char* [p.nr];
    int i;
    char melodie[50];
    for(i=0;i<p.nr;i++){
        cout<<"Introduceti melodia "<<i+1<<':';
        st.getline(melodie,50);
        p.melodii[i]=new char[strlen(melodie)+1];
        strcpy(p.melodii[i],melodie);
    }
    cout<<"Introduceti ratingul:";
    st>>p.rating;
    while(p.rating < 0 || p.rating > 5){
        cout<<"trebuie sa introduceti un rating intre 0 si 5"<<endl;
        st>>p.rating;
    }
    st.ignore();
    return st;
}

ostream &operator <<(ostream &st, const Playlist &p){
    st<< p.nume << endl<< p.nr<<endl;
    int i;
    for(i=0; i<p.nr; i++)
        st<< p.melodii[i]<<endl;
    st<<p.rating<<endl;
    return st;
}

void Playlist :: new_song(char *mel){
    this->nr++;
    this->melodii = (char**) realloc (melodii, (nr+1) * sizeof(char*));
    this->melodii[nr-1] = new char[strlen(mel)+1];
    strcpy(this->melodii[nr-1], mel);
}

void Playlist :: delete_song(int pos){
    for(int i=pos; i<this->nr-1; i++){
        delete []this->melodii[i];
        this->melodii[i] = new char[strlen(melodii[i+1])+1];
        strcpy(this->melodii[i], this->melodii[i+1]);
    }
    delete []this->melodii[nr-1];
    this->nr--;
    this->melodii = (char**) realloc (this->melodii, (nr+1) * sizeof(char*));
}

Playlist & Playlist:: operator =(const Playlist &p){

    if (this == &p)
        return *this;
    int i;
    if(this->nume!=nullptr){
        delete []nume;
    }
    if(this->melodii){
        for(i=0; i<this->nr; i++)
            delete []melodii[i];
        delete []melodii;
    }

    this->nume = new char[strlen(p.nume)+1];
    strcpy(this->nume, p.nume);
    this->nr = p.nr;
    this->melodii = new char*[p.nr+1];
    for(i = 0; i<p.nr; i++){
        this->melodii[i] = new char[strlen(p.melodii[i])+1];
        strcpy(this->melodii[i], p.melodii[i]);
    }
    this->rating = p.rating;
    return *this;
}
