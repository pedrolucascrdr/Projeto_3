#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "usuarios.h"

// Função para cadastrar um novo usuário na lista encadeada
Usuario* cadastrarUsuario(Usuario *inicio) {
    Usuario *novoUsuario = (Usuario*) malloc(sizeof(Usuario));
    if (novoUsuario == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return inicio;
    }

    // Definir valores do novo usuário
    novoUsuario->id = (inicio == NULL) ? 1 : inicio->id + 1; // Atribui o ID de forma automática
    printf("Digite o nome de usuario: ");
    scanf("%s", novoUsuario->nome);
    printf("Digite a senha: ");
    scanf("%s", novoUsuario->senha);

    novoUsuario->historico = NULL;  // Inicializa o histórico vazio

    // Insere o novo usuário no início da lista
    novoUsuario->prox = inicio;
    printf("Usuario cadastrado com sucesso!\n");

    return novoUsuario;
}

// Função para listar todos os usuários cadastrados
void listarUsuarios(Usuario *inicio) {
    if (inicio == NULL) {
        printf("Nenhum usuario cadastrado.\n");
        return;
    }

    Usuario *atual = inicio;
    while (atual != NULL) {
        printf("ID: %d, Nome: %s\n", atual->id, atual->nome);
        atual = atual->prox;
    }
}

// Função para excluir um usuário pelo ID
Usuario* excluirUsuario(Usuario *inicio, int id) {
    Usuario *atual = inicio, *anterior = NULL;

    while (atual != NULL && atual->id != id) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Usuario com ID %d nao encontrado!\n", id);
        return inicio;
    }

    // Remove o usuário da lista encadeada
    if (anterior == NULL) {
        inicio = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    // Liberar o histórico de cálculos
    Calculo *calcAtual = atual->historico;
    while (calcAtual != NULL) {
        Calculo *temp = calcAtual;
        calcAtual = calcAtual->prox;
        free(temp);
    }

    free(atual);
    printf("Usuario excluido com sucesso!\n");

    return inicio;
}

// Função para editar um usuário pelo ID
Usuario* editarUsuario(Usuario *inicio, int id) {
    Usuario *atual = inicio;

    while (atual != NULL && atual->id != id) {
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Usuario com ID %d nao encontrado!\n");
        return inicio;
    }

    printf("Digite o novo nome de usuario: ");
    scanf("%s", atual->nome);
    printf("Digite a nova senha: ");
    scanf("%s", atual->senha);

    printf("Usuario editado com sucesso!\n");
    return inicio;
}

// Função de login que verifica nome e senha
Usuario* login(Usuario *inicio) {
    char nome[MAX_NOME], senha[MAX_SENHA];

    printf("Digite o nome de usuario: ");
    scanf("%s", nome);
    printf("Digite a senha: ");
    scanf("%s", senha);

    Usuario *atual = inicio;
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0 && strcmp(atual->senha, senha) == 0) {
            printf("Login bem-sucedido!\n");
            return atual;
        }
        atual = atual->prox;
    }

    printf("Usuario ou senha incorretos!\n");
    return NULL;
}

// Função para realizar cálculos e armazenar no histórico
void realizarCalculo(Usuario *usuario) {
    char expressao[MAX_EXPRESSAO];
    float num1, num2, resultado;
    char operador;

    printf("Digite uma expressao (ex: 3 + 2): ");
    scanf("%f %c %f", &num1, &operador, &num2);

    switch (operador) {
        case '+': resultado = num1 + num2; break;
        case '-': resultado = num1 - num2; break;
        case '*': resultado = num1 * num2; break;
        case '/': 
            if (num2 != 0)
                resultado = num1 / num2;
            else {
                printf("Erro: Divisao por zero!\n");
                return;
            }
            break;
        default:
            printf("Operador invalido!\n");
            return;
    }

    printf("Resultado: %.2f\n", resultado);

    // Armazenar o cálculo no histórico
    sprintf(expressao, "%.2f %c %.2f = %.2f", num1, operador, num2, resultado);
    Calculo *novoCalculo = (Calculo*) malloc(sizeof(Calculo));
    strcpy(novoCalculo->expressao, expressao);
    novoCalculo->prox = usuario->historico;
    usuario->historico = novoCalculo;

    printf("Calculo salvo no historico!\n");
}

// Função para mostrar o histórico de cálculos de um usuário
void mostrarHistorico(Usuario *usuario) {
    if (usuario->historico == NULL) {
        printf("Historico vazio!\n");
        return;
    }

    Calculo *atual = usuario->historico;
    printf("--- Historico de Calculos ---\n");
    while (atual != NULL) {
        printf("%s\n", atual->expressao);
        atual = atual->prox;
    }
}

// Função para mostrar uma mensagem ao usuário
void falar() {
    printf(":)\n");
}

// Função para mostrar a data e a hora atuais
void mostrarDataHora() {
    time_t t;
    time(&t);
    printf("Data e Hora: %s", ctime(&t));
}
