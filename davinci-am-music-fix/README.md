# AM Music Fix — DaVinci Resolve (VST3 / AU, macOS)

Port do preset de Premiere **AM Music Fix.prfpset** ("Drag this on your music to fix it
from clashing with your voice over") para um plugin de áudio que roda no DaVinci Resolve
(Edit page e Fairlight).

## Cadeia de efeitos (idêntica ao preset, mesma ordem)

| # | Efeito no Premiere | Valor no preset (faixa estéreo) |
|---|--------------------|--------------------------------|
| 1 | Lowpass | Cutoff ≈ 6769 Hz |
| 2 | Mastering — EQ Band 1 (low shelf) | 30 Hz, 0 dB — **desligada** |
|   | Mastering — EQ Band 2 (peak) | **2168.5 Hz, −11.55 dB, Q 0.3** — ligada |
|   | Mastering — EQ Band 3 (high shelf) | 12 kHz, 0 dB — **desligada** |
|   | Mastering — Reverb | 0 % |
|   | Mastering — Widener | +100 (máximo) |
|   | Mastering — Exciter | 20 %, modo Tube |
|   | Mastering — Loudness Maximizer | 20 % |
|   | Mastering — Output Gain | 0 dB |
| 3 | Volume (clip) | **−30 dB** |

O preset do Premiere também guarda uma versão para clipes **Mono / 5.1** (Lowpass ≈ 5015 Hz,
peak 361.5 Hz −2.8 dB Q 0.5, high shelf 2722 Hz +1.9 dB, reverb 10 %, widener 0,
exciter 80 % Tube, maximizer 20 %, volume 0 dB). Ela está disponível como preset de fábrica
"AM Music Fix (Mono / 5.1)" no menu de presets do plugin.

Todos os parâmetros ficam expostos para ajuste fino.

## Instalar

1. Baixe o `AM-Music-Fix-macOS.dmg` (aba **Actions** do GitHub → último run de
   "Build DaVinci plugin (macOS)" → Artifacts).
2. Abra o .dmg e dê dois cliques em **Instalar.command**
   (se o macOS bloquear: botão direito → Abrir).
3. Abra o DaVinci Resolve → Preferences → System → Audio Plugins e confirme o plugin.
4. Na timeline, arraste **AM Music Fix** (Audio FX → VST3/AU) para o clipe ou faixa de música.

## Build manual

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_ARCHITECTURES="arm64;x86_64"
cmake --build build --config Release
```

## Observações honestas

- Os valores numéricos foram extraídos diretamente do XML do `.prfpset` (parâmetros
  normalizados convertidos para Hz/dB). O mapeamento do Lowpass (20–20000 Hz linear)
  é inferido — o Mastering usa essa mesma escala e foi conferido contra os valores
  reais embutidos no preset.
- Lowpass e EQ são filtros biquad padrão. Reverb, Widener, Exciter e Loudness Maximizer
  são algoritmos proprietários da Adobe (vindos do Audition); aqui eles são reproduzidos
  com DSP equivalente, então o som fica muito próximo, mas não é bit-a-bit idêntico.
- O plugin não é assinado/notarizado pela Apple; o `Instalar.command` remove a quarentena.
- Usa JUCE 8 (licença AGPLv3 para uso não comercial / open source).
