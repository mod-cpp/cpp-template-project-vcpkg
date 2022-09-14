winget install -e --id Git.Git
# Based on gist by @robotdad : https://gist.github.com/robotdad/83041ccfe1bea895ffa0739192771732
winget install Microsoft.VisualStudio.2022.Community --silent --override "--wait --quiet --add ProductLang En-us --add Microsoft.VisualStudio.Workload.NativeDesktop --includeRecommended"
winget install -e --id Kitware.CMake
winget install -e --id Microsoft.VisualStudioCode

Write-Host -Foreground green "C++ template development environment install done"
