#include <stdio.h>
#include <string.h>

#define MAX_ITENS 10
#define TAM_NOME 50
#define TAM_TIPO 20

// Struct para representar cada item
struct Item {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
};

// Função para limpar o buffer de entrada
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para adicionar item à mochila
int adicionarItem(struct Item mochila[], int *quantidadeItens) {
    if (*quantidadeItens >= MAX_ITENS) {
        printf("❌ Mochila cheia! Não é possível adicionar mais itens.\n");
        return 0;
    }
    
    printf("\n➕ ADICIONAR ITEM\n");
    
    printf("Nome do item: ");
    fgets(mochila[*quantidadeItens].nome, TAM_NOME, stdin);
    mochila[*quantidadeItens].nome[strcspn(mochila[*quantidadeItens].nome, "\n")] = '\0';
    
    printf("Tipo do item: ");
    fgets(mochila[*quantidadeItens].tipo, TAM_TIPO, stdin);
    mochila[*quantidadeItens].tipo[strcspn(mochila[*quantidadeItens].tipo, "\n")] = '\0';
    
    printf("Quantidade: ");
    scanf("%d", &mochila[*quantidadeItens].quantidade);
    limparBuffer();
    
    (*quantidadeItens)++;
    printf("✅ Item adicionado com sucesso!\n");
    return 1;
}

// Função para remover item pelo nome
int removerItem(struct Item mochila[], int *quantidadeItens) {
    if (*quantidadeItens == 0) {
        printf("❌ Mochila vazia! Não há itens para remover.\n");
        return 0;
    }
    
    printf("\n🗑️ REMOVER ITEM\n");
    char nomeBusca[TAM_NOME];
    
    printf("Digite o nome do item a ser removido: ");
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    for (int i = 0; i < *quantidadeItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            // Move todos os itens uma posição para frente
            for (int j = i; j < *quantidadeItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*quantidadeItens)--;
            printf("✅ Item '%s' removido com sucesso!\n", nomeBusca);
            return 1;
        }
    }
    
    printf("❌ Item '%s' não encontrado na mochila.\n", nomeBusca);
    return 0;
}

// Função para listar todos os itens
void listarItens(struct Item mochila[], int quantidadeItens) {
    printf("\n🎒 MOCHILA FREE FIRE - %d/%d itens\n", quantidadeItens, MAX_ITENS);
    
    if (quantidadeItens == 0) {
        printf("📭 Mochila vazia!\n");
        return;
    }
    
    // Cabeçalho da tabela
    printf("┌────────────────────────────────────┬────────────────────┬────────────┐\n");
    printf("│ %-34s │ %-18s │ %-10s │\n", "NOME", "TIPO", "QUANTIDADE");
    printf("├────────────────────────────────────┼────────────────────┼────────────┤\n");
    
    // Dados dos itens
    for (int i = 0; i < quantidadeItens; i++) {
        printf("│ %-34s │ %-18s │ %-10d │\n", 
               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    
    // Rodapé da tabela
    printf("└────────────────────────────────────┴────────────────────┴────────────┘\n");
}

int main() {
    struct Item mochila[MAX_ITENS];
    int quantidadeItens = 0;
    int opcao;
    
    printf("🎮 SISTEMA MOCHILA VIRTUAL FREE FIRE 🎮\n");
    printf("========================================\n");
    
    do {
        printf("\n📋 MENU PRINCIPAL:\n");
        printf("1 ➕ Adicionar item\n");
        printf("2 🗑️ Remover item\n");
        printf("3 📋 Listar itens\n");
        printf("0 🚪 Sair\n");
        printf("Escolha uma opção: ");
        
        scanf("%d", &opcao);
        limparBuffer();
        
        switch (opcao) {
            case 1:
                adicionarItem(mochila, &quantidadeItens);
                break;
                
            case 2:
                removerItem(mochila, &quantidadeItens);
                break;
                
            case 3:
                listarItens(mochila, quantidadeItens);
                break;
                
            case 0:
                printf("\n👋 Obrigado por usar a Mochila Virtual Free Fire!\n");
                printf("🎯 Boa sorte nas partidas!\n");
                break;
                
            default:
                printf("❌ Opção inválida! Tente novamente.\n");
        }
        
    } while (opcao != 0);
    
    return 0;
}