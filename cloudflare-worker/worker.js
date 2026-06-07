const DEFAULT_MUAPI_UPSTREAM = "https://api.muapi.ai";

function corsHeaders(origin) {
  return {
    "Access-Control-Allow-Origin": origin || "*",
    "Access-Control-Allow-Methods": "GET,HEAD,POST,PUT,PATCH,DELETE,OPTIONS",
    "Access-Control-Allow-Headers": "content-type,x-api-key,x-akashi-token,authorization",
    "Access-Control-Max-Age": "86400",
    "Vary": "Origin",
  };
}

function json(data, init = {}) {
  return new Response(JSON.stringify(data), {
    ...init,
    headers: {
      "content-type": "application/json; charset=utf-8",
      ...(init.headers || {}),
    },
  });
}

function upstreamUrl(url, upstreamBase) {
  const clean = new URL(url);
  const path = clean.pathname.replace(/^\/api\/v1/, "/api/v1");
  return `${upstreamBase}${path}${clean.search}`;
}

function authKey(request, env) {
  return request.headers.get("x-api-key") || env.MUAPI_API_KEY || "";
}

function bridgeToken(request, env) {
  const header = request.headers.get("x-akashi-token") || "";
  const auth = request.headers.get("authorization") || "";
  return header || auth.replace(/^Bearer\s+/i, "") || env.BRIDGE_TOKEN || "";
}

export default {
  async fetch(request, env) {
    const origin = request.headers.get("Origin") || "*";
    const upstreamBase = (env.MUAPI_UPSTREAM || DEFAULT_MUAPI_UPSTREAM).replace(/\/+$/, "");
    const url = new URL(request.url);

    if (request.method === "OPTIONS") {
      return new Response(null, { status: 204, headers: corsHeaders(origin) });
    }

    if (!url.pathname.startsWith("/api/v1")) {
      return json({ error: "Not found" }, { status: 404, headers: corsHeaders(origin) });
    }

    const requiredToken = env.BRIDGE_TOKEN || "";
    if (requiredToken) {
      const providedToken = bridgeToken(request, env);
      if (!providedToken || providedToken !== requiredToken) {
        return json(
          { error: "Unauthorized. Missing or invalid bridge token." },
          { status: 401, headers: corsHeaders(origin) }
        );
      }
    }

    const key = authKey(request, env);
    if (!key) {
      return json(
        { error: "Missing MuAPI key. Send x-api-key or set MUAPI_API_KEY in the Worker." },
        { status: 401, headers: corsHeaders(origin) }
      );
    }

    const upstream = upstreamUrl(url, upstreamBase);
    const headers = new Headers(request.headers);
    headers.set("x-api-key", key);
    headers.delete("host");

    const init = {
      method: request.method,
      headers,
      redirect: "follow",
    };

    if (request.method !== "GET" && request.method !== "HEAD") {
      init.body = request.body;
    }

    const upstreamRes = await fetch(upstream, init);
    const responseHeaders = new Headers(upstreamRes.headers);
    for (const [k, v] of Object.entries(corsHeaders(origin))) {
      responseHeaders.set(k, v);
    }
    return new Response(upstreamRes.body, {
      status: upstreamRes.status,
      statusText: upstreamRes.statusText,
      headers: responseHeaders,
    });
  },
};
