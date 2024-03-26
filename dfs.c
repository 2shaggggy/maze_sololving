#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 1000 

int if_exit (char **maze, int y, int x){

    int sum = 0; 

    if(maze[y-1][x] == 'K'){
        sum ++;
    }
    if(maze[y][x-1] == 'K'){
        sum ++;
    }
    if(maze[y+1][x] == 'K'){
        sum ++;
    }
    if(maze[y][x+1] == 'K'){
        sum ++;
    }
    return sum; 
}

int count (char **maze, int y, int x){
    int sum = 0; 
    if(maze[y-1][x] == ' '){
        sum ++;
    }
    if(maze[y][x-1] == ' '){
        sum ++;
    }
    if(maze[y+1][x] == ' '){
        sum ++;
    }
    if(maze[y][x+1] == ' '){
        sum ++;
    }
    return sum; 
}

void move_forward (char **maze, int *y, int *x){
    
    if(maze[*y][*x+1] == ' '){
        maze[*y][*x] = 'O';
        *x = *x + 1;
        return; 
    }
    
    if(maze[*y+1][*x] == ' '){
        maze[*y][*x] = 'O';
        *y = *y + 1;
        return; 
    }
    
    
    if(maze[*y][*x-1] == ' '){
        maze[*y][*x] = 'O';
        *x = *x - 1;
        return; 
    }
    
    if(maze[*y-1][*x] == ' '){
        maze[*y][*x] = 'O';
        *y = *y - 1;
        return; 
    }
}

void dfs (char ***maze, int height, int width){
    
    int i, j, node_count;

    int nodes[MAX_SIZE][1];

    //P (start) coordinates
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

    //printf("%d, %d - %c\n", i, j, (*maze)[i][j]);

    node_count = 0;

    j++;

    while(if_exit(*maze, i, j) == 0){

        while(count(*maze, i, j) >= 1){
            if(if_exit(*maze, i, j) != 0){
                break;
            }

            if(count(*maze, i, j) >= 2){

                //add_node
                nodes[node_count][0] = i;
                nodes[node_count][1] = j;
                node_count++; 
            }

            //move_forward
            move_forward(*maze, &i, &j);

            //printf("i - %d, j - %d\n", i, j);
        }

        if (count(*maze, i, j) == 0 && node_count != 0){

            //return_to_last_node
            node_count--;
            i = nodes[node_count][0];
            j = nodes[node_count][1];
        }   
    }
    (*maze)[i][j] = 'O';
}