#include <stdio.h>
#include <string.h> // Para strcpy
#include <locale.h> // Para setlocale

// 1. Estrutura para representar uma carta do Super Trunfo
typedef struct {
    char estado[3];       // Ex: "SP", "RJ"
    char codigo[5];       // Ex: "C001"
    char nome_cidade[50]; // Ex: "São Paulo"
    int populacao;        // Ex: 12300000
    float area;           // Ex: 1521.11
    float pib;            // Ex: 763.8 (em bilhões, por exemplo)
    int pontos_turisticos; // Ex: 10

    // Atributos calculados
    float densidade_populacional;
    float pib_per_capita;
} Carta;

// Enum para representar os atributos numéricos para comparação
// Isso torna o código mais legível do que usar números ou strings diretamente.
typedef enum {
    ATRIBUTO_POPULACAO,
    ATRIBUTO_AREA,
    ATRIBUTO_PIB,
    ATRIBUTO_DENSIDADE_POPULACIONAL,
    ATRIBUTO_PIB_PER_CAPITA
} AtributoComparacao;

// 2. Função para calcular densidade populacional e PIB per capita
void calcularAtributosDerivados(Carta *carta) {
    if (carta->area > 0) {
        carta->densidade_populacional = (float)carta->populacao / carta->area;
    } else {
        carta->densidade_populacional = 0.0; // Evita divisão por zero
    }

    if (carta->populacao > 0) {
        carta->pib_per_capita = carta->pib / carta->populacao; // PIB em bilhões, População em unidades
    } else {
        carta->pib_per_capita = 0.0; // Evita divisão por zero
    }
}

int main() {
    // Configura a localização para exibir caracteres especiais corretamente
    setlocale(LC_ALL, "pt_BR.UTF-8");

    printf("--- Comparação de Cartas Super Trunfo ---\n\n");

    // 3. Definindo as duas cartas pré-definidas
    Carta carta1, carta2;

    // Dados da Carta 1
    strcpy(carta1.estado, "SP");
    strcpy(carta1.codigo, "C001");
    strcpy(carta1.nome_cidade, "Sao Paulo");
    carta1.populacao = 12300000; // Exemplo: 12.3 milhões
    carta1.area = 1521.11;       // km²
    carta1.pib = 763.8 * 1e9;     // Bilhões, convertido para unidades para o cálculo de PIB per capita
    carta1.pontos_turisticos = 10;

    // Calculando atributos derivados para Carta 1
    calcularAtributosDerivados(&carta1);

    // Dados da Carta 2
    strcpy(carta2.estado, "RJ");
    strcpy(carta2.codigo, "C002");
    strcpy(carta2.nome_cidade, "Rio de Janeiro");
    carta2.populacao = 6780000;   // Exemplo: 6.78 milhões
    carta2.area = 1200.0;         // km²
    carta2.pib = 370.0 * 1e9;      // Bilhões, convertido para unidades
    carta2.pontos_turisticos = 8;

    // Calculando atributos derivados para Carta 2
    calcularAtributosDerivados(&carta2);

    // 4. Escolha do atributo para comparação (definido no código)
    AtributoComparacao atributo_escolhido = ATRIBUTO_POPULACAO; // Mude aqui para testar outros atributos

    // Variáveis para armazenar os valores do atributo de cada carta e o nome do atributo
    float valor_carta1;
    float valor_carta2;
    char nome_atributo[50];
    int carta_vencedora = 0; // 0 = empate, 1 = carta1 vence, 2 = carta2 vence

    // 5. Lógica de comparação
    switch (atributo_escolhido) {
        case ATRIBUTO_POPULACAO:
            valor_carta1 = (float)carta1.populacao;
            valor_carta2 = (float)carta2.populacao;
            strcpy(nome_atributo, "População");
            // Para População, maior valor vence
            if (valor_carta1 > valor_carta2) {
                carta_vencedora = 1;
            } else if (valor_carta2 > valor_carta1) {
                carta_vencedora = 2;
            } else {
                carta_vencedora = 0; // Empate
            }
            break;

        case ATRIBUTO_AREA:
            valor_carta1 = carta1.area;
            valor_carta2 = carta2.area;
            strcpy(nome_atributo, "Área");
            // Para Área, maior valor vence
            if (valor_carta1 > valor_carta2) {
                carta_vencedora = 1;
            } else if (valor_carta2 > valor_carta1) {
                carta_vencedora = 2;
            } else {
                carta_vencedora = 0; // Empate
            }
            break;

        case ATRIBUTO_PIB:
            valor_carta1 = carta1.pib;
            valor_carta2 = carta2.pib;
            strcpy(nome_atributo, "PIB");
            // Para PIB, maior valor vence
            if (valor_carta1 > valor_carta2) {
                carta_vencedora = 1;
            } else if (valor_carta2 > valor_carta1) {
                carta_vencedora = 2;
            } else {
                carta_vencedora = 0; // Empate
            }
            break;

        case ATRIBUTO_DENSIDADE_POPULACIONAL:
            valor_carta1 = carta1.densidade_populacional;
            valor_carta2 = carta2.densidade_populacional;
            strcpy(nome_atributo, "Densidade Populacional");
            // Para Densidade Populacional, MENOR valor vence
            if (valor_carta1 < valor_carta2) { // Atenção: < para densidade
                carta_vencedora = 1;
            } else if (valor_carta2 < valor_carta1) { // Atenção: < para densidade
                carta_vencedora = 2;
            } else {
                carta_vencedora = 0; // Empate
            }
            break;

        case ATRIBUTO_PIB_PER_CAPITA:
            valor_carta1 = carta1.pib_per_capita;
            valor_carta2 = carta2.pib_per_capita;
            strcpy(nome_atributo, "PIB per capita");
            // Para PIB per capita, maior valor vence
            if (valor_carta1 > valor_carta2) {
                carta_vencedora = 1;
            } else if (valor_carta2 > valor_carta1) {
                carta_vencedora = 2;
            } else {
                carta_vencedora = 0; // Empate
            }
            break;

        default:
            printf("Erro: Atributo de comparação não reconhecido.\n");
            return 1; // Sai do programa com erro
    }

    // 6. Exibir o resultado da comparação
    printf("Comparação de cartas (Atributo: %s):\n\n", nome_atributo);

    // Formatação especial para População e PIB (para mostrar em milhões/bilhões, se desejar)
    // Para simplificar a exibição, vou mostrar o valor numérico bruto ou formatado, dependendo do atributo.
    if (atributo_escolhido == ATRIBUTO_POPULACAO) {
        printf("Carta 1 - %s (%s): %'d habitantes\n", carta1.nome_cidade, carta1.estado, carta1.populacao);
        printf("Carta 2 - %s (%s): %'d habitantes\n", carta2.nome_cidade, carta2.estado, carta2.populacao);
    } else if (atributo_escolhido == ATRIBUTO_PIB) {
        // Exibir PIB em bilhões para melhor leitura
        printf("Carta 1 - %s (%s): R$ %.2f bilhões\n", carta1.nome_cidade, carta1.estado, carta1.pib / 1e9);
        printf("Carta 2 - %s (%s): R$ %.2f bilhões\n", carta2.nome_cidade, carta2.estado, carta2.pib / 1e9);
    } else if (atributo_escolhido == ATRIBUTO_AREA) {
        printf("Carta 1 - %s (%s): %.2f km²\n", carta1.nome_cidade, carta1.estado, carta1.area);
        printf("Carta 2 - %s (%s): %.2f km²\n", carta2.nome_cidade, carta2.estado, carta2.area);
    } else if (atributo_escolhido == ATRIBUTO_DENSIDADE_POPULACIONAL) {
         printf("Carta 1 - %s (%s): %.2f hab/km²\n", carta1.nome_cidade, carta1.estado, carta1.densidade_populacional);
         printf("Carta 2 - %s (%s): %.2f hab/km²\n", carta2.nome_cidade, carta2.estado, carta2.densidade_populacional);
    } else if (atributo_escolhido == ATRIBUTO_PIB_PER_CAPITA) {
         printf("Carta 1 - %s (%s): R$ %.2f per capita\n", carta1.nome_cidade, carta1.estado, carta1.pib_per_capita);
         printf("Carta 2 - %s (%s): R$ %.2f per capita\n", carta2.nome_cidade, carta2.estado, carta2.pib_per_capita);
    }


    printf("\nResultado: ");
    if (carta_vencedora == 1) {
        printf("Carta 1 (%s) venceu!\n", carta1.nome_cidade);
    } else if (carta_vencedora == 2) {
        printf("Carta 2 (%s) venceu!\n", carta2.nome_cidade);
    } else {
        printf("Empate!\n");
    }

    return 0;
}
