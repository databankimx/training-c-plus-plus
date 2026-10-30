# fetch-json.ps1
#
# Downloads the newest nlohmann/json release into resources\vendor\nlohmann-json:
#   json.hpp     the single-header library (MIT)
#   LICENSE.MIT  its license, which travels with the header
#   VERSION.txt  the release tag, so we know exactly what we vendored
#
# Run from this folder with:
#   powershell -ExecutionPolicy Bypass -File .\fetch-json.ps1

$ErrorActionPreference = "Stop"
$target = $PSScriptRoot

# GitHub's API returns the newest release. Its assets include the single header.
$headers = @{ "User-Agent" = "training-cpp-setup" }
$release = Invoke-RestMethod "https://api.github.com/repos/nlohmann/json/releases/latest" -Headers $headers
$tag = $release.tag_name
Write-Host "Newest nlohmann/json release: $tag"

$asset = $release.assets | Where-Object { $_.name -eq "json.hpp" } | Select-Object -First 1
if (-not $asset) {
    throw "Release $tag doesn't have a json.hpp asset. Check https://github.com/nlohmann/json/releases for the single-header file."
}
Invoke-WebRequest $asset.browser_download_url -OutFile (Join-Path $target "json.hpp") -Headers $headers

$license = "https://raw.githubusercontent.com/nlohmann/json/$tag/LICENSE.MIT"
Invoke-WebRequest $license -OutFile (Join-Path $target "LICENSE.MIT") -Headers $headers

Set-Content -Path (Join-Path $target "VERSION.txt") -Value "nlohmann/json $tag (single header, MIT)"

if ((Get-Item (Join-Path $target "json.hpp")).Length -lt 100000) {
    throw "json.hpp is smaller than expected. The download probably failed."
}
Write-Host "Vendored nlohmann/json $tag into $target"
