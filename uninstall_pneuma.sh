#!/bin/bash

# Complete uninstall script for Pneuma
# This removes the app from desktop, app drawer, and cleans all files

echo "═══════════════════════════════════════════════════════════"
echo "                 REMOVING PNEUMA"
echo "═══════════════════════════════════════════════════════════"
echo ""

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

# 1. Remove desktop launcher
echo -e "${YELLOW}→ Removing desktop launcher...${NC}"
if [ -f "$HOME/Desktop/pneuma.desktop" ]; then
    rm -f "$HOME/Desktop/pneuma.desktop"
    echo -e "${GREEN}  ✓ Removed desktop launcher${NC}"
else
    echo "  ✗ Desktop launcher not found"
fi

# Remove any desktop symlinks
if [ -L "$HOME/Desktop/pneuma" ]; then
    rm -f "$HOME/Desktop/pneuma"
    echo -e "${GREEN}  ✓ Removed desktop symlink${NC}"
fi

# 2. Remove from app drawer (applications menu)
echo -e "${YELLOW}→ Removing from applications menu...${NC}"
if [ -f "$HOME/.local/share/applications/pneuma.desktop" ]; then
    rm -f "$HOME/.local/share/applications/pneuma.desktop"
    echo -e "${GREEN}  ✓ Removed app drawer entry${NC}"
else
    echo "  ✗ App drawer entry not found"
fi

# Also check system-wide location
if [ -f "/usr/share/applications/pneuma.desktop" ]; then
    sudo rm -f "/usr/share/applications/pneuma.desktop"
    echo -e "${GREEN}  ✓ Removed system-wide desktop entry${NC}"
fi

# 3. Remove configuration files
echo -e "${YELLOW}→ Removing configuration files...${NC}"
if [ -f "$HOME/.pneuma_mode" ]; then
    rm -f "$HOME/.pneuma_mode"
    echo -e "${GREEN}  ✓ Removed mode configuration${NC}"
fi
 

# Also check for older locations
if [ -f "$HOME/sis/pneuma" ]; then
    rm -f "$HOME/sis/pneuma"
    echo -e "${GREEN}  ✓ Removed old binary from sis/${NC}"
fi

# 5. Remove icon files (optional - keeps your logo)
echo -e "${YELLOW}→ Icon files...${NC}"
echo "  (Keeping your logo.png in ~/pneuma/ - delete manually if desired)"

# 6. Update desktop database
echo -e "${YELLOW}→ Updating desktop database...${NC}"
update-desktop-database "$HOME/.local/share/applications/" 2>/dev/null
echo -e "${GREEN}  ✓ Desktop database updated${NC}"

# 7. Force refresh desktop
echo -e "${YELLOW}→ Refreshing desktop...${NC}"
# For XFCE
if command -v xfdesktop &> /dev/null; then
    xfdesktop --reload 2>/dev/null
    echo -e "${GREEN}  ✓ XFCE desktop refreshed${NC}"
fi

# For GNOME
if command -v gnome-shell &> /dev/null; then
    echo "  (GNOME will refresh automatically)"
fi

echo ""
echo "═══════════════════════════════════════════════════════════"
echo -e "${GREEN}✅ Pneuma has been completely removed from your system${NC}"
echo "═══════════════════════════════════════════════════════════"
echo ""
echo "Removed:"
echo "  • Desktop launcher"
echo "  • App drawer entry"
echo "  • Configuration files"
echo "  • Application binary"
echo ""
echo "Your images and logo are still in ~/pneuma/ (delete manually if wanted)"
echo ""
echo "To reinstall, run: ~/pneuma/create_launchers.sh (after compiling)"
