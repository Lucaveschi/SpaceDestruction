#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <cstdlib>
#include <time.h>
#include <fstream>

using namespace std;

int ncont = 0, ncont1; ///contatore nemico
int tictoc = 0;
int vite = 5;
int modalita = 1;///0 facile   1 difficile
int esc;
int cont;
int margini2 = 4;
char tasto3;
int x, y,esci;///x e y protagonista
int direzione = 0;
int proiettili = 5;
int randoms;
int pausato = 0;
char load;
int i,scelta;
char tasto, tasto2;
int tempo;
int punti = 0;
int livello = 1;
int s = 5;///sensibilità in milli secondi
int sparo;
int colpo;
int uscita = 0;
int l1 = 0;
int conts = 0;
int velo = 5;///velocità nemici
int conta = 0;
int lungezza = 106, h1 = 2, h2 = 48, contatore;
int margini = 0;
int win1 = rand() % 109;
int win2 = rand() % 46;
char nome[100];
string record;
int rcd;
char nomeg[100];
int l = 0, l2 = 109;
int margin = 0;

char colore[1];
int col1;
int col2;



int x1 = 10;
int y1 = 10;

int xa = 43;
int ya = 17;

int x2 = 30;
int y2 = 45;///liv 1



int x3 = 50;
int y3 = 25;

int xb = 24;
int yb = 28;

int x4 = 100;
int y4 = 45;///liv 2


int x5 = 3;
int y5 = 20;

int xc = 45;
int yc = 46;

int x6 = 36;
int y6 = 10;///liv. 3



int x7 = 43;
int y7 = 32;

int xd = 34;
int yd = 34;

int x8 = 56;
int y8 = 23;///liv 4







void gotoxy(int x, int y);
void gioco();
void pausa();
void gameover();
void vittoria();
void gotoxylento(int x1, int y1);
void setting();
void nemico1();
void nemico2();
void nemico3();
void nemico4();
void nemico5();
void nemico6();
void nemico7();
void nemico8();
void nemicoa();
void nemicob();
void nemicoc();
void nemicod();

void boss();






int main()
{

system("mode con cols=145");
system("mode con lines=51");
system("mode con cols=145");
system("title = SPACE DESTRUCTION");
system("color 02");










cout << "LOAD";
Sleep(1000);
cout << ".";
Sleep(1000);
cout << ".";
Sleep(1000);
cout << ".";
Sleep(1000);
system("cls");





int margine1 = 30;
int margine = 0;
int riga = 0;
int riga1 = 51;
do{

    gotoxylento(1,margine);printf("#");
    gotoxylento(50,margine1);printf("#");
    margine++;
    margine1--;




}while(margine != 31 && margine1 != 0);


do{
    riga++;
    riga1--;
    gotoxylento(riga,0);printf("#");
    gotoxylento(riga1,30);printf("#");


}while(riga != 51 && riga1 != 1);

gotoxy(10, 2);printf("           BENVENUTO");
Sleep(1000);
gotoxy(10, 4);printf("            IN THE");
Sleep(1000);
gotoxy(10, 6);printf("      SPACE DESTRUCTION");
Sleep(3000);

gotoxy(10, 10);printf("          [F1]      [F2]");
gotoxy(10, 11);printf("         GIOCA     ESCI");


gotoxy(121, 48);printf("DEVELOPED BY LUCA VESCHI");

do {



Sleep(s);
tictoc++;


if (GetAsyncKeyState(VK_F1)) {

system("cls");
gioco();

}

if (GetAsyncKeyState(VK_F2)) {


    system("cls");
    cout << "SPACE DESTRUCTION\n\n\nDEVELOPED BY LUCA VESCHI";
    Sleep(5000);
    return 0;




}


if(tictoc == 5){


    gotoxy(14, 6);printf("/");
    gotoxy(34, 6);printf("\\");




}

if(tictoc == 10){


    gotoxy(14, 6);printf("-");
    gotoxy(34, 6);printf("-");




}

if(tictoc == 15){


    gotoxy(14, 6);printf("|");
    gotoxy(34, 6);printf("|");




}

if(tictoc == 20){

        tictoc = 0;



    gotoxy(14, 6);printf("\\");
    gotoxy(34, 6);printf("/");



}


}while(esci != 1);

}




void gotoxy(int x, int y) {

COORD coord;


coord.X = x;
coord.Y = y;

SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}



void gotoxylento(int x1, int y1) {

system("color 02");
COORD coord;


coord.X = x1;
coord.Y = y1;

SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}




void gioco() {

x = 20;

y = 20;

if(pausato == 0){
gotoxy(50, 25);printf("COME TI CHIAMI?");
gotoxy(50, 26);printf("[_____________]");
gotoxy(51, 26);scanf("%s", nome);


system("cls");
sndPlaySound("sound.wav", ASYNCH);


    FILE * file; //dichiara il nome del file
    file = fopen ("punti.pt","r"); // directoy del file


    fscanf(file,"%i",&rcd);

    fclose(file);

}


gotoxy(120, 49);printf("DEVELOPED BY LUCA VESCHI");

gotoxy(115, 3);printf("VITE:   DIFFICOLTA': ");///scritte ai lati
gotoxy(115, 5);printf("PUNTEGGIO: ");
gotoxy(115, 7);printf("LIVELLO: ");
gotoxy(115, 9);printf("X:    Y: ");
gotoxy(115, 11);printf("MISSILI: ");
gotoxy(115, 13);printf("F/s: ");
gotoxy(115, 15);printf("RECORD: %i PUNTI", rcd);
do{///disegna i bordi

gotoxy(1, 1);printf("--------------------------------------------------------------------------------------------------------------  |-----------------------------|");///110
gotoxy(1, 50);printf("--------------------------------------------------------------------------------------------------------------  |-----------------------------|");///110
margini++;
gotoxylento(1, margini); printf("|");
gotoxylento(109, margini); printf("|");

}while(margini != 49);


if(pausato == 0){


gotoxy(115, 18);printf("CIAO %s!", nome);
Sleep(3000);
gotoxy(115, 18);printf("                  ");
gotoxy(115, 18);printf("CE LA FARAI A SUPERARE");
gotoxy(115, 19);printf("TUTTI E 5 I LIVELLI E");
gotoxy(115, 20);printf("A BATTERE IL BOSS?");
gotoxy(115, 21);printf("VEDREMO...");
Sleep(5000);
gotoxy(115, 18);printf("                       ");
gotoxy(115, 19);printf("                       ");
gotoxy(115, 20);printf("                       ");
gotoxy(115, 21);printf("                       ");

}


do {


Sleep(s);///sensibilità
uscita++;
ncont++;
ncont1++;
cont++;
conts++;
conta++;

if(punti == 10){

        livello = 2;
        velo = 4;


}

if(punti == 20){

    livello = 3;
    velo = 3;
}


if(punti == 30){

    livello = 4;
    velo = 2;
}


if(punti == 50){

    livello = 4;
    velo = 1;
}


if(punti == 70){

    livello = 5;
    velo = 1;
}




conts = 0;


if(GetAsyncKeyState(VK_LEFT)){ ///spostamento sinistra



gotoxy(x, y-1);printf("     ");
gotoxy(x, y);printf("      ");
gotoxy(x, y+1);printf("     ");

x--; ///sinistra

gotoxy(x, y-1);printf("   /|");
gotoxy(x, y);printf("-[##]=");
gotoxy(x, y+1);printf("   \\|");

direzione = 0;


}



if(GetAsyncKeyState(VK_RIGHT)){///spostamento destra

gotoxy(x, y-1);printf("     ");
gotoxy(x, y);printf("      ");
gotoxy(x, y+1);printf("     ");

x++; ///destra

gotoxy(x, y-1);printf("|\\   ");
gotoxy(x, y);printf("=[##]-");
gotoxy(x, y+1);printf("|/    ");

direzione = 1;


}



if(GetAsyncKeyState(VK_DOWN)){///spostamento giù

if (direzione == 0){///Controlli direzionali

gotoxy(x, y-1);printf("     ");
gotoxy(x, y);printf("      ");
gotoxy(x, y+1);printf("     ");

y++; ///giù

gotoxy(x, y-1);printf("   /|");
gotoxy(x, y);printf("-[##]-");
gotoxy(x, y+1);printf("   \\|");

}

else if (direzione == 1) {

gotoxy(x, y-1);printf("     ");
gotoxy(x, y);printf("      ");
gotoxy(x, y+1);printf("     ");

y++; ///giù

gotoxy(x, y-1);printf("|\\   ");
gotoxy(x, y);printf("=[##]-");
gotoxy(x, y+1);printf("|/    ");

}


}



if(GetAsyncKeyState(VK_UP)){///spostamento su

if (direzione == 0){///Controlli direzionali

gotoxy(x, y-1);printf("     ");
gotoxy(x, y);printf("      ");
gotoxy(x, y+1);printf("     ");

y--; ///su

gotoxy(x, y-1);printf("   /|");
gotoxy(x, y);printf("-[##]=");
gotoxy(x, y+1);printf("   \\|");

}
else if (direzione == 1) {

gotoxy(x, y-1);printf("     ");
gotoxy(x, y);printf("      ");
gotoxy(x, y+1);printf("     ");

y--; ///su

gotoxy(x, y-1);printf("|\\   ");
gotoxy(x, y);printf("=[##]-");
gotoxy(x, y+1);printf("|/    ");


}



}


if(GetAsyncKeyState(VK_F1)){///sparo



if(proiettili == 0){
    gotoxy(x5, y5);printf(" ");
    continue;
}



proiettili--;


if (direzione == 1) {///destra
    int colpo = 0;
    colpo = x+6;
    gotoxy(colpo,y);printf("-");
    do{
            gotoxy(colpo,y);printf("  ");
            colpo++;
            gotoxy(colpo,y);printf("-");
            Sleep(25);
            gotoxy(colpo,y);printf(" |");

            if(colpo == win1 && y == win2){
                sparo = 1;
            }




    }while(colpo != 108);
    gotoxy(colpo,y);printf(" |");


}

else if (direzione == 0){///sinistra

int colpo;
    colpo = x-2;
    gotoxy(colpo,y);printf("-");
    do{
            gotoxy(colpo,y);printf("  ");
            colpo--;
            gotoxy(colpo,y);printf("-");
            Sleep(25);

            if(colpo == win1 && y == win2){
                sparo = 1;
            }





    }while(colpo != 1);
gotoxy(colpo,y);printf("| ");
}

}


if(GetAsyncKeyState(VK_ESCAPE)){///pausa

    pausa();

}



if(GetAsyncKeyState(VK_F5)){///facile

    modalita = 0;

}


if(GetAsyncKeyState(VK_F6)){///difficile

    modalita = 1;

}


if(GetAsyncKeyState(VK_F11) && GetAsyncKeyState(VK_F12)){///trucco boss


    punti = 65;
    livello = 4;


}



if(modalita == 0){

if (x == 102) {///controlli

    x--;
}

if (x == 3) {
    x++;
}

if (y == 49) {
    y--;
}


if (y == 3) {
    y++;
}



}



else if (modalita == 1) {

if (x == 104) {

    x--;
    gotoxy(x-3,y);printf("BOOOM");
    Sleep(1000);
    gotoxy(x, y-1);printf("    |");
    gotoxy(x, y);printf("     |");
    gotoxy(x, y+1);printf("    |");
    gotoxy(x-3,y);printf("  |");
    vite--;

    x = 20;
    y = 20;
}

if (x == 2) {
    x++;
    gotoxy(x+3,y);printf("BOOOM");
    Sleep(1000);
    gotoxy(x, y-1);printf("     ");
    gotoxy(x, y);printf("         ");
    gotoxy(x, y+1);printf("     ");
    gotoxy(x-3,y);printf(" |  ");
    x = 20;
    y = 20;
    vite--;


}

if (y == 49) {
    y--;
    gotoxy(x,y-1);printf("BOOOM");
    Sleep(1000);
    gotoxy(x, y-1);printf("     ");
    gotoxy(x, y);printf("      ");
    gotoxy(x, y+1);printf("     ");
    gotoxy(x,y+1);printf("-----");
    gotoxy(1, 1);printf("--------------------------------------------------------------------------------------------------------------  |-----------------------------|");///110
    gotoxy(1, 50);printf("--------------------------------------------------------------------------------------------------------------  |-----------------------------|");///110
    vite--;
    x = 20;
    y = 20;


}


if (y == 3) {
    y++;
    gotoxy(x,y+1);printf("BOOOM");
    Sleep(1000);
    gotoxy(x, y-1);printf("     ");
    gotoxy(x, y);printf("      ");
    gotoxy(x, y+1);printf("     ");
    gotoxy(x,y-1);printf("-----");
    gotoxy(1, 1);printf("--------------------------------------------------------------------------------------------------------------  |-----------------------------|");///110
    gotoxy(1, 50);printf("--------------------------------------------------------------------------------------------------------------  |-----------------------------|");///110
    vite--;
    x = 20;
    y = 20;
}


}


if (modalita == 0) {

    gotoxy(136, 3);printf("%i", modalita);

}

if (modalita == 1) {

    gotoxy(136, 3);printf("%i", modalita);

}




if(vite == 0) {

    gameover();
}




///nemici inizio


if (x1 == x && y1 == y){///controlli vita nemico 1


    vite--;
    gotoxy(x, y-1);printf("     ");
    gotoxy(x, y);printf("      ");
    gotoxy(x, y+1);printf("     ");

    x = 50;
    y = 25;

}


    if (xc == x && yc == y){///controlli vita nemico c


    vite--;
    gotoxy(x, y-1);printf("     ");
    gotoxy(x, y);printf("      ");
    gotoxy(x, y+1);printf("     ");

    x = 50;
    y = 25;

    }

if (x2 == x && y2 == y){///controllo vita nemico 2


    vite--;
    gotoxy(x, y-1);printf("     ");
    gotoxy(x, y);printf("      ");
    gotoxy(x, y+1);printf("     ");
    x = 50;
    y = 25;


}
    if (xa == x && ya == y){///controlli vita nemico a


    vite--;
    gotoxy(x, y-1);printf("     ");
    gotoxy(x, y);printf("      ");
    gotoxy(x, y+1);printf("     ");

    x = 50;
    y = 25;

    }

    if (x3 == x && y3 == y){///controlli vita nemico 3


    vite--;
    gotoxy(x, y-1);printf("     ");
    gotoxy(x, y);printf("      ");
    gotoxy(x, y+1);printf("     ");

    x = 50;
    y = 25;


}


if(x4 == x && y4 == y){///controlli vita nemico 4

    vite--;
    gotoxy(x, y-1);printf("     ");
    gotoxy(x, y);printf("      ");
    gotoxy(x, y+1);printf("     ");
    x = 50;
    y = 25;

}

if(x5 == x && y5 == y){///controlli vita nemico 5

    vite--;
    gotoxy(x, y-1);printf("     ");
    gotoxy(x, y);printf("      ");
    gotoxy(x, y+1);printf("     ");
    x = 50;
    y = 25;

}

    if (xb == x && yb == y){///controlli vita nemico b


    vite--;
    gotoxy(x, y-1);printf("     ");
    gotoxy(x, y);printf("      ");
    gotoxy(x, y+1);printf("     ");

    x = 50;
    y = 25;

    }

if(x6 == x && y6 == y){///controlli vita nemico 6

    vite--;
    gotoxy(x, y-1);printf("     ");
    gotoxy(x, y);printf("      ");
    gotoxy(x, y+1);printf("     ");
    x = 50;
    y = 25;

}

    if (x7 == x && y7 == y){///controlli vita nemico 7


    vite--;
    gotoxy(x, y-1);printf("     ");
    gotoxy(x, y);printf("      ");
    gotoxy(x, y+1);printf("     ");

    x = 50;
    y = 25;
    }



    if (x8 == x && y8 == y){///controlli vita nemico 8


    vite--;
    gotoxy(x, y-1);printf("     ");
    gotoxy(x, y);printf("      ");
    gotoxy(x, y+1);printf("     ");

    x = 50;
    y = 25;


    }



    if (xd == x && yd == y){///controlli vita nemico d


    vite--;
    gotoxy(x, y-1);printf("     ");
    gotoxy(x, y);printf("      ");
    gotoxy(x, y+1);printf("     ");

    x = 50;
    y = 25;

    }



if(ncont == velo){

    gotoxy(x1, y1);printf(" ");///nemico 1
    gotoxy(x2, y2);printf(" ");///nemico 2
    gotoxy(x3, y3);printf(" ");///nemico 3
    gotoxy(x4, y4);printf(" ");///nemico 4
    gotoxy(x5, y5);printf(" ");///nemico 5
    gotoxy(x6, y6);printf(" ");///nemico 6
    gotoxy(x7, y7);printf(" ");///nemico 7
    gotoxy(x8, y8);printf(" ");///nemico 8
    gotoxy(xa, ya);printf(" ");///nemico a
    gotoxy(xb, yb);printf(" ");///nemico b
    gotoxy(xc, yc);printf(" ");///nemico c
    gotoxy(xd, yd);printf(" ");///nemico d


ncont = 0;


nemico1();

nemicoa();

nemico2();




if(punti > 10){

nemico3();

nemicob();

nemico4();




}///fine livello 2 in poi

if(livello > 2){///dal livello 3 in poi



nemico5();

nemicoc();

nemico6();




}

if(livello > 3){///livello 4

nemico7();

nemicod();

nemico8();




}




if(livello > 4){


gotoxy(115, 18);printf("ARRIVA IL BOSS ATTENZIONE!!!");

/*if(win2 < 6 || win2 > 46){

    win2 = rand() % 46;


}
*/

if (x1 == h2) {///controlli

    x1 = h1+2;
}

if (x1 == h1) {
    x1 = h2-2;
}

if (y1 == l2) {
    y1 = l+2;
}


if (y1 == l) {
    y1 = l2-2;
}




if (x2 == h2) {///controlli

    x2 = h1+2;
}

if (x2 == h1) {
    x2 = h2-2;
}

if (y2 == l2) {
    y2 = l+2;
}


if (y2 == l) {
    y2 = l2-2;
}






if (xa == h2) {///controlli

    xa = h1+2;
}

if (xa == h1) {
    xa = h2-2;
}

if (ya == l2) {
    ya = l+2;
}


if (ya == l) {
    ya = l2-2;
}






if (x3 == h2) {///controlli

    x3 = h1+2;
}

if (x3 == h1) {
    x3 = h2-2;
}

if (y3 == l2) {
    y3 = l+2;
}


if (y3 == l) {
    y3 = l2-2;
}





if (x4 == h2) {///controlli

    x4 = h1+2;
}

if (x4 == h1) {
    x4 = h2-2;
}

if (y4 == l2) {
    y4 = l+2;
}


if (y4 == l) {
    y4 = l2-2;
}




if (xb == h2) {///controlli

    xb = h1+2;
}

if (xb == h1) {
    xb = h2-2;
}

if (yb == l2) {
    yb = l+2;
}


if (yb == l) {
    yb = l2-2;
}








if (x5 == h2) {///controlli

    x5 = h1+2;
}

if (x5 == h1) {
    x5 = h2-2;
}

if (y5 == l2) {
    y5 = l+2;
}


if (y5 == l) {
    y5 = l2-2;
}






if (x6 == h2) {///controlli

    x6 = h1+2;
}

if (x6 == h1) {
    x6 = h2-2;
}

if (y6 == l2) {
    y6 = l+2;
}


if (y6 == l) {
    y6 = l2-2;
}




if (xc == h2) {///controlli

    xc = h1+2;
}

if (xc == h1) {
    xc = h2-2;
}

if (yc == l2) {
    yc = l+2;
}


if (yc == l) {
    yc = l2-2;
}



if (x7 == h2) {///controlli

    x7 = h1+2;
}

if (x7 == h1) {
    x7 = h2-2;
}

if (y7 == l2) {
    y7 = l+2;
}


if (y7 == l) {
    y7 = l2-2;
}



if (x8 == h2) {///controlli

    x8 = h1+2;
}

if (x8 == h1) {
    x8 = h2-2;
}

if (y8 == l2) {
    y8 = l+2;
}


if (y8 == l) {
    y8 = l2-2;
}



if (xd == h2) {///controlli

    xd = h1+2;
}

if (xd == h1) {
    xd = h2-2;
}

if (yd == l2) {
    yd = l+2;
}


if (yd == l) {
    yd = l2-2;
}








contatore++;



gotoxy(win1, win2);printf("/*\\");




if(contatore  == 20){

    contatore = 0;


    h1++;
    h2--;
    l++;
    l2--;


    gotoxy(2, h1);printf("**********************************************************************************************************");///106 **********************************************************************************************************
    gotoxy(2, h2);printf("**********************************************************************************************************");///106



    }


    do{

    margin++;

    gotoxy(l, margin);printf("*");
    gotoxy(l2, margin);printf("*");






    }while(margin != 49);

margin = 0;


    if(sparo == 1){


     gotoxy(win1, win2-1);printf("\\ $% //() =)&$%%& )%%$£");
     gotoxy(win1, win2);printf("BOOOOOOOOOOOOOOOM!");
     gotoxy(win1, win2+1);printf("!//*//-///--+- ()=//(&?");
     Sleep(1000);
     vittoria();



    }


    if(y == h1 ){

        gameover();


    }

if(y == h2 ){

        gameover();


    }


    if(h1 == h2){

        gameover();

    }

    if(x == l){
        gameover();

    }

    if(x+6 == l2){
        gameover();

    }







}

}







///fine nemici




gotoxy(126, 5);printf("%i",punti);///stampa i valori dellle scritte a lato
gotoxy(117, 9);printf("%i",x);
gotoxy(123, 9);printf("%i",y);
gotoxy(124, 7);printf("%i",livello);
gotoxy(124, 11);printf("%i",proiettili);
gotoxy(121, 3);printf("%i", vite); ///conteggio vite a video
gotoxy(120, 13);printf("%i",s);///Velocità di aggiornamento schermo
gotoxy(x1, y1);printf("*");///nemico 1
gotoxy(x2, y2);printf("#");///nemico 2
gotoxy(x3, y3);printf("%%");///nemico 3
gotoxy(x4, y4);printf("°");///nemico 4
gotoxy(x5, y5);printf("+");///nemico 5
gotoxy(x6, y6);printf("°");///nemico 6
gotoxy(x7, y7);printf("°");///nemico 7
gotoxy(x8, y8);printf("!");///nemico 8
gotoxy(xa, ya);printf("|");///nemico a
gotoxy(xb, yb);printf("-");///nemico b
gotoxy(xc, yc);printf(":");///nemico c
gotoxy(xd, yd);printf("°");///nemico d


if(cont == 100){

    cont = 0;
    punti++;


}




}while(esci != 1);




}





void pausa() {


pausato = 1;

system("cls");

gotoxy(20, 3);printf("*--------------------------------------------------------------------*");
gotoxy(20, 23);printf("*--------------------------------------------------------------------*");




gotoxy(24, 5);printf("COMANDI:");
gotoxy(24, 7);printf("ESC = pausa");
gotoxy(24, 8);printf("Freccie direzionali = movimento 'astronave'");
gotoxy(24, 9);printf("F1 = spara");
gotoxy(24, 10);printf("F5 = difficolta' facile");
gotoxy(24, 11);printf("F6 = difficolta' difficile");

gotoxy(24, 15);printf(" [F1]      [F2]    [F3]");
gotoxy(24, 16);printf("CONTINUA   ESCI   SETTING");

do {









if(GetAsyncKeyState(VK_F2)){

    esci = 1;
    esc = 1;

}


if(GetAsyncKeyState(VK_F1)){

    margini = 0;
    system("cls");///cancella lo schermo e ricrea il gioco
    gioco();


}


if(GetAsyncKeyState(VK_F3)){

    system("cls");
    setting();



}




}while(esc != 1);




}




void gameover() {

system("cls");

int margine = 0;
int riga = 0;
do{
    margine++;
    gotoxylento(1,margine);printf("#");
    gotoxylento(50,margine);printf("#");




}while(margine != 30);


do{
    riga++;
    gotoxylento(riga,1);printf("#");
    gotoxylento(riga,30);printf("#");


}while(riga != 50);

do {
        tasto = getch();

        gotoxy(10, 2);printf("|---------------|");
        gotoxy(10, 3);printf("|   GAME OVER   |");
        gotoxy(10, 4);printf("|---------------|");
        gotoxy(10, 7);printf("PUNTEGGIO: %i", punti);

        gotoxy(10, 11);printf(" [F1]          [F2]");
        gotoxy(10, 12);printf("RICOMINCIA     ESCI");

if(GetAsyncKeyState(VK_F2)){

    esci = 1;
    esc = 1;

}


if(GetAsyncKeyState(VK_F1)){

    vite = 5;
    proiettili = 5;
    livello = 1;
    punti = 0;
    margini = 0;
    h1 = 2;
    h2 = 48;
    l = 0;
    l1 = 109;
    contatore = 0;
    sparo = 0;
    gioco();


}

if(rcd >= punti){


    gotoxy(10, 9);printf("NON HAI BATTUTO IL RECORD.");




}

if(rcd < punti){


    gotoxy(10, 9);printf("HAI BATTUTO IL RECORD COMLIMENTI!!");


    ofstream f("punti.pt");


    f<<punti;


    f.close();


}









}while(esc != 1);

}



void vittoria() {

margini = 0;
system("cls");



do{///disegna i bordi

gotoxy(1, 1);printf("--------------------------------------------------------------------------------------------------------------  |-----------------------------|");///110
gotoxy(1, 50);printf("--------------------------------------------------------------------------------------------------------------  |-----------------------------|");///110
margini ++;
gotoxy(1, margini); printf("|");
gotoxy(109, margini); printf("|");

}while(margini != 49);

do{



gotoxy(50, 20);printf("HAI VINTO!!!!");
gotoxy(50, 26);printf("[F1]RICOMINCIA     [F2]ESCI");

gotoxy(50, 22);printf("PUNTEGGIO: %i",punti);




if(GetAsyncKeyState(VK_F2)){

    esci = 1;
    esc = 1;

}


if(GetAsyncKeyState(VK_F1)){

    vite = 5;
    proiettili = 5;
    livello = 1;
    punti = 0;
    margini = 0;
    h1 = 2;
    h2 = 48;
    l = 0;
    l1 = 109;
    contatore = 0;
    sparo = 0;
    system("cls");
    gioco();


}



if(rcd >= punti){


    gotoxy(50, 24);printf("NON HAI BATTUTO IL RECORD.");




}

if(rcd < punti){


    gotoxy(50, 24);printf("HAI BATTUTO IL RECORD COMLIMENTI!!");



    ofstream f("punti.pt");


    f<<punti;


    f.close();


}










}while (esc != 1);

}









void setting(){

int uno, due;


uno = 10;



gotoxy(20, 3);printf("*--------------------------------------------------------------------*");
gotoxy(20, 23);printf("*--------------------------------------------------------------------*");


gotoxy(24, 10);printf("[ ]SPEED REFRESCH [-|-|-|-|-|-|-|-|-]       F/s");
gotoxy(24, 13);printf("[ ]COLOR          [-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-]       ");
gotoxy(20, 5);printf("-----");
gotoxy(20, 6);printf("|ESC|");
gotoxy(20, 7);printf("-----");


if(s == 5){

    due = 51;


}

if(s == 6){

    due = 53;


}

if(s == 7){

    due = 55;

}

if(s == 8){

    due = 57;


}


if(s == 9){

    due = 59;


}


if(s == 4){

    due = 49;


}


if(s == 3){

    due = 47;


}


if(s == 2){

    due = 45;


}

if(s == 1){

    due = 43;


}




for(;;){


Sleep(50);
 gotoxy(25, uno);printf("*");
 gotoxy(due, 11);printf(" ");


 if(GetAsyncKeyState(VK_RIGHT)){

    due = due + 2;
    s++;

    if(due > 60){

        due = due - 2;
        s--;



    }

 }

  if(GetAsyncKeyState(VK_LEFT)){

    due = due - 2;
    s--;

    if(due < 43){

        due = due + 2;
        s++;

    }

 }




if(GetAsyncKeyState(VK_ESCAPE)){


    pausa();



}

gotoxy(due, 11);printf("^");
gotoxy(66, 10);printf("%i ", s);

}


if(GetAsyncKeyState(VK_UP)){





}





}




void nemico1(){


///variabili random nemici
    int nran = rand() % 4;






if (x1 == 102) {///controlli

    x1 = 4;
}

if (x1 == 3) {
    x1 = 101;
}

if (y1 == 49) {
    y1 = 4;
}


if (y1 == 3) {
    y1 = 47;
}


    if(nran == 1) {

        x1++;

    }

    if(nran == 2) {

        y1++;


    }

    if(nran == 3) {

        x1--;


    }

    if(nran == 4) {

        y1--;



    }




}


void nemico2(){


///variabili random nemici

    int nran1 = rand() % 4;







if (x2 == 102) {///controlli

    x2 = 4;
}

if (x2 == 3) {
    x2 = 101;
}

if (y2 == 49) {
    y2 = 3;
}


if (y2 == 3) {
    y2 = 47;
}


if(nran1 == 1) {

        x2--;


    }

    if(nran1 == 2) {

        y2--;


    }

    if(nran1 == 3) {

        x2++;


    }

    if(nran1 == 4) {

        y2++;



    }





}


void nemico3(){

///variabili random nemici
    int nrano = rand() % 4;







if (x3 == 102) {///controlli

    x3 = 4;
}

if (x3 == 3) {
    x3 = 101;
}

if (y3 == 49) {
    y3 = 4;
}


if (y3 == 3) {
    y3 = 47;
}


    if(nrano == 1) {

        x3++;


    }

    if(nrano == 2) {

        y3--;


    }

    if(nrano == 3) {

        x3--;


    }

    if(nrano == 4) {

        y3++;



    }




}


void nemico4(){


///variabili random nemici

    int nran2 = rand() % 4;






if (x4 == 102) {///controlli

    x4 = 4;
}

if (x4 == 3) {
    x4 = 101;
}

if (y4 == 49) {
    y4 = 4;
}


if (y4 == 3) {
    y4 = 47;
}


    if(nran2 == 1) {

        x4++;


    }

    if(nran2 == 2) {

        y4++;


    }

    if(nran2 == 3) {

        x4--;


    }

    if(nran2 == 4) {

        y4--;



    }





}


void nemico5(){

///variabili random nemici

    int nram3 = rand() % 4;





if (x5 == 102) {///controlli

    x5 = 4;
}

if (x5 == 3) {
    x5 = 101;
}

if (y5 == 49) {
    y5 = 4;
}


if (y5 == 3) {
    y5 = 47;
}


    if(nram3 == 1) {

        x5++;


    }

    if(nram3 == 2) {

        y5++;


    }

    if(nram3 == 3) {

        x5--;


    }

    if(nram3 == 4) {

        y5--;



    }




///fine 5




}


void nemico6(){

///variabili random nemici

    int nram4 = rand() % 4;





///inizio 6

if (x6 == 102) {///controlli

    x6 = 4;
}

if (x6 == 3) {
    x6 = 101;
}

if (y6 == 49) {
    y6 = 4;
}


if (y6 == 3) {
    y6 = 47;
}


    if(nram4 == 1) {

        x6++;


    }

    if(nram4 == 2) {

        y6++;


    }

    if(nram4 == 3) {

        x6--;


    }

    if(nram4 == 4) {

        y6--;



    }


///fine 6




}


void nemico7(){

///variabili random nemici

    int nran7 = rand() % 4;






///inizio 7
if (x7 == 102) {///controlli

    x7 = 4;
}

if (x7 == 3) {
    x7 = 101;
}

if (y7 == 49) {
    y7 = 4;
}


if (y7 == 3) {
    y7 = 47;
}


    if(nran7 == 1) {

        x7++;


    }

    if(nran7 == 2) {

        y7++;


    }

    if(nran7 == 3) {

        x7--;


    }

    if(nran7 == 4) {

        y7--;



    }///fine 7





}


void nemico8(){

///variabili random nemici

    int nran9 = rand() % 4;



///inizio 8

if (x8 == 102) {///controlli

    x8 = 4;
}

if (x8 == 3) {
    x8 = 101;
}

if (y8 == 49) {
    y8 = 4;
}


if (y8 == 3) {
    y8 = 47;
}


    if(nran9 == 1) {

        x8++;


    }

    if(nran9 == 2) {

        y8++;


    }

    if(nran9 == 3) {

        x8--;


    }

    if(nran9 == 4) {

        y8--;

    }///fine 8




}



void nemicoa(){

///variabili random nemici

    int nran4 = rand() % 4;







if (xa == 102) {///controlli

    xa = 4;
}

if (xa == 3) {
    xa = 101;
}

if (ya == 49) {
    ya = 4;
}


if (ya == 3) {
    ya = 47;
}


    if(nran4 == 1) {

        xa++;


    }

    if(nran4 == 2) {

        ya++;


    }

    if(nran4 == 3) {

        xa--;


    }

    if(nran4 == 4) {

        ya--;



    }




}


void nemicob(){

///variabili random nemici

    int nran5 = rand() % 4;







if (xb == 102) {///controlli

    xb = 4;
}

if (xb == 3) {
    xb = 101;
}

if (yb == 49) {
    yb = 4;
}


if (yb == 3) {
    yb = 47;
}


    if(nran5 == 1) {

        xb++;


    }

    if(nran5 == 2) {

        yb++;


    }

    if(nran5 == 3) {

        xb--;


    }

    if(nran5 == 4) {

        yb--;



    }






}


void nemicoc(){

///variabili random nemici

    int nran6 = rand() % 4;







///inizio c

if (xc == 102) {///controlli

    xc = 4;
}

if (xc == 3) {
    xc = 101;
}

if (yc == 49) {
    yc = 4;
}


if (yc == 3) {
    yc = 47;
}


    if(nran6 == 1) {

        xc++;


    }

    if(nran6 == 2) {

        yc++;


    }

    if(nran6 == 3) {

        xc--;


    }

    if(nran6 == 4) {

        yc--;



    }


///fine c




}


void nemicod(){


///variabili random nemici

    int nran8 = rand() % 4;




    ///inizio d


if (xd == 102) {///controlli

    xd = 4;
}

if (xd == 3) {
    xd = 101;
}

if (yd == 49) {
    yd = 4;
}


if (yd == 3) {
    yd = 47;
}


    if(nran8 == 1) {

        xd++;


    }

    if(nran8 == 2) {

        yd++;


    }

    if(nran8 == 3) {

        xd--;


    }

    if(nran8 == 4) {

        yd--;



    }


    ///fine d




}






















///DEVELOPED BY LUCA VESCHI 2014 (c)



