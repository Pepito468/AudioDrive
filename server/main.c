#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    printf("Starting Server...\n");
    FILE *server_info_read = NULL;
    char server_info_buffer[32];

    /* Retreiving info from info file */
    server_info_read = fopen("server_ip.txt", "r");
    if (!server_info_read) {
        fprintf(stderr, "Error opening server_ip.txt file\n");
        return 1;
    }
    /*reading the server_ip.txt content with a max buffer size of 32 (and stopping before if i finished reading the file)*/
    for (int i=0; i<31 && server_info_read; i++)
    {
        fscanf(server_info_read, "%c", &server_info_buffer[i]);
    }
    fclose(server_info_read);
    /*checking if the ip was not put in --> reading server_url.txt for an url*/
    if (strcmp(server_info_buffer, "") == 0)
    {
        server_info_read = fopen("server_url.txt", "r");
        if (!server_info_read) {
            fprintf(stderr, "Error opening server_url.txt file\n");
            return 1;
        }
        /*reading the server_url.txt content with a max buffer size of 32 (and stopping before if i finished reading the file)*/
        for (int i=0; i<31 && server_info_read; i++)
        {
            fscanf(server_info_read, "%c", &server_info_buffer[i]);
        }
        fclose(server_info_read);
        /*checking if the url wasnt also put in the config file*/
        if (strcmp(server_info_buffer, "") == 0)
        {
            fprintf(stderr, "IP address or url not provided\n");
            return 1;
        }
    }
    /* Now we have the ip so we can start the server */
    

    return 0;
}