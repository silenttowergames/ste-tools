# C Code Convenience Tools

This repository is for hosting little tools developed for the purpose of making games move along a little quicker.

## ste-newfile

A console-based application for generating code files quick.

It appends to the given files. This is messy, but I figure it will only be messy in an instance where you are in danger of losing work. It's an easy mess to clean up, relative to possibly losing progress.

You can give it a list of files, and you can use flags in-between those files to alternate between modes. Filenames may include a path.

Example:
```ste-newfile -s MyStruct -flecs ECS/Systems/FlecsDrawAllMySprites -f FiniteStateMachine
# -s MyStruct generates:
# MyStruct.h
# -flecs ECS/Systems/FlecsDrawAllMySprites generates:
# ECS/Systems/FlecsDrawAllMySpritesSystem.h
# ECS/Systems/FlecsDrawAllMySpritesSystem.c
# -f generates:
# FiniteStateMachineFunctions.h
# FiniteStateMachineFunctions.c
```

It takes three flags for mode:

### -s

S, aka `struct`, generates a blank file with the given name.

e.g. `ste-newfile MyNewStruct` gives you `MyNewStruct.h` with `typedef struct MyNewStruct {} MyNewStruct;`

### -f

F, aka `functions for struct`, generates a blank struct file, as well as a header & C file for putting those functions in.

e.g. `ste-newfile -f MyFSM` gives you `MyFSM.h` with `typedef struct MyNewStruct {} MyFSM;` as well as a header & C file for `void MyFSMFunction();`

### -flecs

Flecs is an ECS engine written in C99. This flag generates only the header & function files from `-f`, adds `#include <flecs.h>`, and gives the function the parameter `ecs_iter_t* it` to make it a System.
