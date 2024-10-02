$python = "python.exe"
$script = "D:\Projects\Prime-World\pw\branches\r1117\Tools\process_data_pile.py"

$infiles = "data01.txt,data02.txt,data03.txt,data04.txt,data05.txt,data06.txt"
$exfiles = "ignore_these_dirs"

$dir = "..\Packs"
$cclist = "files.list"
$packdir = "..\Data"
$filelists = "localisation_files.txt"
$allfiles = "true"

.$python $script --dir $dir --infiles $infiles --exfiles $exfiles --cclist $cclist --packdir $packdir --filelists $filelists #--allfiles $allfiles