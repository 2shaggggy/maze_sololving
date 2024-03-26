#include <stdlib.h>
#include <stdio.h>

#define QUEUE_MAX_SIZE 20

int if_exit(char **maze, int y, int x) {
    int sum = 0; 

    if(maze[y-1][x] == 'K'){
        sum++;
    }
    if(maze[y][x-1] == 'K'){
        sum++;
    }
    if(maze[y+1][x] == 'K'){
        sum++;
    }
    if(maze[y][x+1] == 'K'){
        sum++;
    }
    return sum; 
}

void enqueue(int (*queue)[2], int a, int b) {
    int i = 0;

    while(queue[i][0] != 0 && i < QUEUE_MAX_SIZE){
        i++;
    }
    if(i < QUEUE_MAX_SIZE){
        queue[i][0] = a; 
        queue[i][1] = b;
    }
}

int dequeue_a(int (*queue)[2]) {
    int a = queue[0][0];
    return a;
}

int dequeue_b(int (*queue)[2]) {
    int b = queue[0][1];
    int i = 1; 
    while (queue[i][0] != 0 && i < QUEUE_MAX_SIZE) {
        queue[i-1][0] = queue[i][0]; 
        queue[i-1][1] = queue[i][1];        
        i++;
    }
    queue[i-1][0] = 0;
    queue[i-1][1] = 0;
    return b; 
}

void check_surroundings(char **maze, int y, int x, int (*queue)[2]) {
    maze[y][x] = 'O';

    if(maze[y][x+1] == ' '){
        maze[y][x+1] = 'O';
        enqueue(queue, y, x+1);
    }
    
    if(maze[y+1][x] == ' '){
        maze[y+1][x] = 'O';
        enqueue(queue, y+1, x);
    }
    
    if(maze[y][x-1] == ' '){
        maze[y][x-1] = 'O';
        enqueue(queue, y, x-1);
    }
    
    if(maze[y-1][x] == ' '){
        maze[y-1][x] = 'O';
        enqueue(queue, y-1, x);
    }
}

void bfs(char ***maze, int height, int width) { 
    int (*queue)[2] = malloc(QUEUE_MAX_SIZE * sizeof(*queue));

    int i, j; 

    for (i = 0; i < height; i++){
        for (j = 0; j < width; j++){
            if ((*maze)[i][j] == 'P'){
                break;
            }
        }
        if ((*maze)[i][j] == 'P'){
            break;
        }
    }

    j++; 

    enqueue(queue, i, j);

    while(if_exit(*maze, i, j) == 0){
        i = dequeue_a(queue);
        j = dequeue_b(queue); 
        check_surroundings(*maze, i, j, queue);
    }

    free(queue);
}