#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define HASHTABLE_LEN 239017        //prime number enough bigger than 10^5
#define POLYNOM_MOD 39119           //also prime

typedef struct ActorBio{
    char Name[31];
    int birth_date;
    char Country[11];
} ActorBio;

typedef struct ActorInMovie{
    char Actor[31];
    char Movie[21];
} ActorInMovie;

typedef struct BioMovieTable{
    ActorBio *actor_info;
    ActorInMovie *movie_info;
} BioMovieTable;

typedef struct BioMovieTableArr{
    BioMovieTable *list;
    int length;
} BioMovieTableArr;

typedef struct Node{
    ActorBio info;
    struct Node *next;
} Node;

typedef Node** HashTable;

typedef ActorInMovie* MoviesList;

uint32_t            polynomial_hash             (char *str);
void                gets_from_qoutes            (char *dest, FILE *in);
void                add_to_list                 (Node **head, ActorBio new);
HashTable           read_actors                 (int len, FILE *input);
MoviesList          read_movies                 (int len, FILE* input);
void                join_table                  (BioMovieTableArr *dest, HashTable src, MoviesList actor);
BioMovieTableArr*   create_table                (HashTable htable, MoviesList movie_list, int movies_num);
void                fwrite_bio_movie_table      (FILE* output, BioMovieTableArr *table);

//gets polynomial hash of a string
uint32_t polynomial_hash(char *str){
    uint32_t    res = 0,
                n = strlen(str);

    for(int i = 0; i < n; i++){
        res += res * POLYNOM_MOD + str[i];
    }

    return res;
}

//reads string placed in quotes from a file
void gets_from_qoutes(char *dest, FILE *in){
    char cur_s = '\0';
    int read_res;

    //find the first quote
    while(cur_s != '"'){
        read_res = fscanf(in, "%c", &cur_s);
        if(read_res == EOF) return;
    }

    read_res = fscanf(in, "%c", &cur_s);
    if(read_res == EOF) return;

    //get everything before second quote
    while(cur_s != '"'){
        *dest = cur_s;
        dest++;
        read_res = fscanf(in, "%c", &cur_s);
        if(read_res == EOF) return;
    }

    *dest = '\0';
}

//adds element to the beginning of a list
void add_to_list(HashTable head, ActorBio new){
    Node *new_node = malloc(sizeof(Node));
    new_node -> info = new;
    new_node -> next = *head;
    *head = new_node;
}

//return Hash Table with info about actors from a file
HashTable read_actors(int len, FILE *input){
    HashTable res = malloc(HASHTABLE_LEN * sizeof(Node));
    ActorBio cur;
    uint32_t hash;

    for (int i = 0; i < len; i++) {
        gets_from_qoutes(cur.Name, input);
        fscanf(input, "%d ", &(cur.birth_date));
        gets_from_qoutes(cur.Country, input);

        hash = polynomial_hash(cur.Name) % HASHTABLE_LEN;

        add_to_list(res + hash, cur);
    }

    return res;
}

//return array with movies info from input
MoviesList read_movies(int len, FILE* input){
    MoviesList res = malloc(len * sizeof(Node));

    for (int i = 0; i < len; i++) {
        gets_from_qoutes(res[i].Actor, input);
        gets_from_qoutes(res[i].Movie, input);
    }

    return res;
}

//adds actor to join table, if it can match someone from src list
void join_table(BioMovieTableArr *dest, HashTable src, MoviesList actor){
    uint32_t hash = polynomial_hash(actor -> Actor) % HASHTABLE_LEN;
    Node *temp = src[hash];

    while(temp != NULL){
        if(strcmp(temp -> info.Name, actor -> Actor) == 0){
            dest->list[dest->length].actor_info = &(temp -> info);
            dest->list[dest->length].movie_info = actor;
            dest->length++;
        }
        temp = temp -> next;
    }

}

//creates array with pointers to pairs of actors and movies
BioMovieTableArr* create_table(HashTable htable, MoviesList movie_list, int movies_num){
    BioMovieTableArr *res = malloc(sizeof(BioMovieTableArr));
    res -> list = malloc(100000 * sizeof(BioMovieTable));
    res -> length = 0;
    for (int i = 0; i < movies_num; i++) {
        join_table(res, htable, movie_list + i);
    }
    return res;
}

//prints array of pairs
void fwrite_bio_movie_table(FILE* output, BioMovieTableArr *table){
    int length = table->length;
    for (int i = 0; i < length; i++) {
        fprintf(output, "\"%s\" %d \"%s\" \"%s\" \"%s\"\n", table->list[i].actor_info->Name,
                table->list[i].actor_info->birth_date,
                table->list[i].actor_info->Country,
                table->list[i].movie_info->Actor,
                table->list[i].movie_info->Movie);
    }
}

int main() {
    FILE    *fi = fopen("input.txt", "r"),
            *fo = fopen("output.txt", "w");

    int num_of_actors;
    fscanf(fi, "%d", &num_of_actors);
    HashTable actors = read_actors(num_of_actors, fi);

    int num_of_films;
    fscanf(fi, "%d", &num_of_films);
    MoviesList movies = read_movies(num_of_films, fi);

    BioMovieTableArr *joined_table = create_table(actors, movies, num_of_films);

    fwrite_bio_movie_table(fo, joined_table);

    fclose(fi);
    fclose(fo);
    return 0;
}
