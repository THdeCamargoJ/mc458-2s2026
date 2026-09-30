# Cadê meu Introsort?

Estamos no ano de 2040, e as coisas têm mudado muito por aqui. Já faz alguns anos que aquela tal singularidade foi atingida, trazendo, junto com aquela vitória para a ciência, um sentimento de derrota e vazio para toda a humanidade. Segura aí, que a coisa fica ainda pior. O último bastião que foi abatido pela IA foi provar, contra todo prognóstico, que $NP=P$, de modo que as grandes perguntas da computação teórica viraram quebra-cabeças de jornal, feitos apenas para o entretenimento dos humanos.

Abatidos pela saudade egocêntrica de fazer ciência, físicos, engenheiros, matemáticos e cientistas da computação do mundo todo se juntaram e conseguiram criar a ASIMOV, um portal para realidades alternativas. Essa máquina encontra e cria portais para linhas alternativas do passado, com o objetivo de permitir que os humanos possam voltar àquelas linhas do tempo e sentir novamente o que era fazer parte de novas descobertas científicas.

~~~txt
╔══════════════════════════════════════════════════════════════════════════════╗
║                  A S I M O V   T I M E   G A T E                             ║
║                         SYSTEM v1.990                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

 C:\ASSIMOV> initialize_portal.exe K-RALEE0

 [ OK ] Temporal coordinates locked
 [ OK ] Alternate timeline found
 [ OK ] David Musser .............................................. NOT FOUND
 [ !! ] INTROSORT ................................................. NOT FOUND
 [ !! ] TIMELINE INTEGRITY ........................................ 37%

 C:\ASSIMOV> deploy_scientist.exe

 Loading ███████████████████████████████████████████████████████████████ 100%

 C:\ASSIMOV> mission.exe

 ┌──────────────────────────────────────────────────────────────────────────┐
 │                                                                          │
 │   MISSION: RESTORE INTROSORT                                             │
 │                                                                          │
 │   [1] Recover INSERTION SORT                                             │
 │   [2] Recover HEAPSORT                                                   │
 │   [3] Recover QUICKSORT                                                  │
 │   [4] Recover MEDIAN-OF-THREE                                            │
 │   [5] SAVE TIMELINE                                                      │
 │                                                                          │
 └──────────────────────────────────────────────────────────────────────────┘

 C:\ASSIMOV> █
 ~~~

Você, que naquela época estava terminando seu doutorado em computação, foi enviado para os anos 90 na linha do tempo K-RALEE0, uma linha do tempo particularmente peculiar. Nessa linha do tempo, o cientista da computação David Musser morreu quando criança, o que significa que nunca chegou a criar o algoritmo Introsort, deixando consequências desastrosas nessa linha do tempo. Sua missão: voltar lá e implementar aquele algoritmo em C.

O problema é que, enquanto você voltava para aquela linha do tempo, o CD-ROM com o algoritmo implementado foi parcialmente danificado. A continuação do que restou do algoritmo:

~~~c
#include <stdio.h>
#include <stdlib.h>

// Função auxiliar para trocar dois elementos
void swap(int *a, int *b) {
    ??????? ????????();
        ������ 00 FF FF 3F 3F 3F
        FF FF FF FF FF FF FF FF
        ??????? ???????? ???????? 
}

// 1. INSERTION SORT (Usado para subarrays pequenos)
void insertionSort(int arr[], int left, int right) {
    ??????????
    ??????? ????????();
        ������ 00 FF FF 3F 3F 3F
        FF FF FF FF FF FF FF FF
        ??????? ???????? ???????? 
}

// 2. HEAPSORT E FUNÇÕES DE HEAP (Usado quando a recursão fica muito profunda)
void heapify(int arr[], int n, int i, int offset) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[offset + l] > arr[offset + largest])
        largest = l;
    if (r < n && arr[offset + r] > arr[offset + largest])
        largest = r;

    if (largest != i) {
        swap(&arr[offset + i], &arr[offset + largest]);
        heapify(arr, n, largest, offset);
    }
}

void heapSort(int arr[], int left, int right) {
    int n = right - left + 1;
    // Constrói o max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, left);
    // Extrai os elementos do heap um por um
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[left], &arr[left + i]);
        heapify(arr, i, 0, left);
    }
}

// 3. QUICKSORT PARTITION (Motor principal usando Mediana de Três)
void medianOfThreeSwap(int arr[], int a, int b, int c) {
    7A 91 FF 00 3F 3F 3F 8D 11 00
        3F 3F 3F 3F 3F 00 FF FF FF
        � � � � � � � � � � � �
}

int partition(int arr[], int left, int right) {
    ????????????????????????
    ?????????????
    ???? ?????? ?? ??????????
    ???????????
    ??????
        ???????
            ????????
    ???????????
    ???
    ??????????
}

// FUNÇÃO RECURSIVA DO INTROSORT
void introSortUtil(int arr[], int left, int right, int depthLimit) {
    int size = right - left + 1;

    // Condição 1: Subarray pequeno -> Insertion Sort
    if (size < 16) {
        insertionSort(arr, left, right);
        return;
    }

    // Condição 2: Profundidade limite atingida -> HeapSort
    if (depthLimit == 0) {
        heapSort(arr, left, right);
        return;
    }

    // Condição 3: Caso normal -> Quicksort
    �#�▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
    00 FF 3F FF 00 FF 3F 3F
    � � � � � � � � � � �
    introSortUtil(arr, left, ▒▒▒▒▒▒▒- 1);
    introSort� � � � � �  right, depthLimit - 1);
}

// FUNÇÃO PRINCIPAL DE CHAMADA
void introSort(int arr[], int n) {
    if (n < 2) return;

    // Calcula o limite de profundidade como 2 * log2(n)
    int depthLimit = 0;
    int temp = n;
    while (temp > 1) {
        depthLimit++;
        temp >>= 1;
    }
    depthLimit *= 2;

    introSortUtil(arr, 0, n - 1, depthLimit);
}

int* gerador(int seed, long long n) {
    int *arr = (int *)malloc(n * sizeof(int));

    // Inicializa a semente de aleatoriedade usando o relógio do sistema
    srand(seed);

    for (long long i = 0; i < n; i++) {
        // Combina duas chamadas de rand() para gerar números de até ~1 bilhão
        // Isso evita que números se repitam excessivamente em sistemas onde RAND_MAX é pequeno
        int numero_aleatorio = (rand() << 15) ^ rand();
        arr[i] = numero_aleatorio;
    }

    return arr;
}

// TESTE DO ALGORITMO
int main() {
    int seed;
    scanf("%d", &seed);
    long long n = 10000000;
    int *arr = gerador(seed, n);

    introSort(arr, n);

    printf("Soma de todos os elementos do array ordenado via Introsort, mod 1000000007: \n");
    int result = 0;
    for (int i = 0; i < n; i++) {
        result = (result + (arr[i] % 1000000007)) % 1000000007;  // Apenas para evitar overflow em casos de teste muito grandes
    }

    printf("%d ", result);
    printf("\n");

    free(arr);
    return 0;
}
~~~

Dessa forma, agora seu trabalho é corrigir aquele código para, assim, salvar aquela linha do tempo.

## Entrada

A entrada será um número inteiro $n$, usado como semente para o gerador de números aleatórios da função gerador.

## Saída

A saída será a soma de todos os elementos do array, gerado aleatoriamente com a semente de entrada, módulo $10^9 + 7$.

**Tempo de execução máximo por teste:** 2 s

**Data de entrega:** 06/10/2026

**Entregas atrasadas sem penalidade até:** 13/10/2026

## Importante
- O código tem que estar em linguagem C.
- Não olhem códigos de outros grupos ou da internet, exceto aqueles fornecidos.
- Os trabalhos poderão ser feitos individualmente ou em duplas. No caso de duplas, apenas um dos integrantes será responsável pelas submissões. O responsável deverá colocar, na primeira linha do código, o RA e o nome (exatamente conforme cadastrado na DAC).
- TODOS os membros do grupo devem participar e compreender completamente a implementação.
- Em caso de plágio, fraude ou tentativa de burlar o sistema, será atribuída nota 0 na disciplina aos envolvidos.
- Alguns alunos poderão ser solicitados a explicar, em detalhes, a implementação.
- Passar em todos os testes não é garantia de obter a nota máxima. A nota também dependerá do cumprimento das especificações do trabalho, da qualidade do código, da clareza dos comentários, das boas práticas de programação e do entendimento da matéria demonstrado em uma possível reunião.
- O responsável pela submissão deverá enviar, até a data de entrega, o código na plataforma runcodes.hokama.com.br.
- Seu código deverá executar dentro do tempo limite estabelecido para cada caso de teste.
- É esperado, e faz parte do aprendizado, que vocês tenham algumas dificuldades, como falhas de segmentação, loops infinitos, códigos sem a eficiência necessária etc. Portanto, não deixem para os últimos dias!
- Código de Honra: O uso de ferramentas de IA generativa não é recomendado. Caso o aluno opte por utilizá-las, compromete-se a tentar primeiro resolver o problema por conta própria, sem o auxílio de ferramentas de IA generativa, antes de recorrer a elas. Além disso, o aluno deve compreender completamente o código gerado ou sugerido pela IA e ser capaz de explicar sua implementação.