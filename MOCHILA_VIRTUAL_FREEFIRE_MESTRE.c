#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ITENS 10
#define TAM_NOME 50
#define TAM_TIPO 20

// Enumeração para critérios de ordenação
enum CriterioOrdenacao {
    POR_NOME = 1,
    POR_TIPO = 2,
    POR_PRIORIDADE = 3
};

// Struct para representar cada item
struct Item {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
    int prioridade; // NOVO CAMPO: valores de 1 a 5
};

// Variável global para contar comparações
int comparacoes = 0;

// Função para limpar o buffer de entrada
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para validar prioridade
bool validarPrioridade(int prioridade) {
    return prioridade >= 1 && prioridade <= 5;
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
    
    // NOVO: Entrada da prioridade
    do {
        printf("Prioridade (1-5, onde 5 é mais importante): ");
        scanf("%d", &mochila[*quantidadeItens].prioridade);
        if (!validarPrioridade(mochila[*quantidadeItens].prioridade)) {
            printf("❌ Prioridade inválida! Digite um valor entre 1 e 5.\n");
        }
    } while (!validarPrioridade(mochila[*quantidadeItens].prioridade));
    
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

// FUNÇÃO NOVA: Ordenação por Insertion Sort
void ordenarMochila(struct Item mochila[], int quantidadeItens, enum CriterioOrdenacao criterio) {
    if (quantidadeItens == 0) {
        printf("❌ Mochila vazia! Não há itens para ordenar.\n");
        return;
    }
    
    comparacoes = 0; // Reinicia contador
    struct Item chave;
    int i, j;
    
    for (i = 1; i < quantidadeItens; i++) {
        chave = mochila[i];
        j = i - 1;
        
        // Move os elementos maiores que a chave uma posição à frente
        while (j >= 0) {
            comparacoes++;
            int comparacao = 0;
            
            switch (criterio) {
                case POR_NOME:
                    comparacao = strcmp(mochila[j].nome, chave.nome);
                    break;
                case POR_TIPO:
                    comparacao = strcmp(mochila[j].tipo, chave.tipo);
                    break;
                case POR_PRIORIDADE:
                    comparacao = (mochila[j].prioridade < chave.prioridade) ? 1 : 
                                (mochila[j].prioridade > chave.prioridade) ? -1 : 0;
                    break;
            }
            
            if (comparacao > 0) {
                mochila[j + 1] = mochila[j];
                j--;
            } else {
                break;
            }
        }
        mochila[j + 1] = chave;
    }
    
    printf("✅ Mochila ordenada com sucesso!\n");
    printf("📊 Comparações realizadas: %d\n", comparacoes);
}

// FUNÇÃO NOVA: Verificar se a mochila está ordenada por nome
bool estaOrdenadaPorNome(struct Item mochila[], int quantidadeItens) {
    for (int i = 0; i < quantidadeItens - 1; i++) {
        if (strcmp(mochila[i].nome, mochila[i + 1].nome) > 0) {
            return false;
        }
    }
    return true;
}

// FUNÇÃO NOVA: Busca binária por nome
void buscaBinariaPorNome(struct Item mochila[], int quantidadeItens) {
    if (quantidadeItens == 0) {
        printf("❌ Mochila vazia! Não há itens para buscar.\n");
        return;
    }
    
    // Verifica se a lista está ordenada por nome
    if (!estaOrdenadaPorNome(mochila, quantidadeItens)) {
        printf("❌ A mochila não está ordenada por nome!\n");
        printf("💡 Use a opção de ordenação (critério: Nome) antes de usar busca binária.\n");
        return;
    }
    
    printf("\n🔍 BUSCA BINÁRIA POR NOME\n");
    char nomeBusca[TAM_NOME];
    
    printf("Digite o nome do item a ser buscado: ");
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    // Implementação da busca binária
    int inicio = 0;
    int fim = quantidadeItens - 1;
    int meio;
    bool encontrado = false;
    int posicao = -1;
    int comparacoesBusca = 0;
    
    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        comparacoesBusca++;
        
        int comparacao = strcmp(mochila[meio].nome, nomeBusca);
        
        if (comparacao == 0) {
            encontrado = true;
            posicao = meio;
            break;
        } else if (comparacao < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    
    // Exibe o resultado da busca
    if (encontrado) {
        printf("\n✅ ITEM ENCONTRADO (Busca Binária)!\n");
        printf("┌────────────────────────────────────────────────────────┐\n");
        printf("│ %-56s │\n", "DETALHES DO ITEM");
        printf("├────────────────────────────────────────────────────────┤\n");
        printf("│ %-15s: %-38s │\n", "Nome", mochila[posicao].nome);
        printf("│ %-15s: %-38s │\n", "Tipo", mochila[posicao].tipo);
        printf("│ %-15s: %-38d │\n", "Quantidade", mochila[posicao].quantidade);
        printf("│ %-15s: %-38d │\n", "Prioridade", mochila[posicao].prioridade);
        printf("│ %-15s: %-38d │\n", "Comparações", comparacoesBusca);
        printf("└────────────────────────────────────────────────────────┘\n");
    } else {
        printf("\n❌ Item '%s' não encontrado na mochila.\n", nomeBusca);
        printf("📊 Comparações realizadas: %d\n", comparacoesBusca);
    }
}

// Busca sequencial mantida para comparação
void buscarItemPorNome(struct Item mochila[], int quantidadeItens) {
    if (quantidadeItens == 0) {
        printf("❌ Mochila vazia! Não há itens para buscar.\n");
        return;
    }
    
    printf("\n🔍 BUSCA SEQUENCIAL POR NOME\n");
    char nomeBusca[TAM_NOME];
    
    printf("Digite o nome do item a ser buscado: ");
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    int itemEncontrado = 0;
    int posicao = -1;
    int comparacoesBusca = 0;
    
    for (int i = 0; i < quantidadeItens; i++) {
        comparacoesBusca++;
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            itemEncontrado = 1;
            posicao = i;
            break;
        }
    }
    
    if (itemEncontrado) {
        printf("\n✅ ITEM ENCONTRADO (Busca Sequencial)!\n");
        printf("┌────────────────────────────────────────────────────────┐\n");
        printf("│ %-56s │\n", "DETALHES DO ITEM");
        printf("├────────────────────────────────────────────────────────┤\n");
        printf("│ %-15s: %-38s │\n", "Nome", mochila[posicao].nome);
        printf("│ %-15s: %-38s │\n", "Tipo", mochila[posicao].tipo);
        printf("│ %-15s: %-38d │\n", "Quantidade", mochila[posicao].quantidade);
        printf("│ %-15s: %-38d │\n", "Prioridade", mochila[posicao].prioridade);
        printf("│ %-15s: %-38d │\n", "Comparações", comparacoesBusca);
        printf("└────────────────────────────────────────────────────────┘\n");
    } else {
        printf("\n❌ Item '%s' não encontrado na mochila.\n", nomeBusca);
        printf("📊 Comparações realizadas: %d\n", comparacoesBusca);
    }
}

// Função para listar todos os itens
void listarItens(struct Item mochila[], int quantidadeItens) {
    printf("\n🎒 MOCHILA FREE FIRE - %d/%d itens\n", quantidadeItens, MAX_ITENS);
    
    if (quantidadeItens == 0) {
        printf("📭 Mochila vazia!\n");
        return;
    }
    
    // Cabeçalho da tabela
    printf("┌────────────────────────────────────┬────────────────────┬────────────┬────────────┐\n");
    printf("│ %-34s │ %-18s │ %-10s │ %-10s │\n", "NOME", "TIPO", "QUANTIDADE", "PRIORIDADE");
    printf("├────────────────────────────────────┼────────────────────┼────────────┼────────────┤\n");
    
    // Dados dos itens
    for (int i = 0; i < quantidadeItens; i++) {
        printf("│ %-34s │ %-18s │ %-10d │ %-10d │\n", 
               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
    }
    
    // Rodapé da tabela
    printf("└────────────────────────────────────┴────────────────────┴────────────┴────────────┘\n");
    
    // Informação sobre ordenação
    if (estaOrdenadaPorNome(mochila, quantidadeItens)) {
        printf("📈 Status: Ordenada por nome (pronta para busca binária)\n");
    } else {
        printf("📉 Status: Não ordenada por nome\n");
    }
}

int main() {
    struct Item mochila[MAX_ITENS];
    int quantidadeItens = 0;
    int opcao;
    int criterio;
    
    printf("🎮 SISTEMA MOCHILA VIRTUAL FREE FIRE - NÍVEL MESTRE 🎮\n");
    printf("=======================================================\n");
    
    do {
        printf("\n📋 MENU PRINCIPAL:\n");
        printf("1 ➕ Adicionar item\n");
        printf("2 🗑️ Remover item\n");
        printf("3 📋 Listar itens\n");
        printf("4 🔍 Busca sequencial por nome\n");
        printf("5 🎯 Busca binária por nome\n"); // NOVA OPÇÃO
        printf("6 📊 Ordenar mochila\n"); // NOVA OPÇÃO
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
                
            case 4:
                buscarItemPorNome(mochila, quantidadeItens);
                break;
                
            case 5: // NOVO: Busca binária
                buscaBinariaPorNome(mochila, quantidadeItens);
                break;
                
            case 6: // NOVO: Ordenação
                printf("\n📊 ORDENAR MOCHILA\n");
                printf("1 - Por nome (A-Z)\n");
                printf("2 - Por tipo (A-Z)\n");
                printf("3 - Por prioridade (5-1)\n");
                printf("Escolha o critério: ");
                scanf("%d", &criterio);
                limparBuffer();
                
                if (criterio >= POR_NOME && criterio <= POR_PRIORIDADE) {
                    ordenarMochila(mochila, quantidadeItens, criterio);
                } else {
                    printf("❌ Critério inválido!\n");
                }
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