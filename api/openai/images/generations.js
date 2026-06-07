function corsHeaders(origin) {
  return {
    "Access-Control-Allow-Origin": origin || "*",
    "Access-Control-Allow-Methods": "GET,HEAD,POST,PUT,PATCH,DELETE,OPTIONS",
    "Access-Control-Allow-Headers": "content-type,x-api-key,authorization",
    "Access-Control-Max-Age": "86400",
    "Vary": "Origin",
  };
}

export default async function handler(req, res) {
  const origin = req.headers.origin || "*";
  const headers = corsHeaders(origin);

  if (req.method === "OPTIONS") {
    Object.entries(headers).forEach(([k, v]) => res.setHeader(k, v));
    return res.status(204).end();
  }

  const key = req.headers["x-api-key"] || process.env.OPENAI_API_KEY || "";
  if (!key) {
    Object.entries(headers).forEach(([k, v]) => res.setHeader(k, v));
    return res.status(401).json({ error: "Missing OpenAI key. Send x-api-key or set OPENAI_API_KEY in Vercel env vars." });
  }

  try {
    const upstream = await fetch("https://api.openai.com/v1/images/generations", {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
        "Authorization": `Bearer ${key}`,
      },
      body: JSON.stringify(req.body || {}),
    });

    const text = await upstream.text();
    Object.entries(headers).forEach(([k, v]) => res.setHeader(k, v));
    res.status(upstream.status);
    res.setHeader("content-type", upstream.headers.get("content-type") || "application/json; charset=utf-8");
    return res.send(text);
  } catch (error) {
    Object.entries(headers).forEach(([k, v]) => res.setHeader(k, v));
    return res.status(502).json({ error: error.message || "Bad gateway" });
  }
}
