# Projeto 15: Validador Numérico das Constantes Assintóticas (c e n₀)

## Objetivo do Projeto

Aplicar experimentalmente a definição matemática formal da **Notação Θ (Teta)**, vista na Aula 4. O programa executa um algoritmo quadrático e demonstra, na prática, que o número de operações cresce na mesma proporção que n², encontrando numericamente as constantes c₁, c₂ e o ponto de estabilização n₀.

---

## Fundamentação Teórica

### A Definição Formal de Θ

Uma função T(n) pertence a **Θ(n²)** se existem constantes positivas c₁, c₂ e um inteiro n₀ tais que:

**0 ≤ c₁ · n² ≤ T(n) ≤ c₂ · n², para todo n ≥ n₀**

Em palavras simples: a partir de um ponto n₀, o trabalho real do algoritmo, T(n), fica **espremido** entre um piso (c₁ · n²) e um teto (c₂ · n²).

### O Algoritmo Escolhido: Selection Sort

O **Selection Sort** foi escolhido porque seu número de comparações é **exato** e previsível, independentemente da ordem inicial dos elementos da entrada. A fórmula é:

**T(n) = n(n − 1) / 2 = (n² − n) / 2**

### A Razão de Convergência R(n)

Dividindo o trabalho real pelo quadrado do tamanho da entrada, obtemos a razão:

**R(n) = T(n) / n² = ½ · (1 − 1/n)**

À medida que n cresce, R(n) converge para **0,5**. É essa estabilização que nos permite escolher as constantes do intervalo entre o limite inferior e o superior.

---

## A Lógica do Código

O código em C implementa a definição matemática da seguinte forma:

1. **Mede o trabalho real (T(n)):** executa o Selection Sort para n = 10, 50, 100, 500, 1000 e 2000 e conta as comparações.
2. **Constrói o intervalo (c₁ · n² e c₂ · n²):** adota c₁ = 0,25 como limite inferior e c₂ = 0,50 como limite superior.
3. **Verifica a desigualdade:** para cada valor de n, verifica se a condição é satisfeita:

   **c₁ · n² ≤ T(n) ≤ c₂ · n²**

4. **Determina o n₀:** identifica o primeiro valor de n a partir do qual a desigualdade permanece válida para todos os valores seguintes.

### Resultado Esperado

O programa encontra **n₀ = 10**, pois, para n = 10:

**R(10) = T(10) / 10² = 45 / 100 = 0,45**

Esse valor está entre os limites escolhidos:

**0,25 ≤ 0,45 ≤ 0,50**

Como a razão R(n) cresce e se aproxima de 0,5 por valores inferiores, a desigualdade permanece válida para todo n ≥ 10. Portanto:

**T(n) ∈ Θ(n²)**

---

## Entendendo a Tabela de Saída

A tabela gerada pelo programa é a **representação visual** da Notação Θ. Cada coluna representa um elemento da definição formal.

| Coluna | Significado | Exemplo para n = 100 |
|:---|:---|---:|
| **n** | Tamanho da entrada, ou seja, o tamanho do problema. | 100 |
| **T(n)** | **Trabalho real:** número exato de comparações realizadas pelo algoritmo. | 4.950 |
| **n²** | Referência quadrática, calculada por n × n. | 10.000 |
| **R(n)** | **Razão:** trabalho real dividido por n². | 0,4950 |
| **c₁n²** | **Limite inferior:** piso do intervalo. | 2.500 (0,25 × 10.000) |
| **c₂n²** | **Limite superior:** teto do intervalo. | 5.000 (0,50 × 10.000) |
| **Θ?** | Verifica se c₁n² ≤ T(n) ≤ c₂n². Se verdadeiro, imprime `[OK]`. | `[OK]` |

---

## Tabela de Resultados (Saída do Programa)

| n | T(n) | n² | R(n) = T(n)/n² | c₁n² = 0,25n² | c₂n² = 0,50n² | Θ? |
|---:|---:|---:|---:|---:|---:|:---:|
| 10 | 45 | 100 | 0,450000 | 25,00 | 50,00 | OK |
| 50 | 1.225 | 2.500 | 0,490000 | 625,00 | 1.250,00 | OK |
| 100 | 4.950 | 10.000 | 0,495000 | 2.500,00 | 5.000,00 | OK |
| 500 | 124.750 | 250.000 | 0,499000 | 62.500,00 | 125.000,00 | OK |
| 1000 | 499.500 | 1.000.000 | 0,499500 | 250.000,00 | 500.000,00 | OK |
| 2000 | 1.999.000 | 4.000.000 | 0,499750 | 1.000.000,00 | 2.000.000,00 | OK |

---

## Conclusão do Experimento

Observa-se que R(n) cresce de 0,45 até 0,49975, aproximando-se de 0,5 à medida que o tamanho da entrada aumenta.

A coluna de veredito `[OK]` demonstra que a desigualdade é satisfeita para todos os valores avaliados:

**0,25n² ≤ T(n) ≤ 0,50n²**

A fórmula matemática também comprova que essa desigualdade é verdadeira para todo n ≥ 10. Portanto, as constantes escolhidas são:

- **c₁ = 0,25** — limite inferior;
- **c₂ = 0,50** — limite superior;
- **n₀ = 10** — ponto a partir do qual a desigualdade é válida.

Conclui-se matematicamente que o algoritmo Selection Sort pertence à classe de complexidade quadrática:

**T(n) ∈ Θ(n²)**

O experimento demonstra, na prática, como as constantes assintóticas permitem validar a taxa de crescimento do número de operações de um algoritmo.

---

*Projeto — Análise e Complexidade de Algoritmos | Linguagem C*
