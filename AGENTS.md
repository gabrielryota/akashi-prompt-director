# Diretrizes do Agente — AKASHI Prompt Director V2

Este documento é a única fonte de verdade para a evolução, refatoração e manutenção do aplicativo AKASHI. A IA deve ler, compreender e respeitar rigorosamente todas as regras técnicas, restrições de arquitetura e a filosofia de design descritas aqui.

---

## 1. Visão Geral do Aplicativo
O AKASHI é um direcionador e roteador avançado de prompts artísticos para ferramentas de IA generativa (imagem e vídeo), operando como um arquivo único estático (Single Page Application)[cite: 1, 2]. O propósito central do app é encapsular a metodologia de "Direção de Fotografia" (óptica, iluminação, textura, física realista) e automatizar o envio direto dos parâmetros estruturados para APIs parceiras[cite: 1, 2].

## 2. Pilha Tecnológica & Arquitetura
* **Abordagem:** Arquivo único (`index.html`) contendo toda a estrutura DOM, estilização CSS e lógica JavaScript corporativa[cite: 1, 2].
* **Segurança:** Bloqueio inicial por Password Gate criptografado em Base64 em memória volátil (`sessionStorage`)[cite: 1].
* **Persistência de Dados:**
  * Configurações sensíveis (API Keys) e preferências (Bridge URL) persistidas localmente via `sessionStorage` e `localStorage`[cite: 1, 2].
  * **Histórico:** Limite estrito de **30 itens** salvos localmente no `localStorage`.
  * **Vault:** Banco de dados robusto local via **IndexedDB** (`akashi_vault_db`) para armazenamento e persistência binária de mídias reais geradas (Blobs de imagens e vídeos)[cite: 1, 2].

---

## 3. Filosofia de Design e UX (Estética Apple Premium)
A IA deve tratar a interface do AKASHI como um aplicativo móvel/desktop nativo, afastando-se de comportamentos típicos de websites:
* **Visual:** Estética *Clean Premium*, minimalista, inspirada nas diretrizes de design da Apple (espaçamento generoso, cantos arredondados sutis, tipografia nítida, foco em scannability e contraste elegante)[cite: 1].
* **Interatividade:** Comportamento fluido e responsivo. Transições suaves, estados de clique (`:active`) rápidos e otimizados para toque, sem lag de renderização[cite: 1].
* **Navegação:** Manter a estrutura focada em blocos e cartões (`.card`) bem delimitados que se comportam como widgets integrados[cite: 1].

---

## 4. Matrizes de Dados e Roteamento (Lógica Interna)
O comportamento do ecossistema do app é governado por objetos estáticos centrais que **nunca** devem ter sua lógica de sincronização corrompida[cite: 1]:
1. **`EP` (Engine Platform Map):** Mapeia quais engines pertencem a quais plataformas e armazena notas técnicas em texto[cite: 1].
2. **`MODEL_META`:** Define metadados rígidos de execução (se o modelo é `image`, `video` ou `tool`), comportamento de proporção (`aspect`), qualidades, durações e o modo de imagens de referência (`refMode`)[cite: 1].
3. **`MUAPI_SLUG` & `IMAGINEART_STYLE_OVERRIDES`:** Dicionários de tradução que convertem os nomes legíveis da interface nos slugs exatos exigidos pelas requisições REST das APIs de destino[cite: 1].

---

## 5. Regras Estritas e Guardrails (Restrições para a IA)

### ⛔ REGRA DE SEGURANÇA CRÍTICA: Password Gate
* A constante `GATE_HASH` que guarda o hash de acesso da tela inicial **NÃO deve ser alterada, modificada ou substituída sob nenhuma circunstância**, a menos que haja uma ordem estrita e explícita do usuário em linguagem natural contendo a nova senha[cite: 1].

### A. Sincronização de Seletores (`syncModelSelectors`)
* Qualquer alteração ou inclusão de novos modelos nas listas suspensas deve passar obrigatoriamente pela função de sincronização reativa[cite: 1]. Quando o usuário altera a plataforma, as engines incompatíveis devem ser filtradas, e vice-versa[cite: 1].
* A flag de controle `syncingSelectors` deve ser respeitada para evitar loops infinitos de redimensionamento de tela ou eventos[cite: 1].

### B. Validação de Imagens de Referência e Envio
* Antes de permitir o disparo do método `sendToplatform()`, a função `getRefCompatibility()` deve validar o grid de referências de 6 slots contra as regras do `MODEL_META`[cite: 1].
* Se o modelo for configurado com `refMode: "none"`, qualquer upload prévio no grid deve bloquear o botão de envio, exibindo uma mensagem de erro estilizada com a cor `--err`[cite: 1].

### C. Captura e Persistência no Vault
* Toda mídia retornada com sucesso por um pipeline externo (seja uma string em Base64 ou uma URL blob remota) deve ser interceptada pela função `captureVaultSource()`[cite: 1].
* O sistema deve tentar converter requisições remotas em `Blob` locais antes de salvar no IndexedDB para evitar expiração de links temporários das APIs[cite: 1, 2].

### D. Formatação do System Prompt (Metodologia AKASHI)
* O motor de geração utiliza a IA Anthropic para estruturar os prompts finais[cite: 1]. O prompt do sistema gerado dinamicamente pela função `buildSys()` deve manter rigorosamente as marcações e blocos delimitadores `[PT]`, `[EN]`, e `[NEG]`[cite: 1].
* O modificador de fotorrealismo ("MAKE IT REAL") deve injetar a string de textura crua e iluminação natural ao final do bloco `[EN]` sem corromper as tags XML do output[cite: 1].

### E. Inteligência Reativa e Validas Cruzadas (Novas Funcionalidades)
* **Sugestão de Ferramenta:** A IA deve implementar uma rotina no frontend que compara a semântica da ideia digitada com a capacidade técnica da engine ativa. Se houver incompatibilidade de performance (ex: fotorrealismo de pessoas em engines de texto), injetar um elemento informativo de alerta discretamente na UI.
* **Mapeamento de Restrições Técnicas:** Adensar o objeto `MODEL_META` e as funções de escuta (`onEngine`/`onPlatform`) para aplicar a propriedade `disabled` ou ocultar elementos do DOM (como seletores de aspect ratio inválidos) com base no endpoint ativo[cite: 1].
* **Estilo de Flutuação 3D:** O contêiner `#genResult` e os blocos de output gerados devem receber estilização de profundidade. Utilizar `perspective: 1000px`, `will-change: transform`, `transform: translateY(-4px) rotateX(2deg)` e transições de elevação com sombreamento difuso premium.
* **Pre-Flight Validation (Testes de Payload Anti-Erro):** Isolar a lógica de montagem do FormData/JSON em funções puras. O app não deve permitir o disparo da requisição sem antes validar se todos os parâmetros obrigatórios daquela plataforma e modelo específicos estão presentes e corretos, impedindo falhas silenciosas de runtime.

### F. Protocolo da Aba "Free" (Modo Ciano)
* **Estado Global:** Criar um estado booleano (`isFreeMode`) controlado por abas superiores em formato de pílulas integradas na interface.
* **Filtragem de Modelos:** Quando `isFreeMode` for verdadeiro, as funções de renderização de seletores devem ignorar as matrizes comerciais e carregar apenas as opções gratuitas abertas (ex: Flux Schnell local, APIs públicas estáveis ou instâncias de teste)[cite: 1].
* **Sobrescrita Estética Nativa:** No modo livre, as variáveis CSS de acento (`--or`, `--or2`, `--or3`) devem ser remapeadas dinamicamente via JavaScript (`document.documentElement.style.setProperty`) para tons específicos de **Ciano Elétrico** e fundos frios, alterando completamente a atmosfera visual do app enquanto ele se comportar como ambiente de homologação[cite: 1].

### G. Sistema de Self-Learning e Avaliação
* **Interface de Notas:** Adicionar abaixo do resultado da geração de mídia um componente interativo de avaliação por estrelas (1 a 5) e um campo de input compacto de texto para observações.
* **Persistência Estruturada:** O input do usuário deve atualizar o respectivo objeto da mídia dentro do banco de dados IndexedDB (`akashi_vault_db`)[cite: 1, 2].
* **Exportação Dinâmica:** Criar uma rotina interna em segundo plano que compila os metadados dos piores erros e melhores acertos e os reporta de maneira estruturada no documento de orientações do repositório, permitindo que os agentes leiam esse histórico para autodetecção de melhorias nas próximas tarefas de codificação.