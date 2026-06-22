#!/usr/bin/env bash

set -e

APP_NAME="MyGame"
BUILD_DIR="."
APPDIR="${APP_NAME}.AppDir"
EXEC_NAME="game"

echo "===================================="
echo "📁 Criando AppDir"
echo "===================================="

rm -rf $APPDIR
mkdir -p $APPDIR

echo "📁 Copiando executável"

cp $BUILD_DIR/$EXEC_NAME $APPDIR/
chmod +x $APPDIR/$EXEC_NAME

echo "📁 Copiando assets (world + textures)"

cp -r world $APPDIR/
cp -r texture $APPDIR/

# Desktop file
cat > $APPDIR/$APP_NAME.desktop <<EOF
[Desktop Entry]
Name=$APP_NAME
Exec=$EXEC_NAME
Icon=$APP_NAME
Type=Application
Categories=Game;
EOF

# AppRun (IMPORTANTE: cd correto)
cat > $APPDIR/AppRun <<EOF
#!/bin/bash
HERE="\$(dirname "\$(readlink -f "\${0}")")"
cd "\$HERE"
exec "./$EXEC_NAME"
EOF

chmod +x $APPDIR/AppRun

echo "===================================="
echo "🖼️ Ícone"
echo "===================================="

if [ -f "icon.png" ]; then
    cp icon.png $APPDIR/MyGame.png
else
    echo "⚠️ Nenhum icon.png encontrado"
fi

echo "===================================="
echo "📦 linuxdeploy"
echo "===================================="

if [ ! -f linuxdeploy-x86_64.AppImage ]; then
    wget -q https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage
    chmod +x linuxdeploy-x86_64.AppImage
fi

echo "===================================="
echo "🚀 Gerando AppImage"
echo "===================================="
export NO_STRIP=1

./linuxdeploy-x86_64.AppImage \
    --appdir $APPDIR \
    --executable $APPDIR/$EXEC_NAME \
    --desktop-file $APPDIR/$APP_NAME.desktop \
    --icon-file $APPDIR/$APP_NAME.png \
    --output appimage \

echo "===================================="
echo "✅ Pronto!"
echo "===================================="