#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 255 

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

void move_forward (char **maze, int *y, int *x, int *dir, int *dir_node){
    if (*dir_node == 1){
        if(maze[*y][*x+1] == ' '){
            maze[*y][*x] = 'O';
            *x = *x + 1;
            *dir = 1;
            return; 
        }
        if(maze[*y+1][*x] == ' '){
            maze[*y][*x] = 'O';
            *y = *y + 1;
            *dir = 2;
            return; 
        }    
        if(maze[*y][*x-1] == ' '){
            maze[*y][*x] = 'O';
            *x = *x - 1;
            *dir = 3; 
            return; 
        }
        if(maze[*y-1][*x] == ' '){
            maze[*y][*x] = 'O';
            *y = *y - 1;
            *dir = 0;
            return; 
        }
    }
    if (*dir_node == 2){
        if(maze[*y+1][*x] == ' '){
            maze[*y][*x] = 'O';
            *y = *y + 1;
            *dir = 2;
            return; 
        }
        if(maze[*y][*x-1] == ' '){
            maze[*y][*x] = 'O';
            *x = *x - 1;
            *dir = 3;
            return; 
        }    
        if(maze[*y-1][*x] == ' '){
            maze[*y][*x] = 'O';
            *y = *y - 1;
            *dir = 0; 
            return; 
        }
        if(maze[*y][*x+1] == ' '){
            maze[*y][*x] = 'O';
            *x = *x + 1;
            *dir = 1;
            return; 
        }
    }
    if (*dir_node == 3){
        if(maze[*y][*x-1] == ' '){
            maze[*y][*x] = 'O';
            *x = *x - 1;
            *dir = 3;
            return; 
        }
        if(maze[*y-1][*x] == ' '){
            maze[*y][*x] = 'O';
            *y = *y - 1;
            *dir = 0;
            return; 
        }    
        if(maze[*y][*x+1] == ' '){
            maze[*y][*x] = 'O';
            *x = *x + 1;
            *dir = 1; 
            return; 
        }
        if(maze[*y+1][*x] == ' '){
            maze[*y][*x] = 'O';
            *y = *y + 1;
            *dir = 2;
            return; 
        }
    }
    if (*dir_node == 0){
        if(maze[*y-1][*x] == ' '){
            maze[*y][*x] = 'O';
            *y = *y - 1;
            *dir = 0;
            return; 
        }
        if(maze[*y][*x+1] == ' '){
            maze[*y][*x] = 'O';
            *x = *x + 1;
            *dir = 1;
            return; 
        }    
        if(maze[*y+1][*x] == ' '){
            maze[*y][*x] = 'O';
            *y = *y + 1;
            *dir = 2; 
            return; 
        }
        if(maze[*y][*x-1] == ' '){
            maze[*y][*x] = 'O';
            *x = *x - 1;
            *dir = 3;
            return; 
        }
    }
}

void wall_follower (char ***maze, int height, int width){
    int i, j;

    int nodes[MAX_SIZE][1];


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

    int direction = 0; 
    int dir_in_node = 1;
    // 0 - góra 
    // 1 - prawo
    // 2 - dół 
    // 3 - lewo  
    
    int node_count = 0;
    j++;
    
    while (if_exit(*maze, i, j) == 0){

        while(count(*maze, i, j) >= 1){
            if(if_exit(*maze, i, j) != 0){
                break;
            }
            if (count(*maze, i, j) >= 2){

                //add_node
                nodes[node_count][0] = i;
                nodes[node_count][1] = j;
                node_count++;

                //change_direction
                if (direction != 0){
                dir_in_node = direction - 1; 
                } else {
                    dir_in_node = 3;
                }
            }
            move_forward(*maze, &i, &j, &direction, &dir_in_node);
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