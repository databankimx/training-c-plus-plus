# build.ps1
#
# Builds the WebView2 spike with g++, and copies the loader DLL next to the program.
# Needs g++ 14 or later (for C++23), and the SDK from fetch-webview2.ps1.
#
# Run from this folder with:
#   powershell -ExecutionPolicy Bypass -File .\build.ps1

$ErrorActionPreference = "Stop"
$sdk = Join-Path $PSScriptRoot "sdk"
$out = Join-Path $PSScriptRoot "build"

if (-not (Get-Command g++ -ErrorAction SilentlyContinue)) {
    throw "g++ isn't on PATH. Open the MSYS2 UCRT64 shell, or add its bin folder to PATH, then try again."
}

$versionLine = (& g++ --version | Select-Object -First 1)
if ($versionLine -notmatch "(\d+)\.\d+") {
    throw "Couldn't read the g++ version from: $versionLine"
}
$major = [int]$Matches[1]
if ($major -lt 14) {
    throw "g++ $major was found, but this project needs g++ 14 or later for C++23. Update MSYS2 (pacman -Syu) and install mingw-w64-ucrt-x86_64-gcc."
}
Write-Host "Using $versionLine"

$header = Join-Path $sdk "build\native\include\WebView2.h"
if (-not (Test-Path $header)) {
    throw "The WebView2 SDK isn't in $sdk. Run fetch-webview2.ps1 first."
}

New-Item -ItemType Directory -Force $out | Out-Null

# -municode and -mwindows make this a Windows GUI program with a wWinMain entry point, so no console window opens.
# -Wall -Wextra -Wpedantic keep the build warnings-clean, as the course requires.
$source = Join-Path $PSScriptRoot "src\main.cpp"
$exe = Join-Path $out "webview2-spike.exe"
& g++ -std=c++23 -municode -mwindows -DUNICODE -D_UNICODE -Wall -Wextra -Wpedantic `
    -isystem (Join-Path $sdk "build\native\include") `
    $source -o $exe -lole32 -luuid
if ($LASTEXITCODE -ne 0) {
    throw "g++ failed. The errors above say what went wrong."
}

# The program loads WebView2Loader.dll at runtime, so it has to sit next to the executable.
Copy-Item (Join-Path $sdk "build\native\x64\WebView2Loader.dll") $out -Force

Write-Host ""
Write-Host "Built $exe" -ForegroundColor Green
Write-Host "Run it with: .\build\webview2-spike.exe"
