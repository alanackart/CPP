/*
 * server.c: Server program
 *           to demonstrate interprocess commnuication
 *           with POSIX message queues
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define SERVER_QUEUE_NAME   "/sp-example-server"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10

int main (int argc, char **argv)
{
    mqd_t qd_server, qd_client;   // queue descriptors
    long token_number = 1; // next token to be given to client

    printf ("Server: Hello, World!\n");

    struct mq_attr attr;
    char * ptr = NULL;
    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    if ((qd_server = mq_open (SERVER_QUEUE_NAME, O_RDONLY | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1) {
        perror ("Server: mq_open (server)");
        exit (1);
    }
    char in_buffer [MSG_BUFFER_SIZE];
    char out_buffer [MSG_BUFFER_SIZE];
    char client_mq_name[100];
    while (1) {
        // get the oldest message with highest priority
        if (mq_receive (qd_server, in_buffer, MSG_BUFFER_SIZE, NULL) == -1) {
            perror ("Server: mq_receive");
            exit (1);
        }
	
	printf("Server: got a message, msg is %s, ", in_buffer);
	ptr = strtok(in_buffer, "#");
	if(ptr != NULL) {
		printf("the msg is from client %s, ", ptr);
		sprintf(client_mq_name, "/sp-example-client-%s", ptr);
	}
	else{
		printf("the msg is corrupted! server is down!\n");
		return 0; /*this won't happen in real prod situation */
		
	}
	ptr = strtok(NULL, "#"); /*just for demo, in real the message should be in xml or json format */
        printf ("msg content is %s\n", ptr);

        // send reply message to client

	printf("prepare to send message to queue %s\n", client_mq_name);
	fflush(stdout);
        if ((qd_client = mq_open (client_mq_name, O_WRONLY)) == 1) {
            perror ("Server: Not able to open client queue");
            continue;
        }

        sprintf (out_buffer, "I have got your message#%s#, id:#%d#\n", ptr, token_number);

        if (mq_send (qd_client, out_buffer, strlen (out_buffer) + 1, 0) == -1) {
            perror ("Server: Not able to send message to client");
            continue;
        }

        printf ("Server: successfuly send response str:%s\n", out_buffer);
        token_number++;
    }
}
