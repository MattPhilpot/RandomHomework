#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
 
#define NUM_READ 2
#define NUM_WRIT 2
 
sem_t mutex;
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
    if((sem_init(&mutex,0,1))<0)
        perror("ERROR");
    if((sem_init(&db,0,1))<0)
        perror("ERROR");
    for(i=0;i<NUM_READ;i++)
        if((pthread_create(&readers[i],NULL,reader,&reader_name[i]))!=0)
            perror("ERROR");
    for(j=0;j<NUM_WRIT;j++)
        if((pthread_create(&writers[j],NULL,writer,&writer_name[j]))!=0)
            perror("ERROR");
    for(i=0;i<NUM_READ;i++)
        if((pthread_join(readers[i],NULL))!=0)
            perror("ERROR");
    for(j=0;j<NUM_WRIT;j++)
        if((pthread_join(writers[j],NULL))!=0)
            perror("ERROR");
    sem_destroy(&mutex);
    sem_destroy(&db);
}
 
void *reader(void *n)
{
    int i=*(int *)n;
    if((sem_wait(&mutex))<0)
        perror("ERROR");
    reader_count++;
    if(reader_count==1)
        if((sem_wait(&db))<0)
            perror("ERROR");
    if((sem_post(&mutex))<0)
        perror("ERROR");
    printf("reader %d is reading\n",i);
    sleep(1);
    if((sem_wait(&mutex))<0)
        perror("ERROR");
    reader_count=reader_count-1;
    if((sem_post(&mutex))<0)
        perror("ERROR");
    if(reader_count==0)
    {
        if((sem_post(&db))<0)
            perror("ERROR");
    }
}
void *writer(void *n)
{
    int j=*((int *)n);
    printf("writer %d is waiting\n",j);
    if((sem_wait(&db))<0)
        perror("ERROR");
    printf("writer %d is writing\n",j);
    if((sem_post(&db))<0)
        perror("ERROR");
}