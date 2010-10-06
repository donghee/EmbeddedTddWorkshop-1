#include "RuntimeErrorStub.h"

static const char * error = "No Error";
void RuntimeErrorStub_Reset()
{
    error = "No Error";
}

const char * RuntimeErrorStub_GetLastError()
{
    return error;
}

void RuntimeError(const char * description, const char * file, int line)
{
    error = description;
}
