# LORAC — Contexto da Sessão de Trabalho

> **Leia este arquivo PRIMEIRO ao iniciar uma nova sessão.**  
> Ele resume tudo que já foi feito e o que fazer a seguir — sem precisar perguntar ao cliente.

---

## Branch de trabalho
`claude/sentinel-visual-identity-logo-evr7hy`

---

## Status atual: PRONTO PARA GERAR

O logo base já foi aprovado conceptualmente pelo cliente. A tarefa agora é **refinar e vetorizar**.

---

## O que o cliente quer

O cliente gerou um logo no ChatGPT e **gostou do conceito**, mas disse que está "amador".  
As imagens estão em:
- `brand/lorac/reference/lorac-chatgpt-seal.png` — **o logo que ele aprovou (conceito)**
- `brand/lorac/reference/lorac-chatgpt-brand-doc.png` — documento de marca gerado junto

Ele quer:
1. **Manter o conceito** (selo circular, escudo hexagonal, pilar + balança, tipografia LORAC)
2. **Eliminar o aspecto amador** (ver lista abaixo)
3. **Vetorizar** ao final

---

## O que está bom (MANTER)
- Selo circular com texto em arco
- Escudo hexagonal como contentor
- Pilar + balança como símbolo jurídico
- Traço diagonal no "A" de LORAC (lockup horizontal)
- Paleta preto/ouro

---

## O que precisa mudar para ficar premium

| Problema | Correção |
|---|---|
| Gradientes metálicos no ouro | Flat fill, ouro chapado `#F2B705` |
| Estrada com linha tracejada | Simplificar para linhas geométricas ou remover |
| Pontos dourados decorativos nos lados | Remover |
| Stroke weights inconsistentes | Harmonizar todas as linhas |
| Tipografia no anel com rendering borrado | Caixa-alta, tracking uniforme, limpo |
| Sombras/glows nos elementos | Remover — só linhas e fills planos |

---

## Referências disponíveis em `brand/lorac/reference/`
- `lorac-chatgpt-seal.png` — logo aprovado pelo cliente (conceito a refinar)
- `lorac-chatgpt-brand-doc.png` — documento de marca com variações
- `ref-symbol-construction.png` — referência G&O (nível de qualidade/sofisticação desejado)
- `ref-symbol-elements.png` — elementos do G&O decompostos
- `ref-lockups.png` — lockups G&O (fundo claro/escuro)
- `ref-symbol-typography.png` — tipografia G&O
- `concept-sketch-geometry.png/.svg` — esboço bruto inicial (NÃO é o alvo)

---

## Plano de execução (próxima sessão)

### Passo 1 — Verificar modelo Higgsfield
```
models_explore(action: "get", model_id: "recraft_v4_1")
```
Confirmar se aceita image reference e quais roles.

### Passo 2 — Upload das referências
Subir via `media_upload`:
1. `brand/lorac/reference/lorac-chatgpt-seal.png` → role: "style" ou "image_reference"
2. `brand/lorac/reference/ref-symbol-construction.png` → role: "style"

### Passo 3 — Gerar com Higgsfield Recraft vector
```
generate_image({
  model: "recraft_v4_1",
  model_type: "vector",
  aspect_ratio: "1:1",
  count: 4,
  resolution: "2k",
  colors: ["#1A1A1A", "#4A4A4A", "#F2B705"],
  background_color: "#FFFFFF",
  medias: [
    { value: <upload_id_chatgpt_seal>, role: "image_reference" },
    { value: <upload_id_go_construction>, role: "style" }
  ],
  prompt: "..."  // ver prompt abaixo
})
```

### Prompt para geração
```
Premium legal services monogram logo seal. Circular badge with hexagonal shield at center. 
Inside shield: balanced scales of justice flanking a central pillar/column, with angular 
geometric road lines converging below. LORAC text arched at top of circle. Tagline 
"CONSULTORIA E ASSESSORIA JURÍDICA DE TRÂNSITO" arched at bottom. 
Style: flat vector, NO gradients, NO shadows, NO 3D effects, NO metallic textures. 
Clean uniform stroke weights. Square terminals, miter joints, 100% angular geometry. 
Colors: near-black #1A1A1A background fill, white strokes for inner elements, 
gold #F2B705 accent on shield frame and select details only. 
Quality level: sophisticated premium law firm identity, like the G&O reference provided.
```

### Passo 4 — Após aprovação do resultado
- Salvar SVGs gerados em `brand/lorac/output/`
- Limpar paths no SVG se necessário
- Commit e push na branch

---

## Permissões (já configuradas)
O arquivo `.claude/settings.json` já existe com `bypassPermissions` e regras para Higgsfield.  
Higgsfield deve funcionar sem prompts de aprovação nesta sessão.

---

## Brief completo
Ver `brand/lorac/LORAC-LOGO-BRIEF.md` — mas atenção: o cliente mudou de direção.  
O brief proibia balança da justiça, mas o cliente **aprovou** o conceito do ChatGPT que usa balança.  
**O pedido novo do cliente vence** (como o próprio brief instrui).

---

## Créditos Higgsfield
Conta Creator, ~6.000 créditos no início. Verificar saldo antes de gerar.
