#!/bin/bash
# Instala o AM Music Fix (VST3 + AU) para DaVinci Resolve.
set -e
DIR="$(cd "$(dirname "$0")" && pwd)"
echo "Instalando AM Music Fix..."
mkdir -p "$HOME/Library/Audio/Plug-Ins/VST3" "$HOME/Library/Audio/Plug-Ins/Components"
rm -rf "$HOME/Library/Audio/Plug-Ins/VST3/AM Music Fix.vst3" "$HOME/Library/Audio/Plug-Ins/Components/AM Music Fix.component"
cp -R "$DIR/AM Music Fix.vst3" "$HOME/Library/Audio/Plug-Ins/VST3/"
cp -R "$DIR/AM Music Fix.component" "$HOME/Library/Audio/Plug-Ins/Components/"
# Plugin não é notarizado pela Apple: remove a quarentena para o Resolve conseguir carregar.
xattr -dr com.apple.quarantine "$HOME/Library/Audio/Plug-Ins/VST3/AM Music Fix.vst3" 2>/dev/null || true
xattr -dr com.apple.quarantine "$HOME/Library/Audio/Plug-Ins/Components/AM Music Fix.component" 2>/dev/null || true
killall -9 AudioComponentRegistrar 2>/dev/null || true
echo ""
echo "Pronto! Abra (ou reinicie) o DaVinci Resolve."
echo "Em Preferences > System > Audio Plugins, confirme que o AM Music Fix está ativo."
read -n 1 -s -r -p "Pressione qualquer tecla para fechar."
