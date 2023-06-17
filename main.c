#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Conversão
// Fila:  A C T G
// Pilha: T G A C

#define tamanho 20

typedef struct node {
    int id;
    char dado;
    struct node * proximo;
} * ptr_node;

ptr_node pilha;
ptr_node fila;
int FilaID = 0;
int PilhaID = 0;

void menu();
ptr_node inicializar(ptr_node elemento);
void menuInserir();
void menuExcluir();
bool verificacao(char string[], int stringTamanho);
void IDRecount(ptr_node elemento);
void limparBuffer();

// Funções da Fila
void InserirFila(ptr_node navegador, char string[], int stringTamanho);
void exibirFila(ptr_node navegador);
void ExcluirFila(ptr_node nodeExcluir);

// Funções da Pilha
void InserirPilha(ptr_node navegador, ptr_node navegadorFila, char string[], int stringTamanho);
void exibirPilha(ptr_node navegador);
void ExcluirPilha(ptr_node navegador);

int main(void)
{
    menu();

    return 0;
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
            InserirPilha(pilha, fila, string, stringTamanho);
        }
        
    } while (verify != true);
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

        navegador->id = FilaID;
        navegador->dado = string[i];
        navegador->proximo = inicializar(fila); // inicializando o próximo elemento
        navegador = navegador->proximo;
        FilaID++;
    }
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
        FilaID--;
        nodeExcluir = fila; // guardando o ponteiro para o primeiro elemento
        fila = fila->proximo; // fazendo a lista começar à partir do segundo elemento
        free(nodeExcluir); // excluindo o primeiro elemento
    }

    IDRecount(fila);

    return;
}

// Para fazer a inserção na pilha eu "leio" a lista como se fosse uma pilha, assim
// os valores entram na pilha ao contrário seguindo o exemplo apresentado no mapa

// O mecanismo de navegar pela fila funciona semelhante a uma máquina de escrever
// onde você digitava até onde queria (indice da fila) depois tinha de retornar para o 
// começo da folha manualmente, para começar uma nova linha (inserir novo elemento na pilha)

void InserirPilha(ptr_node navegadorPilha, ptr_node navegadorFila, char string[], int stringTamanho)
{
    stringTamanho--; // subtraindo 1 pra atribuir ela ao indice
    for (int i = stringTamanho; i >= 0; i--)
    {
        if (stringTamanho != 0)
        {   
            navegadorFila = fila; // retornando ao primeiro elemento da lista
            char letra;
           
            while (i != navegadorFila->id)
            {
                navegadorFila = navegadorFila->proximo; // indo até o ultimo elemento desejado da fila
            }

            letra = navegadorFila->dado; // pega a letra do elemento da fila para conversão

            switch (letra) // converte as letras
            {
            case 'A':
                letra = 'T'; 
                break;

            case 'C':
                letra = 'G';
                break;

            case 'T':
                letra = 'A';
                break;
            
            case 'G':
                letra = 'C';
                break;
            
            default:
                break;
            }

            if (navegadorPilha == NULL) // incializa a pilha
            {
                pilha = inicializar(pilha);
                navegadorPilha = pilha;
            }

            while (navegadorPilha->proximo != NULL) // vai até o ultimo elemento da pilha
            {
                navegadorPilha = navegadorPilha->proximo;
            }
               
            navegadorPilha->id = PilhaID; // por fim, insere todos os dados do elemento
            navegadorPilha->dado = letra;
            navegadorPilha->proximo = inicializar(pilha); // inicializa o proximo elemento
            navegadorPilha = navegadorPilha->proximo;
            PilhaID++;
        }
    }
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
        PilhaID--;
        ptr_node atual;
        while (nodeExcluir->proximo != NULL )
        {
            atual = nodeExcluir;
            nodeExcluir = nodeExcluir->proximo;
        }
        
        atual->proximo = nodeExcluir->proximo;
        free(nodeExcluir);
    }

    IDRecount(pilha);
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

void IDRecount(ptr_node elemento)
{
    if (elemento == NULL)
    {
        return;
    }
    
    int newID = 0;
    while (elemento->proximo != NULL)
    {
        elemento->id = newID;
        elemento = elemento->proximo;
        newID++;
    }
}

ptr_node inicializar(ptr_node elemento)
{
    elemento = (ptr_node)malloc(sizeof(ptr_node));
    elemento->id = 0;
    elemento->dado = '\0';
    elemento->proximo = NULL;

    return elemento;
}

void limparBuffer()
{
    int c; 
    while((c = getchar()) != '\n');
}