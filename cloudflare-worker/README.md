# AKASHI MuAPI Bridge

This Cloudflare Worker proxies `/api/v1/*` to MuAPI and keeps the browser-side app simple for mobile use.

## Deploy

1. Install Wrangler.
2. Deploy this folder as a Worker.
3. Set a secret if you want the browser to stop sending the key:

```bash
wrangler secret put MUAPI_API_KEY
```

4. Point the AKASHI app's `MUAPI BRIDGE URL` to:

```text
https://<your-worker-domain>/api/v1
```

If you do not set `MUAPI_API_KEY`, the app can still send `x-api-key` itself.

## Routes

- `OPTIONS /api/v1/*` -> CORS preflight
- `GET|POST|PUT|PATCH|DELETE /api/v1/*` -> proxied to `https://api.muapi.ai/api/v1/*`
