const DEFAULT_MUAPI_UPSTREAM = "https://api.muapi.ai";

function corsHeaders(origin) {
  return {
    "Access-Control-Allow-Origin": origin || "*",
    "Access-Control-Allow-Methods": "GET,HEAD,POST,PUT,PATCH,DELETE,OPTIONS",
    "Access-Control-Allow-Headers": "content-type,x-api-key,authorization",
    "Access-Control-Max-Age": "86400",
    "Vary": "Origin",
  };
}

function cleanUpstream(base) {
  return (base || DEFAULT_MUAPI_UPSTREAM).replace(/\/+$/, "");
}

function upstreamPath(reqUrl) {
  const url = new URL(reqUrl);
  const path = url.pathname.replace(/^\/api\/v1/, "/api/v1");
  return `${path}${url.search}`;
}

export default async function handler(req, res) {
  const origin = req.headers.origin || "*";
  const headers = corsHeaders(origin);

  if (req.method === "OPTIONS") {
    Object.entries(headers).forEach(([k, v]) => res.setHeader(k, v));
    return res.status(204).end();
  }

  const upstreamBase = cleanUpstream(process.env.MUAPI_UPSTREAM);
  const key = req.headers["x-api-key"] || process.env.MUAPI_API_KEY || "";
  if (!key) {
    Object.entries(headers).forEach(([k, v]) => res.setHeader(k, v));
    return res.status(401).json({
      error: "Missing MuAPI key. Send x-api-key or set MUAPI_API_KEY in Vercel env vars.",
    });
  }

  const target = `${upstreamBase}${upstreamPath(req.url)}`;
  const forwardHeaders = {
    "content-type": req.headers["content-type"] || "application/json",
    "x-api-key": key,
  };

  try {
    const upstreamRes = await fetch(target, {
      method: req.method,
      headers: forwardHeaders,
      body: ["GET", "HEAD"].includes(req.method) ? undefined : JSON.stringify(req.body ?? {}),
    });

    const text = await upstreamRes.text();
    Object.entries(headers).forEach(([k, v]) => res.setHeader(k, v));
    res.status(upstreamRes.status);
    const contentType = upstreamRes.headers.get("content-type") || "application/json; charset=utf-8";
    res.setHeader("content-type", contentType);
    return res.send(text);
  } catch (error) {
    Object.entries(headers).forEach(([k, v]) => res.setHeader(k, v));
    return res.status(502).json({ error: error.message || "Bad gateway" });
  }
}
