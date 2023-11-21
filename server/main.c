#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

char *get_ip_address_from_url(char *hostname);
int is_a_valid_ip_address(char* ip);

int main()
{
    printf("Starting Server...\n");

    FILE *server_info_read = NULL;
    char server_info_buffer[32];
    char* static_ip_buffer; /* needed only for URL to IP*/
    char* real_ip_address = (char*) malloc(sizeof(char)*16); /*12 digits + 3 dots + \0 */

    /* Retreiving info from info file */
    server_info_read = fopen("server_info.txt", "r");
    if (!server_info_read) {
        fprintf(stderr, "Error opening server_ip.txt file\n");
        return 1;
    }

    /*reading the server_ip.txt content with a max buffer size of 32 (and stopping before if i finished reading the file). No stack overflows here >:) */
    for (int i=0; i<31 && server_info_read; i++)
    {
        fscanf(server_info_read, "%c", &server_info_buffer[i]);
    }
    fclose(server_info_read);
    
    /*Now I have to check if the string is an IP address or a url*/

    /* checking if it is an ip address */
    if (!is_a_valid_ip_address(server_info_buffer))
    {
        /* it is NOT an ip address, so I will see if it is an url*/
        static_ip_buffer = get_ip_address_from_url(server_info_buffer);
        if (static_ip_buffer == NULL)
        {
            /* this is not ip or url its just a random string. Exiting...*/
            fprintf(stderr, "server_info.txt does not contain a valid IP address or URL. Exiting...\n");
            return 1;
        } else {
        /* if I am here that means that the ip address returned is valid! */
        memcpy(real_ip_address, static_ip_buffer, sizeof(char)*16);
        }
    } else {
        /* If I am here that means the server_info.txt contains a valid IP address*/
        memcpy(real_ip_address, server_info_buffer, sizeof(char)*16);
    }

    printf("%s\n", real_ip_address);
    free(real_ip_address);
    return 0;
}

/* get ip address from url function*/
char *get_ip_address_from_url(char *hostname) {
  struct hostent *he;
  char *ip_address;

  he = gethostbyname(hostname);
  if (he == NULL) {
    return NULL;
  }

  ip_address = inet_ntoa(*((struct in_addr *)he->h_addr));
  return ip_address;
}

int is_a_valid_ip_address(char* ip){
    struct sockaddr_in sa;
    int valid = 0;
    valid = inet_pton(AF_INET, ip, &(sa.sin_addr));
    return valid;
}