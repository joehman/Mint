
#include "mtUtilities.h"
#include <Mint.h>

int trackerCount = 0;  
struct mtObject* trackerBuffer[512];


void garbageCollectorFreeObjects()
{
#if 0
    for (int i = 0; i < trackerCount; i++) 
    {
        if (!trackerBuffer[i]->data)
            continue;

        free( trackerBuffer[i]->data);
        free( trackerBuffer[i] );
        printf("freeing index %d, ptr: %p\n", i, trackerBuffer[i]);
    }
#endif
}

// defined in mtObjectInternal.h
int garbageCollectorTrackObject(struct mtObject* object)
{

#if 0
    if (trackerCount > mtArraySize(trackerBuffer))
        return mtFail;

    trackerBuffer[trackerCount] = object;
    trackerCount++;

    return mtSuccess;
#endif
}


struct mtObject* mtCreateObject(struct Type type)
{
    struct mtObject* var = malloc(sizeof(struct mtObject));
    var->data = malloc(type.size);
    var->type = type;

    memset(var->data, 0, var->type.size);
    
    garbageCollectorTrackObject(var);

    return var;
}

void mtDeleteObject(struct mtObject* object)
{
    if (!object)
        return;

    if (object->data)
        free(object->data);
    free(object);
}
