# C Code Convenience Tools

This repository is for hosting little tools developed for the purpose of making games move along a little quicker.

## ste-newfile

A console-based application for generating code files quick. It takes three flags:

### -s

S, aka `struct`, generates a blank file with the given name.

e.g. `ste-newfile MyNewStruct` gives you `MyNewStruct.h` with `typedef struct MyNewStruct {} MyNewStruct;`

### -f

F, aka `functions for struct`, generates a blank struct file, as well as a header & C file for putting those functions in.

e.g. `ste-newfile -f MyFSM` gives you `MyFSM.h` with `typedef struct MyNewStruct {} MyFSM;` as well as a header & C file for `void MyFSMFunction();`

### -flecs

Flecs is an ECS engine written in C99. This flag generates only the header & function files from `-f`, adds `#include <flecs.h>`, and gives the function the parameter `ecs_iter_t* it` to make it a System.
