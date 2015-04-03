#include "MathFunc.h"
#include <math.h>
using namespace ACGCross;

float ACGCross::ArcFunc(float x)
{
    if (x>=1.0) return -1.0;
    else return sqrt(1-(x-1)*(x-1));
}

float ACGCross::FArcFunc(float x)
{
    if (x>=1.0) return -1.0;
    else return 1-ACGCross::ArcFunc(1-x);
}
