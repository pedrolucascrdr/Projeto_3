#ifndef USUARIOS_H
#define USUARIOS_H

#include <time.h>

#define MAX_NOME 50
#define MAX_SENHA 50
#define MAX_EXPRESSAO 100

// Estrutura para armazenar o histórico de cálculos
typedef struct Calculo {
    char expressao[MAX_EXPRESSAO];
    struct Calculo *prox;
} Calculo;

// Estrutura de usuário
typedef struct Usuario {
    int id;
    char nome[MAX_NOME];
    char senha[MAX_SENHA];
    Calculo *historico;  // Ponteiro para o histórico de cálculos (lista encadeada de cálculos)
    struct Usuario *prox;
} Usuario;

// Funções para manipulação de usuários
Usuario* cadastrarUsuario(Usuario *inicio);
Usuario* excluirUsuario(Usuario *inicio, int id);
Usuario* editarUsuario(Usuario *inicio, int id);
void listarUsuarios(Usuario *inicio);
Usuario* login(Usuario *inicio);

// Funções para cálculos e histórico
void realizarCalculo(Usuario *usuario);
void mostrarHistorico(Usuario *usuario);
void falar();
void mostrarDataHora();

#endif
