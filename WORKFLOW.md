# AKASHI Workflow

This repo is the working area for AKASHI Prompt Director.

## Use this repo only

- Treat this repository as the canonical workspace for AKASHI.
- Avoid cross-repo assumptions.
- If you need to change app behavior, edit `index.html` first and validate the flow locally or in the browser.

## Preferred order of work

1. Inspect the current code path in `index.html`.
2. Check `README.md` and `AGENTS.md` for constraints.
3. Validate with the smallest safe change.
4. Test the exact user-facing flow after each meaningful change.
5. Commit only when the result is stable enough to hand off.

## Hard rules

- Do not commit API keys.
- Keep the FREE flow stable and explicit.
- Do not assume browser cache is clear.
- If a payload looks wrong, verify the official API docs before changing the model name again.

## Files that matter most

- `index.html`
- `README.md`
- `AGENTS.md`
- `cloudflare-worker/`
- `api/`

## Current practical note

- The FREE path is the highest-risk area for regressions.
- If a change touches Google image generation, verify the exact REST shape and the model availability for the current key before shipping.
