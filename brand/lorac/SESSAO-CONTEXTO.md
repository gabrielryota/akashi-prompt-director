# AKASHI — Sessão de Contexto (branch: claude/sessao-contexto-continuation-w7si6q)

## Estado do app ao início desta sessão

### Implementado e estável
- Password Gate (GATE_HASH imutável)
- syncModelSelectors com flag anti-loop
- Vault (IndexedDB `akashi_vault_db`) — captura, exibição, download, remoção
- Histórico local (localStorage, limite 30 itens)
- Modo FREE / PRO com troca de paleta CSS dinâmica (ciano elétrico no FREE)
- Make It Real toggle
- 3D float effect (`perspective`, `rotateX`, `translateY`) no `#genResult` e `.out-box`
- Pre-Flight validation em `validateSendState()`
- Rotas: MuAPI, OpenAI API, ImagineArt, Gemini/Google AI Studio, FREE (Google Image)
- Importação de keys via TXT/JSON

### Pendente (AGENTS.md)
1. **Seção G — Self-Learning e Avaliação**
   - Interface de estrelas (1–5) abaixo do resultado de mídia
   - Campo de observação de texto compacto
   - Atualização do objeto da mídia no IndexedDB com `rating` e `notes`
   - Exportação dinâmica em segundo plano (compilar melhores/piores resultados como log estruturado neste arquivo)

2. **Seção E — Sugestão de Ferramenta**
   - Rotina que compara semântica da ideia com capacidade da engine ativa
   - Injetar alerta discreto na UI quando há incompatibilidade (ex: fotorrealismo de pessoas em engines de texto puro)

## O que foi feito nesta sessão

### Self-Learning implementado
- Adicionado componente de avaliação (`#ratingBlock`) após `#genResult` no card 03
- Estrelas 1–5 com hover/click interativo
- Campo de observação de texto
- Botão "salvar avaliação" que persiste `rating` e `notes` no IndexedDB via `updateVaultRating()`
- Adicionado `idbUpdate()` para operações parciais no IndexedDB
- Rating e notes exibidos no vault (estrelas + texto)

### Tool Suggestion implementado
- Função `getToolCompatibilityWarning(engine, ideaText)` com mapa semântico de incompatibilidades
- Gatilho no `onEngine()` e no evento `input` do textarea `#ctx`
- Elemento `#toolSuggestAlert` injetado na card 01 abaixo do campo de ideia

## Próximos passos sugeridos
- Refinamento dos mapas semânticos de incompatibilidade (adicionar mais engines)
- Exportação dos dados de rating para este arquivo via rotina background
- Testar no iPhone (cache do iOS WebView pode afetar IndexedDB updates)
