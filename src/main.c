#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_contents(const char *filename);
int Scanner(char *file_contents);

int main(int argc, char *argv[]) {
    // Disable output buffering
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    if (argc < 3) {
        fprintf(stderr, "Usage: ./your_program tokenize <filename>\n");
        return 1;
    }

    const char *command = argv[1];
    int return_value = 0;

    if (strcmp(command, "tokenize") == 0) {
        // You can use print statements as follows for debugging, they'll be visible when running tests.
        fprintf(stderr, "Logs from your program will appear here!\n");
        
        char *file_contents = read_file_contents(argv[2]);

        // Uncomment this block to pass the first stage
        // if (strlen(file_contents) > 0) {
        //     fprintf(stderr, "Scanner not implemented\n");
        //     exit(1);
        // } 
        // printf("EOF  null\n"); // Placeholder, remove this line when implementing the scanner

        if(strlen(file_contents) > 0)
        {
            int result = Scanner(file_contents);
            return_value = result;
        }
        printf("EOF  null\n");
        
        free(file_contents);
    } else {
        fprintf(stderr, "Unknown command: %s\n", command);
        return 1;
    }

    return return_value;
}

char *read_file_contents(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error reading file: %s\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *file_contents = malloc(file_size + 1);
    if (file_contents == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    size_t bytes_read = fread(file_contents, 1, file_size, file);
    if (bytes_read < file_size) {
        fprintf(stderr, "Error reading file contents\n");
        free(file_contents);
        fclose(file);
        return NULL;
    }

    file_contents[file_size] = '\0';
    fclose(file);

    return file_contents;
}


int Scanner(char *file_contents)
{
    int file_iterator = 0; //iterate through the file_content array
    int line_number = 1; //current line context. Used to report warnings and errors. For now 1
    int returnable_value = 0; //0 if all right, 65 if something is wrong

    while(file_contents[file_iterator] != '\0')
    {
        switch(file_contents[file_iterator])
        {
            case '(' :
            {
                printf("LEFT_PAREN ( null\n");
                break;
            }
            case ')' :
            {
                printf("RIGHT_PAREN ) null\n");
                break;
            }
            case '{' :
            {
                printf("LEFT_BRACE { null\n");
                break;
            }
            case '}' :
            {
                printf("RIGHT_BRACE } null\n");
                break;
            }
            case '.' :
            {
                printf("DOT . null\n");
                break;
            }
            case '*' :
            {
                printf("STAR * null\n");
                break;
            }
            case ',' :
            {
                printf("COMMA , null\n");
                break;
            }
            case '+' :
            {
                printf("PLUS + null\n");
                break;
            }
            case '-' :
            {
                printf("MINUS - null\n");
                break;
            }
            case ';' :
            {
                printf("SEMICOLON ; null\n");
                break;
            }
            case '/' :
            {
                printf("SLASH / null\n");
                break;
            }
            default :
            {
                //for error reporting
                printf("[Line %d] Error: Unexpected character %c\n",line_number,file_contents[file_iterator]);
                returnable_value = 65;
            }    
        }

        file_iterator += 1;
    }

    return returnable_value;
}