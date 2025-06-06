#!/usr/bin/env pwsh
<#
.SYNOPSIS
    Script to build asymptote
.DESCRIPTION
    Builds asymptote installer file.
    This script uses asymptote source directory. If building fails, try removing cmake-build-msvc/release directory
.PARAMETER Version
    Specifies Asymptote version to build. If not given, will automatically determine version from configure.ac.
#>
param(
    [AllowEmptyString()]
    [Parameter()]
    [string]$Version
)
$ErrorActionPreference = "Stop"
$PSNativeCommandUseErrorActionPreference = $true

$usageString="Usage: $PSCommandPath -Version <version>"

$asymptoteRoot="$(Split-Path -Parent $PSCommandPath)/.."

if (-Not (Test-Path -PathType container $asymptoteRoot))
{
    Write-Error "No asymptote root found. Exiting."
    Break
}

# ----------------------------------------------------
# checking documentation files

if ($env:ASYMPTOTE_BUILD_SHARED_DIRECTORY)
{
    $extfilesRoot="$env:ASYMPTOTE_BUILD_SHARED_DIRECTORY/asydoc"
}
else
{
    $extfilesRoot = "asydoc"
}

$requiredDocumentationFiles=@(
    "asymptote.sty"
    "asymptote.pdf"
    "asy-latex.pdf"
    "CAD.pdf"
    "TeXShopAndAsymptote.pdf"
    "asyRefCard.pdf"
    "asy-keywords.el"
)

$hasDocFiles=$true
foreach ($requiredDocFile in $requiredDocumentationFiles) {
    if (-Not (Test-Path -PathType leaf "$extfilesRoot/$requiredDocFile")) {
        $hasDocFiles=$false
        Write-Error "$requiredDocFile not found.
Please ensure $requiredDocFile is available in $extfilesRoot directory"
    }
}

if (-Not $hasDocFiles) {
    Write-Error "Documentation file(s) are not present in $extFilesRoot directory. Will not build asymptote."
    Break
}

# ----------------------------------------------------
# copy documentation files to asymptote directory
$localAsyDocRoot="$asymptoteRoot/asydoc"

if (-Not (Test-Path -Type Container $localAsyDocRoot))
{
    New-Item -ItemType Directory -Path $localAsyDocRoot -Force
}

foreach ($requiredDocFile in $requiredDocumentationFiles)
{
    $sourceDocFile="$extfilesRoot/$requiredDocFile"
    $destDocFile="$localAsyDocRoot/$requiredDocFile"

    $docFileHash=Get-FileHash -Algorithm SHA256 -Path $sourceDocFile
    if (Test-Path -Type Leaf "$destDocFile")
    {
        $asyDocFilehash=Get-FileHash -Algorithm SHA256 -Path $destDocFile
        if ($docFileHash.Hash -eq $asyDocFilehash.Hash)
        {
            Write-Host "File $requiredDocFile exists in asydoc directory; not copying"
            continue
        }
    }

    Write-Host "Copying $sourceDocFile to $destDocFile"
    Copy-Item -Force $sourceDocFile -Destination $destDocFile
}

# ----------------------------------------------------
# tools cache
$toolscacheRoot="tools-cache"
New-Item -ItemType Directory -Path $toolscacheRoot -Force

$useToolsCacheVcpkg=$false

# tools cache variables
$vcpkgSha256="5e5d0e1cd7785623065e77eff011afdeec1a3574"

# vcpkg
if (-Not $env:VCPKG_ROOT)
{
    $vcpkgToolsCacheLoc = "$toolscacheRoot/vcpkg"
    Write-Host "VCPKG_ROOT Not found, checking for $vcpkgToolsCacheLoc"
    if (-Not (Test-Path -PathType Container $vcpkgToolsCacheLoc))
    {
        git clone https://github.com/microsoft/vcpkg.git "$vcpkgToolsCacheLoc"
    }
    else
    {
        Write-Host "vcpkg directory found"
    }
    git -C $vcpkgToolsCacheLoc fetch
    git -C $vcpkgToolsCacheLoc reset --hard $vcpkgSha256

    if (-Not (Test-Path $vcpkgToolsCacheLoc/vcpkg.exe))
    {
        Push-Location $vcpkgToolsCacheLoc
        & ./bootstrap-vcpkg.bat
        Pop-Location
    }

    $useToolsCacheVcpkg=true
}
else
{
    Write-Host "Using VCPKG_ROOT at $($env:VCPKG_ROOT)"
}

# ------------------------------------------------------
# checking for NSIS
$makeNsisLoc=$null

# checking for downloaded nsis
if ($null -eq $makeNsisLoc)
{
    $nsisToolsCacheRoot="$toolscacheRoot/nsis"
    $downloadedNsis = "$nsisToolsCacheRoot/makensis.exe"
    if (Test-Path -PathType leaf $downloadedNsis)
    {
        Write-Host "Found downloaded NSIS at $downloadedNsis"
        $makeNsisLoc=$downloadedNsis
    }
}

# checking registry & install location
if ($null -eq $makeNsisLoc)
{
    $nsisInstallEntry = Get-ItemProperty `
    -Path HKLM:\SOFTWARE\WOW6432Node\Microsoft\Windows\CurrentVersion\Uninstall\NSIS `
    -Name InstallLocation `
    -ErrorAction SilentlyContinue

    if ($null -ne $nsisInstallEntry)
    {
        # entry found for registry
        $nsisTestPath = "$( $nsisInstallEntry.InstallLocation )/makensis.exe"
        if (Test-Path -PathType leaf $nsisTestPath)
        {
            Write-Host "Found installed NSIS. Using NSIS at $nsisTestPath"
            $makeNsisLoc = $nsisTestPath
        }
    }
}

# check in tools-cache/nsis
if ($null -Eq $makeNsisLoc)
{
    $nsisPathExec = Get-Command makensis -ErrorAction ignore
    if ($null -Ne $nsisPathExec)
    {
        Write-Host "Found NSIS in PATH at $($makeNsisLoc.Path)".
        $makeNsisLoc=$nsisPathExec.Path
    }
}

# nsis not found
if ($null -eq $makeNsisLoc)
{
    Write-Error "Cannot find NSIS. Please either
(1, Recommended) Install NSIS from https://sourceforge.net/projects/nsis/
(2) Download NSIS ZIP and extract the files to $toolscacheRoot so that $nsisToolsCacheRoot/makensis.exe
    is available
"
    Break
}

# ------------------------------------------------
# python
$pyVenvLocation="$toolscacheRoot/pyxasy"
$pyXasyActivateScript="$pyVenvLocation/Scripts/activate.ps1"
if (-Not (Test-Path -PathType leaf $pyXasyActivateScript))
{
    python -m virtualenv -p C:\\Users\\jamievl\\AppData\\Local\\Programs\\Python\\Python39\\python.exe $pyVenvLocation
}

# ----------------------------------------------------
# determine version, if not given in arguments

if (0 -eq $Version.Length) {
    Write-Host "Version not given; will try to determine version"
    Push-Location $asymptoteRoot
    $Version=python generate_asy_ver_info.py --version-for-release
    if (0 -ne $LASTEXITCODE) {
        Write-Error $usageString
        Write-Error "Cannot automatically determine release asymptote version. Please specify the version manually"
        Pop-Location
        Break
    }
    Pop-Location
    Write-Host "Asymptote version is $Version"
}

# ----------------------------------------------------
# build GUI
& $pyXasyActivateScript
Push-Location $asymptoteRoot/GUI
& python -m pip install -r requirements.txt
& python buildtool.py build --version-override=$Version
Pop-Location


# ----------------------------------------------------

function buildAsy($preset, $cfgDir) {
    # build C++ side
    Import-VisualStudioVars -Architecture x64
    Push-EnvironmentBlock
    $env:ASY_VERSION_OVERRIDE = $Version
    if ($useToolsCacheVcpkg)
    {
        $env:VCPKG_ROOT = $vcpkgToolsCacheLoc
    }

    # ------------------------------------
    # clear CMakeCache.txt
    if (Test-Path -Type Leaf "$asymptoteRoot/$cfgDir/CMakeCache.txt")
    {
        Remove-Item -Force "$asymptoteRoot/$cfgDir/CMakeCache.txt"
    }

    # ------------------------------------
    # configure
    Push-Location $asymptoteRoot
    cmake --preset $preset
    Pop-Location

    # ------------------------------------
    # build
    cmake --build $asymptoteRoot/$cfgDir --target asy-pre-nsis-targets -j
    Pop-EnvironmentBlock  # ASY_VERSION_OVERRIDE, VCPKG_ROOT
    Pop-EnvironmentBlock  # Visual studio vars
    # install to pre-installation root
}

buildAsy msvc/release/with-external-doc-files cmake-build-msvc/release
cmake --install $asymptoteRoot/cmake-build-msvc/release --component asy-pre-nsis
copy $asymptoteRoot/cmake-build-msvc/release/base/version.asy base
# ------------------------------------------------------
# Generate NSIS installer file
& $asymptoteRoot/cmake-install-w32-nsis-release/build-asy-installer.ps1 "$makeNsisLoc"

$asySetupName="asymptote-$Version-setup.exe"
$asySetupFile="$asymptoteRoot/cmake-install-w32-nsis-release/$asySetupName"

if (Test-Path -PathType leaf "$asySetupName")
{
    Write-Host "Found old setup file. Will delete the file."
    Remove-Item -Force "asymptote-$Version-setup.exe"
}

if (Test-Path -PathType leaf $asySetupFile)
{
    # ---------------------------------------
    # copy setup file to shared directory, if given
    if ($env:ASYMPTOTE_BUILD_SHARED_DIRECTORY)
    {
        Write-Host "Copying setup file to shared directory."
        Copy-Item -Force $asySetupFile "$env:ASYMPTOTE_BUILD_SHARED_DIRECTORY/$asySetupName"
    }

    Move-Item $asySetupFile . -Force
}
else
{
    Write-Error "Asymptote setup file not built."
    Break
}

# ------------------------------------------------------
# building for CTAN

buildAsy msvc/release/with-external-doc-files/with-ctan cmake-build-msvc/release

if ($env:ASYMPTOTE_BUILD_SHARED_DIRECTORY)
{
    Write-Output "Using shared build directory at $ASYMPTOTE_BUILD_SHARED_DIRECTORY for CTAN output"
    $ctanOutputDir = "$env:ASYMPTOTE_BUILD_SHARED_DIRECTORY/CTAN"
}
else
{
    Write-Output "No shared directory specified. Using CTAN directory at top-level"
    $ctanOutputDir = "CTAN"
}

New-Item -ItemType Directory -Path "$ctanOutputDir" -Force
New-Item -ItemType Directory -Path "$ctanOutputDir/dll" -Force
Get-ChildItem "$asymptoteRoot/cmake-install-w32-nsis-release/build-$Version/" `
    -Filter "*.dll" | Copy-Item -Force -Destination "$ctanOutputDir/dll"
Copy-Item $asymptoteRoot/cmake-build-msvc/release/asy.exe -Force -Destination "$ctanOutputDir/asy.exe"

Pop-Location  # asymptote
deactivate  # pyxasy build environment
