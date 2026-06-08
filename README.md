# AKASHI Prompt Director

Personal static web app for prompt generation and image/video platform handoff.

## Current status

- Single-file app (`index.html`) for GitHub Pages and local use.
- Prompt generation with engine/platform-aware routing.
- Generation targets supported across:
  - Muapi.ai
  - OpenAI API
  - ImagineArt
  - Gemini / Google AI Studio
- Engine/platform pairing is filtered in the UI so unsupported combinations are hidden or blocked before generation.
- Reference-image handling is validated before sending:
  - Models that accept references allow them in the flow.
  - Models that do not accept references are blocked early with a clear message.
  - Google `Nano Banana` models are treated as reference-capable.
  - Google `Imagen 4 Ultra` / `Imagen 4 Pro` remain text-only in this app flow.
- Output vault is persistent in the browser via IndexedDB, so generated images and videos do not disappear when the result panel clears or refreshes.
- History is preserved locally in the browser.
- The app includes a password gate.
- The MuAPI bridge can be pointed at a public Worker URL through the app settings when running on GitHub Pages or mobile.

## Security

Do not commit API keys to this repository. Add keys only inside the app UI; they are stored locally in your browser.

## Notes

- `BRIDGE URL` is meant for a public proxy/Worker when you want MuAPI to work outside the local Mac.
- The app currently expects local API credentials to stay in the browser, not in the repository.
- If you change the model registry in `index.html`, update the README status section to match the new rules.

---

# AKASHI Prompt Director

Aplicativo web estático pessoal para geração de prompts e envio para plataformas de imagem e vídeo.

## Status atual

- App em arquivo único (`index.html`) para GitHub Pages e uso local.
- Geração de prompt com roteamento baseado em engine e plataforma.
- Destinos suportados:
  - Muapi.ai
  - OpenAI API
  - ImagineArt
  - Gemini / Google AI Studio
- A combinação engine/plataforma é filtrada na interface, então pares incompatíveis ficam ocultos ou bloqueados antes do envio.
- O uso de imagens de referência é validado antes de gerar:
  - modelos que aceitam referências seguem normalmente;
  - modelos que não aceitam referências são bloqueados com mensagem clara;
  - modelos `Nano Banana` da Google são tratados como compatíveis com referência;
  - `Imagen 4 Ultra` e `Imagen 4 Pro` continuam como modelos sem referência neste fluxo do app.
- O vault de saídas fica persistido no navegador via IndexedDB, então imagens e vídeos gerados não somem quando a área de resultado limpa ou a página é atualizada.
- O histórico também fica salvo localmente no navegador.
- O app tem uma proteção por senha.
- O bridge da MuAPI pode apontar para uma URL pública de Worker nas configurações do app, quando o uso for no GitHub Pages ou no celular.

## Segurança

Não faça commit das chaves de API neste repositório. Elas devem ser adicionadas apenas pela interface do app e ficam salvas localmente no navegador.

## Observações

- `BRIDGE URL` é para um proxy/Worker público quando você quiser usar MuAPI fora do Mac local.
- O app continua esperando que as credenciais fiquem no navegador, e não no repositório.
- Se a matriz de modelos em `index.html` mudar, atualize esta seção de status para manter o README alinhado.
