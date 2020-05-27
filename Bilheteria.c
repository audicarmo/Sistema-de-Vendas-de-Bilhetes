#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<string.h>
#include<ctype.h>
#define NUM_POLTRONAS 50
#define N 30                      // n�mero de caracteres do nome da pe�a
#define VALOR_PADRAO 20.0         // valor padr�o da entrada inteira

int totalisento=0;
int totalmeio=0;
int totalinteiro =0;

void menu_principal(void);        //Prot�tipo da fun��o menu_principal()
void menu_vendas(void);           //Prot�tipo da fun��o menu_vendas()
void menu_pecas(void);            //Prot�tipo da fun��o menu_pecas()
void menu_relatorio(void);        //Prot�tipo da fun��o menu_relatorio()



// defini��es de estruturas e tipo bool
typedef int bool;
enum { false, true };

typedef struct poltrona {
    int numero;
    bool ocupada;
} poltrona;

typedef struct peca {
    int codigo;
    char nome[N];
    char horario[5];
    double valor_arrecadado;
    int qtde_poltronas_disponiveis;
    poltrona lista_poltronas[NUM_POLTRONAS];
    
} peca;

// listas de nomes de pe�as e a lista do objeto pe�a
char nomes_pecas[][N] = {"Espet�culo n� 1 18:00", "Espet�culo n� 2 19:00", "Espet�culo n� 3 20:00", "Espet�culo n� 4 21:00"};
peca pecas_diponiveis[sizeof(nomes_pecas)/sizeof(char[N])];

// procedimento usado para obter o nome e o hor�rio dos itens da lista nome_peca
void separar_nome_horario(char nome_peca[], char horario_peca[], char nome_horario[])  {
    long tamanho = strlen(nome_horario);
    for(int i = 0; i < tamanho-5; i++)   {
        nome_peca[i] = nome_horario[i];
    }
    for(long i = 0; i < 5; i++)   {
        horario_peca[i] = nome_horario[i+tamanho-5];
    }
}


// inicializa valores dentro da estrutura pe�a
peca inicializa_peca(peca item_peca, int codigo, char nome_horario[])   {
    item_peca.codigo = codigo;
    separar_nome_horario(item_peca.nome, item_peca.horario, nome_horario);
    item_peca.valor_arrecadado = 0;
    item_peca.qtde_poltronas_disponiveis = NUM_POLTRONAS;
    for(int i = 0 ; i < NUM_POLTRONAS; i++)   {
        item_peca.lista_poltronas[i].numero = i+1;
        item_peca.lista_poltronas[i].ocupada = false;
    }
    return item_peca;
}


// faz a leitura do caracter para escolha das op��es de menu
int ler_opcao(int min, int max)   {
    int opcao=0;    
    do{    //Este trecho da função faz a validação da opção selecionada.    	
        scanf("%d", &opcao);
       
        if (opcao < min || opcao > max){
        	printf("Op��o Inv�lida. Digite digite novamente: "); 

			fflush(stdin);			                 	
		}
            
    }
    while(opcao < min || opcao > max);
    return opcao;
}

// lista na tela as pe�as dispon�veis e retorna a quantidade de itens
int listar_pecas()   {
    int max = 0;
    for(int i = 0; i < sizeof(pecas_diponiveis)/sizeof(peca); i++)  {
        printf("%d - %s \n", pecas_diponiveis[i].codigo, pecas_diponiveis[i].nome);
        if(max < pecas_diponiveis[i].codigo)
            max = pecas_diponiveis[i].codigo;
    }
    return max;
}



// encontra a pe�a pelo c�digo da pe�a
peca busca_peca(int codigo_peca)   {
    peca peca_selecionada = {};
    for(int i = 0; i < sizeof(pecas_diponiveis)/sizeof(peca); i++)  {
        if(pecas_diponiveis[i].codigo == codigo_peca)
            peca_selecionada = pecas_diponiveis[i];
    }
    return peca_selecionada;
}


// encontra o �ndice da pe�a no vetor pecas_disponiveis pelo c�digo da pe�a
int retornar_indice_peca_pelo_codigo(int codigo)   {
    int i;
    for(i = 0; i < sizeof(pecas_diponiveis)/sizeof(peca); i++)   {
        if(pecas_diponiveis[i].codigo == codigo)
            break;
    }
    return i;
}


// menu que define qual valor ser� cobrado e que realiza a finaliza��o da compra
void menu_valor(int codigo_peca, int poltrona_selecionada)   {
    int opcao_valor, indice_peca, indice_poltrona;
    char opcao_confirmacao;
    indice_peca = retornar_indice_peca_pelo_codigo(codigo_peca);
    indice_poltrona = poltrona_selecionada-1; // porque o �ndice come�a em zero e os n�meros de poltronas em 1
    printf("Selecione o valor de venda: \n \n");
    printf("1 - Inteira - R$ 20,00 \n");
    printf("2 - Meia-entrada (estudantes, crian�as de 02 a 12 anos, adultos a partir de 60 anos e professores da rede p�blica de ensino) - R$ 10,00\n");
    printf("3 - Entrada gratuita (somente ter�as-feiras, para crian�as carentes da rede p�blica de ensino)\n");
    printf("0 - Desistir da compra e voltar ao menu principal \n \n");
    opcao_valor = ler_opcao(0, 3);
    
    if(opcao_valor != 0)  {
        printf("Confirma a compra do ingresso? (S/N)");
        scanf(" %c", &opcao_confirmacao);
        fflush(stdin);
        while(!(opcao_confirmacao == 's' || opcao_confirmacao == 'S' || opcao_confirmacao == 'n' || opcao_confirmacao == 'N'))  {
            printf("Op��o inv�lida!\n");
            
            scanf("%c", &opcao_confirmacao);
            fflush(stdin);
        }
        if(opcao_confirmacao == 's' || opcao_confirmacao == 'S')   {
            int valor = VALOR_PADRAO;
            switch (opcao_valor) {
                case 2:
                    valor = VALOR_PADRAO/2; 
					totalmeio = totalmeio+1;                   
                    break;
                case 3:
                    valor = 0;
					totalisento = totalisento+1;                    
                    break;
                case 1:
                    valor = VALOR_PADRAO; 
					totalinteiro = totalinteiro+1;                   
                    break;
            }
            
            // define que a poltrona est� ocupada, decrementa a quantidade de poltronas dispon�veis e soma ao total arrecadado
            pecas_diponiveis[indice_peca].lista_poltronas[indice_poltrona].ocupada = true;
            pecas_diponiveis[indice_peca].qtde_poltronas_disponiveis--;
            pecas_diponiveis[indice_peca].valor_arrecadado = pecas_diponiveis[indice_peca].valor_arrecadado + valor;
            printf("\n \n ***Poltrona %d vendida*** \n \n \n", poltrona_selecionada);
            
            //system("cls");
            menu_pecas();
        } else {
            printf("\n \n Venda n�o realizada!\n \n \n");
            
            menu_pecas();
        }
    } else {
        printf("\n \n Venda n�o realizada!\n \n \n");
        menu_pecas();
    }
    
    switch (opcao_valor){
        case 1:
            menu_pecas();
            break;
            
        default:
            system("cls");
            menu_principal();
    }
    
}


////////////////////////////////////////////////////////////////////////////////////////////////
// mostra informa��es da pe�a e poltronas dispon�veis
void menu_poltronas(int codigo_peca)   {
    peca peca_selecionada = busca_peca(codigo_peca);
    printf("********************************************************\n");
    printf("Nome da apresenta��o: %s\n", peca_selecionada.nome);
    printf("Hor�rio da apresenta��o: %s\n", peca_selecionada.horario);
    printf("Lota��o m�xima: %d lugares\n \n \n", NUM_POLTRONAS);
    if(peca_selecionada.qtde_poltronas_disponiveis == 0)   {
        printf("N�o h� mais lugares dispon�veis para esta pe�a. \n \n \n");
        menu_pecas();
    }
    printf("Poltronas dispon�veis:\n \n");
    for(int i = 0; i < sizeof(peca_selecionada.lista_poltronas)/sizeof(poltrona); i++)   {
        if(peca_selecionada.lista_poltronas[i].ocupada == false)   {
            printf("[%d]", peca_selecionada.lista_poltronas[i].numero);
            if(i % 10 == 0)
                printf("\n");
        }
    }
    
    int opcao_poltrona, indice_poltrona;
    
    printf("\n \n");
    printf("Digite o n�mero da poltrona: ");
    opcao_poltrona = ler_opcao(1, sizeof(peca_selecionada.lista_poltronas)/sizeof(poltrona));      
    indice_poltrona = opcao_poltrona - 1; // pq o �ndice come�a em zero e a numera��o em 1
    while(peca_selecionada.lista_poltronas[indice_poltrona].ocupada == true)  {
        printf("A poltrona digitada n�o est� dispon�vel! Selecione novamente... \n \n");
        opcao_poltrona = ler_opcao(1, sizeof(peca_selecionada.lista_poltronas)/sizeof(poltrona));
        indice_poltrona = opcao_poltrona - 1;
    }
    printf("Poltrona %d selecionada! \n \n", opcao_poltrona);
    menu_valor(peca_selecionada.codigo, opcao_poltrona);
    
}


////////////////////////////////////////////////////////////////////////////////////////////////
// menu com as pe�as dispon�veis
void menu_pecas(){
    printf("********************************************************\n");
    printf("Selecione a pe�a: \n \n");
    int max = listar_pecas();
    printf("ou\n");
    printf("0 - Voltar\n");
    printf("\n");
    printf("Op��o: ");
    int opc_peca = ler_opcao(0, max);
    
    switch (opc_peca){
        case 0:
            system("cls");
			menu_vendas();
            break;
       
        default:
            system("cls");
            menu_poltronas(opc_peca);
            break;
            
    }
    
}


// menu vendas
void menu_vendas(){        //Fun��o do MENU VENDAS.
    
    printf("********************************************************\n");
    printf("1 - Pe�as e hor�rios\n");
    printf("0 - Voltar\n");
    printf("--> ");
    
    int opc_menu_vendas = ler_opcao(0, 1);
    
    //Ap�s a valida��o, a fun��o levar� � fun��o respectiva.
    switch (opc_menu_vendas){
        case 1:
        	system("cls");
            menu_pecas();
            break;
            
        default:
            system("cls");
            menu_principal();
    }
    
}


// exibe o relat�rio de vendas
void menu_relatorio()   {
    double total = 0;
    printf("\n\nTotal arrecadado:\n\n");
    int i = 0;
    while(i < sizeof(pecas_diponiveis)/sizeof(peca))   {
        total = total + pecas_diponiveis[i].valor_arrecadado;
        printf("%s: ", pecas_diponiveis[i].nome);
        printf("R$ %.2f\n", pecas_diponiveis[i].valor_arrecadado);
        i++;
    }
        
    printf("\nTotal de isentos: %d", totalisento);
    printf("\nTotal de meias entradas: %d", totalmeio);
    printf("\nTotal de entradas inteiras: %d", totalinteiro);
    
    printf("\n\nTotal arrecadado: R$ %.2f", total);
    printf(" \n \n \n \n");
    printf("Pressione qualquer tecla para continuar...");
	system("PAUSE>>null");
	system("cls");
    menu_principal();
}


////////////////////////////////////////////////////////////////////////////////////////////////
void menu_principal(){        //Fun��o do MENU PRINCIPAL. 1� primeira fun��o a ser chamada no programa.
    
    
    printf("********************************************************\n");
    printf("********* SEJA BEM VINDO AO TEATRO DO BEM **************\n");
    printf("********************************************************\n");
    printf("\n");
    printf("Escolha uma das fun��es abaixo:\n");
    printf("\n");
    printf("1 - Vender Ingresso\n");
    printf("2 - Relat�rio de vendas\n");
    printf("3 - Sair\n");
    printf("\n");
    printf("Digite a op��o desejada: ");
    
    int opc_menu_principal = ler_opcao(1, 3);    
    //Ap�s a valida��o, a fun��o levar� � fun��o respectiva.
    switch (opc_menu_principal){
        case 1:
            system("cls");
            menu_vendas();
			
            break;
            
        case 2:
            system("cls");
            menu_relatorio();
            break;
            
       case 3:
            system("cls");
            char opcao_sair;
            printf("Deseja realmente sair ('S' para sim e 'N' para n�o)? ");
            scanf(" %c", &opcao_sair);
           
	        while(!(opcao_sair == 's' || opcao_sair == 'S' || opcao_sair == 'n' || opcao_sair == 'N'))  {
	           
	            printf("Opcao inv�lida!\n", opcao_sair);
	            printf("Deseja realmente sair ('S' para sim e 'N' para n�o)? ");
	            scanf(" %c", &opcao_sair);
	        }
	        if(opcao_sair == 's' || opcao_sair == 'S')   {
	           exit(0); 
	            } 
				else {
					 system("cls");
         			 menu_principal();
       		 		}
                       
        
    }
}

int main(){
    
    setlocale(LC_ALL, "Portuguese");  //Defini��o de Unicode, para apresenta��o correta de caracteres acentuados.
    
    printf("********************************************************\n");
    printf("********************BILHETERIA**************************\n");
    printf("********************************************************\n");
    
    
    
    for(int i = 0; i < sizeof(nomes_pecas)/sizeof(char[N]); i++)  {
        pecas_diponiveis[i] = inicializa_peca(pecas_diponiveis[i], i+1, nomes_pecas[i]);
    }
    
    menu_principal();
    
	return 0;
}
