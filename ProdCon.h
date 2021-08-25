#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

class ProdCon {
    public:
    ProdCon();
    static void runMethod();

    private:
    static void* produceItem(void* threadID);
};