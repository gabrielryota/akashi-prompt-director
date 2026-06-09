# AKASHI Prompt Director

Personal static web app for prompt generation and image/video platform handoff.

## Current status

- Single-file app (`index.html`) for GitHub Pages and local use.
- Prompt generation with engine/platform-aware routing[cite: 1, 2].
- Generation targets supported across: Muapi.ai, OpenAI API, ImagineArt, Gemini / Google AI Studio[cite: 1, 2].
- Engine/platform pairing is filtered in the UI so unsupported combinations are hidden or blocked before generation[cite: 1, 2].
- Reference-image handling is validated before sending:
  - Models that accept references allow them in the flow[cite: 1, 2].
  - Models that do not accept references are blocked early with a clear message[cite: 1, 2].
  - Google `Nano Banana` models are treated as reference-capable[cite: 1, 2].
  - Google `Imagen 4 Ultra` / `Imagen 4 Pro` remain text-only in this app flow[cite: 1, 2].
- Free mode is intentionally limited to a single image generator for stability: Google image generation via the Gemini API, backed by a user-provided Google AI Studio key.
- Output vault is persistent in the browser via IndexedDB, so generated images and videos do not disappear when the result panel clears or refreshes[cite: 1, 2].
- History is preserved locally in the browser (Limite expandido para 30 itens)[cite: 1, 2].
- The app includes a password gate[cite: 1, 2].
- The MuAPI bridge can be pointed at a public Worker URL through the app settings when running on GitHub Pages or mobile[cite: 1, 2].

## Próximos Recursos & Inteligência de Negócio (Roadmap Avançado)

1. **Consultoria Ativa de Engines:** O app deve analisar a ideia do usuário e a engine selecionada. Caso haja uma engine significativamente superior para aquele caso de uso específico (ex: fotorrealismo de pele, texto embutido, render geométrico), a interface exibirá um aviso técnico sugerindo a troca, sem forçar a alteração.
2. **Bloqueio Reativo de Interface:** A matriz de compatibilidade deve desabilitar dinamicamente campos de formulário, seletores de proporção (aspect ratio) ou o botão de upload de referências visuais com base nas limitações exatas da combinação Engine + Plataforma escolhida.
3. **Placa de Output com Profundidade (Design 3D):** A seção de resultados de geração de imagens e vídeos deve possuir estilização CSS avançada baseada em eixos de perspectiva e sombras em camadas, criando um efeito visual de que o painel está fisicamente descolado e flutuando sobre a página.
4. **Arquitetura Anti-Falha (Fail-Safe):** Bloqueio absoluto de requisições malformadas através de mapeamento rígido de payloads por plataforma. O ecossistema deve rodar uma rotina de validação pré-vôo (Mocks) antes de disparar os tokens das APIs parceiras para evitar falhas de runtime.
5. **Modo Homologação / Aba "Free" (Roteador Econômico):** Inclusão de uma alternância de contexto (Aba Superior) que reconfigura o app para um único caminho gratuito estável.
   * **Identidade Visual:** Quando ativo, o app adota obrigatoriamente uma paleta de cores acentuada em **Ciano**, indicando o modo de simulação e teste de prompts.
   * **Propósito:** Validar a aderência estrutural e a semântica do prompt em um fluxo gratuito confiável antes de gastar créditos em engines de produção.
6. **Sistema de Self-Learning (Loop de Feedback):** Inclusão de um componente de qualificação (1-5 estrelas e campo de notas) abaixo do resultado gerado. A nota atribuída é persistida no registro do item no IndexedDB, servindo para futuras consultas e refinamento automatizado das diretrizes.

## Security

Do not commit API keys to this repository. Add keys only inside the app UI; they are stored locally in your browser[cite: 2].
