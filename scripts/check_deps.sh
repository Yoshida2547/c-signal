#!/bin/bash

# List your required libraries or packages here
REQUIRED_PKGS=("libsndfile1-dev" "gcc" "make")

MISSING=()

echo "🔍 Checking for required packages..."

for pkg in "${REQUIRED_PKGS[@]}"; do
    # First try pkg-config (common for libraries like libsndfile)
    if pkg-config --exists "$pkg"; then
        echo "✅ Found (via pkg-config): $pkg"
    # Then try dpkg-query (for system packages on Debian/Ubuntu)
    elif dpkg -s "$pkg" &> /dev/null; then
        echo "✅ Found (via dpkg): $pkg"
    # Fallback: try which for binaries like gcc or make
    elif which "$pkg" &> /dev/null; then
        echo "✅ Found (via which): $pkg"
    else
        echo "❌ Missing: $pkg"
        MISSING+=("$pkg")
    fi
done

if [ ${#MISSING[@]} -ne 0 ]; then
    echo ""
    echo "⚠️ Missing packages:"
    for pkg in "${MISSING[@]}"; do
        echo "   - $pkg"
    done
    echo ""
    echo "💡 On Debian/Ubuntu, you can install them with:"
    echo "   sudo apt install ${MISSING[*]}"
    exit 1
else
    echo "🎉 All dependencies are satisfied!"
fi
