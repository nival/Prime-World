$dataPath = "../Data"
$scriptPath = $PSScriptRoot

cd $dataPath
ls * -Recurse -File |
        Resolve-Path -Relative |
        ForEach-Object {$_ -replace "^\.", "" -replace "\\","/"} |
        Out-File "$scriptPath\all-files.txt" -Encoding utf8
cd $scriptPath