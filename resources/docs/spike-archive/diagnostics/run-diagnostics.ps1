# run-diagnostics.ps1
#
# Answers three questions about the MinGW g++ toolchain, for the lesson runner's Backtrace option:
#   1. Does std::stacktrace show function names when an exception is thrown?
#   2. Does -fsanitize=undefined catch signed overflow at run time?
#   3. Does -fsanitize=address link, and does it catch a heap overflow?
#
# Each test is compiled (trying a couple of flag sets where we aren't sure which one is needed), run, and its output
# checked for the expected text. The script reports PASS or FAIL for each, and which flags worked.
#
# Run from this folder with:
#   powershell -ExecutionPolicy Bypass -File .\run-diagnostics.ps1

# Continue, not Stop: Windows PowerShell treats anything a native program writes to stderr as an error, and the
# compiler's warnings and sanitizer reports both go to stderr.
$ErrorActionPreference = "Continue"
$here = $PSScriptRoot
$out = Join-Path $here "build"
New-Item -ItemType Directory -Force $out | Out-Null

if (-not (Get-Command g++ -ErrorAction SilentlyContinue)) {
    Write-Host "g++ isn't on PATH. Open the MSYS2 UCRT64 shell, or add its bin folder to PATH, then try again." -ForegroundColor Red
    exit 1
}
$version = (& g++ --version 2>&1 | Select-Object -First 1)
Write-Host "Using $version"
Write-Host ""

function Invoke-Tool([string]$program, [string[]]$arguments) {
    $text = (& $program @arguments 2>&1 | Out-String)
    return [pscustomobject]@{ Code = $LASTEXITCODE; Text = $text }
}

# Tries each flag set in turn, and returns the first one that compiles, or $null.
function Build-Test([string]$name, [string]$source, $flagSets) {
    $exe = Join-Path $out "$name.exe"
    foreach ($flags in $flagSets) {
        $compile = Invoke-Tool "g++" (@("-o", $exe, (Join-Path $here $source)) + @($flags))
        if ($compile.Code -eq 0) {
            return [pscustomobject]@{ Exe = $exe; Flags = ($flags -join " "); Error = $null }
        }
        $lastError = $compile.Text
    }
    return [pscustomobject]@{ Exe = $null; Flags = $null; Error = $lastError }
}

function Show-Result([string]$title, [bool]$passed, [string]$detail) {
    $label = if ($passed) { "PASS" } else { "FAIL" }
    $color = if ($passed) { "Green" } else { "Red" }
    Write-Host ("[{0}] {1}" -f $label, $title) -ForegroundColor $color
    if ($detail) { Write-Host "       $detail" }
    Write-Host ""
}

function Show-Snippet([string]$text) {
    $lines = $text -split "`r?`n" | Where-Object { $_.Trim() -ne "" } | Select-Object -First 15
    foreach ($line in $lines) { Write-Host "       | $line" }
    Write-Host ""
}

# Test 1: std::stacktrace ------------------------------------------------------------------------------------

Write-Host "== 1. std::stacktrace (function names in an exception's trace) ==" -ForegroundColor Cyan
$stackFlags = @(
    @("-std=c++23", "-g", "-Wall", "-Wextra"),
    @("-std=c++23", "-g", "-Wall", "-Wextra", "-lstdc++exp")
)
$build = Build-Test "stacktrace" "stacktrace.cpp" $stackFlags
if (-not $build.Exe) {
    Show-Result "stacktrace compiles" $false "Neither flag set compiled. The first error:"
    Show-Snippet $build.Error
} else {
    $run = Invoke-Tool $build.Exe @()
    $caught = $run.Text -match "Caught: boom from level3"
    $names = @("level3", "level2", "level1") | Where-Object { $run.Text -match $_ }
    $passed = $caught -and ($names.Count -eq 3)
    $detail = "compiled with: $($build.Flags)"
    Show-Result "stacktrace shows level1, level2, and level3" $passed $detail
    if (-not $passed) {
        Write-Host "       Output was:"
        Show-Snippet $run.Text
    }
}

# Test 2: UndefinedBehaviorSanitizer ---------------------------------------------------------------------

Write-Host "== 2. UndefinedBehaviorSanitizer (signed overflow) ==" -ForegroundColor Cyan
$ubsanFlags = ,@("-std=c++23", "-g", "-fsanitize=undefined", "-fno-sanitize-recover=undefined")
$build = Build-Test "ubsan" "ubsan.cpp" $ubsanFlags
if (-not $build.Exe) {
    Show-Result "ubsan compiles" $false "The compiler rejected the flags. The first error:"
    Show-Snippet $build.Error
} else {
    $run = Invoke-Tool $build.Exe @()
    $passed = ($run.Text -match "runtime error") -and ($run.Text -match "signed integer overflow")
    Show-Result "ubsan reports the signed overflow" $passed "compiled with: $($build.Flags)"
    if (-not $passed) {
        Write-Host "       Output was:"
        Show-Snippet $run.Text
    }
}

# Test 3: AddressSanitizer -------------------------------------------------------------------------------

Write-Host "== 3. AddressSanitizer (heap overflow) ==" -ForegroundColor Cyan
$asanFlags = ,@("-std=c++23", "-g", "-fsanitize=address")
$build = Build-Test "asan" "asan.cpp" $asanFlags
if (-not $build.Exe) {
    Show-Result "asan links" $false "The compiler or linker rejected -fsanitize=address. The first error:"
    Show-Snippet $build.Error
} else {
    $run = Invoke-Tool $build.Exe @()
    $passed = ($run.Text -match "AddressSanitizer") -and ($run.Text -match "heap-buffer-overflow")
    Show-Result "asan reports the heap overflow" $passed "compiled with: $($build.Flags)"
    if (-not $passed) {
        Write-Host "       Output was:"
        Show-Snippet $run.Text
    }
}

Write-Host "Done. Send me the whole output above, and I'll pick the flags for the runner from it." -ForegroundColor Green
