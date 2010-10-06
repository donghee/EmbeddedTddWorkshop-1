#include "RuntimeErrorStub.h"

static const char * message = "No Error";
static int parameter = -1;
static const char * file = 0;
static int line = -1;

void RuntimeErrorStub_Reset()
{
    message = "No Error";
    parameter = -1;
}

const char * RuntimeErrorStub_GetLastError()
{
    return message;
}

void RuntimeError(const char * m, int param, const char * f, int l)
{
    message = m;
    parameter = param;
    file = f;
    line = l;
}
