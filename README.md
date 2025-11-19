# Atividade A2: Ordenação e Análise de Desempenho em C

---

## 1. Contextualização

Este projeto visa analisar o comportamento prático de diferentes algoritmos de ordenação. A atividade consiste na implementação de três métodos distintos em linguagem C pura, aplicados à ordenação dos dígitos do RGM (Registro Geral de Matrícula) do aluno e a vetores aleatórios de diferentes tamanhos (benchmark).

O objetivo central é comparar a **complexidade teórica** (Big-O) com o **desempenho prático** medido em tempo de CPU e número de passos (operações fundamentais).

---

## 2. Métodos Escolhidos

Para esta análise, foram implementados os seguintes algoritmos:

1.  **Bubble Sort:**
    * *Motivação:* Algoritmo clássico de ensino. Escolhido para servir de "linha de base" (pior caso), demonstrando a ineficiência de soluções $O(n^2)$ em grandes volumes de dados.
2.  **Insertion Sort:**
    * *Motivação:* Embora também seja $O(n^2)$ no caso médio/pior, tende a ser mais rápido que o Bubble Sort na prática e é muito eficiente para vetores pequenos ou quase ordenados. É um algoritmo estável.
3.  **Heap Sort:**
    * *Motivação:* Representante dos algoritmos eficientes de complexidade $O(n \log n)$. Escolhido por sua consistência (não decai para quadrático como o QuickSort) e por ser *in-place* (não requer memória extra como o MergeSort).

---

## 3. Metodologia de Medição

### Contagem de Passos
Foi utilizado um contador global (`unsigned long long steps`) incrementado via macros. A política adotada foi:
* **1 passo** para cada **comparação** de chaves (ex: `if (v[i] > v[j])`).
* **1 passo** para cada **movimentação/troca** de valores (ex: `swap()` ou atribuições de deslocamento).

### Medição de Tempo
Utilizou-se a função `clock()` da biblioteca `<time.h>`.
* O tempo é capturado antes e depois da função de ordenação.
* O cálculo final é: `(t1 - t0) * 1000.0 / CLOCKS_PER_SEC` para obter o resultado em milissegundos (ms).
* Os testes foram executados 5 vezes para cada cenário e a média foi reportada.

---

## 4. Como Compilar e Rodar

### Pré-requisitos
* Compilador GCC instalado.
* Ambiente Linux, Windows (MinGW) ou macOS.

### Compilação
No terminal, navegue até a pasta raiz do projeto e execute:

```bash
gcc main.c -o ordena
