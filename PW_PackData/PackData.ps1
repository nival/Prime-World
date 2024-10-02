#
# !!! ВНИМАНИЕ. В пути к данному скрипту и пути к директории с игрой не должно быть пробелов !!! #
# !!! Необходимо дождаться завершения работы питоновского скрипта, так как он временно перемещает DDS файлы локализации в папку _processedFiles !!! #
#  


##### Настройки #####
# Путь к корневой директории игры
$gamePath = "D:\Projects\Prime-World\pw\branches\r1117"

# Путь к Python 2.7
$pythonPath = "C:\Python27\python.exe"

# Очищать папку out перед запуском
$clearOutBeforeStart = $true

# Копировать остальные файлы из папок Bin, Profiles (можно будет сразу запустить игру)
$copyOtherFiles = $true


##################################################################################################
$FilePileCompilerPath = "FilePileCompiler"
$processScript = "process_data_pile.py"

function log ($msg) { "$(Get-Date) | $msg" | Out-Host }
function createOutSubdirectory($outDir, $path) {
    New-Item -Path "out\$outDir\$path" -ItemType Directory -Force > $null
    log "Created: $path"
}

$currentDir = Get-Location
Set-Location $PSScriptRoot
$startTime = Get-Date

# Preparing directories
log "Preparing directories..."

$tempDir = if (Test-Path "temp") { Get-Item "temp" } else { New-Item "temp" -ItemType Directory }
$tempDir = $tempDir.FullName
Remove-Item "$PSScriptRoot\temp\*" -Recurse -Force

$outDir = "out-" + (Get-Date -Format "yyyyMMdd-HHmmss")
if ($clearOutBeforeStart) {
    Remove-Item "$PSScriptRoot\out\*" -Recurse -Force
}


createOutSubdirectory $outDir "Data\Audio"
createOutSubdirectory $outDir "Data\Localization\ru-RU"
createOutSubdirectory $outDir "Packs"

if ($copyOtherFiles) {
    createOutSubdirectory $outDir "Bin"
    createOutSubdirectory $outDir "Profiles"
}

$outDirPath = (Get-Item "out\$outDir").FullName


# Creating CCL
log "Creating cross checking file list..."

$types = Get-Content "$PSScriptRoot\$FilePileCompilerPath\types.txt"

Set-Location "$gamePath\Data"
Get-ChildItem  -Recurse -File -Include $types |
        Resolve-Path -Relative |
        ForEach-Object {$_ -replace "^\.", "" -replace "\\","/"} |
        Out-File "$PSScriptRoot\$FilePileCompilerPath\ccl.txt" -Encoding utf8
Set-Location $PSScriptRoot


# Starting Python script
log "Starting data process python script..."

Set-Location "$PSScriptRoot\$FilePileCompilerPath"
$dir = "..\temp"
$cclist = "ccl.txt"
$packdir = "$gamePath\Data"
$filelists = "localisation_files.txt"
$infiles = "data01.txt,data02.txt,data03.txt,data04.txt,data05.txt,data06.txt"
$exfiles = "ignore_these_dirs.txt"

.$pythonPath $processScript --dir $dir --infiles $infiles --exfiles $exfiles --cclist $cclist --packdir $packdir --filelists $filelists
Set-Location $PSScriptRoot


log "Moving localisation_files.pile pile file"
Move-Item "temp\localisation_files.pile" "$outDirPath\Data\Localization\ru-RU\"

log "Moving Pack pile files"
Move-Item "temp\data*.pile" "$outDirPath\Packs\"

log "Copying Audio: *.fsb, *.fev"
$excludeSounds = "*_DE*", "*_EN*", "*_FR*", "*_TR*"
Copy-Item "$gamePath\Data\Audio\*.fsb", "$gamePath\Data\Audio\*.fev"  -Exclude  $excludeSounds "$outDirPath\Data\Audio"


if ($copyOtherFiles) {
    log "Copying Other Files..."
    Copy-Item "$gamePath\Bin\*" "$outDirPath\Bin"  
    Copy-Item "$gamePath\Profiles\*" "$outDirPath\Profiles"
}


log "Created directories sizes:"
$createdDirs = Get-ChildItem "$outDirPath" -Directory
foreach ($dir in $createdDirs) {
    $size = (Get-ChildItem -Path $dir.FullName -Recurse -File | Measure-Object -Property Length -Sum).Sum
    $sizeMB = [math]::Round($size / 1MB, 2)  
    log "$($dir.Name) `t $sizeMB MB"
}


$endTime = Get-Date
$executionTime = $endTime - $startTime
$executionTimeInMinutes= [math]::Round($executionTime.TotalMinutes, 2)

Set-Location $currentDir
log "*** DONE in $executionTimeInMinutes min ***"