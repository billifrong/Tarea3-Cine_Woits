#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Map.h"
#include "List.h"
#include "SortedMap.h"

typedef struct{
    SortedMap *mapota;
    char points[30];
    char name[30];
}lista;

typedef struct{
    char position[300];
    char identify[300];
    char created[300];
    char modified[300];
    char descript[300];
    char title[300];
    char url[300];
    char title_type[300];
    char rating[300];
    char runtime[300];
    char year[300];
    char genres[300];
    char votes[300];
    char release_date[300];
    char directors[300];
    int marcado;
    list* listita;
}movie;

int cmp(const void * key1, const void * key2) {
    const char * Key1 = (char*)key1;
    const int * Key2 = (char*)key2;
    return (strcmp(key2,key1));
}
//prototipos funciones utilizadas en main
void almacenar_lista(SortedMap*, SortedMap*);
void view_list_movies(SortedMap*);
void view_movies_list(SortedMap*);
void view_info(SortedMap*);
void guardar_favorita(SortedMap*, SortedMap*);
void recomendar(SortedMap*);

const char *get_csv_field (char * tmp, int k) {
    //se crea una copia del string tmp

    int open_mark = 0;
    char* ret=(char*) malloc (100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while(tmp[i+1]!='\0'){

        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ','){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }

    if(k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }


    return NULL;
}

int main(){
    int apartado, indice;
    char cargar[20];
    char titulo[20];
    FILE * archive;
    movie *pelicula, *alt;
    SortedMap *movie_map = createSortedMap(cmp), *movielist = createSortedMap(cmp);
    while (apartado != 7){
        printf("~~~~~~~~~~~~~~~~~~~~Cine_Woits~~~~~~~~~~~~~~~~~~~~\n");
        printf("Digite el numero para entrar al apartado: \n");
        printf("1. Cargar lista de peliculas\n");
        printf("2. Mostrar lista de peliculas\n");
        printf("3. Mostrar peliculas de lista\n");
        printf("4. Mostrar informacion de una pelicula\n");
        printf("5. Guardar pelicula como preferida\n");
        printf("6. Recomendar una pelicula\n");
        printf("7. Salir\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        do{
            scanf("%d", &apartado);
            if((apartado >= 8)||(apartado <= 0)){
                printf("Digite una opcion valida\n");
            }
        }while((apartado >= 8)||(apartado <= 0));
        if(apartado==1){
            almacenar_lista(movie_map,movielist);
            printf("\n Archivo leido con exito\n\n");
        }
        if(apartado==2){
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            view_list_movies(movielist);
        }
        if(apartado==3){
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            view_movies_list(movielist);
        }
        if(apartado==4){
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            view_info(movie_map);
        }
        if(apartado==5){
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            guardar_favorita(movie_map, movielist);
        }
        if(apartado==6){
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            recomendar(movielist);
        }
    }
    return 0;
}
void almacenar_lista(SortedMap* mapa_peliculas, SortedMap* movielist){
    char linea[1024];
    char *namelist;
    namelist = (char*)malloc(sizeof(char)*30);
    char alt[30];
    char *alter;
    FILE * archivo;
    lista *listofmovies;
    listofmovies=(lista*)malloc(sizeof(lista));
    listofmovies->mapota=createSortedMap(cmp);
    strcpy(listofmovies->points,"0");
    movie *peli,*aux;
    printf ("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf ("                                     \n");
    printf (" Escriba el nombre de la lista que desea agregar\n");
    printf ("                                     \n");
    do{
        scanf("%s", namelist);
        strcpy(listofmovies->name,namelist);
        strcpy (alt, namelist);
        strcat(alt,".csv");
        archivo=fopen(alt,"r");
        if(archivo==NULL){
            printf("ERROR. Ingrese un nombre de lista que sea valido: \n");
        }
    }while(archivo==NULL);
    fgets(linea,1023,archivo);
    while(fgets(linea,1023,archivo)!=NULL){
        peli=(movie*)malloc(sizeof(movie));
        peli -> marcado = 0;
        peli->listita=list_create_empty();
        alter = get_csv_field(linea, 0);
        strcpy(peli->position,alter);
        alter = get_csv_field(linea,1);
        strcpy(peli->identify,alter);
        alter = get_csv_field(linea,2);
        strcpy(peli->created,alter);
        alter = get_csv_field(linea,3);
        strcpy(peli->modified,alter);
        alter = get_csv_field(linea,4);
        strcpy(peli->descript,alter);
        alter = get_csv_field(linea,5);
        strcpy(peli->title,alter);
        alter = get_csv_field(linea,6);
        strcpy(peli->url,alter);
        alter = get_csv_field(linea,7);
        strcpy(peli->title_type,alter);
        alter = get_csv_field(linea,8);
        strcpy(peli->rating,alter);
        alter = get_csv_field(linea,9);
        strcpy(peli->runtime,alter);
        alter = get_csv_field(linea,10);
        strcpy(peli->year,alter);
        alter = get_csv_field(linea,11);
        strcpy(peli->genres,alter);
        alter = get_csv_field(linea,12);
        strcpy(peli->votes,alter);
        alter = get_csv_field(linea,13);
        strcpy(peli->release_date,alter);
        alter = get_csv_field(linea,14);
        strcpy(peli->directors,alter);
        list_push_back(peli->listita,namelist);
        aux=searchSortedMap(mapa_peliculas,peli->identify);
        if(aux==NULL){
           insertSortedMap(mapa_peliculas,peli->identify,peli);
           insertSortedMap(listofmovies->mapota,peli->rating,peli);
        }else{
            insertSortedMap(listofmovies->mapota,aux->rating,aux);
            list_push_back(aux->listita,namelist);
            free(peli);
        }
    }
    insertSortedMap(movielist, listofmovies->name, listofmovies);
}
void view_list_movies(SortedMap* listas){
    lista* auxiliar = firstSortedMap(listas);
    printf ("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf ("                                     \n");
    printf (" La(s) lista(s) de pelicula(s) guardada(s) es/son: \n");
    printf ("                                     \n");
    while(auxiliar != NULL){
        printf("%s\n", auxiliar -> name);
        auxiliar = nextSortedMap(listas);
    }
}
void view_movies_list(SortedMap* listas){
    lista *auxlista;
    movie *pelicula;
    char nombre_lista[40];
    printf ("                                     \n");
    printf ("Ingrese la lista a revisar: \n");
    printf ("                                     \n");
    do{
        scanf("%s", nombre_lista);
        auxlista = searchSortedMap(listas, nombre_lista);
        if(auxlista==NULL){
            printf("ERROR. Ingrese un nombre de lista que haya cargado anteriormente: \n");
        }
    }while(auxlista==NULL);
    printf ("  \n");
    printf ("Las peliculas que contiene la lista son: \n");
    printf ("  \n");
    pelicula = firstSortedMap(auxlista->mapota);
    while(pelicula!=NULL){
        printf("-Nombre: %s\n", pelicula->title);
        printf(" ID: %s\n", pelicula->identify);
        printf(" Rating: %s\n\n", pelicula->rating);
        pelicula = nextSortedMap(auxlista->mapota);
    }
}
void view_info(SortedMap* mapa_peliculas){
    char *nombre_lista;
    char identificacion[300];
    movie *auxiliar;
    printf ("                                     \n");
    printf ("Ingrese pelicula a procesar: \n");
    printf ("                                     \n");
    do{
        scanf("%s", identificacion);
        auxiliar = searchSortedMap(mapa_peliculas, identificacion);
        if(auxiliar==NULL){
            printf("ERROR. Ingrese una pelicula valida: \n");
        }
    }while(auxiliar==NULL);
    printf("Titulo: %s\n", auxiliar->title);
    printf("Fecha: %s\n", auxiliar->year);
    printf("Director: %s\n", auxiliar->directors);
    printf("Rating: %s\n", auxiliar->rating);
    printf("Genero: %s\n", auxiliar->genres);
    nombre_lista = list_first(auxiliar->listita);
    printf("La(s) lista(s) que se asocia(n) a las peliculas es/son: \n");
    while(nombre_lista != NULL){
        printf("%s\n", nombre_lista);
        nombre_lista = list_next(auxiliar -> listita);
    }
}
void guardar_favorita(SortedMap* mapa_peliculas, SortedMap* mapa_lista){
    char identificacion[300];
    movie *auxiliar;
    lista *aux;
    int alt;
    char *nombre_lista;
    printf ("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf ("                                     \n");
    printf ("Ingrese la pelicula que desea marcar como favorita: \n");
    printf ("                                     \n");
    do{
        scanf("%s", identificacion);
        auxiliar = searchSortedMap(mapa_peliculas, identificacion);
        if(auxiliar==NULL){
            printf("Ingrese un id correcto: \n");
        }
    }while(auxiliar == NULL);
    auxiliar -> marcado = 1;
    nombre_lista = list_first(auxiliar -> listita);
    while(nombre_lista != NULL){
        aux = searchSortedMap(mapa_lista, nombre_lista);
        alt = atoi(aux -> points);
        alt++;
        sprintf(aux -> points, "%d", alt);
        printf(" Se ha guardado la pelicula como favorita exitosamente\n\n");
        printf ("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        nombre_lista = list_next(auxiliar -> listita);
    }
}
void recomendar(SortedMap* mapa_lista){
    lista *auxiliar;
    lista *aux;
    movie *peliculon;
    int cont=0;
    auxiliar = firstSortedMap(mapa_lista);
    aux = auxiliar;
    while(auxiliar != NULL){
        if(atoi(auxiliar -> points) > atoi(aux -> points)){
            aux = auxiliar;
        }
        auxiliar = nextSortedMap(mapa_lista);
    }
    peliculon = firstSortedMap(aux -> mapota);
    printf ("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf ("                                     \n");
    printf ("El ranking de las mejores 10 peliculas es: \n");
    printf ("                                     \n");
    while(cont<10 && peliculon != NULL){
        if((peliculon -> marcado)== 0){
            printf("-%s con un rating de %s puntos\n", peliculon->title, peliculon->rating);
            cont++;
        }
        peliculon = nextSortedMap(aux -> mapota);
    }
}
