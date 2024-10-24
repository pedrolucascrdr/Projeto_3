#include <stdio.h>
#include "usuarios.h"

void menuPosLogin(Usuario *usuario) {
    int opcao;

    do {
        printf("\n--- BEM VINDO ---\n");
        printf("1. Realizar Calculo\n");
        printf("2. Mostrar Historico de Calculos\n");
        printf("3. Falar\n");
        printf("4. Mostrar Data e Hora\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                realizarCalculo(usuario);
                break;
            case 2:
                mostrarHistorico(usuario);
                break;
            case 3:
                falar();
                break;
            case 4:
                mostrarDataHora();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

int main() {
    Usuario *listaUsuarios = NULL;
    int opcao, id;

    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Cadastrar Usuario\n");
        printf("2. Fazer Login\n");
        printf("3. Listar Usuarios\n");
        printf("4. Editar Usuario\n");
        printf("5. Excluir Usuario\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                listaUsuarios = cadastrarUsuario(listaUsuarios);
                break;
            case 2: {
                Usuario *usuarioLogado = login(listaUsuarios);
                if (usuarioLogado != NULL) {
                    menuPosLogin(usuarioLogado);
                }
                break;
            }
            case 3:
                listarUsuarios(listaUsuarios);
                break;
            case 4:
                printf("Digite o ID do usuario a ser editado: ");
                scanf("%d", &id);
                listaUsuarios = editarUsuario(listaUsuarios, id);
                break;
            case 5:
                printf("Digite o ID do usuario a ser excluido: ");
                scanf("%d", &id);
                listaUsuarios = excluirUsuario(listaUsuarios, id);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
