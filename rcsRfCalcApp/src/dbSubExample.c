#include <stdio.h>
#include <math.h>

#include <dbDefs.h>
#include <registryFunction.h>
#include <subRecord.h>
#include <aSubRecord.h>
#include <epicsExport.h>
#include <dbAccess.h>

int mySubDebug;

static long mySubInit(subRecord *precord)
{
    if (mySubDebug)
        printf("Record %s called mySubInit(%p)\n",
               precord->name, (void*) precord);
    return 0;
}

static long mySubProcess(subRecord *precord)
{
    if (mySubDebug)
        printf("Record %s called mySubProcess(%p)\n",
               precord->name, (void*) precord);
    return 0;
}

static long myAsubInit(aSubRecord *precord)
{
    if (mySubDebug)
        printf("Record %s called myAsubInit(%p)\n",
               precord->name, (void*) precord);
    return 0;
}

static long myAsubProcess(aSubRecord *precord)
{
    long i;
    unsigned long *a;
    double *b;
    unsigned long *c;

    unsigned long noa;
    unsigned long nob;

    double *pDest;
    double *oDest;
    
    a = (unsigned long *)precord->a;
    b = (double *)precord->b;
    c = (unsigned long *)precord->c;
    pDest = (double *)precord->vala;
    oDest = (double *)precord->valb;

    nob = precord->nob;

    dbGetLink(&precord->inpa, DBR_ULONG, precord->a, 0, &noa);
    dbGetLink(&precord->inpb, DBR_DOUBLE, precord->b, 0, &nob);

    for(i=0;i<precord->nova;i++)
    {
                if(c[0] == 0)
                {
                    pDest[i] = 0;
                    oDest[i] = 0;
                }
                else
                    pDest[i] = sqrt(oDest[i]*oDest[i]*(c[0]-1)/c[0] + b[i]*b[i]/c[0]);
    }

    for(i=0;i<precord->noc;i++){
        if(c[i] < a[i])
        {
            c[i]++;
        }
        else
            c[i] = 0;
    }
    memcpy(oDest, pDest, nob);

    return 0;
}

/* Register these symbols for use by IOC code: */

epicsExportAddress(int, mySubDebug);
epicsRegisterFunction(mySubInit);
epicsRegisterFunction(mySubProcess);
epicsRegisterFunction(myAsubInit);
epicsRegisterFunction(myAsubProcess);