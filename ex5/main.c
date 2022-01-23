#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error_handler.h"
#include "file_handler.h"
#include "defines.h"
#include "rational_fractions.h"

// enum { ERROR, NONE };

int main(int argc, char* argv[]) {
    if (argc != NUM_ARGS) 
        error_handler(NULL, (argc<NUM_ARGS)? ARG_TOO_FEW:ARG_TOO_MANY); 

    printf("Running %s...\n\n", argv[0]);

    FILEx* finX  = fileX_init(argv[1],"rt");
    FILEx* foutX = fileX_init(argv[2],"at");

    int success = (finX==NULL || foutX==NULL)? FAILURE : SUCCESS;
    if (success) success = rational_fraction_handler(finX, foutX);

    if (finX!=NULL) fileX_kill(finX);
    if (foutX!=NULL) fileX_kill(foutX);
    if (!success) {
        printf("deleting file %s\n", argv[2]);
        remove(argv[2]);
    }

    exit_message(success);
    return (success)? EXIT_SUCCESS : EXIT_FAILURE;
}