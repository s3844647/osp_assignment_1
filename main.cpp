//MAIN METHOD
//(used to initiate functionality)

#include "ProdCon.h"
#include "Barbers.h"

int main(void)
{
#ifdef PRODCON
    ProdCon *pc = new ProdCon();
    pc->runMethod();
#elif defined(BARBERS)
    Barbers *ba = new Barbers();
    ba->runMethod();
#endif
    return 0;
}