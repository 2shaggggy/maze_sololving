#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define RAND_MAX 4

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

void choose_path (char **maze, int *y, int *x, int r){

    if (r = 0){
        if(maze[*y-1][*x]== ' '){
            maze[*y][*x] = 'O';
            *y = *y - 1;
            return; 
        }
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
    }
    if (r = 1){
        if(maze[*y][*x+1]== ' '){
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
    if (r = 2){
        if(maze[*y+1][*x]== ' '){
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
        if(maze[*y][*x+1] == ' '){
            maze[*y][*x] = 'O';
            *x = *x + 1;
            return; 
        }
    }
    if (r = 3){
        if(maze[*y][*x-1]== ' '){
            maze[*y][*x] = 'O';
            *x = *x - 1;
            return; 
        }
        if(maze[*y-1][*x] == ' '){
            maze[*y][*x] = 'O';
            *y = *y - 1;
            return; 
        }      
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
    }
}

void bruteforce (char ***maze, int height, int width){

    int i, j;

    srand(time(NULL));

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

    j++;

    int x, y; 
    y = i;
    x = j; 

    int h = 0;

    while(if_exit(*maze, i, j) == 0){

        if (count(*maze, i, j) >= 3){
            i = y;
            j = x; 
            for (int h = 0; h <= height; h++){
                for (int g = 0; g <= width; g++){
                    if((*maze)[h][g] == 'O'){
                        (*maze)[h][g] == ' ';
                    }
                }
            }
        }  
        if (count(*maze, i, j) >= 2){
            int r = rand() % RAND_MAX;
            choose_path(*maze, &i, &j, r);
        }
        
        move_forward(*maze, &i, &j);

    }
    (*maze)[i][j] = 'O';
}