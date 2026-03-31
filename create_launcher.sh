#!/bin/bash

# universal launcher for pneuma
clear

# colors
red='\033[0;31m'
green='\033[0;32m'
yellow='\033[1;33m'
blue='\033[0;34m'
cyan='\033[0;36m'
magenta='\033[0;35m'
nc='\033[0m' # no color

# set paths
app_path="$HOME/pneuma/pneuma"
icon_path="$HOME/pneuma/logo.png"

echo ""
echo -e "${cyan}╔═══════════════════════════════════════════════════════════╗${nc}"
echo -e "${cyan}║${magenta}          p n e u m a   l a u n c h e r                 ${cyan}   ║${nc}"
echo -e "${cyan}╚═══════════════════════════════════════════════════════════╝${nc}"
echo ""

# check if files exist
if [ ! -f "$app_path" ]; then
    echo -e "${red}[error]${nc} pneuma binary not found at $app_path"
    exit 1
fi

if [ ! -f "$icon_path" ]; then
    echo -e "${red}[error]${nc} logo.png not found at $icon_path"
    exit 1
fi

echo -e "${green}[✓]${nc} binary found: $app_path"
echo -e "${green}[✓]${nc} icon found: $icon_path"
echo ""

echo -e "${blue}[i]${nc} creating launchers for pneuma..."
echo ""

# 1. app drawer launcher
echo -e "${yellow}[1/3]${nc} creating app drawer launcher..."
mkdir -p "$HOME/.local/share/applications"

cat > "$HOME/.local/share/applications/pneuma.desktop" << desktop_eof
[Desktop Entry]
Version=1.0
Type=Application
Name=pneuma
Comment=dual mode quote app with death note and boondocks themes
Exec=$app_path
Icon=$icon_path
Terminal=false
StartupNotify=true
Categories=Utility;
desktop_eof

chmod 644 "$HOME/.local/share/applications/pneuma.desktop"
echo -e "${green}[✓]${nc} app drawer launcher created"

# 2. desktop launcher
echo -e "${yellow}[2/3]${nc} creating desktop launcher..."
mkdir -p "$HOME/Desktop"

cat > "$HOME/Desktop/pneuma.desktop" << desktop_eof
[Desktop Entry]
Version=1.0
Type=Application
Name=pneuma
Exec=$app_path
Icon=$icon_path
Terminal=false
Categories=Utility;
desktop_eof

chmod +x "$HOME/Desktop/pneuma.desktop"

# mark as trusted
if command -v gio &> /dev/null; then
    gio set "$HOME/Desktop/pneuma.desktop" metadata::trusted true
    echo -e "${green}[✓]${nc} desktop launcher created (trusted)"
else
    echo -e "${green}[✓]${nc} desktop launcher created"
fi

# 3. update desktop database
echo -e "${yellow}[3/3]${nc} updating desktop database..."
update-desktop-database "$HOME/.local/share/applications/" 2>/dev/null

echo ""
echo -e "${cyan}╔═══════════════════════════════════════════════════════════════════╗${nc}"
echo -e "${cyan}║${green}adunyi, the launchers have been created successfully               ${cyan}║${nc}"
echo -e "${cyan}╚═══════════════════════════════════════════════════════════════════╝${nc}"
echo ""
echo -e "${cyan}app:${nc}     $app_path"
echo -e "${cyan}icon:${nc}    $icon_path"
echo ""
echo -e "${cyan}to launch:${nc}"
echo -e "  ${green}•${nc} sissy, you'll find the app in applications menu → type 'pneuma'"
echo -e "  ${green}•${nc} sissy, double-click the pneuma icon on desktop"
echo -e "  ${green}•${nc} run: $app_path"
echo ""
echo -e "${yellow}note:${nc} hey sissy, if the app doesn't appear in the menu, log out and log back in"
echo ""
echo -e "${yellow}note:${nc} "
echo "just wanted to say i love you, my sweet sister. 💕 my pneuma forever. 🌬️✨ adunyi, you're the best sister anyone could ask for. 🥹👑 love you always! ❤️"
echo ""
echo -e "${magenta}✨ forever and always, your sibling ✨${nc}"
echo ""
echo -e "${magenta}✨ love $USER✨${nc}"
echo ""
#!/bin/bash

# universal launcher for pneuma
clear

# colors
red='\033[0;31m'
green='\033[0;32m'
yellow='\033[1;33m'
blue='\033[0;34m'
cyan='\033[0;36m'
magenta='\033[0;35m'
nc='\033[0m' # no color

# set paths
app_path="$HOME/pneuma/pneuma"
icon_path="$HOME/pneuma/logo.png"

echo ""
echo -e "${cyan}╔═══════════════════════════════════════════════════════════╗${nc}"
echo -e "${cyan}║${magenta}          p n e u m a   l a u n c h e r                 ${cyan}   ║${nc}"
echo -e "${cyan}╚═══════════════════════════════════════════════════════════╝${nc}"
echo ""

# check if files exist
if [ ! -f "$app_path" ]; then
    echo -e "${red}[error]${nc} pneuma binary not found at $app_path"
    exit 1
fi

if [ ! -f "$icon_path" ]; then
    echo -e "${red}[error]${nc} logo.png not found at $icon_path"
    exit 1
fi

echo -e "${green}[✓]${nc} binary found: $app_path"
echo -e "${green}[✓]${nc} icon found: $icon_path"
echo ""

echo -e "${blue}[i]${nc} creating launchers for pneuma..."
echo ""

# 1. app drawer launcher
echo -e "${yellow}[1/3]${nc} creating app drawer launcher..."
mkdir -p "$HOME/.local/share/applications"

cat > "$HOME/.local/share/applications/pneuma.desktop" << desktop_eof
[Desktop Entry]
Version=1.0
Type=Application
Name=pneuma
Comment=dual mode quote app with death note and boondocks themes
Exec=$app_path
Icon=$icon_path
Terminal=false
StartupNotify=true
Categories=Utility;
desktop_eof

chmod 644 "$HOME/.local/share/applications/pneuma.desktop"
echo -e "${green}[✓]${nc} app drawer launcher created"

# 2. desktop launcher
echo -e "${yellow}[2/3]${nc} creating desktop launcher..."
mkdir -p "$HOME/Desktop"

cat > "$HOME/Desktop/pneuma.desktop" << desktop_eof
[Desktop Entry]
Version=1.0
Type=Application
Name=pneuma
Exec=$app_path
Icon=$icon_path
Terminal=false
Categories=Utility;
desktop_eof

chmod +x "$HOME/Desktop/pneuma.desktop"

# mark as trusted
if command -v gio &> /dev/null; then
    gio set "$HOME/Desktop/pneuma.desktop" metadata::trusted true
    echo -e "${green}[✓]${nc} desktop launcher created (trusted)"
else
    echo -e "${green}[✓]${nc} desktop launcher created"
fi

# 3. update desktop database
echo -e "${yellow}[3/3]${nc} updating desktop database..."
update-desktop-database "$HOME/.local/share/applications/" 2>/dev/null

echo ""
echo -e "${cyan}╔═══════════════════════════════════════════════════════════════════╗${nc}"
echo -e "${cyan}║${green}adunyi, the launchers have been created successfully               ${cyan}║${nc}"
echo -e "${cyan}╚═══════════════════════════════════════════════════════════════════╝${nc}"
echo ""
echo -e "${cyan}app:${nc}     $app_path"
echo -e "${cyan}icon:${nc}    $icon_path"
echo ""
echo -e "${cyan}to launch:${nc}"
echo -e "  ${green}•${nc} sissy, you'll find the app in applications menu → type 'pneuma'"
echo -e "  ${green}•${nc} sissy, double-click the pneuma icon on desktop"
echo -e "  ${green}•${nc} run: $app_path"
echo ""
echo -e "${yellow}note:${nc} hey sissy, if the app doesn't appear in the menu, log out and log back in"
echo ""
echo -e "${yellow}note:${nc} "
echo "just wanted to say i love you, my sweet sister. 💕 my pneuma forever. 🌬️✨ adunyi, you're the best sister anyone could ask for. 🥹👑 love you always! ❤️"
echo ""
echo -e "${magenta}✨ forever and always, your sibling ✨${nc}"
echo ""
echo -e "${magenta}✨ love $USER✨${nc}"
echo ""
echo -e "${magenta}✨ love pneuma & me✨${nc}"
echo ""
