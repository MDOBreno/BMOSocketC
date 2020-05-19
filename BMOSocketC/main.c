//
//  main.c
//  BMOSocketC
//
//  Created by Breno Medeiros on 17/05/20.
//  Copyright © 2020 ProgramasBMO. All rights reserved.
//  Link do vídeo: https://youtu.be/GaxjJvMnz-I
//

#include <stdio.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>



int main(int argc, const char * argv[]) {
    // insert code here...

    
    
    // SERVIDOR
    struct sockaddr_in saddr = {            //Informações do Servidor [Como Endereço e Porta ultilizadas pelo Cliente]
        .sin_family      = AF_INET,             //Familia de Protocolo(ipv4 ou ipv6)
        .sin_addr.s_addr = htonl(INADDR_ANY),   //Endereço na rede local [nesse caso htonl(INADDR_ANY)=definidoPelaRede]
        .sin_port        = htons(5000)          //Porta
    };
    // AF_INET=ipv4      e   AF_INET6=ipv6
    // SOCK_STREAM=TCP   e   SOCK_DGRAM=UDP
    // O terceiro argumento é para se desejassemos especificar algum protocolo
    int socketServer = socket(AF_INET, SOCK_STREAM, 0); //Cria e retorna o Número de socket do servidor
    
    
    
    // CLIENTE
    struct sockaddr_in caddr;               //Informações do Cliente [Como Endereço e Porta ultilizadas pelo Cliente]
    int caddrSize  = sizeof caddr;              // Tamanho em bytes das informações do cliente
    int socketCliente;                          // Número de socket do cliente
    
    
    
    // A função bind() serve para alocar um endereço+porta na rede local(ou Socket ao qual deseja associar esse endereço)
    bind(socketServer, (struct sockaddr *) &saddr, sizeof saddr); //O terceiro argumento(saddr) é o tamnho em bytes do segundo arg.
    listen(socketServer, 5);    // O segundo argumento define o numero de conexões permitidas neste socket
    
    
    
    char buff[129];
    int tamnhoBytesDadosRecebidos;
    
    // Evitar que o programa se encerre, mantendo o programa em listening
    while(1){
        // Aceitar conexões feitas, retornando um novo socket em que ha a nova conexao do sevido com o cliente
        socketCliente = accept(socketServer, (struct sockaddr *) &caddr, &caddrSize);
        
        //Insere os dados(no buff) e Retorna o tamanho desses dados enviados pelo Cliente
        tamnhoBytesDadosRecebidos = recv(socketCliente, buff, sizeof buff, 0);  //O ultimo argumento define como recv() trabalha para retornar os dados
        //Faz o Inverso do recv()
        send(socketCliente, buff, tamnhoBytesDadosRecebidos, 0);
        
        //'Print' no terminal
        puts(buff);
        fflush(stdout);

        close(socketCliente);
    }

    
    
    return 0;
}
