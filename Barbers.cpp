#include "Barbers.h"

/* Main inspirations for this solution:
https://github.com/Stolichnayer/sleeping_barber/blob/master/sleeping_barber.c
Alex Perrakis - Accessed 4 September 2021.
https://www.geeksforgeeks.org/sleeping-barber-problem-in-process-synchronization/
Kunal Joshi (GeeksforGeeks) - Accessed 7 September 2021. */

//SEMAPHORES USED (not sure if this meets the requirements)

int availableSeats = 4; //by default
double runningTime;     //ensure the program stops creating customers after 10 seconds. (???)

sem_t barberReady; //condition handling
sem_t custReady;
pthread_mutex_t seats;

Barbers::Barbers()
{
}

void Barbers::runMethod()
{
    sem_init(&barberReady, 0, 0); //initialise semaphores
    sem_init(&custReady, 0, 0);

    pthread_t barber;
    pthread_t makeCustomer;

    pthread_create(&barber, NULL, barberMethod, NULL);
    pthread_create(&makeCustomer, NULL, makeCustomerMethod, NULL);

    pthread_join(barber, NULL);
    pthread_join(makeCustomer, NULL);

    //graceful exit
    std::cout << "Threads finished, now sleeping" << std::endl;
    sleep(10);
    std::cout << "Exiting" << std::endl;
}

void *Barbers::barberMethod(void *threadID) //Barber method.
{
    while (runningTime < 10) //ensure loop
    {
        //wait for customer
        sem_wait(&custReady);

        pthread_mutex_lock(&seats);
        availableSeats++; //no longer waiting
        pthread_mutex_unlock(&seats);

        sem_post(&barberReady);
        std::cout << "Now servicing customer" << std::endl;

        //barber 'service' (sleep)
        int msInterval = rand() % 400 + 100;
        std::cout << "Service time: " << msInterval << " ms" << std::endl;
        usleep(msInterval * 1000); //defined in microseconds
    }
    return NULL;
}

void *Barbers::customerMethod(void *threadID) //Customer method. (I think this way of using condition variables is correct.)
{
    std::cout << "Customer " << threadID << " entered" << std::endl;
    pthread_mutex_lock(&seats); //restrict access to seats

    if (availableSeats > 0)
    {
        availableSeats--;
        pthread_mutex_unlock(&seats);
        std::cout << availableSeats << " seats remaining" << std::endl;

        //notify and wait for barber
        sem_post(&custReady);
        sem_wait(&barberReady);

        std::cout << "Customer waiting" << std::endl;
    }
    else //no seats available
    {
        pthread_mutex_unlock(&seats);
        std::cout << "No seats available - Customer left" << std::endl;
    }

    return NULL;
}

void *Barbers::makeCustomerMethod(void *threadID) //Method for making customers.
{
    int id = 0; //thread identifier
    while (runningTime < 10)
    {
        pthread_t customer;
        pthread_create(&customer, NULL, customerMethod, (void*) id); //create individual customer thread
        id++;

        int msInterval = rand() % 400 + 100;        //range 100-499 (I think)
        runningTime += ((double)msInterval / 1000); //increment
        usleep(msInterval * 1000);                  //sleep (defined in microseconds)
    }

    return NULL;
}