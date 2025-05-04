#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//random comment so that I can push. - Scanning: Negation & inequality operators

//global variables
long GLOBAL_file_size;
int GLOBAL_error_flag;
FILE *GLOBAL_log_file;

//declaration of functions (fuck you for declaring functions at the start and defining at the end. I hate that)
char *read_file_contents(const char *filename);
int Scanner(char *file_contents);
void testing(char *file_contents);
int skip_to_next_line(int file_iterator,char* file_contents);


int main(int argc, char *argv[]) {
    // Disable output buffering
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    if (argc < 3) {
        fprintf(stderr, "Usage: ./your_program tokenize <filename>\n");
        return 1;
    }

    //open debug file:
    FILE *log_file = fopen("log.txt","w");
    if(log_file == NULL)
    {
        printf("cant open, wont open\n");
        return 1;
    }
    else
    {
        GLOBAL_log_file = log_file;
    }


    const char *command = argv[1];
    int return_value = 0;

    if (strcmp(command, "tokenize") == 0) {
        // You can use print statements as follows for debugging, they'll be visible when running tests.
        fprintf(stderr, "Logs from your program will appear here!\n");
        
        char *file_contents = read_file_contents(argv[2]);

        //testing(file_contents);

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

    fprintf(stderr,"return_value : %d\n",return_value);
    return return_value;
}

char *read_file_contents(const char *filename) {
    FILE *file = fopen(filename, "r");
    //fprintf(stderr,"filename : %s\n",filename);
    if (file == NULL) {
        fprintf(stderr, "Error reading file: %s\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    GLOBAL_file_size = file_size;
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
    int comment_flag = 0; //if set true, skips line. For now, this will skip the entire file.

    while(file_contents[file_iterator] != '\0')
    {
        switch(file_contents[file_iterator])
        {
            //block and line defines
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
            case ';' :
            {
                printf("SEMICOLON ; null\n");
                break;
            }
            //whatever charecters
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
            //operators
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
            case '/' :
            {
                if(file_contents[file_iterator + 1] == '/' )
                {
                    comment_flag = 1;
                    file_iterator = skip_to_next_line(file_iterator,file_contents); //skip until just before '\n'
                    //break;
                }
                else
                {
                    printf("SLASH / null\n");
                }

                break;
            }
            case '=' :
            {
                if(file_contents[file_iterator + 1] == '=')
                {
                    printf("EQUAL_EQUAL == null\n");
                    file_iterator += 1;
                }
                else
                {
                    printf("EQUAL = null\n");
                }

                break;
            }
            case '!' :
            {
                if(file_contents[file_iterator + 1] == '=')
                {
                    printf("BANG_EQUAL != null\n");
                    file_iterator += 1;
                }
                else
                {
                    printf("BANG ! null\n");
                }

                break;
            }
            case '<' :
            {
                if(file_contents[file_iterator + 1] == '=')
                {
                    printf("LESS_EQUAL <= null\n");
                    file_iterator += 1;
                }
                else
                {
                    printf("LESS < null\n");
                }

                break;
            }
            case '>' :
            {
                if(file_contents[file_iterator + 1] == '=')
                {
                    printf("GREATER_EQUAL >= null\n");
                    file_iterator += 1;
                }
                else
                {
                    printf("GREATER > null\n");
                }

                break;
            }
            //ignoring mfs
            case ' ' :
            {
                break;
            }
            case '\t' :
            {
                break;
            }
            case '\n' :
            {
                line_number += 1;
                break;
            }  
            //error bitching
            default :
            {
                //for error reporting
                fprintf(stderr,"[line %d] Error: Unexpected character: %c\n",line_number,file_contents[file_iterator]);
                returnable_value = 65;
            }    
        }

        file_iterator += 1;
    }

    return returnable_value;
}

void testing(char *file_contents)
{
    int file_iterator = 0;

    printf("testing:\n");
    while(file_contents[file_iterator] != '\0')
    {
        printf("iterator : %d : %c\n",file_iterator,file_contents[file_iterator]);
        file_iterator += 1;
    }
}

int skip_to_next_line(int file_iterator,char* file_contents)
{
    //file_iterator points to the current charecter scanned by scanner()
    //file_contents will contain the actual data from the file that we are scaning.
    //thus we get the current element by file_contents[file_iterator]

    fprintf(GLOBAL_log_file,"skip_to_next_line invoked\n")

    while(file_contents[file_iterator] != '\n' && file_contents[file_iterator] != '\0');
    {
        file_iterator += 1;
    }

    //file_iterator += 1;
    return file_iterator - 1;
}