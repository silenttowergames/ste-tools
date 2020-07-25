#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    FILE* f;
    char* slug;
    char* files[3];
    
    const char* paramsFlecs = "ecs_iter_t* it";
    const char* paramsNoFlecs = "";
    const char* params = paramsNoFlecs;
    
    const char* includesFlecs = "#include <flecs.h>\n\n";
    const char* includesNoFlecs = "";
    const char* includes = includesNoFlecs;
    
    const char* functionTypeFlecs = "System";
    const char* functionTypeNoFlecs = "Functions";
    const char* functionType = functionTypeNoFlecs;
    
    int doFunctions = 0;
    
    for(int i = 1; i < argc; i++)
    {
        if(strcmp("-flecs", argv[i]) == 0)
        {
            doFunctions = 2;
            
            params = paramsFlecs;
            
            includes = includesFlecs;
            
            functionType = functionTypeFlecs;
            
            continue;
        }
        else if(strcmp("-f", argv[i]) == 0)
        {
            doFunctions = 1;
            
            functionType = functionTypeNoFlecs;
            
            continue;
        }
        else if(strcmp("-s", argv[i]) == 0)
        {
            doFunctions = 0;
            
            continue;
        }
        
        // Get the slug
        // AKA, everything after the last /
        // This will tell us what to call our classes
        int lastSlash = 0;
        for(int j = 0; j < strlen(argv[i]); j++)
        {
            if(argv[i][j] == '/')
            {
                lastSlash = j + 1;
            }
        }
        
        size_t sizeOfSlug = (strlen(argv[i]) - lastSlash + 1);
        slug = malloc(sizeof(char) * sizeOfSlug);
        memcpy(slug, &argv[i][lastSlash], sizeOfSlug * sizeof(char));
        
        if(doFunctions < 2)
        {
            files[0] = malloc(strlen(argv[i]) + 3);
        }
        if(doFunctions > 0)
        {
            files[1] = malloc(strlen(argv[i]) + 12);
            files[2] = malloc(strlen(argv[i]) + 12);
        }
        
        if(doFunctions < 2)
        {
            memcpy(files[0], argv[i], strlen(argv[i]));
            memcpy(&files[0][strlen(argv[i])], ".h\0", sizeof(char) * 3);
            f = fopen(files[0], "a");
            fprintf(f, "#pragma once\n\ntypedef struct %s\n{\n\t// fields\n} %s;\n", slug, slug);
            fclose(f);
        }
        
        if(doFunctions > 0)
        {
            memcpy(files[1], argv[i], strlen(argv[i]));
            memcpy(&files[1][strlen(argv[i])], "Functions.h\0", sizeof(char) * 12);
            f = fopen(files[1], "a");
            fprintf(f, "#pragma once\n\n%svoid %s%s(%s);\n", includes, slug, functionType, params);
            fclose(f);
            
            memcpy(files[2], argv[i], strlen(argv[i]));
            memcpy(&files[2][strlen(argv[i])], "Functions.c\0", sizeof(char) * 12);
            f = fopen(files[2], "a");
            fprintf(f, "#include \"%sFunctions.h\"\n\nvoid %s%s(%s)\n{\n\t// logic\n}\n", slug, slug, functionType, params);
            fclose(f);
        }
        
        if(doFunctions < 2)
        {
            printf("%s\n", files[0]);
        }
        if(doFunctions > 0)
        {
            printf("%s\n", files[1]);
            printf("%s\n", files[2]);
        }
    }
    
    return 0;
}
