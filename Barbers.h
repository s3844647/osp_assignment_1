#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

class Barbers //Didn't seem to work otherwise.
{
public:
    Barbers();
    void runMethod();

private:
    static void *barberMethod(void *threadID);
    static void *customerMethod(void *threadID);
    static void *makeCustomerMethod(void *threadID);
};