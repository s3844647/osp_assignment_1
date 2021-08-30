#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

class ProdCon
{   //For some reason the variables HAD to be static or there would be errors.
    //As far as I can tell this is not normal behaviour.
public:
    ProdCon();
    ~ProdCon();
    static void runMethod();

private:
    static void *produceItem(void *threadID);
    static void *consumeItem(void *threadID);
};