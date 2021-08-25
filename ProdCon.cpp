#include "ProdCon.h"

//REMEMBER TO CLEAN THIS UP

ProdCon::ProdCon() { //blank constructor

}

void ProdCon::runMethod() {
    pthread_t th1;
    int check;

    std::cout << "Creating thread" << std::endl;
    check = pthread_create(&th1, NULL, &produceItem, (void *) 1);

}

void* ProdCon::produceItem(void* threadID) {

    return NULL;
}
