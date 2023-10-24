#include <iostream>
#import <random>
using namespace std;

struct Punkt{
    int x,y;
    Punkt* next;

    Punkt(): x(),y(){}
    Punkt(int zakres): x(rand()%zakres), y(rand()%zakres), next(nullptr){}
    Punkt(Punkt & a): x(a.x), y(a.y){}
};

Punkt* zadanie1(int zakres)
{
    ///////TWORZENIE LISTY
    Punkt* head = new Punkt(zakres);
    Punkt* temp = head;
    for(int i=0; i<9; i++)
    {
        temp->next = new Punkt(zakres);
        temp=temp->next;
    }

    ///////SUMOWANIE ELEMENTOW
    int suma=0;
    temp=head;
    while(temp)
    {
        suma+=temp->x;
        suma+=temp->y;
        temp=temp->next;
    }

    ///////WYLICZANIE SREDNIEJ
    int srednia = suma/20;
    //cout << "Suma: " << suma << " , Srednia: " << srednia << "\nSuma ze srednia: " << suma+srednia;
    return head;
}

struct Stos{
    int x,y;
    Stos* next;

    Stos(): x(-1),y(-1){}
    Stos(int x, int y): x(x), y(y){}
    Stos(Punkt* a): x(a->x),y(a->y){}
    void push(Punkt* a);
};

void Stos::push(Punkt* a) {
    if (x < 0) {
        x = a->x;
        y = a->y;
    } else {
        Stos *temp = new Stos(x,y);
        x = a->x;
        y = a->y;
        temp->next = next;
        next = temp;
    }
}

Stos* zadanie2(Punkt* b)
{
    Stos* a = new Stos();
    Punkt* tempP = b;
    while(tempP)
    {
        a->push(tempP);
        tempP=tempP->next;
    }

    int max=-1;

    Stos* temp = a;
    while(temp)
    {
        if(temp->x+temp->y>max)
        {
            max=temp->x+temp->y;
        }
        temp=temp->next;
    }
    temp=a;
    while(temp)
    {
        if(temp->x+temp->y == max)
        {
            if(temp->next)
            {
                temp->x = temp->next->x;
                temp->y = temp->next->y;
                temp->next = temp->next->next;
            }
            return a;
        }
        if(!temp->next->next)
        {
            cout << "LAST ELEMENT IS MAX";
            temp->next=nullptr;
        }
        temp=temp->next;
    }



    return a;


}
int main() {
    srand(time(nullptr));

    Punkt *zad1 = zadanie1(100);

    for(int i=0; i<30; i++) { Stos *zad2 = zadanie2(zad1); }




    return 0;


}
