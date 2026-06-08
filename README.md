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
