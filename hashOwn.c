/*
 * Autor: Samuel Hetteš
 * Predmet: Dátové šturktúry a algoritmy
 * Zadanie: Vyhľadávanie v dynamických množinách
 * Metóda: Hashovacia tabuľka s reťazením
 * Prostredie: Visual Studio Code
 * Dátum: 5. 4. 2021
*/



/*HEADERS*/

#include <stdio.h>
#include <stdlib.h>    //alokácia pamäti
#include <math.h>    //sqrt

#include "hashOwn.h"

int collisionsHashOwn = 0;


/*FUNCTIONS*/

//nájdenie najväčšieho prvočísla v danom rozsahu
unsigned long long getPrime(unsigned long long number){
    int divisor;    //deliteľ čísla (pracujeme s ňou ako s boolovskou prem.)
    unsigned long long root;    //odmocnina 

    for(unsigned long long i = number; i >= 2; i--){    //hľadaj od najväčšieho čísla po najmenšie
        divisor = 0;
        root = sqrt(i);    //vypočítaj odmocninu z i

        for(unsigned long long j = 2; j < root; j++){    //hľadáme deliteľov, stačí po odmocninu z i
            if((i % j) == 0){    //ak je číslo deliteľné, označ deliteľa ako true a vyskoč z cyklu
                divisor = 1;
                break;
            }
        }

        if(!divisor)    //ak sa nenašiel žiadny deliteľ vráť toto prvočíslo
            return i;
    }

    printf("Size of hash table is not a prime number\n");
    return number;    //ak nebolo nájdené prvočíslo, vráť dané číslo
}

//inicializácia hashovacej tabuľky
HASHTABLE *initHashOwn(HASHTABLE *hashTable, unsigned long long tableSize){
    if(hashTable){    //ak už prebehla inicializácia ukonči funkciu
        return hashTable;
    }

    tableSize = getPrime(tableSize);    //veľkosť tabuľky skresáme na najväčšie prvočíslo v danom rozsahu

    if(!(hashTable = (HASHTABLE *) malloc(sizeof(HASHTABLE)))){    //alokácia miesta pre tabuľku
        printf("Allocation of memory for hash table failed\n");
        return NULL;
    }

    hashTable->size = tableSize;    //nastavenie veľkosti tabuľky
    hashTable->inserted = 0;    //počet vložených prvkov

    if(!(hashTable->data = (DATA **) malloc(hashTable->size * sizeof(DATA *)))){    //alokácia miesta pre uloženie ukazovateľov na dáta
        printf("Allocation of memory for hash table failed\n");
        free(hashTable);
        return NULL;
    }

    for(unsigned long long i = 0; i < hashTable->size; i++)    //nastavenie ukazovateľov na NULL
        hashTable->data[i] = NULL;

    return hashTable;
}

//vytvorenie miesta pre uloženie dát
DATA *createData(unsigned long long key){
    DATA *data;

    if(!(data = (DATA *) malloc(sizeof(DATA)))){    //alokácia miesta pre dáta
        printf("Allocation of memory for data failed\n");
        return NULL;
    }

    data->key = key;    //uloženie daného kľúča
    data->next = NULL;    //pripájame na koniec, preto nasledovník je NULL

    return data;
}

//zahashovanie dát - multiplication method
unsigned long long hashData(HASHTABLE *hashTable, unsigned long long key){
    return (key % hashTable->size);
}

//vloženie dát do tabuľky
int insertHashOwn(HASHTABLE *hashTable, unsigned long long key){
    if(!hashTable)    //ak neprebehla inicializácia tabuľky vráť 0
        return 0;

    /* Pokiaľ chcete automatické zväčšovanie tabuľky pri polovičom zaplnení, treba odkomentovať túto časť kódu
    if((float)hashTable->inserted / (float)hashTable->size >= 0.5)
        hashTable = resizeHashTable(hashTable);
    */

    unsigned long long index = hashData(hashTable, key);    //zahashovanie dát

    if(hashTable->data[index]){    //ak na danom indexe už niečo je, nastáva kolízia
        DATA *data = hashTable->data[index];

        if(key == data->key)    //porovnaj daný kľúč s pridávaným
                return 0;    //ak sa zhoduje, nepridávaj dáta, ukonči funkciu

        while(data->next){    //ak dáta na niečo ukazujú
            collisionsHashOwn++;
            data = data->next;    //prejdi na nasledovníka

            if(key == data->key)    //opäť porovnaj daný kľúč, v prípade zhody ukonči funkciu
                return 0;
        }
        
        data->next = createData(key);    //získali sme dáta, ktoré nemajú nasledovníka, preto vytvoríme miesto pre nové dáta, ktoré budú nasledovníkom

        if(data->next == NULL)    //ak sa nepodarilo vytvoriť miesto pre dáta, ukonči funkciu
            return 0;
    }
    else{
        hashTable->data[index] = createData(key);    //ak na indexe nič nie je, vytvor miesto pre nové dáta a ulož ich na tomto indexe

        if(hashTable->data[index] == NULL)    //ak sa nepodarilo vytvoriť miesto pre dáta, ukonči funkciu
            return 0;
    }

    hashTable->inserted++;    //zvýš počet vložených dát

    return 1;    //ak bolo vloženie úspešné, vráť 1
}

//funkcia pre zväčšenie tabuľky
HASHTABLE *resizeHashTable(HASHTABLE *hashTable){
    unsigned long long tableSize = hashTable->size;

    hashTable->size = getPrime(hashTable->size * 2);    //nová veľkosť tabuľky bude dvojnásobok predchádzajúcej

    if(!(hashTable->data = (DATA **) realloc(hashTable->data, hashTable->size * sizeof(DATA *)))){    //realokácia miesta pre uloženie ukazovateľov na dáta
        printf("Resizing table failed\n");
        hashTable->size = tableSize;
        return hashTable;
    }

    for(unsigned long long i = tableSize; i < hashTable->size; i++)    //nastav nové pointre na NULL
        hashTable->data[i] = NULL;

    for(unsigned long long i = 0; i < tableSize; i++){    //preusporiadaj už uložené dáta
        if(hashTable->data[i]){    //ak sú na danom indexe uložené nejaké dáta
            unsigned long long key = hashTable->data[i]->key;    //ulož daný kľuč do dočasnej premennej
            free(hashTable->data[i]);    //uvoľni miesto kde boli tieto dáta 
            hashTable->data[i] = NULL;    //nastav pointer na NULL
            hashTable->inserted--;    //keďže pridávame tie isté dáta, musíme dekrementovať počet pridaných dát
            insertHashOwn(hashTable, key);    //nanovo vlož dáta do tabuľky
        }
    }

    return hashTable;
}

//vyhľadanie dát v hashovacej tabuľke
DATA *searchHashOwn(HASHTABLE *hashTable, unsigned long long key){
    if(!hashTable)    //ak neexistuje hashovacia tabuľka vráť NULL
        return NULL;

    unsigned long long index = hashData(hashTable, key);    //získaj index dát

    if(hashTable->data[index]){    //ak na danom indexe sú uložené dáta
        DATA *data = hashTable->data[index];

        while(data){    //môže tam byť aj viacero dát, preto while cyklom prezri všetky
            if(key == data->key)    //ak sa dáta zhodujú s hľadanými vráť pointer na tieto dáta
                return data;

            data = data->next;    //ak nenastala zhoda, prejdi na nasledovníka
        }
    }

    return NULL;    //ak sa nič nenašlo vráť NULL
}

//uvoľnenie alokovaného miesta
void freeHashOwn(HASHTABLE *hashTable){
    if(!hashTable)
        return;

    for(unsigned long long i = 0; i < hashTable->size; i++){
        DATA *temp = hashTable->data[i];
        DATA *data = temp;

        while(data){    //najprv uvoľníme ukazovatele na dáta
            data = data->next;
            free(temp);
            temp = data;
        }
    }

    free(hashTable->data);    //nakoniec uvoľníme ukazovatele na ukazovatele na dáta a samotnú tabuľku
    free(hashTable);
}