long get_mem_usage ();
int if_exit (char **maze, int y, int x);
int count (char **maze, int y, int x);
void enqueue(int (*queue)[4], int a, int b, int c, int d);
void check_surroundings(char **maze, int height, int width, int y, int x, int y2, int x2, int (*queue)[4]);
int find_lowest(int (*queue)[4]);
void a_star(char ***maze, int height, int width);
