
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//general terms
#define SEARCH "ministru"
#define DOMAIN 200
#define LENGTH 5000

//initializations
FILE *file;
char check[DOMAIN];
char checkTo[DOMAIN];
int searchVar;
int n=0;

typedef struct
{
    char inputs[DOMAIN];
    int code;
}Working;
Working number[LENGTH];

void initialization()
{
    file = fopen("FisierTest.txt", "r");
    if(file!=NULL)
    {
        strcpy(checkTo,"X");

        do{
            n++;
            fscanf(file,"%d",&number[n].code);
            strset(check,NULL);
            strcpy(check,checkTo);
            fgets(checkTo,DOMAIN,file);
            strcpy(number[n].inputs, strtok(checkTo,"\n"));

        }while(strcmp(check,number[n].inputs));

        n--;

        fclose(file);
    }
    else printf("\n\n//ERROR :: FILE IS EMPTY//\n\n");
}

void interpolation_search()
{
    int m,s,d;

    printf("\n\n// GIVE INPUT SEARCH CODE // :: ");
    scanf("%d",&searchVar);
    s=1;
    d=n-1;

    do{
        m=s+abs((searchVar-number[s].code)*(d-s))/(number[d].code-number[s].code);
        if (searchVar>number[m].code) s=m+1;
            else d=m-1;

    }while ((s<d)&&(number[m].code!=searchVar)&&(number[d].code!=number[s].code)&&(searchVar>=number[s].code)&&(searchVar<=number[d].code));

    if ((number[m].code==searchVar)&&(m<n)) printf("\n\n// CODE %d FOUND // JOB :: %s //\n\n", searchVar, number[m].inputs);
        else printf("\n\nCODE // JOB // NOT FOUND //\n\n");
}

void file_write(int parity)
{
    if(parity==1)
    file=fopen("AlphabeticOrder.txt", "w");

    else
    file=fopen("ParitySort.txt", "w");

    int i;
    for(i=1;i<=n;i++)
        fprintf(file,"%d %s\n",number[i].code,number[i].inputs);

    fclose(file);
}

void interchange(int i, int j)
{
    char change[DOMAIN];
    strcpy(change,number[i].inputs);
    strset(number[i].inputs,NULL);
    strcpy(number[i].inputs,number[j].inputs);
    strset(number[j].inputs,NULL);
    strcpy(number[j].inputs,change);

    int changeCode;
    changeCode=number[i].code;
    number[i].code=number[j].code;
    number[j].code=changeCode;
}

void sort(int parity)
{
    int i,j;
    for(i=parity;i<n;i+=parity)
        for(j=i+parity;j<=n;j+=parity)
    {
        int compare;
        char input_01[DOMAIN],input_02[DOMAIN];
        strcpy(input_01,number[i].inputs);
        strcpy(input_02,number[j].inputs);

        compare=strcmp(strlwr(input_01),strlwr(input_02));

        if(compare>0) interchange(i,j);
    }

    file_write(parity);
    if(parity==1)printf("\n\n// FILE & DATA SAVED IN 'AlphabeticOrder.txt' //\n\n");
    else printf("\n\n// FILE SAVED IN 'ParitySort.txt' //\n\n");
}

void search()
{
    file=fopen("Search.txt","w");
    printf("\n\n// ALL WORDS FOUND //\n\n");

    int i,j,counter=0;
    for(i=1;i<=n;i++)
    {
        int stop=1;
        for(j=0;j<strlen(SEARCH)&&stop;j++)
            if(SEARCH[j]!=number[i].inputs[j+1])stop=0;

        if(stop)
        {
            fprintf(file,"%s\n",number[i].inputs);
            printf("%s\n",number[i].inputs);
            counter=1;
        }
    }
    if(!counter)fprintf(file,"\n\n// THERE WERE NO ITEMS FOUND //\n\n");

    printf("\n\n// ALSO :: FILE & DATA SAVED IN 'Search.txt' //\n\n");
    fclose(file);
}

void efficiency_sort()
{
    int j=n, i=1, stop, upperLimit=n;
    file=fopen("EfficiencySort.txt","w");

    while(i<j)
    {
        if(number[i].code%2==1)
        {
            stop=1;
            for(j=upperLimit;j>i&&stop;j--)
                if(number[j].code%2==0)
                {
                    upperLimit=j-1;
                    stop=0;

                    //change
                    interchange(i,j);
                }
        }
        i++;
    }

    for(i=1;i<=n;i++)
        fprintf(file,"%d%s\n",number[i].code,number[i].inputs);

    fclose(file);
    printf("\n\n// FILE & DATA SAVED IN 'EfficiencySort.txt' //\n\n");
}

void show()
{
    printf("\n\n//FILE CONTENT//\n\n");
    int i;
    for(i=1;i<=n;i++)printf("%d %s \n",number[i].code, number[i].inputs);
    printf("\n\n//END OF FILE//\n\n");
}

int main()
{
    initialization();

    printf("\n\n// CHOOSE AN OPTION //\n\n");
    printf("\n// a. Sa se caute folosind cautarea prin interpolare denumirea unei anumite ocupatii date de la tastatura prin cod //\n");
    printf("\n// b. Sa se ordoneze si sa afiseze intr-un fisier separat toate ocupatiile in ordine alfabetica (a->z) //\n");
    printf("\n// c. Sa se afiseze toate ocupatiile care incep cu cuvantul 'ministru' //\n");
    printf("\n// d. Sa se ordoneze crescator, dupa cod, doar acele ocupatii care ocupa in tablou pozitii pare, fara insa a afecta pozitiile impare din tablou si sa se afiseze intr-un fisier separat tabloul astfel ordonat //\n");
    printf("\n// e. Sa se ordoneze tabloul (cu o eficienta O(n)) in felul urmator: pe primele pozitii se afla ocupatiile cu coduri pare si pe pozitiile din urma se afla ocupatii cu coduri impare si sa se afiseze intr-un fisier separat tabloul astfel ordonat //\n");
    printf("\n// f. Afisare //\n");
    printf("\n\n// YOUR OPTION // :: ");

    char choice;
    scanf("%c",&choice);

    switch(choice)
    {
    case 'a':
    case 'A':
        interpolation_search();
        break;
    case 'b':
    case 'B':
        sort(1);
        break;
    case 'c':
    case 'C':
        search();
        break;
    case 'd':
    case 'D':
        sort(2);
        break;
    case 'e':
    case 'E':
        efficiency_sort();
        break;
    case 'f':
    case 'F':
        show();
        break;
    default:
        printf("\n\n// INVALID INPUT :: EXIT //\n\n");
    }

    return 0;
}
