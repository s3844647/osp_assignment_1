#include "ProdCon.h"

/* Based on example code given in tutorials.
SOURCES:
https://shivammitra.com/c/producer-consumer-problem-in-c/#
Shivam Mitra - Accessed 3 September 2021.
https://gist.github.com/alexklibisz/7cffdfe90c97986f8393
Alex Klibisz - Accessed 3 September 2021. */

//NO SEMAPHORES USED

int in = 0;
int out = 0;
int buckets[10];

pthread_cond_t pvar; //condition variables
pthread_cond_t cvar;
pthread_mutex_t lock; //mutex

int prodDone = 1; //condition handling
int conDone = 1;

ProdCon::ProdCon()
{
}

void ProdCon::runMethod()
{
    pthread_t prod[5]; //Arrays of threads
    pthread_t con[5];

    std::cout << "Running producer-consumer problem" << std::endl;
    std::cout << "Initialising mutex" << std::endl;
    pthread_mutex_init(&lock, NULL);

    std::cout << "Creating threads..." << std::endl;
    for (int i = 0; i < 5; i++)
    {
        pthread_create(&prod[i], NULL, ProdCon::produceItem, (void *)i);
    }
    for (int j = 0; j < 5; j++)
    {
        pthread_create(&con[j], NULL, consumeItem, (void *)j);
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_join(prod[i], NULL);
    }
    for (int j = 0; j < 5; j++)
    {
        pthread_join(con[j], NULL);
    }

    //graceful exit
    std::cout << "Threads finished, now sleeping" << std::endl;
    sleep(10);
    std::cout << "Exiting" << std::endl;

    pthread_mutex_destroy(&lock);
}

void *ProdCon::produceItem(void *threadID)
{ //Producer method.
    for (int i = 0; i < 10; i++)
    {
        int item = rand() % 100 + 1; //Generate a random number between 1 and 100.

        pthread_mutex_lock(&lock);
        std::cout << "Mutex locked" << std::endl;
        if (prodDone == 1)
        {
            prodDone = 2;
            pthread_cond_wait(&pvar, &lock); //enable thread to sleep
        }
        else //activates after value changed
        {
            buckets[in] = item; //Put numbers in the array.
            std::cout << "Thread: " << threadID << std::endl;
            std::cout << "Item " << buckets[in] << " inserted at " << in << std::endl;
            in = (in + 1) % 10;         //Increment.
            pthread_cond_signal(&pvar); //wake up thread
        }
        pthread_mutex_unlock(&lock);
        std::cout << "Mutex unlocked" << std::endl;
    }
    return NULL;
}

void *ProdCon::consumeItem(void *threadID)
{ //Consumer method.
    for (int i = 0; i < 10; i++)
    {
        pthread_mutex_lock(&lock);
        std::cout << "Mutex locked" << std::endl;
        if (conDone == 1)
        {
            conDone = 2;
            pthread_cond_wait(&cvar, &lock);
        }
        else
        {
            int item = buckets[out];
            std::cout << "Thread: " << threadID << std::endl;
            std::cout << "Item " << item << " removed from " << out << std::endl;
            out = (out + 1) % 10; //Increment.
            pthread_cond_signal(&cvar);
        }
        pthread_mutex_unlock(&lock);
        std::cout << "Mutex unlocked" << std::endl;
    }

    return NULL;
}