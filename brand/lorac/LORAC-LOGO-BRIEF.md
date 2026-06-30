# LORAC — Brief de criação do logo (spec de execução)

> **Status:** logo ainda **não definido**. Este arquivo trava todas as decisões para que a
> geração possa ser executada sem novas perguntas ao cliente. Se algo aqui conflitar com um
> pedido novo do cliente, o pedido novo vence.

## Marca
- **Nome:** LORAC
- **Assinatura/tagline:** Consultoria e Assessoria Jurídica de Trânsito
- **Segmento:** assessoria jurídica especializada em **trânsito** (defesa, recursos, infrações).
- **Percepção desejada:** séria, confiável, moderna, especializada, premium. NÃO parecer
  despachante, autoescola, seguradora, nem escritório tradicional clichê.

## Direção estética (TRAVADA)
- Elegante / minimalista / premium. Muito espaço negativo.
- Geometria **100% angular**: cantos retos, **pontas e terminais quadrados**, junções em
  esquadria (miter). **NADA arredondado, sem curvas.** — este é um pedido explícito do cliente.
- Símbolo **forte e contido** (emblema/monograma fechado), no **espírito da referência G&O**
  (ver `reference/`), mas com a identidade e o conceito da LORAC.

## Conceito do símbolo (TRAVADO)
Síntese visual (não ilustração) unindo universo jurídico + trânsito. 4 pilares:
**direção · fluxo · proteção · estrutura.**
- "L" integrado como **vetor/chevron de direção** (aponta avanço/rumo).
- Linhas/formas angulares que **envolvem e ancoram** (proteção + estrutura sólida).
- Pode dialogar com a inicial "L" de forma sofisticada e não óbvia.
- **PROIBIDO** (clichês a evitar): balança da justiça, martelo, coluna grega, escudo genérico,
  carro, volante, estrada literal, placa de trânsito, brasão antiquado.

## Cores (TRAVADAS)
- Primária (base): **Grafite/quase-preto `#1A1A1A`**
- Secundária (profundidade): **Cinza `#4A4A4A`**
- Acento: **Amarelo `#F2B705`** — usar **só como acento** no vetor de direção / ponto focal.
  Nunca dominante, nunca "cara de placa de trânsito".
- Neutro: **Branco `#FFFFFF`**

## Tipografia (TRAVADA)
- **Wordmark "LORAC":** serifada display elegante de alto contraste (vibe Playfair Display /
  DM Serif Display / a "Florilst Realik" da referência). Caixa alta, espaçamento generoso,
  forte presença institucional. Cor `#1A1A1A`.
- **Tagline:** sans geométrica (Montserrat), caixa alta, tracking amplo, peso leve, discreta,
  bem hierarquizada abaixo do nome. Cor `#4A4A4A`.

## Entregáveis do kit (quando o símbolo for aprovado)
1. Lockup **vertical** (símbolo acima do nome) — principal
2. Lockup **horizontal** (símbolo à esquerda do nome)
3. **Símbolo isolado**
4. **Selo circular** (símbolo + texto ao redor)
5. **Monocromático**: tudo preto / tudo branco (reverso)
6. Versões em **fundo claro** e **fundo escuro**

## Como gerar (ferramenta + parâmetros — TRAVADO)
- Ferramenta: **Higgsfield** → modelo **`recraft_v4_1`**, **`model_type: "vector"`** (saída SVG editável).
- `aspect_ratio: "1:1"`, `count: 4`, `resolution: "2k"`,
  `colors: ["#1A1A1A", "#4A4A4A", "#F2B705"]`, `background_color: "#FFFFFF"`.
- **PULO DO GATO (o que faltou antes):** alimentar a **imagem da referência** como referência
  visual de estilo/forma (image/style reference), não só descrever em texto.
  - Cheque `models_explore` para o papel (`role`) de mídia aceito pelo recraft vector; se vector
    não aceitar imagem de referência, use um modelo que aceite para gerar o conceito do símbolo
    e depois vetorize, OU use a referência via `nano_banana_pro`/equivalente e refine.
  - Imagem de referência sugerida: `reference/ref-symbol-construction.png` (símbolo isolado) e
    `reference/ref-lockups.png` (lockups).

## Histórico (para não repetir erros)
- Canva (`generate-design`): saiu **genérico**, rejeitado.
- Higgsfield Recraft vector **só com texto**: rejeitado (genérico/sem graça).
- SVG **codificado à mão**: rejeitado (rudimentar, longe do esperado). **Não repetir.**
- Conclusão: o caminho é **Recraft vector + imagem de referência visual** + iteração.

## Arquivos de referência (pasta `reference/`)
- `ref-symbol-construction.png` — símbolo G&O isolado (grade de construção). Melhor para passar a FORMA.
- `ref-symbol-elements.png` — decomposição do símbolo G&O em elementos.
- `ref-lockups.png` — lockups horizontais (fundo claro/escuro).
- `ref-symbol-typography.png` — símbolo + tipografia da referência.
- `concept-sketch-geometry.svg/.png` — **APENAS** esboço grosseiro da ideia geométrica
  (L-vetor + emblema contido + acento amarelo). **Baixa fidelidade — NÃO é o alvo de qualidade.**

## Crédito disponível
- Conta Higgsfield: plano Creator, ~6.000 créditos no início do projeto.
