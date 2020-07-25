#include <stdio.h>
#include <dirent.h>

int main(int argc, char* argv)
{
    const char* dir = ".";
    
    DIR* d = opendir(".");
    struct dirent* e;
    
    if(!d)
    {
        printf("ERROR: Could not open directory!\n");
        
        return 1;
    }
    
    while((e = readdir(d)) != NULL)
    {
        printf("%s\n", e->d_name);
    }
    
    closedir(d);
    
    return 0;
}
