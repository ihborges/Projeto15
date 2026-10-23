#include <stdio.h>   // Inclui a biblioteca padrão de entrada/saída (para usar printf)
#include <stdlib.h>  // Inclui a biblioteca padrão (para usar malloc, free e rand)

/* ========================================================================= */
/* FUNÇÃO 1: Ordena o vetor e CONTA quantas comparações foram feitas         */
/* ========================================================================= */
long long selection_sort_comparacoes(int *v, int n) {
    long long comparacoes = 0;       // Cria o contador. 'long long' evita estouro em n=2000
    for (int i = 0; i < n - 1; i++) { // Loop externo: vai da posição 0 até a penúltima
        int min_idx = i;              // Assume que o menor elemento está na posição atual (i)
        for (int j = i + 1; j < n; j++) { // Loop interno: procura nos elementos à frente de 'i'
            comparacoes++;            // INCREMENTA O CONTADOR: achamos mais uma comparação!
            if (v[j] < v[min_idx])    // Compara o elemento atual (j) com o menor encontrado até agora
                min_idx = j;          // Se for menor, guarda a nova posição do menor
        }
        if (min_idx != i) {           // Terminou de procurar? Se o menor não estava na posição 'i'...
            int tmp = v[i];           // Guarda o valor que estava na posição 'i'
            v[i] = v[min_idx];        // Coloca o menor valor na posição 'i'
            v[min_idx] = tmp;         // Coloca o antigo valor na posição do menor (troca)
        }
    }
    return comparacoes;               // Devolve o total de comparações feitas (o nosso T(n))
}

/* ========================================================================= */
/* FUNÇÃO 2: Preenche o vetor com números aleatórios                         */
/* ========================================================================= */
void preencher_aleatorio(int *v, int n) {
    for (int i = 0; i < n; i++)       // Percorre o vetor do início ao fim
        v[i] = rand() % 100000;       // Preenche cada posição com um número aleatório de 0 a 99.999
}

/* ========================================================================= */
/* FUNÇÃO 3: O programa principal                                            */
/* ========================================================================= */
int main(void) {
    // Cria uma lista (vetor) com os tamanhos de entrada que vamos testar
    int tamanhos[] = {10, 50, 100, 500, 1000, 2000};
    // Calcula quantos elementos existem na lista acima (dá 6)
    int num_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);

    // Define as constantes assintóticas que queremos provar
    const double c1 = 0.25;           // Limite inferior escolhido (chão do túnel)
    const double c2 = 0.50;           // Limite superior escolhido (teto do túnel)
    int n0 = -1;                      // Variável para guardar o n0. Começa em -1 (não encontrado)

    // Imprime o cabeçalho da tabela formatado
    printf("=== Validador Numerico de Constantes Assintoticas ===\n\n");
    printf("%8s %14s %14s %14s %14s %14s\n",
           "n", "T(n)", "n^2", "T(n)/n^2", "c1*n^2", "c2*n^2");
    printf("-------------------------------------------------------------------------------\n");

    // Loop principal: testa um tamanho de cada vez (10, depois 50, depois 100...)
    for (int k = 0; k < num_tamanhos; k++) {
        int n = tamanhos[k];          // Pega o tamanho atual (ex: na 1ª volta, n = 10)
        
        // Aloca memória dinamicamente para um vetor do tamanho 'n'
        int *v = malloc(n * sizeof(int)); 
        
        // Chama a função para encher o vetor com números aleatórios
        preencher_aleatorio(v, n);

        // Chama a função de ordenação e guarda o número de comparações na variável T
        long long T = selection_sort_comparacoes(v, n);
        
        // Libera a memória do vetor (boa prática em C, evita vazamento de memória)
        free(v);

        // --- Cálculos Matemáticos ---
        double n2      = (double)n * n;              // Calcula n ao quadrado (ex: 10 * 10 = 100)
        double razao   = (double)T / n2;             // Calcula a Razão R(n) = T(n) / n^2
        double limite1 = c1 * n2;                    // Calcula o limite inferior: 0.25 * n^2
        double limite2 = c2 * n2;                    // Calcula o limite superior: 0.50 * n^2

        // --- Impressão da linha da tabela ---
        printf("%8d %14lld %14.0f %14.6f %14.2f %14.2f%s\n",
               n, T, n2, razao, limite1, limite2,
               // Operador ternário: se T estiver entre os limites, imprime "[OK]", senão "[--]"
               (T >= limite1 && T <= limite2) ? "  [OK]" : "  [--]");

        // --- Descoberta do n0 ---
        // Se ainda não achamos o n0 (n0 == -1) E a desigualdade for verdadeira...
        if (n0 == -1 && (double)T >= c1 * n2 && (double)T <= c2 * n2)
            n0 = n;                   // ...guarda o 'n' atual como o nosso n0!
    }

    // Imprime o rodapé da tabela
    printf("-------------------------------------------------------------------------------\n\n");
    
    // Mostra os resultados finais
    printf("Constantes escolhidas:\n");
    printf("  c1 = %.4f   (limite inferior)\n", c1);
    printf("  c2 = %.4f   (limite superior)\n", c2);
    printf("  n0 = %d    (primeiro n que satisfaz a desigualdade)\n", n0);
    
    // Conclusão teórica baseada nos dados
    printf("\nConclusao: T(n) = (n^2 - n)/2 esta em Theta(n^2)\n");
    printf("pois R(n) -> 0.5 conforme n cresce.\n");

    return 0;                         // Encerra o programa indicando sucesso
}
