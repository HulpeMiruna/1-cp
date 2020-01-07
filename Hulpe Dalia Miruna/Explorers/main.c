#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int const MAX_LENGHT_NAME=200;
int const MAX_LENGHT_COUNTRY=100;
typedef struct
{
    char *name;
    char *country;
    int discoveries;
    int distance;

} explorer;
typedef struct
{
    char *name;
    int age;
} Grayl;
void initializeStruct(explorer *el)
{
    el->name=(char *) malloc (sizeof(char )*MAX_LENGHT_NAME);
    el->country=(char *) malloc (sizeof(char )*MAX_LENGHT_COUNTRY);
}
explorer *ConstructAndRead(FILE *f,int N)
{
    int i;
    explorer *man=(explorer *) malloc (sizeof(explorer)*N);
    for(i=0; i<N; i++)
    {
        initializeStruct (&man[i]);
        fscanf(f,"%s %s %d %d\n",man[i].name,man[i].country,&man[i].discoveries,&man[i].distance);

    }
    return man;
}
void Sort(explorer *man,int N,int m,FILE *g)
{
    int i,j;
    explorer aux;
    initializeStruct(&aux);
    for(i=0; i<N-1; i++)
        for(j=i; j<N; j++)
            if(man[i].discoveries<man[j].discoveries)
            {
                strcpy (aux.name,man[i].name);
                strcpy(man[i].name,man[j].name);
                strcpy(man[j].name,aux.name);
                strcpy (aux.country,man[i].country);
                strcpy(man[i].country,man[j].country);
                strcpy(man[j].country,aux.country);
                aux.discoveries=man[i].discoveries;
                man[i].discoveries=man[j].discoveries;
                man[j].discoveries=aux.discoveries;
                aux.distance=man[i].distance;
                man[i].distance=man[j].distance;
                man[j].distance=aux.distance;
            }
    i=0;
    while(i<m&&i<N)
    {
        fprintf(g,"%s %s %d %d\n",man[i].name,man[i].country,man[i].discoveries,man[i].distance);
        i++;
    }
}
void InitializeGrayl(Grayl *Holy)
{
    Holy->name=(char *) malloc (sizeof(char )*MAX_LENGHT_NAME);
}
void CloseToHoly(explorer *man,int N, FILE *h, FILE *k)
{
    int i,j;
    Grayl Holy;
    InitializeGrayl(&Holy);
    fscanf(h,"%s %d",Holy.name, &Holy.age);
    explorer aux;
    initializeStruct(&aux);
    for(i=0; i<N-1; i++)
        for(j=i; j<N; j++)
            if(man[i].distance>man[j].distance)
            {
                strcpy (aux.name,man[i].name);
                strcpy(man[i].name,man[j].name);
                strcpy(man[j].name,aux.name);
                strcpy (aux.country,man[i].country);
                strcpy(man[i].country,man[j].country);
                strcpy(man[j].country,aux.country);
                aux.discoveries=man[i].discoveries;
                man[i].discoveries=man[j].discoveries;
                man[j].discoveries=aux.discoveries;
                aux.distance=man[i].distance;
                man[i].distance=man[j].distance;
                man[j].distance=aux.distance;
            }
    for(i=0; i<N; i++)
        fprintf(k,"%s %s %d %d\n",man[i].name,man[i].country,man[i].discoveries,man[i].distance);


}

int main()
{
    int N,m;
    FILE* f=fopen("exp.txt", "r");
    fscanf(f,"%d\n",&N);
    explorer *man=ConstructAndRead(f,N);
    fscanf(f,"%d\n",&m);
    FILE *g=fopen("discoveriesExplorers.dat","w");
    Sort(man,N,m,g);
    FILE* h=fopen("holyGrayl.dat", "r");
    FILE* k=fopen("grailExplorers.txt", "w");
    CloseToHoly(man,N,h,k);
    return 0;
}
