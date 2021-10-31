#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INPUT_LENGTH 128
#define FIELD_LENGTH 30
#define NUM_FIELDS   9

int main( void )
{
    FILE *template = NULL;
    FILE *data = NULL;

    char input[INPUT_LENGTH];                     // a string for reading from a file
    char customerData[NUM_FIELDS][FIELD_LENGTH];  // an **array of strings** for storing the results of a "split"

    // these 3 variables are useful for processing the text input
    int  element = 0;
    char *next;
    char ch;

    // yes, we're hard-coding file names... note that this is *unacceptable*, unless we explicitly tell you to do it
    template = fopen( "template.txt", "r" );
    if ( template != NULL )
    {
        // read in the customers until we're done
        data = fopen( "data.txt", "r" );
        if ( data != NULL )
        {
            while ( fgets( input, INPUT_LENGTH, data ) != NULL )
            {
                // INSERT PARSING CODE FOR `data.txt` HERE! 
                // Your job here is to:
                //
                // * Tokenize the line from the file data.txt
                // * Copy each field into the customerData array
                //
                // We're trying to do something that resembles `split` in Java
                char inputCpy[strlen(input) + 1];
                strcpy(inputCpy, input);
                next = strtok(inputCpy, "|");

                while(next != NULL){
                    strcpy(customerData[element], next);
                    element++;
                    next = strtok(NULL, "|"); 
                }

                // generate the output by reading and parsing the template
                // instead of reading it into a buffer it just re-reads the file each time
                rewind( template );
                while ( fgets( input, INPUT_LENGTH, template ) != NULL )
                {
                    // INSERT PARSING CODE FOR `template.txt` HERE!
                    // Your job here is to:
                    //
                    // * Read one character at a time (it's an *array*!)
                    // * Based on the character you read, decide
                    //   * Is this a character to print?
                    //   * Is this a variable to replace with customerData data?
                    int index = 0;
 
                    while(input[index] != '\0'){
                        ch = input[index];
                        if(ch != '$')
                            printf("%c", ch);
                        else
                        {   
                            index++;//get integer after $ 
                            ch = input[index];
                            if(ch == '$')
                                printf("%c", ch);
                            else if(ch >= '0' && ch <= '9'){
                                char str[1];
                                str[0] = ch;
                                int position = atoi(str);
                                printf("%s ", customerData[position]);
                            }
                            else
                                printf("bad schema ");
                        }
                        index++;
                    }
                }
                      
                 element = 0;     
                     
                }
            }

            fclose( data );
        

        fclose( template );
    }

    return EXIT_SUCCESS;
}
