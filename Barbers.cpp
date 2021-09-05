#include "Barbers.h"

//Main inspiration for this solution:
//https://github.com/Stolichnayer/sleeping_barber/blob/master/sleeping_barber.c
//Alex Perrakis - Accessed 4 September 2021.

int availableSeats = 4; //by default
pthread_mutex_t lockB;
double runningTime; //ensure the program stops creating customers after 10 seconds. (???)

Barbers::Barbers()
{
}

void Barbers::runMethod()
{

    pthread_t barber;       //Barber thread
    pthread_t makeCustomer; //Thread for making customers

    pthread_mutex_init(&lockB, NULL);

    pthread_create(&barber, NULL, barberMethod, (void *)0);
    pthread_create(&makeCustomer, NULL, makeCustomerMethod, (void *)1);

    pthread_join(barber, NULL);

    pthread_join(makeCustomer, NULL);
}

void *Barbers::barberMethod(void *threadID) //Barber method.
{
    return NULL;
}

void *Barbers::customerMethod(void *threadID) //Customer method.
{
    std::cout << "Customer " << pthread_self() << " generated" << std::endl;
    if (availableSeats > 0)
    {
        availableSeats--;
    }
    return NULL;
}

void *Barbers::makeCustomerMethod(void *threadID) //Method for making customers.
{
    while (runningTime < 10)
    {

        pthread_t customer; //declare thread

        pthread_create(&customer, NULL, customerMethod, NULL);

        int msInterval = rand() % 400 + 100;        //range 100-499 (I think)
        runningTime += ((double)msInterval / 1000); //increment
        usleep(msInterval * 1000);                  //sleep (defined in microseconds)
    }

    return NULL;
}