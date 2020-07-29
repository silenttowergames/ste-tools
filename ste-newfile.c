#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum TemplateType
{
    Struct,
    FunctionsWithStruct,
    Flecs,
} TemplateType;

const char* getSlug(const char* full)
{
    char* slug;
    
    // Get the slug
    // AKA, everything after the last /
    // This will tell us what to call our classes
    int lastSlash = 0;
    for(int j = 0; j < strlen(full); j++)
    {
        if(full[j] == '/')
        {
            lastSlash = j + 1;
        }
    }
    
    size_t sizeOfSlug = strlen(full) - lastSlash + 1;
    slug = malloc(sizeof(char) * sizeOfSlug);
    memcpy(slug, &full[lastSlash], sizeOfSlug * sizeof(char));
    
    return slug;
}

int main(int argc, char* argv[])
{
    FILE* f;
    const char* slug;
    const char* files[3];
    const char* current;
    // Maximum of 1k characters. That's a lot!
    char* filename = malloc(sizeof(char) * 1000);
    
    const char* paramsFlecs = "ecs_iter_t* it";
    const char* paramsNoFlecs = "";
    const char* params = paramsNoFlecs;
    
    const char* includesFlecs = "#include <flecs.h>\n";
    const char* includesNoFlecs = "";
    const char* includes = includesNoFlecs;
    
    const char* functionTypeFlecs = "System";
    const char* functionTypeNoFlecs = "Functions";
    const char* functionType = functionTypeNoFlecs;
    
    TemplateType type;
    
    for(int i = 1; i < argc; i++)
    {
        current = argv[i];
        
        // If it's a type flag, just handle that this cycle
        if(strcmp(current, "-flecs") == 0)
        {
            type = Flecs;
            
            includes = includesFlecs;
            params = paramsFlecs;
            functionType = functionTypeFlecs;
            
            continue;
        }
        else if(strcmp(current, "-f") == 0)
        {
            type = FunctionsWithStruct;
            
            includes = includesNoFlecs;
            params = paramsNoFlecs;
            functionType = functionTypeNoFlecs;
            
            continue;
        }
        else if(strcmp(current, "-s") == 0)
        {
            type = Struct;
            
            continue;
        }
        
        slug = getSlug(current);
        
        if(type == Struct || type == FunctionsWithStruct)
        {
            sprintf(filename, "%s.h", current);
            
            f = fopen(filename, "a");
            fprintf(f, "#pragma once\n\ntypedef struct %s\n{\n\t// fields\n} %s;\n", slug, slug);
            fclose(f);
        }
        
        if(type == FunctionsWithStruct || type == Flecs)
        {
            sprintf(filename, "%s%s.h", current, functionType);
            
            f = fopen(filename, "a");
            fprintf(f, "#pragma once\n\n#include\"%s.h\"\n%s\nvoid %s%s(%s);\n", slug, includes, slug, functionType, params);
            fclose(f);
            
            sprintf(filename, "%s%s.c", current, functionType);
            
            f = fopen(filename, "a");
            fprintf(f, "%s#include \"%s%s.h\"\n\nvoid %s%s(%s)\n{\n\t// logic\n}\n", includes, slug, functionType, slug, functionType, params);
            fclose(f);
        }
    }
    
    return 0;
}
