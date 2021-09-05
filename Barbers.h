#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

class Barbers
{ //See ProdCon note.
public:
    Barbers();
    ~Barbers();
    static void runMethod();

private:
    static void *barberMethod(void *threadID);
    static void *customerMethod(void *threadID);
    static void *makeCustomerMethod(void *threadID);
};