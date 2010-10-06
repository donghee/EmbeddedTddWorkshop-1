#include "RuntimeErrorStub.h"

static const char * error = "No Error";
static int parameter = -1;
void RuntimeErrorStub_Reset()
{
    error = "No Error";
    parameter = -1;
}

const char * RuntimeErrorStub_GetLastError()
{
    return error;
}

void RuntimeError(const char * description, int param, const char * file, int line)
{
    error = description;
    parameter = param;
}
