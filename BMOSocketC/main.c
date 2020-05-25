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


#define PORTA 5000


int main(int argc, const char * argv[]) {
    // insert code here...

    
    
  // SERVIDOR
    struct sockaddr_in saddr = {            //Informações do Servidor [Como Endereço e Porta ultilizadas pelo Cliente]
        .sin_family      = AF_INET,             //Familia de Protocolo(ipv4 ou ipv6)
        .sin_addr.s_addr = htonl(INADDR_ANY),   //Endereço na rede local [nesse caso htonl(INADDR_ANY)=definidoPelaRede]
        .sin_port        = htons(PORTA)          //Porta
    };
    // AF_INET=ipv4      e   AF_INET6=ipv6
    // SOCK_STREAM=TCP   e   SOCK_DGRAM=UDP
    // O terceiro argumento é para se desejassemos especificar algum protocolo
    int socketServer = socket(AF_INET, SOCK_STREAM, 0); //Cria e retorna o Número de socket do servidor
    
    
    
  // CLIENTE
    struct sockaddr_in caddr;               //Informações do Cliente [Como Endereço e Porta ultilizadas pelo Cliente]
    socklen_t caddrSize = sizeof caddr;         // Tamanho em bytes das informações do cliente
    int socketCliente;                          // Número de socket do cliente
    
    
    
  // VINCULAR(bind) o socket do SERVIDOR a um endereço+porta
    // A função bind() serve para alocar um endereço+porta da rede a um Socket
    bind(socketServer, (struct sockaddr *) &saddr, sizeof saddr); //O terceiro argumento(saddr) é o tamnho em bytes do segundo arg.
    
    

  // COLOCAR/Avisar ao Winsock que o socket ficará no modo de escuta(listening)
    listen(socketServer, 5);    // O segundo argumento define o numero de conexões permitidas neste socket.
    //Print da escuta
    char stringPorta[10], impressao[256];
    sprintf(stringPorta, "%d", PORTA);
    snprintf(impressao, sizeof impressao, "%s%s", "[Servidor] Escutando na porta ", stringPorta);
    puts(impressao);
    fflush(stdout);
    
    
    
    char buff[129];
    int tamanhoBytesDadosRecebidos;
    
  // Evitar que o programa se encerre, mantendo o programa em listening
    while(1){
        // Aceitar conexões feitas, retornando um novo socket em que ha a nova conexao do sevido com o cliente
        socketCliente = accept(socketServer, (struct sockaddr *) &caddr, &caddrSize);
        puts("[Servidor] Cliente conectado com sucesso.");
        fflush(stdout);
        
        
        //Insere os dados(no buff) e Retorna o tamanho desses dados enviados pelo Cliente
        tamanhoBytesDadosRecebidos = recv(socketCliente, buff, sizeof buff, 0);  //O ultimo argumento define como recv() trabalha para retornar os dados
        // Ecoa mensagem de volta para o cliente   [Faz o Inverso do recv()]
        send(socketCliente, buff, tamanhoBytesDadosRecebidos, 0);
        
        
        //'Print' no terminal
        puts(buff);
        fflush(stdout);
        
        
        //FECHAR/destruir o socket
        close(socketCliente);
    }

    
    
    return 0;
}
