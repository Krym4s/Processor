//
// Created by egolg on 20.10.2020.
//

#ifndef DED_PROCESSOR_ISE_PROCESSOR_H
#define DED_PROCESSOR_ISE_PROCESSOR_H

#include "IsE_Stack.h"
#include "IsE_text.h"

struct Processor
{
    struct Stack* stack;
    char* code;
    int nMembers;
    size_t rip;
    int errorCode;
#define DEF_REG(name,value) double name;
#include "C:\Users\egolg\CLionProjects\DED_ASM\cmake-build-debug\data\registers.IsCPU"

#undef DEF_REG
};

enum ProcessorErrors
{
    NO_PROCESSOR_ERRORS = 0,
    NULL_STACK_POINTER_ERRORS = 1
};

int processorInit(struct Processor* thou);

int processorConstruct (struct Processor* thou, char* byteCode, int nMembers, const FILE* processorLogs);

int processorDestruct (struct Processor* thou);

int readIsE_ByteCode (const char* filename, char** storage, int* nMembers);

int executeProcessorCommand (struct Processor* processor);

int processorDump (struct Processor* processor, char* reason, int line);

#endif //DED_PROCESSOR_ISE_PROCESSOR_H
