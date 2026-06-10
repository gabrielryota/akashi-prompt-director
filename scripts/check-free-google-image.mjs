import fs from "node:fs";
import path from "node:path";

const ROOT = path.resolve(process.cwd());
const INDEX_PATH = path.join(ROOT, "index.html");

function fail(message) {
  console.error(`FAIL: ${message}`);
  process.exit(1);
}

function extractFunctionSource(source, functionName) {
  const startToken = `async function ${functionName}(`;
  const startIndex = source.indexOf(startToken);
  if (startIndex === -1) fail(`Could not find ${functionName}`);

  const braceStart = source.indexOf("{", startIndex);
  if (braceStart === -1) fail(`Could not find function body start for ${functionName}`);

  let depth = 0;
  for (let i = braceStart; i < source.length; i++) {
    const ch = source[i];
    if (ch === "{") depth++;
    else if (ch === "}") {
      depth--;
      if (depth === 0) {
        return source.slice(startIndex, i + 1);
      }
    }
  }
  fail(`Could not parse function body for ${functionName}`);
}

const html = fs.readFileSync(INDEX_PATH, "utf8");
const match = html.match(/<script[^>]*>([\s\S]*)<\/script>/);
if (!match) fail("Could not find script block in index.html");

const script = match[1];
const fn = extractFunctionSource(script, "sendGoogleImagen3Free");

const required = [
  "https://generativelanguage.googleapis.com/v1beta/openai/images/generations",
  "Bearer ${apiKey}",
  'model: "gemini-2.5-flash-image"',
  'response_format: "b64_json"',
  "size",
];

const forbidden = [
  "extra_body",
  "responseFormat",
  "responseModalities",
  "imageConfig",
  ":generateContent",
];

for (const needle of required) {
  if (!fn.includes(needle)) fail(`Expected FREE flow to include: ${needle}`);
}

for (const needle of forbidden) {
  if (fn.includes(needle)) fail(`FREE flow still contains forbidden field or endpoint: ${needle}`);
}

console.log("PASS: FREE Google image payload looks consistent.");
