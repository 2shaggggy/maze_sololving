/*
MIT License

Copyright (c) 2024 @jazdzewt

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>
#include <unistd.h> 

#define MAX_SIZE 1024

//#include "a_star.h"
#include "zalewanie.h"
//#include "wall_follower.h"
//#include "dfs.h"
//#include "bfs.h"
//#include "bruteforce.h"

long get_mem_usage (){
    struct rusage myusage;

    getrusage(RUSAGE_SELF, &myusage);
    return myusage.ru_maxrss;
}

int main(int argc, char *argv[]) {

    clock_t start, end;
    double cpu_time_used;
    long baseline = get_mem_usage();

    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Could not open file: %s\n", argv[1]);
        return 1;
    }
    
    int height = 0; 
    int width = 0;
    char ch; 

    char buffer[MAX_SIZE];

    while(fgets(buffer, MAX_SIZE, file) != NULL){
        height ++; 
    }

    rewind(file);

    while (ch = fgetc(file) != EOF){
        width++;
    }

    width = (width - height)/height; 

    //printf("%d, %d \n", height, width);

    char** tablica = malloc((height*width) * sizeof(char*)); 

    for (int i = 0; i < (height*width); i++){
        tablica[i] = malloc((height*width)*sizeof(char));
    }

    rewind(file); 

    for (int i = 0; i< height; i++){
        for (int j = 0; j< width + 1; j++){
            tablica[i][j] = (char) fgetc(file); 
        }
    }

    start = clock();

    //a_star(&tablica, height, width);
    while(zalewanie(&tablica, height, width));
    //wall_follower(&tablica, height, width);
    //bfs(&tablica, height, width);
    //dfs(&tablica, height, width); //maze_1, maze_2, maze_3, maze_5, maze_6, maze_7, maze_8
    //bruteforce(&tablica, height, width); //maze_1, maze_6, maze_7
    
    end = clock();

    long baseline2 = get_mem_usage ();

    for (int i = 0; i< height; i++){
        for (int j = 0; j< width + 1; j++){
            printf(" %c ", tablica[i][j]);
        }
    }

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    printf("\nCzas wykonania: %f sekund\n", cpu_time_used);
    printf("Usage: %ld Kb, %ld Kb\n", get_mem_usage(), baseline2 - baseline);

    fclose(file);

    for (int i = 0; i < (height*width); i++){
        free(tablica[i]);
    }

    free(tablica);

    return 0;
}
