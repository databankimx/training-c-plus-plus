// Small tokenizers for the Source and Lesson panes. They are not parsers: they recognize comments, strings,
// numbers, keywords, and identifiers well enough to color code the way Visual Studio does.

const CPP_KEYWORDS = new Set([
  "alignas", "alignof", "auto", "class", "concept", "const", "consteval", "constexpr", "constinit",
  "decltype", "delete", "explicit", "export", "extern", "false", "friend", "inline", "mutable",
  "namespace", "new", "noexcept", "nullptr", "operator", "private", "protected", "public", "register",
  "requires", "static", "struct", "template", "this", "thread_local", "true", "typedef", "typename",
  "union", "using", "virtual", "volatile",
]);

const CPP_CONTROL = new Set([
  "break", "case", "catch", "co_await", "co_return", "co_yield", "continue", "default", "do", "else",
  "for", "goto", "if", "return", "switch", "throw", "try", "while",
]);

const CPP_TYPES = new Set([
  "bool", "char", "char8_t", "char16_t", "char32_t", "double", "float", "int", "long", "short",
  "signed", "unsigned", "void", "wchar_t", "size_t", "std", "string", "string_view", "vector", "map",
  "set", "array", "optional", "variant", "unique_ptr", "shared_ptr",
]);

// Order matters: the first alternative that matches at a position wins.
const CPP_TOKEN = new RegExp(
  [
    String.raw`\/\*[\s\S]*?\*\/`,                       // block comment
    String.raw`\/\/[^\n]*`,                             // line comment
    String.raw`R"\([\s\S]*?\)"`,                        // raw string
    String.raw`"(?:\\[\s\S]|[^"\\\n])*"`,               // string
    String.raw`'(?:\\[\s\S]|[^'\\\n])+'`,               // character literal
    String.raw`#[^\n]*`,                                // preprocessor line, such as #include
    String.raw`\b0[xX][0-9a-fA-F']+\b`,                 // hexadecimal number
    String.raw`\b\d[\d']*(?:\.\d[\d']*)?(?:[eE][+-]?\d+)?[fFuUlL]*\b`, // number
    String.raw`[A-Za-z_][A-Za-z0-9_]*`,                 // identifier
    String.raw`\s+`,                                    // whitespace
    String.raw`[\s\S]`,                                 // anything else
  ].join("|"),
  "g",
);

function escapeHtml(text) {
  return text
    .replaceAll("&", "&amp;")
    .replaceAll("<", "&lt;")
    .replaceAll(">", "&gt;");
}

function classifyWord(word, previous, next) {
  if (CPP_KEYWORDS.has(word)) return "keyword";
  if (CPP_CONTROL.has(word)) return "control";
  if (CPP_TYPES.has(word)) return "type";
  if (next === "(") return /^[A-Z]/.test(word) ? "type" : "function";
  if (/^[A-Z][A-Z0-9_]+$/.test(word)) return "constant";
  if (/^[A-Z]/.test(word)) return "type";
  return "variable";
}

function classifyCpp(text, source, end, previous) {
  if (text.startsWith("/*") || text.startsWith("//")) return "comment";
  if (text.startsWith('"') || text.startsWith('R"')) return "string";
  if (text.startsWith("'")) return "string";
  if (text.startsWith("#")) return "attribute";
  if (/^\d/.test(text) || /^0[xX]/.test(text)) return "number";
  if (/^[A-Za-z_]/.test(text)) {
    const next = (source.slice(end).match(/^\s*(.)/) || [])[1];
    return classifyWord(text, previous, next);
  }
  return "";
}

const PY_KEYWORDS = new Set([
  "and", "as", "assert", "async", "await", "class", "def", "del", "from", "global", "import",
  "in", "is", "lambda", "nonlocal", "not", "or", "with", "yield",
]);

const PY_CONTROL = new Set([
  "break", "continue", "elif", "else", "except", "finally", "for", "if", "pass", "raise", "return",
  "try", "while",
]);

const PY_CONSTANTS = new Set(["True", "False", "None"]);

const PY_BUILTINS = new Set([
  "bool", "dict", "float", "int", "list", "len", "open", "print", "range", "set", "str", "tuple",
  "super", "type",
]);

const PY_TOKEN = new RegExp(
  [
    String.raw`#[^\n]*`,                                  // comment
    String.raw`"""[\s\S]*?"""|'''[\s\S]*?'''`,         // triple-quoted string
    String.raw`"(?:\\[\s\S]|[^"\\\n])*"|'(?:\\[\s\S]|[^'\\\n])*'`, // string
    String.raw`\b\d[\d_]*(?:\.\d+)?\b`,                  // number
    String.raw`[A-Za-z_][A-Za-z0-9_]*`,                  // identifier
    String.raw`\s+`,                                     // whitespace
    String.raw`[\s\S]`,                                  // anything else
  ].join("|"),
  "g",
);

function classifyPython(text, source, end) {
  if (text.startsWith("#")) return "comment";
  if (text.startsWith('"') || text.startsWith("'")) return "string";
  if (/^\d/.test(text)) return "number";
  if (/^[A-Za-z_]/.test(text)) {
    if (PY_CONSTANTS.has(text)) return "constant";
    if (PY_KEYWORDS.has(text)) return "keyword";
    if (PY_CONTROL.has(text)) return "control";
    if (PY_BUILTINS.has(text)) return "type";
    const next = (source.slice(end).match(/^\s*(.)/) || [])[1];
    if (next === "(") return "function";
    return "variable";
  }
  return "";
}

/** Returns Python source as HTML with `tok-*` spans, coloured like the C++ highlighting. */
export function highlightPython(source) {
  const parts = [];
  PY_TOKEN.lastIndex = 0;
  let match;
  while ((match = PY_TOKEN.exec(source)) !== null) {
    const text = match[0];
    const type = classifyPython(text, source, PY_TOKEN.lastIndex);
    parts.push(type ? `<span class="tok-${type}">${escapeHtml(text)}</span>` : escapeHtml(text));
  }
  return parts.join("");
}

/** Returns C++ source as HTML with `tok-*` spans. */
export function highlightCpp(source) {
  const parts = [];
  let previous = "";
  CPP_TOKEN.lastIndex = 0;
  let match;
  while ((match = CPP_TOKEN.exec(source)) !== null) {
    const text = match[0];
    const type = classifyCpp(text, source, CPP_TOKEN.lastIndex, previous);
    if (!/^\s+$/.test(text)) previous = text;
    parts.push(type ? `<span class="tok-${type}">${escapeHtml(text)}</span>` : escapeHtml(text));
  }
  return parts.join("");
}
