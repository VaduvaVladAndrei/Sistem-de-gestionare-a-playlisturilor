#include <iostream>
#include "Playlist.h"
#include <string.h>
#include <conio.h>
#include <fstream>
#include <dirent.h>

using namespace std;

void arrowhere(int realposition,int arrowposition){
    if(realposition==arrowposition)
        cout<<"---> ";
}



Playlist citire(string filename){
    filename=filename+".txt";
    string nume, line;
    ifstream File(filename);
    getline(File,nume);
    char *cnume;
    cnume=new char[nume.length()];
    strcpy(cnume,nume.c_str());

    getline(File,line);
    int nr=stoi(line);
    getline(File,line);
    float rating=stof(line);

    //construieste array-ul de melodii
    char **melodii;
    int i=0;
    melodii=new char*[nr];
    while(getline(File,line)){
        melodii[i]=new char[line.length()];
        strcpy(melodii[i],line.c_str());
        i++;
    }
    Playlist p(cnume,nr,melodii,rating);

    File.close();
    return p;
}

int endswith(char s[],char ends[])
{
    int d=strlen(s)-1;
    for(int i=strlen(ends)-1;i>=0;i--){
        if(s[d]!=ends[i]){
            return 0;
        }
        d--;
    }
    return 1;
}

void creare(){
    int ok = 0, ok1=0;
    char name[45];
    Playlist p;
    while(ok == 0){
        cout<<"===============\nCreare playlist\n===============\n\n";
        ok=1;
        ok1++;
        if(ok1>1)
            cout<<"Acest playlist exista deja"<<endl<<endl;
        cin>>p;
        strcpy(name, p.Getnume());
        strcat(name, ".txt");
        DIR *d;
        struct dirent *dir;
        d = opendir(".");
        if (d)
        {
            while ((dir = readdir(d)) != NULL)
            {
                if(endswith(dir->d_name,".txt")){
                        if(strcmp(dir->d_name,name)==0){
                            ok=0;
                            break;
                        }
                }
            }
        }
        system("cls");
    }
    ofstream fout(name);
    fout<<p;

    fout.close();

}

void stergere(){
    cout<<"introduce nume:";
    char nume[40];
    fflush(stdin);
    gets(nume);
    strcat(nume,".txt");
    remove(nume);
}



void adaugare_melodie(Playlist p){
    system("cls");
        char melodie[50];
        char *mel;
        cout<<"====================\nIntroduceti melodia:\n====================\n";
        fflush(stdin);
        gets(melodie);
        mel = new char[strlen(melodie)+1];
        strcpy(mel, melodie);
        p.new_song(melodie);
        cout<<p;
        char *s = new char[strlen(p.Getnume())+1];
        strcpy(s, p.Getnume());
        strcat(s, ".txt");
        remove(s);
        ofstream fout(s);
        fout<<p;
        fout.close();
}

void stergere_melodie(Playlist p){
    system("cls");
    cout<<"==========Stergeti melodia==========";
        int keypressed=0;
        int position=1;
        if(p.Getnr()==1){
            char *s = new char[strlen(p.Getnume())+6];
            strcpy(s, p.Getnume());
            strcat(s, ".txt");
            remove(s);
        }
        else{
            while(keypressed!=13){
                system("cls");
                for(int i=0; i<p.Getnr(); i++){
                    arrowhere(i+1, position);
                    cout<<p.Getsong(i)<<endl;
                }
                keypressed = getch();
                if(keypressed==80 && position!=p.Getnr())
                    position++;
                else if(keypressed==72 && position!=1)
                    position--;

            }
            p.delete_song(position-1);
            char *s = new char[strlen(p.Getnume())+6];
            strcpy(s, p.Getnume());
            strcat(s, ".txt");
            remove(s);
            ofstream fout(s);
            fout<<p;
            fout.close();
        }

}
int vizualizare(){
    Playlist p[50];
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    int nr=0;
    if (d)
    {   printf("Playlisturi: \n-----------------------------------------------\n");
        int i,j;
        while ((dir = readdir(d)) != NULL)
        {
            if(endswith(dir->d_name,".txt")){
                int ok=0;
                Playlist new_p;
                ifstream fin(dir->d_name);
                fin>>new_p;
                fin.close();
                for(i=0; i<nr; i++){
                    if(p[i].Getrating() < new_p.Getrating()){
                        for(j=nr; j>i; j--){
                            p[j]= p[j-1];
                        }
                        p[i] = new_p;
                        ok=1;
                        break;
                    }
                }
                nr++;
                if(ok==0){
                    p[nr-1]=new_p;
                }

            }
        }
        closedir(d);}

        if(nr == 0){
            cout<<"Nu exista playlisturi\n";
            cout<<"Introduceti enter pentru a va intoarce la meniul principal\n";
            getc(stdin);
            return 1;
        }
        int keypressed=0;
        int position=1;
        while(keypressed!=13){
            system("cls");

            cout<<"========================\nVizualizare playlisturi\n========================\n";
            int nrp=0;
            for(int i=0; i<nr; i++){
                nrp++;
                arrowhere(nrp,position);
                cout<<p[i];
                cout<<"\n========================\n\n";
            }
            arrowhere(nrp+1,position);
            cout<<"Meniu principal\n";
            cout<<"\n========================\n\n";
            arrowhere(nrp+2,position);
            cout<<"Iesire\n";
            cout<<"\n========================\n";
            keypressed=getch();
            if(keypressed==80 && position!=nrp+2)
                position++;
            else if(keypressed==72 && position!=1)
                position--;
        }
        if(position==nr+1)
            return 1;
        if(position==nr+2)
            return 0;
        keypressed=0;
        int position1=1;
        while(keypressed!=13){
            system("cls");
            cout<<"====Meniu====\n\n";
            arrowhere(1,position1);
            cout<<"1.Adaugare melodie\n";
            arrowhere(2,position1);
            cout<<"2.Stergere melodie\n";
            arrowhere(3,position1);
            cout<<"3.Meniu principal\n";
            arrowhere(4,position1);
            cout<<"4.Iesire\n\n";

            keypressed=getch();
            if(keypressed==80 && position1!=4)
                position1++;
            else if(keypressed==72 && position1!=1)
                position1--;
        }

        switch(position1)
        {
            case 1:
                adaugare_melodie(p[position-1]);
                return 1;
                break;
            case 2:
                stergere_melodie(p[position-1]);
                return 1;
                break;
            case 3:
                return 1;
                break;
            case 4:
                return 0;

        }

}

int menu2(){
            int pos1=1;
            int keypressed=0;
            while(keypressed!=13){
                system("cls");
                cout<<"====Meniu====\n\n";
                arrowhere(1,pos1);
                cout<<"1.Meniu\n";
                arrowhere(2,pos1);
                cout<<"2.Iesire\n";
                keypressed=getch();

                if(keypressed==80 && pos1!=2)
                    pos1++;
                else if(keypressed==72 && pos1!=1)
                    pos1--;
            }
            switch(pos1)
            {
                case 1:
                    return 1;
                    break;
                case 2:
                    return 0;
                    break;
                default:
                    cout<<"Error";
            }
}

int menu(){
    int keypressed=0;
    int position=1;
    while(keypressed!=13){
        system("cls");
        cout<<"====Meniu====\n\n";
        arrowhere(1,position);
        cout<<"1.Creare playlist\n";
        arrowhere(2,position);
        cout<<"2.Vizualizare playlisturi\n";
        arrowhere(3,position);
        cout<<"3.Stergere playlist\n";
        arrowhere(4,position);
        cout<<"4.Iesire\n\n";
        keypressed=getch();

        if(keypressed==80 && position!=4)
            position++;
        else if(keypressed==72 && position!=1)
            position--;
    }
    system("cls");
    switch(position)
    {
        case 1:

            creare();
            if (menu2()==1)
                return 1;
            else
                return 0;
            break;
        case 2:
            cout<<"=======================\nVizualizare playlisturi\n=======================\n";
            if(vizualizare()==1)
                return 1;
            else
                return 0;
            break;
        case 3:
            cout<<"=================\nStergere playlist\n=================\n\n";
            stergere();
            if (menu2()==1)
                return 1;
            else
                return 0;
            break;
        default:
            return 0;
            break;

    }
}

int main()
{
    while(menu()==1);
    system("cls");
    printf("\n============\nLa revedere!\n============\n\n");

    return 0;
}
