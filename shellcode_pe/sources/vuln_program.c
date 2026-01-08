#include <stdio.h>
#include <string.h>

void vulnerable_function() {
    char buffer[64];
    printf("Enter some data: ");
    
    gets(buffer); 
    
    printf("You entered: %s\n", buffer);
}

int main() {
    vulnerable_function();
    return 0;
}
