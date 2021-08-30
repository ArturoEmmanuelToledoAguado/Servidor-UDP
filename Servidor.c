/*Servidor UDP que recivira 4 valores enteros*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8081
#define BUFFER 1024

int main()
{
	int sock, len, n;
	struct sockaddr_in server, cliaddr;
	char buf[BUFFER];

	//Creacion del descriptor del socket
	if((sock=socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("Fallo en la creacion del socket");
		exit(EXIT_FAILURE);
	}
	//Ponemos a cero la región de memoria correspondientes al servidor y al cliente.
	bzero(&server,sizeof(server));
	bzero(&cliaddr, sizeof(cliaddr));
	//LLenando la información del servidor
	server.sin_family = AF_INET;//Protocolo (IPv4)
	server.sin_addr.s_addr = INADDR_ANY;//Cualquier conexión
	server.sin_port = htons(PORT);//Puerto para la conexión
	//Asignamos un puerto al socket servidor
	if (bind(sock,(struct sockaddr *)&server,sizeof(server))<0)
	{
		perror("Asignacion fallida");
		exit(EXIT_FAILURE);
	}
	
	len = sizeof(cliaddr);
	//Quedando en escucha permanente
	while (1)
	{
		n = recvfrom(sock,(char *)buf,BUFFER,0,(struct sockaddr *)&cliaddr,&len);//n = numero de bytes escritos
		if (n < 0)
			perror("Error en recvfromn 1");
		int n1 = (int)strtol(buf,NULL,10);//Convertimos el string a int
		fflush(stdin);
		
		printf("Numero 1: %d\n",n1);
		n = recvfrom(sock,(char *)buf,BUFFER,0,(struct sockaddr *)&cliaddr,&len);//n = numero de bytes escritos
		if (n < 0)
			perror("Error en recvfrom 2");
		int n2 = (int)strtol(buf,NULL,10);//Convertimos el string a int
		fflush(stdin);
		
		printf("Numero 2: %d\n",n2);
		n = recvfrom(sock,(char *)buf,BUFFER,0,(struct sockaddr *)&cliaddr,&len);//n = numero de bytes escritos
		if (n < 0)
			perror("Error en recvfrom 3");
		int n3 = (int)strtol(buf,NULL,10);//Convertimos el string a int
		fflush(stdin);
		
		printf("Numero 3: %d\n",n3);
		n = recvfrom(sock,(char *)buf,BUFFER,0,(struct sockaddr *)&cliaddr,&len);//n = numero de bytes escritos
		if (n < 0)
			perror("Error en recvfrom 4");
		int n4 = (int)strtol(buf,NULL,10);//Convertimos el string a int
		fflush(stdin);
		
		printf("Numero 4: %d\n",n4);
		//Operación
		int resultado = ((n1+n4)*n2)-n3;
		printf("El resultado es: %d\n",resultado);
		sprintf(buf, "%d",resultado);//Convertir a string
		if (resultado > 500)
		{
			n = sendto(sock,"Los datos son correctos",24,0,(struct sockaddr *)&cliaddr,len);
			if (n < 0)
				perror("Error en mensaje datos");
		}
		else
		{
			n = sendto(sock,"Los datos son incorrectos",26,0,(struct sockaddr *)&cliaddr,len);
			if (n < 0)
				perror("Error en mensaje datos");
		}
		//Envio del resultado
		n = sendto(sock,buf,strlen(buf),0,(struct sockaddr *)&cliaddr,len);
		if (n < 0)
			perror("Error en sendto");
	}
}
