//Matthew Philpot   &&   Preston Henniger
//3600.001
//Homework 4

//Problem #1

#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

#define NUM_READ 2
#define NUM_WRIT 2

pthread_mutex_t mutex;
sem_t db;
int reader_count=0;
int reader_name[]={1,2};
int writer_name[]={1,2};
void *reader(void *i);
void *writer(void *i);

int main()
{
	int i,j;

	pthread_t readers[NUM_READ];
	pthread_t writers[NUM_WRIT];
	pthread_mutex_init(&mutex, NULL);
	sem_init(&db,0,1);
	for(i=0;i<NUM_READ; i++)
		pthread_create(&readers[i],NULL,reader,&reader_name[i]);
	for(j=0;j<NUM_WRIT;j++)
		pthread_create(&writers[j],NULL,writer,&writer_name[j]);
	for(i=0;i<NUM_READ; i++)
		pthread_join(readers[i],NULL);
	for(j=0;j<NUM_WRIT;j++)
		pthread_join(writers[j],NULL);

	pthread_mutex_destroy(&mutex);
	sem_destroy(&db);
}


void *reader(void *n)
{

	int i=*(int *)n;

	pthread_mutex_lock(&mutex);
	reader_count++;
	if(reader_count==1)
		sem_wait(&db);
	pthread_mutex_unlock(&mutex);
	printf("reader #%d is reading\n",i);
	sleep(2);
	pthread_mutex_lock(&mutex);
	reader_count = reader_count - 1;
	pthread_mutex_unlock(&mutex);
	if(reader_count==0)
		sem_post(&db);
}

void *writer(void *n)
{

	int j=*((int *)n);
	printf("writer #%d is waiting\n",j);
	sem_wait(&db);
	printf("writer #%d is writing\n",j);
	sem_post(&db);
}
