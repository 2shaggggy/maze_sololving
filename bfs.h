int if_exit(char **maze, int y, int x);
void enqueue(int (*queue)[2], int a, int b);
int dequeue_a(int (*queue)[2]);
int dequeue_b(int (*queue)[2]);
void check_surroundings(char **maze, int y, int x, int (*queue)[2]);
void bfs(char ***maze, int height, int width);
