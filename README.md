# Validador Numérico das Constantes Assintóticas

# Projeto 15: Validador Numérico das Constantes Assintóticas (c e n₀)

## Objetivo do Projeto
Aplicar experimentalmente a definição matemática formal da **Notação Θ (Teta)**, vista na Aula 4. O programa executa um algoritmo quadrático e prova, na prática, que o número de operações cresce na mesma proporção que \(n^2\), encontrando numericamente as constantes \(c_1\), \(c_2\) e o ponto de estabilização \(n_0\).

---

## Fundamentação Teórica

### A Definição Formal de Θ
Uma função \(T(n)\) pertence a \(\Theta(n^2)\) se existem constantes positivas **\(c_1\), \(c_2\)** e um inteiro **\(n_0\)** tais que:

\[
0 \le c_1 \cdot n^2 \le T(n) \le c_2 \cdot n^2, \quad \forall n \ge n_0
\]

Em palavras simples: a partir de um ponto \(n_0\), o trabalho real do algoritmo (\(T(n)\)) fica **espremido** entre um piso (\(c_1 n^2\)) e um teto (\(c_2 n^2\)).

### O Algoritmo Escolhido: Selection Sort
O **Selection Sort** foi escolhido porque seu número de comparações é **exato** e previsível, independentemente da entrada. A fórmula é:
\[
T(n) = \frac{n(n-1)}{2} = \frac{n^2 - n}{2}
\]

### A Razão de Convergência R(n)
Dividindo o trabalho real pelo quadrado do tamanho, obtemos a razão:
\[
R(n) = \frac{T(n)}{n^2} = \frac{1}{2} \cdot \left(1 - \frac{1}{n}\right)
\]
À medida que \(n\) cresce, \(R(n)\) converge para **0,5**. É essa estabilização que nos permite escolher as constantes do "túnel".

---

## A Lógica do Código

O código em C implementa a definição matemática da seguinte forma:

1. **Mede o mundo real (\(T(n)\)):** Executa o Selection Sort para \(n = 10, 50, 100, 500, 1000, 2000\) e conta as comparações.
2. **Constrói o túnel (\(c_1 n^2\) e \(c_2 n^2\)):** Adota \(c_1 = 0,25\) (piso) e \(c_2 = 0,50\) (teto).
3. **Verifica a desigualdade:** Para cada \(n\), checa se \(c_1 n^2 \le T(n) \le c_2 n^2\).
4. **Descobre o \(n_0\):** O programa guarda o **primeiro** \(n\) em que a regra é satisfeita.

**Resultado Esperado:**
O programa encontra **\(n_0 = 10\)**, pois em \(n=10\), \(R(10) = 0,45\), que já está entre 0,25 e 0,50. Como a razão só cresce (tendendo a 0,5), todos os \(n\) seguintes também satisfazem a regra, provando que \(T(n) \in \Theta(n^2)\).

---

## Entendendo a Tabela de Saída

A tabela gerada pelo programa é a **prova visual** da Notação Θ. Cada coluna representa um pedaço da definição formal:

| Coluna | Significado | Exemplo (para n = 100) |
| :--- | :--- | :--- |
| **`n`** | O tamanho da entrada (tamanho do problema). | 100 |
| **`T(n)`** | O **Trabalho Real**. O número exato de comparações que o algoritmo fez. | 4.950 |
| **`n²`** | A régua base quadrática (\(n \times n\)). | 10.000 |
| **`R(n)`** | A **Razão** (\(T(n) / n^2\)). Mostra a taxa de esforço. Se ela se estabiliza em um número (0,5), prova que o algoritmo é quadrático. | 0,4950 |
| **`c₁n²`** | O **Limite Inferior** (Piso do túnel). O trabalho real nunca pode ser menor que isso. | 2.500 (0,25 × 10.000) |
| **`c₂n²`** | O **Limite Superior** (Teto do túnel). O trabalho real nunca pode ser maior que isso. | 5.000 (0,50 × 10.000) |
| **`Θ?`** | O **Veredito**. Testa a desigualdade: `c₁n² ≤ T(n) ≤ c₂n²`. Se verdadeiro, imprime `[OK]`. | `[OK]` (pois 2.500 ≤ 4.950 ≤ 5.000) |

---

## Tabela de Resultados (Saída do Programa)

| n | T(n) | n² | R(n)=T(n)/n² | c₁n²=0,25n² | c₂n²=0,50n² | Θ? |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 10 | 45 | 100 | 0,450000 | 25,00 | 50,00 | ✅ OK |
| 50 | 1.225 | 2.500 | 0,490000 | 625,00 | 1.250,00 | ✅ OK |
| 100 | 4.950 | 10.000 | 0,495000 | 2.500,00 | 5.000,00 | ✅ OK |
| 500 | 124.750 | 250.000 | 0,499000 | 62.500,00 | 125.000,00 | ✅ OK |
| 1000 | 499.500 | 1.000.000 | 0,499500 | 250.000,00 | 500.000,00 | ✅ OK |
| 2000 | 1.999.000 | 4.000.000 | 0,499750 | 1.000.000,00 | 2.000.000,00 | ✅ OK |

**Conclusão do Experimento:** 
Observa-se que \(R(n)\) cresce de \(0,45\) até \(0,49975\) (aproximando-se de \(0,5\)). A coluna de veredito `[OK]` prova que a desigualdade \(0,25n^2 \le T(n) \le 0,50n^2\) é **verdadeira para todo \(n \ge 10\)**. Portanto, **\(n_0 = 10\)**, confirmando matematicamente que o algoritmo pertence a **\(\Theta(n^2)\)**.

---

## Como Compilar e Executar

1. Salve o código em um arquivo chamado `validador.c`.
2. Abra o terminal e compile com o GCC:
   ```bash
   gcc validador.c -o validador
   ```
3. Execute o programa:
   ```bash
   ./validador
   ```

---

## Observações Finais sobre as Constantes

*   **\(c_2 = 0,50\):** Como o \(R(n)\) nunca chega a 0,5 (ele apenas se aproxima), a desigualdade \(T(n) \le 0,5n^2\) é **sempre verdadeira**.
*   **\(c_1 = 0,25\):** Foi escolhido com "folga". A regra para o piso é \(c_1 \le R(n_0)\). Como \(R(10) = 0,45\), qualquer valor de \(c_1\) até 0,45 funcionaria. O valor 0,25 é seguro e didático.
*   **\(n_0 = 10\):** É o primeiro tamanho testado onde a desigualdade se sustenta. Se escolhêssemos um \(c_1\) maior (ex: 0,49), precisaríamos de um \(n_0\) maior (ex: \(n_0 = 100\)). As constantes e o \(n_0\) estão matematicamente interligados.
