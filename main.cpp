#include <iostream>
#import <random>
using namespace std;

//uzywam tego modulu do generowania liczb losowych od 0-100
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dis(0, 100);

////////////ZADANIE1//////////////
struct Punkt{
    int x,y;
    Punkt* next;

    Punkt(){
        x=dis(gen);
        y=dis(gen);
        next= nullptr;
    }
    Punkt(int x, int y): x(x), y(y){}
};

Punkt* stworzListe()
{
    Punkt* head = new Punkt;
    Punkt* temp = head;
    for(int i=0; i<9; i++) //tworzac head juz utworzylem jeden element wiec teraz tylko 9
    {
        temp->next = new Punkt;
        temp=temp->next;
    }
    return head;
}

void dodajsrednia(Punkt* lista)
{
    int sumaX = 0;
    int sumaY = 0; // w sumach podliczam wartosci elementow listy
    int licznik = 0; //licznik przechowuje ilosc elementow listy
    Punkt* temp = lista; //tworze tymczasowy odnosnik do listy
    while(temp->next)
    {
        sumaX += temp->x;
        sumaY += temp->y;
        licznik++;
        temp=temp->next;
    } //iteruje do przedostatniego elementu

    sumaX += temp->x;
    sumaY += temp->y;
    licznik++;
    //dodaje wartosci ostatniego elementu


    temp->next=new Punkt(); //dodaje 11ty element listy
    temp=temp->next;
    temp->x= sumaX/licznik; //zmieniam wartosci 11tego elementu
    temp->y= sumaY/licznik; //na srednie x i y
}




////////////ZADANIE2//////////////
struct Stos{
    Punkt* top;

    Stos()
    {
        top=nullptr;
    }

    void push(Punkt* punkt);
    Punkt* pop();

};

void Stos::push(Punkt* punkt)
{
    Punkt* temp = new Punkt();
    temp->x = punkt->x;
    temp->y = punkt->y;
    temp->next = top;
    top=temp;
}

Punkt *Stos::pop() {
    Punkt* temp = top;
    top=top->next;
    temp->next=nullptr;
    return temp;
}

Stos* zadanie2(Punkt* lista)
{
    Punkt* temp = lista;
    Stos* stos = new Stos;

    while(temp)
    {
        stos->push(temp);
        temp=temp->next;
    } //Dodaje elementy listy na stos


    int max=-1; //zmienna przechowujaca max wartosc
    Stos* tem = new Stos; //stos pomocniczy
    while(stos->top)
    {
        tem->push(stos->pop());
        if(tem->top->x + tem->top->y > max)
        {
            max = tem->top->x + tem->top->y;
        }
    } // przenosze elementy ze stosu pierwszego na drugi i szukam max wartosci

    int count = 0;
    while(tem->top)
    {
        Punkt* te = tem->pop();
        if(te->x + te->y == max && count == 0)
        {
            count++;
            continue;
        }
        else
        {
            stos->push(te);
        }
    } // przenosze elementy ze stosu 2 na 1 pomijajac maksymalna wartosc
    delete tem;
    delete temp;

    return stos;
}





////////////ZADANIE3//////////////
struct Kolejka{
    int size=0;
    Punkt* nowy;
    Punkt* stary;

    Kolejka()
    {
        nowy=nullptr;
        stary=nullptr;
    }


    void enqueue(Punkt* punkt);
    Punkt* dequeue();
    void przeniesDoKolejki(Stos* stos);
};

void Kolejka::enqueue(Punkt* punkt)
{
    if(!stary)
    {
        stary = new Punkt(punkt->x,punkt->y);
        nowy=stary;
    }
    else
    {
        nowy->next = new Punkt(punkt->x, punkt->y);
        nowy= nowy->next;
    }
    size++;
}

Punkt* Kolejka::dequeue()
{
    Punkt* temp = new Punkt(stary->x,stary->y);
    stary=stary->next;
    size--;
    if(size==0)
    {
        nowy=nullptr;
    }
    return temp;
}

void Kolejka::przeniesDoKolejki(Stos* stos) {

    Punkt* temp;
    while(stos->top)
    {
        temp = stos->pop(); //usuwam element ze stosu
        enqueue(temp); //i dodaje do kolejki
    }
}

int findLowestInQue(Kolejka* kolejka)
{
    int min = INT_MAX;
    Kolejka* tempk = new Kolejka;

    while(kolejka->stary){ //szukam najmniejszego elementu w kolejce
        Punkt* temp = kolejka->dequeue(); //sciagam najstarszy element kolejki

        if(temp->x+temp->y < min) //porownuje zdjety element z min
        {
            min=temp->x+temp->y;
        }
        tempk->enqueue(temp); //dodaje zdjety element do kolejki tymczasowej
    }

    while(tempk->stary) //teraz z kolejki tymczasowej dodaje elementy do starej kolejki
    {
        kolejka->enqueue(tempk->dequeue());
    }

    return min; //zwracam najmniejsza wartosc w kolejce
}

Kolejka* Posortuj(Kolejka* kolejka)
{
    Kolejka* result = new Kolejka;
    int x = kolejka->size;

    for(int i=0; i<x; i++) //funkcja wykonuje sie dla wszystkich elementow kolejki
    {
        int a = findLowestInQue(kolejka); //znajduje najmniejszy element w kolejce 1

        for(int j=0; j<kolejka->size; j++)  //i przelatuje po elementach kolejki
        {
            Punkt* d = kolejka->dequeue(); //zdejmuje element z kolejki 1
            if (d->x + d->y == a) //sprawdzam czy jest rowny minimum
            {
                result->enqueue(d); //jezeli tak to dodaje go do kolejki 2
            }
            else
            {
                kolejka->enqueue(d); //jesli nie to wraca na koniec kolejki 1
            }
        }

    }
    return result; //zwracam posortowana kolejke
}





int main() {
    ////////////ZADANIE1//////////////
    Punkt* lista = stworzListe();
    dodajsrednia(lista);
    //tworze liste o okreslonej ilosci elementow
    //dodajsrednia() dodaj do listy element zawierajacy srednie x i y


    ////////////ZADANIE2//////////////
    Stos* stos = zadanie2(lista);
    //Wykorzystuje przenoszenie elementow ze stosu z zadania 2 do zadania 3 wiec
    //po wykonaniu zadania 3 stos bedzie pusty
    //dla sprawdzenia efektu zadania 2 polecam zakomentowac zadanie 3


    ////////////ZADANIE3//////////////
    Kolejka* kolejka = new Kolejka;
    kolejka->przeniesDoKolejki(stos);
    kolejka = Posortuj(kolejka);
    //tworze nowa kolejka i przenosze do niej elementy ze stosu z zadania 2
    //nastepnie sortuje podana kolejke

    cout << "GEET";
    return 0;
}
