#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Conversão
// Fila:  A C T G
// Pilha: C A G T

#define tamanho 20

typedef struct node {
    char dado;
    struct node * proximo;
} * ptr_node;

ptr_node pilha;
ptr_node fila;
int FilaQTD = 0;
int PilhaQTD = 0;

void limparBuffer();
void menu();

void menuInserir();
ptr_node inicializar(ptr_node elemento);
bool verificacao(char string[], int stringTamanho);

// Funções da Fila
void InserirFila(ptr_node navegador, char string[], int stringTamanho);
void exibirFila(ptr_node navegador);
void ExcluirFila(ptr_node nodeExcluir);


// Funções da Pilha
void InserirPilha(ptr_node navegadorPilha, char string[], int stringTamanho);
void empilhar(ptr_node navegadorFila, int stringTamanho);
void converter(char string[], int stringTamanho);
void exibirPilha(ptr_node navegador);
void ExcluirPilha(ptr_node navegador);

int main(void)
{
    menu();

    return 0;
}

void limparBuffer()
{
    int c; 
    while((c = getchar()) != '\n');
}

void menu()
{
    int seletor = -1;
    while (seletor != 0)
    {
        system("clear");
        printf("--------------| ELEMETOS |--------------\n");
        exibirFila(fila);
        exibirPilha(pilha);
        
        printf("\nSelecione uma opção: \n\n");
        printf("0. Sair \n");
        printf("1. Inserir dados.\n");
        printf("2. Excluir dados.\n");
        
        printf("\n >>> ");
        limparBuffer();
        scanf("%d", &seletor);

        switch (seletor)
        {
        case 0:
            return;
            break;
        
        case 1:
            menuInserir();
            break;

        case 2:
            ExcluirFila(fila);
            ExcluirPilha(pilha);
            break;
        
        default:
            printf("Opção inválida! Tente novamente. \n\n");
            limparBuffer();
            getchar();
            break;
        }
    }
}


void menuInserir()
{  
    char string[tamanho];
    bool verify = false;
    int stringTamanho = 0;

    do
    {
        printf("Para sair digite: 0\n");
        printf("Insira a sequência de nucleotídeos: \n\n>>> ");
        limparBuffer();
        fgets(string, tamanho, stdin);
        stringTamanho = strlen(string) - 1; // pegando o tamanho da string pra usar na verificação e na inserção 
                                            // (subtraindo o indice que irá armazenar o "\n")

        if (strcmp(string, "0") == 1)
            return;

        verify = verificacao(string, stringTamanho); // verificando a string
        if (verify != true) // caso a string esteja inválida
        {
            printf("Caracteres inválidos foram inseridos, tente novamente! \n\n");
            limparBuffer();
            getchar();
        }
        else
        {
            InserirFila(fila, string, stringTamanho);
            empilhar(fila, stringTamanho);
        }
        
    } while (verify != true);
}

ptr_node inicializar(ptr_node elemento)
{
    elemento = (ptr_node)malloc(sizeof(ptr_node));
    elemento->dado = '\0';
    elemento->proximo = NULL;

    return elemento;
}

bool verificacao(char string[], int stringTamanho)
{   
    bool setTrue = true;
    for (int i = 0; i < stringTamanho; i++)
    {
        if (string[i] != 'A' && string[i] != 'C' && string[i] != 'T' && string[i] !='G')
        {
            setTrue = false;
        }
    }
    
    return setTrue;
}


void InserirFila(ptr_node navegador, char string[], int stringTamanho) // variavél utilizada pra navegar na fila
{
    if (fila == NULL)
    { 
        fila = inicializar(fila); // caso navegador não existisse, não seria possivel iniciar a lista
        navegador = fila;
    }

    for (int i = 0; i < stringTamanho; i++)
    {
        while (navegador->proximo!= NULL)
        {
            navegador = navegador->proximo; // "pulando" de elemento em elemento
        }

        //navegador->id = FilaID;
        navegador->dado = string[i];
        navegador->proximo = inicializar(fila); // inicializando o próximo elemento
        navegador = navegador->proximo;
        FilaQTD++;
    }
}

void exibirFila(ptr_node navegador)
{
    printf("Fila:  [ ");
    if (navegador != NULL)
    {
        while (navegador->proximo != NULL)
        {
            printf("%c ", navegador->dado);
            navegador = navegador->proximo;
        }
    } 
    else 
    {
        printf("vazia ");
    }
    
    printf("]\n");
}

void ExcluirFila(ptr_node nodeExcluir)
{   
    if (nodeExcluir == NULL)
    {
        printf("A fila esta vazia, não há elementos para excluir!\n");
        limparBuffer();
        getchar();
        return;
    } 
    else if (nodeExcluir->proximo == NULL)
    {
        fila = NULL; // Assinando como NULL para poder ser iniciado na inserção
        free(fila);
    } 
    else 
    {
        FilaQTD--;
        nodeExcluir = fila; // guardando o ponteiro para o primeiro elemento
        fila = fila->proximo; // fazendo a lista começar à partir do segundo elemento
        free(nodeExcluir); // excluindo o primeiro elemento
    }

    return;
}


void InserirPilha(ptr_node navegadorPilha, char string[], int stringTamanho)
{
    for (int i = 0; i < stringTamanho; i++)
    {
        if (navegadorPilha == NULL) // incializa a pilha
        {
            pilha = inicializar(pilha);
            navegadorPilha = pilha;
        }

        while (navegadorPilha->proximo != NULL) // vai até o ultimo elemento da pilha
        {
            navegadorPilha = navegadorPilha->proximo;
        }

        navegadorPilha->dado = string[i];
        navegadorPilha->proximo = inicializar(pilha); // inicializa o proximo elemento
        navegadorPilha = navegadorPilha->proximo;
        PilhaQTD++;
    }
}

void empilhar(ptr_node navegadorFila, int stringTamanho)
{   
    // Para empilhar os valores eu leio a fila na da esquerda pra direita (seguindo o padrão FIFO)
    // porém enchendo o vetor da direita pra esquerda (seguindo o padrão LIFO)

    int indice = stringTamanho - 1;
    int parada = PilhaQTD;
    char string[stringTamanho];

    if (stringTamanho != 0)
    {
        if (pilha != NULL)
        {
            int i = 0;
            for (int i = 0; i < parada; i++) // vai até o ponto onde os novos elementos foram adicionados
            {
                navegadorFila = navegadorFila->proximo;
                i++;
            }
        }

        while (navegadorFila->proximo != NULL) // corre pelos novos elementos colocando-os na string à partir do ultimo indice
        {
            string[indice] = navegadorFila->dado;
            navegadorFila = navegadorFila->proximo;
            indice--;
        }
        
        converter(string, stringTamanho);
        InserirPilha(pilha, string, stringTamanho);
    }
}

void converter(char string[], int stringTamanho)
{
    for (int i = 0; i < stringTamanho; i++)
    {
        char letra = string[i];
        switch (letra)
        {
        case 'A':
            string[i] = 'T'; 
            break;

        case 'C':
            string[i] = 'G';
            break;

        case 'T':
            string[i] = 'A';
            break;
        
        case 'G':
            string[i] = 'C';
            break;
        }
    }
}

void exibirPilha(ptr_node navegador)
{
    printf("Pilha: [ ");
    if (navegador != NULL)
    {
        while (navegador->proximo != NULL)
        {
            printf("%c ", navegador->dado);
            navegador = navegador->proximo;
        }
    } 
    else 
    {
        printf("vazia ");
    }
    
    printf("]\n");
}

void ExcluirPilha(ptr_node nodeExcluir)
{
    if (nodeExcluir == NULL)
    {
        return;
    } 
    else if (nodeExcluir->proximo == NULL)
    {
        pilha = NULL;
        free(pilha);
        return;
    } 
    else
    {
        PilhaQTD--;
        ptr_node atual;
        while (nodeExcluir->proximo != NULL )
        {
            atual = nodeExcluir;
            nodeExcluir = nodeExcluir->proximo;
        }
        
        atual->proximo = nodeExcluir->proximo;
        free(nodeExcluir);
    }
}