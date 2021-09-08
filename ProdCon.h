#include <iostream>
#include <pthread.h>
#include <unistd.h>

class ProdCon //Didn't seem to work otherwise.
{

public:
    ProdCon();
    void runMethod();

private:
    static void *produceItem(void *threadID);
    static void *consumeItem(void *threadID);
};