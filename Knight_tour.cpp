#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include <time.h>
#include <stdbool.h>

#define N 8
#define nn 8

int size;
int *a;
other

static int dx[N] = {1,1,2,2,-1,-1,-2,-2};
static int dy[N] = {2,-2,1,-1,2,-2,1,-1};

bool bounds(int x, int y,int size)
other

{
	return ((x >= 0 && y >= 0) && (x < size && y < size));
}

bool isempty(int a[], int x, int y,int size)
{
	return (bounds(x, y,size)) && (a[y*size+x] < 0);
}

other

int getDeg(int a[], int x, int y,int size)
{
	int count = 0;
	for (int i = 0; i < N; ++i){
		if (isempty(a, (x + dx[i]), (y + dy[i]),size))
			count++;
	}
	return count;
}

typedef struct{
    int x;
    int y;
    int c;
    int k;
}pass;

void * test(void * arg){
        pass* obj=(pass*)arg;
		int nx = (obj->x)+ dx[obj->k];
		int ny = (obj->y)+ dy[obj->k];
		if ((isempty(a, nx, ny,size)) ){
            obj->c=getDeg(a, nx, ny,size);
		}
        pthread_exit(NULL);
		return NULL;
}
pthread_t t[nn];
bool nextMove(int a[],int size, int *x, int *y,int cur, struct timeval startt)
{
	int min_deg_idx = -1, c, min_deg = (N+1), nx, ny;

    struct timeval stop;
	gettimeofday(&stop, NULL);
    unsigned long long tt=(stop.tv_sec - startt.tv_sec) * 1000000 + stop.tv_usec - startt.tv_usec;
	int start = rand()%N;
other

	for (int count = 0; count < N; ++count)
	{
		int i = (start + count)%N;
		nx = *x + dx[i];
		ny = *y + dy[i];
		if ((isempty(a, nx, ny,size)) &&
other

		(c = getDeg(a, nx, ny,size)) < min_deg)
		{
			min_deg_idx = i;
			min_deg = c;
		}
	}

	if (min_deg_idx == -1)
		return false;

	nx = *x + dx[min_deg_idx];
	ny = *y + dy[min_deg_idx];

	a[ny*size + nx] = a[(*y)*size + (*x)]+1;

	*x = nx;
	*y = ny;

	return true;
}

void print1(int a[],int size)
{
other

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
            printf("%d\t",a[j*size+i]);
        printf("\n");
    }
}
void print(int *a[2],int size)
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
			printf("%d,%d|",a[0][i*size+j],a[1][i*size+j]);
	}
}

bool check(int arr[],int size){
    for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
			if(a[i*size+j]==-1)
                return false;
	}
    return true;
}
pthread_mutex_t lock;

typedef struct{
    int size;
    int i;
    int j;
} tosend;
tosend obj[nn];
void *findClosedTour(void * args)
{
    tosend * obj=(tosend *)args;
    struct timeval startt;
    a=(int *)malloc(size*size*sizeof(int));
	int *b[2];
	b[0]=(int *)malloc(size*size*sizeof(int));
	b[1]=(int *)malloc(size*size*sizeof(int));
	for (int k = 0; k< size*size; ++k)
		a[k] = -1;

	int x = obj->i, y = obj->j;
	a[y*size+x] = 1; 


	b[0][0]=x;
	b[1][0]=y;
    gettimeofday(&startt, NULL);
	for (int k = 0; k < size*size - 1; ++k)
		if (!nextMove(a, size,&x, &y,k,startt) == 0){
		
			b[0][k+1]=x;
			b[1][k+1]=y;
        }
        else{
			return NULL;
        }

    if(check(a,size)){
        pthread_mutex_lock(&lock);
		print(b,size);  
		exit(0);
    }
	return NULL;
}
int main(int argc,char *argv[])
{
	
    if (argc != 4) {
		printf("Usage: ./Knight.out grid_size StartX StartY");
		exit(-1);
	}
	size = atoi(argv[1]);
	int i=atoi(argv[2]);
	int j=atoi(argv[3]);
	srand(time(NULL));
    int jj=0;
    pthread_mutex_init(&lock, NULL);
    while(jj<200){
    for(int k=0;k<nn;k++){
	    obj[k].i=i;
	    obj[k].j=j;
	    obj[k].size=size;
	    pthread_create(&t[k],NULL,findClosedTour,&obj[k]);
	}
    for(int k=0;k<nn;k++){
	    pthread_join(t[k],NULL);
    }
    jj++;
    }
	printf("No Possible Tour");
	return 0;
}