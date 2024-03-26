#include <stdlib.h>
#include <stdio.h>

#define QUEUE_MAX_SIZE 1000
#define MAX_VALUE 1000

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

int find_free(int (*queue)[4], char **maze) {
    for (int i = 0; i < QUEUE_MAX_SIZE; i++) {
        int y = queue[i][2];
        int x = queue[i][3];

        if (maze[y][x + 1] == ' ') {
            return i; // Found a free space to the right
        }
        if (maze[y + 1][x] == ' ') {
            return i; // Found a free space below
        }
        if (maze[y][x - 1] == ' ') {
            return i; // Found a free space to the left
        }
        if (maze[y - 1][x] == ' ') {
            return i; // Found a free space above
        }
    }

    return -1;
}


void enqueue(int (*queue)[4], int a, int b, int c, int d) {
    int i = 0;

    while (queue[i][0] != 0 && i < QUEUE_MAX_SIZE) {
        i++;
    }
    if (i < QUEUE_MAX_SIZE) {
        queue[i][0] = a;
        queue[i][1] = b;
        queue[i][2] = c;
        queue[i][3] = d;
    } else {
        printf("Queue is full. Cannot enqueue.\n");
    }
}

void check_surroundings(char **maze, int height, int width, int y, int x, int y2, int x2, int (*queue)[4]) {
    if (y < 0 || y >= height || x < 0 || x >= width)
        return; // Out of bounds

    int odk, odkp;

    if (x + 1 < width && maze[y][x + 1] == ' ') {
        maze[y][x + 1] = 'O';
        odk = (y2 - y) + (x2 - x + 1);
        odkp = (y2 - y) + (x2 - x + 1) + (y + x + 1) - 1;
        enqueue(queue, odk, odkp, y, x + 1);
    }

    if (y + 1 < height && maze[y + 1][x] == ' ') {
        maze[y + 1][x] = 'O';
        odk = (y2 - y + 1) + (x2 - x);
        odkp = (y2 - y + 1) + (x2 - x) + (y + 1 + x) - 1;
        enqueue(queue, odk, odkp, y + 1, x);
    }

    if (x - 1 >= 0 && maze[y][x - 1] == ' ') {
        maze[y][x - 1] = 'O';
        odk = (y2 - y) + (x2 - x - 1);
        odkp = (y2 - y) + (x2 - x - 1) + (y + x - 1) - 1;
        enqueue(queue, odk, odkp, y, x - 1);
    }

    if (y - 1 >= 0 && maze[y - 1][x] == ' ') {
        maze[y - 1][x] = 'O';
        odk = (y2 - y - 1) + (x2 - x);
        odkp = (y2 - y - 1) + (x2 - x) + (y - 1 + x) - 1;
        enqueue(queue, odk, odkp, y - 1, x);
    }
}

int find_lowest(int (*queue)[4]) {
    int temp = queue[0][0]; // Initialize to the first value in the queue
    int index = -1; // Initialize to a value indicating invalid index
    int count = 0;

    for (int i = 0; i < QUEUE_MAX_SIZE; i++) {
        if (queue[i][0] == temp) {
            count++;
        }
        if (queue[i][0] < temp && queue[i][0] != 0) {
            temp = queue[i][0];
            index = i;
        }
    }

    if (count != 0) {
        int temp2 = MAX_VALUE; // Initialize to a large value
        for (int i = 0; i < QUEUE_MAX_SIZE; i++) {
            if (queue[i][0] == temp && queue[i][1] == temp2){
                return 0; 
            }
            if (queue[i][0] == temp && queue[i][1] < temp2) {
                temp2 = queue[i][1];
                index = i;
            }
        }
    }

    return index;
}


void a_star(char ***maze, int height, int width) {
    int i, j, k, l;
    
    int (*queue)[4] = malloc(QUEUE_MAX_SIZE * sizeof(*queue)); 

    // P - position
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if ((*maze)[i][j] == 'P') {
                break;
            }
        }
        if ((*maze)[i][j] == 'P') {
            break;
        }
    }

    // K - position
    for (k = 0; k < height; k++) {
        for (l = 0; l < width; l++) {
            if ((*maze)[k][l] == 'K') {
                break;
            }
        }
        if ((*maze)[k][l] == 'K') {
            break;
        }
    }

    j++;
    k--;

    for (int n = 0; n < QUEUE_MAX_SIZE; n++) {
        for (int m = 0; m < 4; m++) {
            queue[n][m] = 0;
        }
    }

    queue[0][0] = 100;
    queue[0][1] = 100; 
    queue[0][2] = i;
    queue[0][3] = j;

    while (if_exit(*maze, i, j) == 0) {

        int index = 0;

        if (find_lowest(queue) != 0 && count(*maze, queue[find_lowest(queue)][2], queue[find_lowest(queue)][3]) != 0){
            index = find_lowest(queue);
        } else {
            index = find_free(queue, *maze);
        }
        if (index != -1) {
            i = queue[index][2];
            j = queue[index][3];
            check_surroundings(*maze, height, width, i, j, k, l, queue);
            (*maze)[i][j] = 'O';
        } else {
            printf("Cannot find a path to the exit.\n");
            break;
        }
    }

    free(queue);
}
