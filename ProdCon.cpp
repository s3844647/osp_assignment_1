#include "ProdCon.h"

//Based on example code given in tutorials. REMEMBER TO ADD OUTPUT

pthread_cond_t condition;
bool prodDone = false;

int in = 0;
int out = 0;
int buckets[10];
pthread_mutex_t lock;

ProdCon::ProdCon()
{ //blank constructor
}

ProdCon::~ProdCon()
{ //destructor
    for (int i = 0; i < 10; i++)
    {
        buckets[i] = 0;
    }
}

void ProdCon::runMethod()
{
    pthread_t prod[5]; //Arrays of threads
    pthread_t con[5];

    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < 5; i++)
    {
        pthread_create(&prod[i], NULL, produceItem, (void *)i);
    }
    for (int j = 0; j < 5; j++)
    {
        pthread_create(&con[j], NULL, consumeItem, (void *)j);
    }

    sleep(10);

    for (int i = 0; i < 5; i++)
    {
        pthread_join(prod[i], NULL);
    }
    for (int j = 0; j < 5; j++)
    {
        pthread_join(con[j], NULL);
    }

    pthread_mutex_destroy(&lock);
}

void *ProdCon::produceItem(void *threadID)
{ //Producer method.
    for (int i = 0; i < 10; i++)
    {
        int item = rand() % 10 + 1; //Generate a random number between 1 and 10.

        pthread_mutex_lock(&lock);
        if (!prodDone)
        {
            prodDone = true;
            pthread_cond_wait(&condition, &lock);
            buckets[in] = item; //Put numbers in the array.
            in = (in + 1) % 10; //Increment.
        }
        else
        {

            pthread_cond_signal(&condition);
        }
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void *ProdCon::consumeItem(void *threadID)
{ //Consumer method.
    for (int i = 0; i < 10; i++)
    {
        pthread_mutex_lock(&lock);
        int item = buckets[i];
        pthread_mutex_unlock(&lock);
    }

    return NULL;
}
