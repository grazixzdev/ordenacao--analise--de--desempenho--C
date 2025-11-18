#include <stdio.h>
#include <stdbool.h> 
#include <stdlib.h>
#include <time.h>
#include <string.h> // Necessário para strlen se precisar

// Macros para facilitar a leitura e contagem.
// Uso steps++ para incrementar meu contador global a cada comparação ou troca relevante.
#define COUNT_CMP()   (steps++)
#define COUNT_SWAP()  (steps++)

// Variável global para acumular os passos (comparações + trocas)
unsigned long long steps = 0;

// Função ajustada para saída em formato CSV como pedido no enunciado:
// metodo,N,caso,passos,tempo_ms
void relatar_csv(char metodo[], int n, char caso[], unsigned long long passos, double tempo_ms) {
    // Imprimo nesse formato para facilitar a criação da tabela no README depois
    printf("%s,%d,%s,%llu,%.4f\n", metodo, n, caso, passos, tempo_ms);
}

void printArray(int arr[], int n) {
    // Função auxiliar apenas para conferência visual se o array for pequeno
    if (n > 20) { 
        printf("[Array grande demais para exibir...]\n"); 
        return; 
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// --- 1. BUBBLE SORT ---
// Escolhi este método pela simplicidade de implementação, apesar de ser O(n^2).
void bubbleSort(int arr[], int n) {
    int i, j;
    
    // O loop externo garante que passaremos por todo o vetor
    for (i = 0; i < n - 1; i++) {
        
        // O loop interno empurra o maior valor para o final (fundo do poço)
        // A cada iteração 'i', os últimos elementos já estão garantidos como ordenados
        for (j = 0; j < n - i - 1; j++) {
            COUNT_CMP(); // Conto a comparação do if abaixo
            
            if (arr[j] > arr[j + 1]) {
                // Realizo a troca (swap) manual
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                COUNT_SWAP(); // Conto a movimentação de dados
            }
        }
    }
}

// --- 2. INSERTION SORT ---
// Escolhi este método pois ele é eficiente para conjuntos pequenos ou quase ordenados.
void insertionSort(int arr[], int n) {
    int i, key, j;
    
    // Começo do segundo elemento (índice 1), assumindo que o índice 0 já "é" uma lista ordenada
    for (i = 1; i < n; i++) {
        key = arr[i]; // Pego o elemento atual para inserir na posição correta
        j = i - 1;
        
        COUNT_SWAP(); // Conto a cópia para 'key' como uma movimentação
        
        // Movo os elementos maiores que a 'key' para a direita para abrir espaço
        // Verifico j >= 0 antes para evitar acesso inválido à memória
        // OBS: A comparação do while conta a cada iteração
        while (j >= 0) {
            COUNT_CMP(); // Conto a comparação arr[j] > key
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                j = j - 1;
                COUNT_SWAP(); // Conto o deslocamento
            } else {
                break; // Se não é maior, achei a posição
            }
        }
        
        // Insiro a key na posição correta (j+1)
        arr[j + 1] = key;
        COUNT_SWAP(); // Conto a inserção final
    }
}

// --- 3. HEAP SORT ---
// Escolhi o Heap Sort pela sua estabilidade de desempenho O(n log n) e por não usar memória extra.

// Função auxiliar para garantir a propriedade de Heap (Max-Heap) em um sub-nó
void heapify(int arr[], int n, int i) {
    int maior = i;           // Assumo inicialmente que a raiz é o maior
    int esquerdo = 2 * i + 1; 
    int direito = 2 * i + 2; 
    
    // Verifico se o filho esquerdo existe e é maior que a raiz
    if (esquerdo < n) {
        COUNT_CMP();
        if (arr[esquerdo] > arr[maior]) {
            maior = esquerdo;
        }
    }
    
    // Verifico se o filho direito existe e é maior que o atual "maior"
    if (direito < n) {
        COUNT_CMP();
        if (arr[direito] > arr[maior]) {
            maior = direito;
        }
    }
    
    // Se o maior não for a raiz original, preciso trocar e recursivar
    if (maior != i) {
        int temp = arr[i];
        arr[i] = arr[maior];
        arr[maior] = temp;
        COUNT_SWAP(); // Conto a troca física
        
        // Ajusto recursivamente a subárvore afetada
        heapify(arr, n, maior);
    }
}

void heapSort(int arr[], int n) {
    // Passo 1: Construir o Heap (reorganizar o array)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    
    // Passo 2: Extrair um elemento por vez do heap
    for (int i = n - 1; i > 0; i--) {
        // Movo a raiz atual (o maior) para o final
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        COUNT_SWAP(); // Conto a troca
        
        // Chamo heapify na heap reduzida para restaurar a ordem
        heapify(arr, i, 0);
    }
}

// Função para gerenciar a execução e medição
void executar_teste(char *nome_metodo, void (*func_sort)(int[], int)) {
    clock_t t0, t1;
    double tempo_ms;
    int n;
    int *arr = NULL;
    char caso_str[20]; // Para guardar "rgm" ou "aleatorio"
    
    printf("\n--- Configuração do Teste para %s ---\n", nome_metodo);
    printf("1 - Usar meu RGM\n2 - Gerar Aleatório\nEscolha: ");
    int opcao;
    scanf("%d", &opcao);
    
    if (opcao == 1) {
        // Configuração para RGM
        char rgmString[20]; // Buffer com espaço seguro
        printf("Digite os dígitos do RGM: ");
        scanf("%s", rgmString);
        
        n = strlen(rgmString);
        arr = (int*) malloc(n * sizeof(int));
        strcpy(caso_str, "rgm");
        
        // Converto char para int
        for (int i = 0; i < n; i++) {
            arr[i] = rgmString[i] - '0';
        }
        
    } else if (opcao == 2) {
        // Configuração para Aleatório
        strcpy(caso_str, "aleatorio");
        printf("Digite o tamanho N (ex: 100, 1000, 10000): ");
        scanf("%d", &n);
        
        arr = (int*) malloc(n * sizeof(int));
        // Preencho com números aleatórios
        for(int i=0; i<n; i++) {
            arr[i] = rand() % 10000; // 0 a 9999
        }
    } else {
        printf("Opção inválida!\n");
        return;
    }
    
    // Exibo antes (se for pequeno)
    if (n <= 20) { printf("Entrada: "); printArray(arr, n); }
    
    // --- MEDIÇÃO ---
    steps = 0; // Reseto o contador global antes de começar
    t0 = clock();
    func_sort(arr, n); // Executo a função passada por parâmetro
    t1 = clock();
    // ---------------
    
    tempo_ms = 1000.0 * (t1 - t0) / CLOCKS_PER_SEC;
    
    // Exibo depois (se for pequeno)
    if (n <= 20) { printf("Saída:   "); printArray(arr, n); }
    
    // SAÍDA CSV OFICIAL
    printf("\nCopie a linha abaixo para seu relatório:\n");
    printf("metodo,N,caso,passos,tempo_ms\n"); // Cabeçalho opcional
    relatar_csv(nome_metodo, n, caso_str, steps, tempo_ms);
    
    // Libero a memória alocada
    free(arr);
}

void menu(){
   int num = -1;
   srand(time(NULL)); // Semente para aleatórios
   
   while (num != 0) {
        printf("\n================================\n"
               " MENU DE ORDENAÇÃO\n"
               "================================\n"
               " 1 - Bubble Sort\n"
               " 2 - Insertion Sort\n"
               " 3 - Heap Sort\n"
               " 0 - Sair\n"
               " Escolha: ");
        scanf("%d", &num);
        
        switch (num) {
            case 1:
                executar_teste("bubble", bubbleSort);
                break;
            case 2:
                executar_teste("insertion", insertionSort);
                break;
            case 3:
                executar_teste("heap", heapSort);
                break;
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opção Inválida!\n");
                break;
        }
   }
}

int main() {
   menu();
   return 0;
}
