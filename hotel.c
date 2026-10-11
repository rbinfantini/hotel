//KLPR-Hotel-Ativ06 - Controle de Reservas e Ocupação de Hotel
/*Kaua Bezerra Brito, Livia de Aguiar Almeida Figueiredo, 
  Pedro Chagas Neves de Farias Nascimento, Rafael Barros Infatini - 23/06/2025
  
  Descricao do problema:
  Um hotel possui 20 andares com 14 apartamentos por andar. Conforme os hospedes vão chegando, eles escolhem o apartamento desejado. 
  Se estiver livre, o apartamento é alocado e o hospede faz o registro. Ao deixar o hotel, o hospede faz o check-out e libera o apartamento.  
  O gerente também precisa saber quais apartamentos estão livres e a taxa de ocupação do hotel.
  
  Objetivo do projeto:
  • Desenvolver um programa em C para controlar a ocupação e reservas dos apartamentos do hotel. 
    Deve ser mantido o status de cada apartamento e as opções de check-in/check-out e a 
    apresentação da ocupação.  
  • Visando a simplificação por motivos pedagógicos, este projeto não está considerando qualquer 
    controle de agenda, ignorando por completo as datas de reserva, datas de checkin e chekout, 
    inclusive as disponibilidades de aptos no decorrer do tempo.
  • Todas as operações apresentadas nos requisitos a seguir, podem ser aperfeiçoadas e 
    complementadas conforme a criatividade dos alunos, desde que atendam o que está sendo 
    proposto nestes objetivos (continua a simplificação de não considerar datas).
    
  Requisitos Funcionais:
  • REQ01-O programa deve permitir ao usuário visualizar a ocupação dos apartamentos do hotel (mapa geral). 
  
  • REQ02-O programa deve permitir ao usuário fazer a reserva de um apartamento. 
  
  • REQ03-O programa deve permitir ao usuário realizar o checkin no hotel a partir de uma reserva realizada.
  
  • REQ04-O programa deve permitir ao usuário realizar o checkin no hotel de hospede que não fez reserva.
  
  • REQ05-O programa deve permitir ao usuário realizar o checkout, ou seja, liberar o apartamento que estava ocupado.
  
  • REQ06-O programa deve permitir ao usuário cancelar uma reserva.
  
  • REQ07-O programa deve permitir ao usuário visualizar as taxas de ocupação e de reservas do hotel. 
  
  • REQ08-O programa deve permitir ao usuário cadastrar as informações do hospede 
    (CPF, nome, endereço completo, telefone celular e e-mail) no checkin. 
  
  • REQ09-O programa deve permitir ao usuário visualizar a situação de um apto. específico, e caso esteja ocupado, 
    todas as informações do hospede.

  Requisitos opcionais:
  • REQ10-O programa deve permitir ao usuário quando fizer a reserva, já cadastrar os dados do hospede
 
  • REQ11-O programa deve permitir ao usuário quando fizer o checkin, caso já exista uma reserva, 
    conferir se se trata do hospede que fez a reserva. 

  • REQ12–Outros controles imaginados e criados pelos alunos do grupo que valorizam e aperfeiçoam o Projeto do Hotel.
  
  Estes requisitos opcionais poderão ser desenvolvidos durante todos os outros anteriores*/

#include <stdio.h>
#include <string.h>

//Estrutura para armazenar endereço completo do hospede
typedef struct Endereco 
{
	char ender[40];
 	char munic[20];
 	char UF[3];
 	char cep[10];
} TipoEndereco;
TipoEndereco endereco;

//Estrutura para armazenar os dados do hospede
typedef struct Hospede
{
	char cpf[14];
 	char nome[40];
 	TipoEndereco endereco;
 	char telefone[15];
 	char email[30];
} TipoHospede;
TipoHospede Cliente;

//Estrutura do apartamento com status e dados do cliente
typedef struct Apto
{
 	char situacao; 
 	TipoHospede Cliente; 
} TipoApto;
TipoApto Hotel[20][14];

int CHECK_IN(TipoApto Hotel[20][14], int *andar, int *ap);
int CADASTRO_HOSP(TipoApto Hotel[20][14], int* andar, int* ap);
int CHECK_OUT(TipoApto Hotel[20][14], int *andar, int *ap);
int RESERVA(TipoApto Hotel[20][14], int *andar, int *ap);
int CANCELAR_RESERVA(TipoApto Hotel[20][14], int *andar, int *ap);
void MAPA_HOTEL(TipoApto Hotel[20][14]);
void INFO_APTO(TipoApto Hotel[20][14], int *andar, int *ap);
void TAXA_OCUP_RESERV(TipoApto Hotel[20][14]);
void fClear();

//AO EXECUTAR O PROGRAMA, COLOQUE EM TELA CHEIA PARA MELHOR VISUALIZACAO DO MAPA DO HOTEL
int main()
{
	int andar, ap;
	int op;
	
	//Inicializa todos os apartamentos livres, representados por '.'
	for (andar = 0; andar < 20; andar++)
	{
		for (ap = 0; ap < 14; ap++)
		{
			Hotel[andar][ap].situacao = '.';
		}
	}
	
	//Loop principal: apresenta menu e executa a operação escolhida pelo usuário
    do 
	{
		//Exibe as opções do menu para o usuário
        printf("\n\n=============== MENU ===============\n");
        printf("(1) - Check-in\n");
        printf("(2) - Check-out\n");
        printf("(3) - Reserva\n");
        printf("(4) - Cancelar Reserva\n");
        printf("(5) - Mapa de ocupacao e reservas\n");
        printf("(6) - Informacoes do apartamento\n");
        printf("(7) - Taxas de ocupacao e reservas\n");
        printf("(8) - Sair\n");
        printf("====================================\n");
        printf("Escolha a sua opcao: ");
        scanf("%d", &op);

		//Verifica se a opcao escolhida e valida
        if (op < 1 || op > 8) 
		{
            printf("OPCAO INVALIDA.\n");
            continue; //Volta pro início do loop
        }

        switch (op) 
		{
            case 1:
            	printf("\nCHECK-IN\n");
            	printf("Andar (1 - 20): ");
                scanf("%d", &andar);
                printf("Apartamento (1 - 14): ");
                scanf("%d", &ap);
                fClear();
                
                CHECK_IN(Hotel, &andar, &ap);
                MAPA_HOTEL(Hotel);
                break;
                
            case 2:
            	printf("\nCHECK-OUT\n");
            	printf("Andar (1 - 20): ");
                scanf("%d", &andar);
                printf("Apartamento (1 - 14): ");
                scanf("%d", &ap);
				fClear();
				
                CHECK_OUT(Hotel, &andar, &ap);
                MAPA_HOTEL(Hotel);
                break;
                
            case 3:
            	printf("\nRESERVA\n");
                printf("Andar (1 - 20): ");
                scanf("%d", &andar);
                printf("Apartamento (1 - 14): ");
                scanf("%d", &ap);
				fClear();
				
                RESERVA(Hotel, &andar, &ap);
                MAPA_HOTEL(Hotel);
                break;
                
            case 4:
            	printf("\nCANCELAR RESERVA\n");
            	printf("Andar (1 - 20): ");
                scanf("%d", &andar);
                printf("Apartamento (1 - 14): ");
                scanf("%d", &ap);
				fClear();
				
                CANCELAR_RESERVA(Hotel, &andar, &ap);
                MAPA_HOTEL(Hotel);
                break;
                
            case 5:
				MAPA_HOTEL(Hotel);		//Exibe o mapa com o status atual dos apartamentos do hotel	
                break;
                
            case 6:
            	printf("\nINFORMACOES DO HOSPEDE\n");
            	printf("Andar (1 - 20): ");
                scanf("%d", &andar);
                printf("Apartamento (1 - 14): ");
                scanf("%d", &ap);
                fClear();
                
                INFO_APTO(Hotel, &andar, &ap);
                MAPA_HOTEL(Hotel);
            	break;
            	
            case 7:
            	TAXA_OCUP_RESERV(Hotel);
            	MAPA_HOTEL(Hotel);
            	break;
            	
            case 8:
                printf("\nENCERRANDO PROGRAMA...\n");
                return 0;        
        }
    } while (1);
}

int CHECK_IN(TipoApto Hotel[20][14], int *andar, int *ap)
{   
	char CPF[14];
	            
    if (*andar < 1 || *andar > 20 || *ap < 1 || *ap > 14) 
	{
    	printf("\nANDAR OU APARTAMENTO INVALIDO.\n");
    	return 0;
	}
				
	else if (Hotel[*andar - 1][*ap - 1].situacao == '.') //Se o apartamento estiver livre, cadastra o hospede e marca como ocupado
	{
		CADASTRO_HOSP(Hotel, andar, ap);
		Hotel[*andar - 1][*ap - 1].situacao = 'O';		
		printf("\nCHECK-IN REALIZADO (APTO NAO RESERVADO).\n");
	} 
			
	else if (Hotel[*andar - 1][*ap - 1].situacao == 'R') //Se estiver reservado, confere o CPF antes de permitir check-in
	{
		printf("\n============= CLIENTE ==============\n");
		printf("CPF: ");
		gets(CPF);
		
		if (strcmp(Hotel[*andar - 1][*ap - 1].Cliente.cpf, CPF) == 0)
		{
			Hotel[*andar - 1][*ap - 1].situacao = 'O';	
			printf("\nCHECK-IN REALIZADO (APTO RESERVADO).\n");
		}
		
		else
		{
			printf("\nAPARTAMENTO RESERVADO POR OUTRO CLIENTE.\n");
		}
	}        
	
	else
	{
		printf("\nAPARTAMENTO OCUPADO.\n");	
	}  
}

int CADASTRO_HOSP(TipoApto Hotel[20][14], int* andar, int* ap)
{	
	printf("\n============= CLIENTE ==============\n");
						
	printf("CPF: ");
	gets(Hotel[*andar - 1][*ap - 1].Cliente.cpf);
						
	printf("NOME: ");
	gets(Hotel[*andar - 1][*ap - 1].Cliente.nome); 
						
	printf("ENDERECO: ");
	gets(Hotel[*andar - 1][*ap - 1].Cliente.endereco.ender);
						
	printf("MUNICIPIO: ");
	gets(Hotel[*andar - 1][*ap - 1].Cliente.endereco.munic);
						
	printf("UF: ");
	gets(Hotel[*andar - 1][*ap - 1].Cliente.endereco.UF);
						
	printf("CEP: ");
	gets(Hotel[*andar - 1][*ap - 1].Cliente.endereco.cep);
						
	printf("TELEFONE: ");
	gets(Hotel[*andar - 1][*ap - 1].Cliente.telefone);
										
	printf("EMAIL: ");
	gets(Hotel[*andar - 1][*ap - 1].Cliente.email);
	
	return 0;
}

int CHECK_OUT(TipoApto Hotel[20][14], int *andar, int *ap)
{
	char CPF[14];
	
	if (*andar < 1 || *andar > 20 || *ap < 1 || *ap > 14) 
	{
    	printf("\nANDAR OU APARTAMENTO INVALIDO.\n");
    	return 0;
	}
                
    else if (Hotel[*andar - 1][*ap - 1].situacao == '.')
    {
        printf("\nAPARTAMENTO LIVRE.\n");
	}
	
	else if (Hotel[*andar - 1][*ap - 1].situacao == 'R')
    {
        printf("\nAPARTAMENTO RESERVADO.\n");
	}
				
	else
	{
		printf("\n============= CLIENTE ==============\n");
		printf("CPF: ");
		gets(CPF);
		
		if (strcmp(Hotel[*andar - 1][*ap - 1].Cliente.cpf, CPF) == 0)
		{
			Hotel[*andar - 1][*ap - 1].situacao = '.'; 	//Libera o apartamento ocupado
			printf("\nCHECK-OUT REALIZADO.\n");	
		}
		
		else
		{
			printf("\nAPARTAMENTO OCUPADO POR OUTRO HOSPEDE.\n");
		}
	}
}

int RESERVA(TipoApto Hotel[20][14], int *andar, int *ap)
{
	if (*andar < 1 || *andar > 20 || *ap < 1 || *ap > 14) 
	{
    	printf("\nANDAR OU APARTAMENTO INVALIDO.\n");
    	return 0;
	}
                
    else if (Hotel[*andar - 1][*ap - 1].situacao == 'R') 
    {
       	printf("\nAPARTAMENTO RESERVADO POR OUTRO HOSPEDE.\n");
	}
	
	else if (Hotel[*andar - 1][*ap - 1].situacao == 'O') 
    {
       	printf("\nAPARTAMENTO OCUPADO.\n");
	}
				
	else
	{
		CADASTRO_HOSP(Hotel, andar, ap);				//Cadastra as informações do hospede no momento da reserva
		Hotel[*andar - 1][*ap - 1].situacao = 'R';		//Reserva o apartamento livre
		printf("\nRESERVA REALIZADA.\n");
	}
}

int CANCELAR_RESERVA(TipoApto Hotel[20][14], int *andar, int *ap)
{
	char CPF[14];
	
	if (*andar < 1 || *andar > 20 || *ap < 1 || *ap > 14) 
	{
    	printf("\nANDAR OU APARTAMENTO INVALIDO.\n");
    	return 0;
	}
                
    else if (Hotel[*andar - 1][*ap - 1].situacao == '.')
    {
        printf("\nAPARTAMENTO LIVRE.\n");
	}
	
	else if (Hotel[*andar - 1][*ap - 1].situacao == 'O')
    {
        printf("\nAPARTAMENTO OCUPADO.\n");
	}
				
	else
	{
		printf("\n============= CLIENTE ==============\n");
		printf("CPF: ");
		gets(CPF);
		
		if (strcmp(Hotel[*andar - 1][*ap - 1].Cliente.cpf, CPF) == 0)
		{
			Hotel[*andar - 1][*ap - 1].situacao = '.';		//Cancela o apartamento reservado
			printf("\nRESERVA CANCELADA.\n");	
		}
		
		else
		{
			printf("\nAPARTAMENTO RESERVADO POR OUTRO CLIENTE.\n");
		}
	}
}

//Exibe o mapa do hotel com os apartamentos de cada andar
//O símbolo '.' indica apartamento livre
//O símbolo 'R' indica apartamento reservado
//O símbolo 'O' indica apartamento ocupado
void MAPA_HOTEL(TipoApto Hotel[20][14])
{
	int andar, ap;
	
	printf("\n                                           MAPA DO HOTEL                                        \n");
	printf("                                                 *                                              \n");
	printf("                                                 |									         	\n");
	printf("                           ______________________|______________________						\n");
	printf("                           |                     ______      ______    |						\n");
	printf("                           | |  /     |          |     \\     |     \\   |						\n");
	printf("                           | | /      |          |      |    |      |  |						\n");
	printf("                           | ||       |          |_____/     |_____/   |						\n");
	printf("                           | | \\      |          |           |     \\   |					    \n");
	printf("          _________________| |  \\     |_____     |           |      \\  |_________________     \n"); 
	printf("          |                                                                             |       \n");
	
	printf("          |");
	for (ap = 1; ap < 15; ap++)
	{
		printf("  AP%d", ap);
	}
	printf("  |      \n");
	
	for (andar = 20; andar > 0; andar--)
	{
		printf("Andar %2d  |", andar);
		
		for (ap = 1; ap < 10; ap++)
		{
			printf("  %2.c ", Hotel[andar - 1][ap - 1].situacao);
		}
		
		for (ap = 10; ap < 15; ap++)
		{
			printf("  %3.c ", Hotel[andar - 1][ap - 1].situacao);
		}
		
		printf("  |              \n");
	} 
	
	printf("          |                                                                             |\n");
}     

void INFO_APTO(TipoApto Hotel[20][14], int *andar, int *ap)
{
	if (*andar < 1 || *andar > 20 || *ap < 1 || *ap > 14) 
	{
    	printf("\nANDAR OU APARTAMENTO INVALIDO.\n");
	}
				
	else if (Hotel[*andar - 1][*ap - 1].situacao == '.')
	{
		printf("\nAPTO: LIVRE\n");
	}
					
	else	
	{	
		if (Hotel[*andar - 1][*ap - 1].situacao == 'R')
		{
			printf("\nAPTO: RESERVADO\n");
		}
		
		else
		{
			printf("\nAPTO: OCUPADO\n");
		}
		
		printf("\n============= CLIENTE ==============\n");
						
		printf("CPF: %s\n", Hotel[*andar - 1][*ap - 1].Cliente.cpf);
						
		printf("NOME: %s\n", Hotel[*andar - 1][*ap - 1].Cliente.nome);
						
		printf("ENDERECO: %s\n", Hotel[*andar - 1][*ap - 1].Cliente.endereco.ender);
						
		printf("MUNICIPIO: %s\n", Hotel[*andar - 1][*ap - 1].Cliente.endereco.munic);
						
		printf("UF: %s\n", Hotel[*andar - 1][*ap - 1].Cliente.endereco.UF);
						
		printf("CEP: %s\n", Hotel[*andar - 1][*ap - 1].Cliente.endereco.cep);
						
		printf("TELEFONE: %s\n", Hotel[*andar - 1][*ap - 1].Cliente.telefone);
						
		printf("EMAIL: %s\n", Hotel[*andar - 1][*ap - 1].Cliente.email);
	}
}

void TAXA_OCUP_RESERV(TipoApto Hotel[20][14])
{
	printf("\nTAXAS DE OCUPACAO E RESERVAS\n");
            	
	float O = 0, R = 0;
    
    for (int andar = 0; andar < 20; andar++)
   	{
        for (int ap = 0; ap < 14; ap++)
    	{
      		if (Hotel[andar][ap].situacao == 'O')
    		{
            	O++;
			}
			
			else if (Hotel[andar][ap].situacao == 'R')
    		{
            	R++;
			}
		}
	}	
	
	printf("Porcentagem de quartos ocupados: %.2f%%%.\n", (O / ( 20 * 14)) * 100);
	printf("Porcentagem de quartos reservados: %.2f%%%.\n", (R / ( 20 * 14)) * 100);
}

//Função para limpar o buffer do teclado, evitando problemas com entrada de dados
void fClear()
{
	char carac;
	while ((carac = fgetc(stdin)) != EOF && carac != '\n') {}
}