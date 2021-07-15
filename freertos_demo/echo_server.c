// include LwIP headers
#include <lwip/sockets.h>
#include <netif/etharp.h>

// include FreeRTOS headers
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include "lwip_main.h"


#if LWIP_SOCKET == 1
void prvMySocketTest(__unused void *params)
{
	// create server socket stuff
	int lSocket;
	struct sockaddr_in sLocalAddr;

	printf("Starting socket test interface.\n");

	lSocket = lwip_socket(AF_INET, SOCK_STREAM, 0);
	printf("socket returns %d\n", lSocket);
	if (lSocket < 0) {
		perror("socket");
		return;
	}

	memset((char *)&sLocalAddr, 0, sizeof(sLocalAddr));
	sLocalAddr.sin_family = AF_INET;
	sLocalAddr.sin_len = sizeof(sLocalAddr);
	sLocalAddr.sin_addr.s_addr = 0;
	sLocalAddr.sin_port = htons(23);

	printf("Binding socket\n");
	if (lwip_bind(lSocket, (struct sockaddr *)&sLocalAddr, sizeof(sLocalAddr)) < 0) {
		perror("bind");
		return;
	}

	printf("Listening for socket\n");
	if (lwip_listen(lSocket, 20) != 0) {
		perror("listen");
		lwip_close(lSocket);
	    return;
	}

	while (1) {
		int clientfd;
		struct sockaddr_in client_addr;
		int addrlen = sizeof(client_addr);
		char buffer[1024];
		int nbytes;

		printf("Waiting for new client\n");

		clientfd = lwip_accept(lSocket, (struct sockaddr*)&client_addr, (socklen_t*)&addrlen);
         	print_ipad(client_addr.sin_addr.s_addr, buffer);
		printf("client socket %d connected from %s\n", clientfd, buffer);
		if (clientfd > 0) {
			do {
				nbytes = lwip_read(clientfd, buffer, sizeof(buffer));
				if (nbytes > 0)
					lwip_write(clientfd, buffer, nbytes);

			}  while (nbytes>0);

			if (!lwip_close(clientfd))
				perror("close client");
		}
		else
			perror("accept");
	}

	if (!lwip_close(lSocket))
		perror("close server");
}
#endif
