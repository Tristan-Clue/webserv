#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>

int main()
{
	int tcp;
	int opt = 1;
	sockaddr_in addr;
	
	std::memset(&addr, 0, sizeof(addr));
	if ((tcp = socket(AF_INET, SOCK_STREAM , 0)) == -1)
		return(-1);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(8080);

	if (setsockopt(tcp, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
	{
		perror("setsockopt SOL_SOCKET");
		return(1);
	}
	if ((bind(tcp, (sockaddr *)&addr, sizeof(addr)) < 0) || (listen(tcp, 10) < 0))
	{
		perror("bind or listen");
		close(tcp);
		return(-1);
	}
	
	for (;;)
	{
		sockaddr_in client;
		socklen_t len;
		char ip[INET_ADDRSTRLEN];
		int cfd;

		std::memset(&client, 0, sizeof(client));
		len = sizeof(client);
		if ((cfd = accept(tcp, (sockaddr *)&client, &len)) < 0)
		{
			perror("Client accept");
			continue;
		}
		inet_ntop(AF_INET, &client.sin_addr, ip, sizeof(ip));
		std::printf("client: %s:%u connected\n", ip, ntohs(client.sin_port));

		const char msg[] = "Hello World\n";
		send(cfd, msg, sizeof(msg) - 1, 0);
		close(cfd);
	}
}