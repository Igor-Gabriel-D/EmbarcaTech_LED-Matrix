# EmbarcaTech_LED-Matrix
Adição de novas funções ao arquivo neopixel.c do repositório BitDogLab-C, visando tornar a manipulação da matriz de LEDs da placa mais intuitiva .


# Funções para Manipulação de Matriz de LEDs

Este documento explica o funcionamento das funções implementadas para controlar uma matriz de LEDs 5x5, utilizando coordenadas lógicas e físicas. Abaixo, cada função é descrita detalhadamente.

---

## Definições

```c
#define ROWS 5
#define COLS 5
```

As constantes `ROWS` e `COLS` definem as dimensões da matriz de LEDs (5 linhas por 5 colunas).

---

## `cords_to_idx`

**Protótipo:**
```c
uint cords_to_idx(uint x, uint y);
```

### Descrição
Esta função converte coordenadas lógicas \( (x, y) \) exibidas na canto inferior e na lateral da blaca em um índice linear da matriz. A matriz é tratada como um array unidimensional.

### Cálculo do Índice
\[ i = (\text{ROWS} \times y) + x \]

### Exemplo
Para \( x = 2 \), \( y = 1 \):
\[ i = (5 \times 1) + 2 = 7 \]

---

## `idx_to_zigzag`

**Protótipo:**
```c
uint idx_to_zigzag(int i);
```

### Descrição
Converte um índice linear para refletir o layout "zigzag" da matriz de LEDs. Em linhas ímpares, os LEDs são invertidos.

### Funcionamento
- Calcula a linha correspondente: \( \text{row} = (i / 5) + 1 \).
- Para linhas ímpares, inverte a posição horizontal:
\[ j = (i / 5) \times 5 + (4 - (i \% 5)) \]

### Exemplo
Para \( i = 6 \):
- Linha \( \text{row} = 2 \), sem inversão: \( j = 6 \).
Para \( i = 7 \):
- Linha \( \text{row} = 2 \), inversão: \( j = 7 \).

---

## `npSetLED_coord`

**Protótipo:**
```c
void npSetLED_coord(int x, int y, uint R, uint G, uint B);
```

### Descrição
Define a cor de um LED em coordenadas lógicas \( (x, y) \) usando valores de vermelho (R), verde (G) e azul (B).

### Funcionamento
1. Converte \( (x, y) \) em índice lógico usando `cords_to_idx`.
2. Converte índice lógico em físico usando `idx_to_zigzag`.
3. Atualiza as cores do LED correspondente:
   ```c
   leds[physical_position].R = R;
   leds[physical_position].G = G;
   leds[physical_position].B = B;
   ```

---

## `draw_line`

**Protótipo:**
```c
void draw_line(int x1, int y1, int x2, int y2, uint r, uint g, uint b);
```

### Descrição
Desenha uma linha de LEDs entre os pontos \( (x_1, y_1) \) e \( (x_2, y_2) \) usando o algoritmo de Bresenham.

### Funcionamento
1. Calcula as diferenças \( dx \) e \( dy \).
2. Determina os passos \( sx \) e \( sy \) com base nos sinais de \( dx \) e \( dy \).
3. Ajusta \( x \) e \( y \) em cada iteração para traçar a linha.
4. Define a cor do LED na posição atual usando `npSetLED_coord`.

---

## `draw_square`

**Protótipo:**
```c
void draw_square(int x1, int y1, int x2, int y2, uint r, uint g, uint b);
```

### Descrição
Preenche um retângulo (ou quadrado) delimitado pelos vértices \( (x_1, y_1) \) e \( (x_2, y_2) \) com a cor especificada.

### Funcionamento
1. Garante que \( x_1 \leq x_2 \) e \( y_1 \leq y_2 \) ajustando os valores, se necessário.
2. Percorre todas as coordenadas no intervalo \( [x_1, x_2] \) e \( [y_1, y_2] \).
3. Define a cor de cada LED usando `npSetLED_coord`.

---

Essas funções juntas formam uma base poderosa para manipular uma matriz de LEDs, permitindo criar padrões e efeitos visuais complexos de forma intuitiva.
