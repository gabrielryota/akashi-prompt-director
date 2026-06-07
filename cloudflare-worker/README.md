# AKASHI MuAPI Bridge

This Cloudflare Worker proxies `/api/v1/*` to MuAPI and keeps the browser-side app simple for mobile use.

## Deploy

1. Install Wrangler.
2. Deploy this folder as a Worker.
3. Set a secret so the MuAPI key stays only in the Worker:

```bash
wrangler secret put MUAPI_API_KEY
```

4. Set a second secret to protect the bridge itself:

```bash
wrangler secret put BRIDGE_TOKEN
```

5. Point the AKASHI app's `BRIDGE URL` to:

```text
https://<your-worker-domain>/api/v1
```

6. Put the same token in the app's `BRIDGE TOKEN` field.

If you do not set `MUAPI_API_KEY`, the app can still send `x-api-key` itself, but the recommended setup is to keep the MuAPI key only in the Worker and use the bridge token for access control.

## Routes

- `OPTIONS /api/v1/*` -> CORS preflight
- `GET|POST|PUT|PATCH|DELETE /api/v1/*` -> proxied to `https://api.muapi.ai/api/v1/*`
