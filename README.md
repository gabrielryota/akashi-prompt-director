# AKASHI Workspace

Repo dedicado ao AKASHI Prompt Director. Este repositório deve ser usado como o espaço único de trabalho do projeto.

## O que existe aqui

- `index.html`: app principal em arquivo único.
- `README.md`: visão geral e instruções operacionais.
- `AGENTS.md`: instruções locais do projeto.
- `api/`: rotas auxiliares usadas no fluxo do app.
- `cloudflare-worker/`: bridge/proxy de MuAPI para uso em GitHub Pages e mobile.
- `akashi-muapi-bridge.zip`: pacote do bridge.

## Estado atual

- App single-file com gate por senha.
- Vault persistente para imagens e vídeos via IndexedDB.
- Histórico local persistente no navegador.
- Modo PRO/FREE.
- FREE mode limitado a um fluxo estável de imagem via Google AI Studio / Gemini API.
- MuAPI pode rodar via bridge público quando necessário.
- Google `Nano Banana` é tratado como compatível com referência.
- Google `Imagen 4 Ultra` / `Imagen 4 Pro` permanecem text-only no fluxo do app.

## Como trabalhar neste repo

- Faça mudanças só aqui.
- Preserve o fluxo FREE estável.
- Não assuma que keys ou cache do navegador estão limpos.
- Se algo depender de API/SDK/documentação, valide antes de hardcodar um modelo ou payload.

## Para a Jules

- Use este repositório como fonte única de verdade.
- Não copie suposições do repo antigo sem confirmar com o código atual.
- Se um erro parecer de payload/modelo, confira primeiro a documentação oficial da API antes de tentar outro nome de modelo.
- Se a mudança tocar o fluxo FREE, teste em navegador limpo e também no atalho do iPhone, porque cache pode enganar.

## Publicação

- Branch principal: `main`
- Remoto novo do projeto: `akashi`
- O deploy do site continua separado do repo antigo.

## Segurança

- Não comitar API keys neste repositório.
- As keys devem ser inseridas na UI do app e ficam salvas localmente no navegador.

## Troubleshooting

- Se o erro mencionar `responseFormat`, o payload ainda está fora do formato aceito pela API.
- Se o erro mencionar modelo inexistente, o modelo escolhido não está disponível para a chave/projeto atual.
- Se o erro persistir depois de atualizar a página, teste com cache limpo ou recrie o atalho do web app no iPhone.
