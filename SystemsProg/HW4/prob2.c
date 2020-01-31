//Matthew Philpot   &&   Preston Henniger
//3600.001
//Homework 4

//Problem #2

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

typedef int buffer_item;
#define BUFFER_SIZE 5
#define divisor 100000000
#define TRUE 1

pthread_mutex_t mutex;
pthread_t tid; 
pthread_attr_t attr; 
sem_t full, empty;
buffer_item buffer[BUFFER_SIZE];
int counter;

void *producer(void *xx); 
void *consumer(void *xx); 


void *producer(void *xx) 
{
   	buffer_item item;

   	while(TRUE) 
	{
	     	int rNum = rand() / divisor;
      		sleep(rNum);

      	       item = rand();
 	       sem_wait(&empty);
      		pthread_mutex_lock(&mutex);
		if(insert_item(item))
			printf("Producer Error");
		else
         		printf("producer produced %d\n", item);
      		pthread_mutex_unlock(&mutex);
      		sem_post(&full);
	}
}


void *consumer(void *xx) 
{
	buffer_item item;

   	while(TRUE) 
	{
	      	int rNum = rand() / divisor;
	     	sleep(rNum);
		sem_wait(&full);
		pthread_mutex_lock(&mutex);
		if(remove_item(&item))
			printf("Consumer Error");
		else
			printf("consumer consumed %d\n", item);
      		pthread_mutex_unlock(&mutex);
      		sem_post(&empty);
	}
}

int insert_item(buffer_item item) 
{
	if(counter < BUFFER_SIZE) 
	{
      		buffer[counter] = item;
      		counter++;
      		return 0;
   	}
   	else //buffer is full
      		return -1;
}


int remove_item(buffer_item *item) 
{
	if(counter > 0) 
	{
      		*item = buffer[(counter-1)];
      		counter--;
      		return 0;
   	}
   	else //buffer is empty
      		return -1;
}

int main(int argc, char *argv[]) 
{
	int x;
	int Sleeper = 10;
	counter = 0;
	if(argc!=3)
		printf("Error: Please use ./prob2 <int1> <int2> where int1 is the # of producers and int2 is the # of consumers.\n");
	int Producers = atoi(argv[1]);
	int Consumers = atoi(argv[2]);

	pthread_mutex_init(&mutex, NULL);
	sem_init(&full, 0, 0);
	sem_init(&empty, 0, BUFFER_SIZE);
	pthread_attr_init(&attr);

	for(x = 0; x < Producers; x++) //producer
		pthread_create(&tid,&attr,producer,NULL);
	for(x = 0; x < Consumers; x++) //consumer
		pthread_create(&tid,&attr,consumer,NULL);
	sleep(Sleeper);
	exit(0);
}
