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

int bsearch_actors(ActorBio* actors_list, int right, char* name){
    int left = 0,
        id,
        res_id=-1,
        cmp_res;
    char cur_str[31];
    right--;
    while(left<=right){
        id = (right+left)/2;
        strcpy(cur_str, actors_list[id].Name);
        cmp_res = strcmp(cur_str, name);
        if(cmp_res == 0){
            right = id - 1;
            res_id = id;
        }
        else if(cmp_res < 0){
            left = id + 1;
        }
        else right = id - 1;
    }
    return res_id;
}

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

ActorBio* read_actors( FILE *input, int length){
    ActorBio *res = malloc(length * sizeof(ActorBio));
    for (int i = 0; i < length; i++) {
        gets_from_qoutes(res[i].Name, input);
        fscanf(input, "%d ", &(res[i].birth_date));
        gets_from_qoutes(res[i].Country, input);
    }
    return res;
}

ActorInMovie* read_movies(FILE *input, int movies_num){
    ActorInMovie *res = malloc(movies_num * sizeof(ActorInMovie));
    for (int i = 0; i < movies_num; i++) {
        gets_from_qoutes(res[i].Actor, input);
        gets_from_qoutes(res[i].Movie, input);
    }
    return res;
}

void add_elems_to_join_table(BioMovieTableArr* dest, ActorBio* src, int src_len, int id, ActorInMovie* movie){
//    src_len--;                  //we will compare length with id to avoid array outrun
    int cmp_res = strcmp(src[id].Name, movie->Actor);
    while(cmp_res == 0){
        dest -> list[dest->length].actor_info = src + id;
        dest -> list[dest->length].movie_info = movie;
        dest->length++;
        id++;
        if(src_len == id) return;
        cmp_res = strcmp(src[id].Name, movie->Actor);
    }
}

BioMovieTableArr create_table(ActorBio* actors_list, int actors_len, ActorInMovie* movies_list, int movies_len){
    BioMovieTableArr res;
    res.list = malloc(100000 * sizeof(BioMovieTableArr));
    res.length = 0;
    int found_id;
    for (int i = 0; i < movies_len; i++) {
        found_id = bsearch_actors(actors_list, actors_len, movies_list[i].Actor);
        add_elems_to_join_table(&res, actors_list, actors_len, found_id, movies_list + i);
    }
    return res;
}

void fwrite_bio_movie_table(FILE* output, BioMovieTableArr table){
    int length = table.length;
    for (int i = 0; i < length; i++) {
        if(table.list[i].actor_info != NULL) {
            fprintf(output, "%s %d %s %s %s\n", table.list[i].actor_info->Name,
                    table.list[i].actor_info->birth_date,
                    table.list[i].actor_info->Country,
                    table.list[i].movie_info->Actor,
                    table.list[i].movie_info->Movie);
        }
    }
}

int main() {
    FILE    *fi = fopen("input.txt", "r"),
            *fo = fopen("output.txt", "w");

    int num_of_actors;
    fscanf(fi, "%d", &num_of_actors);
    ActorBio* actors = read_actors(fi, num_of_actors);

    int num_of_films;
    fscanf(fi, "%d", &num_of_films);
    ActorInMovie *movies = read_movies(fi, num_of_films);

    BioMovieTableArr joined_table = create_table(actors, num_of_actors, movies, num_of_films);

    fwrite_bio_movie_table(fo, joined_table);

    fclose(fi);
    fclose(fo);
    return 0;
}
