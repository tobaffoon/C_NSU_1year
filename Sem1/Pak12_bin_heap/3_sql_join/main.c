#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef ActorBio* ActorsList;

typedef ActorInMovie* MoviesList;

void                gets_from_qoutes            (char *dest, FILE *in);
ActorsList          read_actors                 (int len, FILE *input);
MoviesList          read_movies                 (int len, FILE* input);
BioMovieTableArr*   create_table                (ActorsList actor_list, int actors_num, MoviesList movie_list, int movies_num);
void                fwrite_bio_movie_table      (FILE* output, BioMovieTableArr *table);

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

//return Hash Table with info about actors from a file
ActorsList read_actors(int len, FILE *input){
    ActorsList res = malloc(len * sizeof(ActorBio));
    ActorBio cur;

    for (int i = 0; i < len; i++) {
        gets_from_qoutes(res[i].Name, input);
        fscanf(input, "%d ", &(res[i].birth_date));
        gets_from_qoutes(res[i].Country, input);
    }

    return res;
}

//return array with movies info from input
MoviesList read_movies(int len, FILE* input){
    MoviesList res = malloc(len * sizeof(ActorInMovie));

    for (int i = 0; i < len; i++) {
        gets_from_qoutes(res[i].Actor, input);
        gets_from_qoutes(res[i].Movie, input);
    }

    return res;
}

//creates array with pointers to pairs of actors and movies
BioMovieTableArr* create_table(ActorsList actors_list, int actors_num, MoviesList movie_list, int movies_num){
    BioMovieTableArr *res = malloc(sizeof(BioMovieTableArr));
    res -> list = malloc(100000 * sizeof(BioMovieTable));
    res -> length = 0;
    for (int i = 0; i < movies_num; i++) {
        for (int j = 0; j < actors_num; ++j) {
            if(strcmp(movie_list[i].Actor, actors_list[j].Name) == 0){
                res->list[res->length].actor_info = actors_list + j;
                res->list[res->length].movie_info = movie_list + i;
                res->length++;
            }
        }
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
    ActorsList actors = read_actors(num_of_actors, fi);

    int num_of_films;
    fscanf(fi, "%d", &num_of_films);
    MoviesList movies = read_movies(num_of_films, fi);

    BioMovieTableArr *joined_table = create_table(actors, num_of_actors, movies, num_of_films);

    fwrite_bio_movie_table(fo, joined_table);

    fclose(fi);
    fclose(fo);
    return 0;
}
