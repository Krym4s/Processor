//
// Created by egolg on 20.10.2020.
//

#include "IsE_Processor.h"

FILE* logs = fopen ("logs_stack.txt","w");

int processorInit (struct Processor* thou)
{
    assert(thou);

    stackInit(thou->stack);
    thou->nMembers = 0;
    thou->code = {};
    thou->rip = 0;

    FILE* processorLogs = fopen ("processor_logs.txt","w");

    stackConstructor (thou->stack, 10, processorLogs);

#define DEF_REG(name,value) thou->name = 0;
#include "C:\Users\egolg\CLionProjects\DED_ASM\cmake-build-debug\data\registers.IsCPU"

#undef DEF_REG
    return NO_ERRORS;

}

int processorConstruct (struct Processor* thou, char* byteCode, int nOfMembers, const FILE* processorLogs)
{
    assert(thou);
    assert(byteCode);

    thou->stack = newStack ();

    thou->rip = 0;
    thou->nMembers = nOfMembers;

#define DEF_REG(name,value) thou->name = 0;
#include "C:\Users\egolg\CLionProjects\DED_ASM\cmake-build-debug\data\registers.IsCPU"

#undef DEF_REG

    stackConstructor (thou->stack, 10, processorLogs);
    thou->code = byteCode;

    return NO_ERRORS;
}

int readIsE_ByteCode (const char* filename, char** storage, int* nMembers)
{
    readToStorage (filename, storage);
    *nMembers = *(int*)(*storage + 8);
    *storage = (*storage + 12);

    return NO_ERRORS;
}

int executeProcessorCommand (struct Processor* processor)
{
    for (;processor->rip < processor->nMembers;)
    {
        char command = processor->code[processor->rip++];
        printf ("%d\n", command);
        switch (command)
        {
            #define DEF_CPU(name,value,nParams,instruction) case value: instruction break;

#include "C:\Users\egolg\CLionProjects\DED_ASM\cmake-build-debug\data\processor_commit.IsCPU"

#undef DEF_REG
            default:
                printf ("There is no such command\n");

        }
    }
    return NO_ERRORS;
}

int processorDump (struct Processor* processor, char* reason, int line)
{
    if (!processor)
    {
        fprintf(logs, "ERROR_Processor(NULL_PTR)");
        return NULL_POINTER_IN_ARGUMENT;
    }

    fprintf (logs, "executed on line %d\n",   line);
    fprintf (logs, "Processor(%s) [%p] \n { \n",  reason, processor);
    fprintf (logs, "\t" "nMembers  = %zux\n", processor->nMembers);
    fprintf (logs, "\t" "rip       = %zu\n",  processor->rip);
    fprintf (logs, "\t" "errorCode = %d\n",   processor->errorCode);
    fprintf (logs, "\t" "rax       = %lg\n",  processor->rax);
    fprintf (logs, "\t" "rbx       = %lg\n",  processor->rbx);
    fprintf (logs, "\t" "rcx       = %lg\n",  processor->rcx);
    fprintf (logs, "\t" "rdx       = %lg\n",  processor->rdx);

    for (int i = 0; i < processor->nMembers; ++i)
        fprintf (logs, "\t\t" "[%d] %lg\n", i, *(processor->code + i));

    stackDump (processor->stack, ARGNAME(processor->stack->errcode), line);

}



