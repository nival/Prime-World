function exec-sql ($sql, $outfile) {
$sw = [System.Diagnostics.Stopwatch]::StartNew()
  # если файл с результатами существует, то скрипт повторно не выполняется
  if (test-path $outfile) { write 'found file ' $outfile }
  else {
    write 'executing query' $sql
    $outfile = $outfile.Replace('\', '\\')
    # коннект к серверу (подразумевает наличие pgpass.conf)
    psql -h $dbhost -p $dbport -d $dbname -U $dbuser -c "COPY ($sql) TO STDOUT CSV" > $outfile
    if (!$?) { 
      write 'psql failed'
      return
    }
    write 'created file ' $outfile
  }
write-host $sw.elapsed
$sw.stop()
}

function insert-to-excel ($worksheet, $cell, $str) {
  Add-Type -Assembly PresentationCore
  [Windows.Clipboard]::SetText($str, [Windows.TextDataFormat]'Text')
  $worksheet.range($cell.Address()).pasteSpecial(-4104) | out-null # xlPasteAll = -4104
}

function write-data-by-type ($csvfile, $ws, $col, $type) {
$sw = [System.Diagnostics.Stopwatch]::StartNew()
  write-host "writing type $type"
  $ws.range($ws.cells.item(1,$col),$ws.cells.item(2,$col+2)).font.bold = $true
  $ws.columns.item($col).columnwidth = 11
  $ws.columns.item($col+1).columnwidth = 13
  $ws.columns.item($col+1).HorizontalAlignment = -4152 # xlRight
  $ws.cells.item(2,$col+1).HorizontalAlignment = -4131 # xlLeft
  $ws.columns.item($col+2).columnwidth = 18
  
  $alldata = "Type $type`nauid`tip`ttime"
  get-content $csvfile |? { $_.split(',')[0] -eq $type } |% {
    $data = $_.split(',')
    $alldata = "$($alldata)`n$($data[2])`t$($data[4])`t$($data[1])"
  }
  insert-to-excel $ws $ws.cells.item(1,$col) $alldata
write-host $sw.elapsed
$sw.stop()
}

# ---------------------------------------------------------------------------------------
# start ---------------------------------------------------------------------------------
# ---------------------------------------------------------------------------------------

$exectime = [System.Diagnostics.Stopwatch]::StartNew()

Write-Host "`n`nstarted cheat-reporter"
$i = 0
$args |% { 
  write-host "args[$i] = '$_', $($_.gettype())"
  $i++
}

Write-Host args = $args

# соединение с БД
$dbhost = 'b489.SITE'
$dbport = 5432
$dbname = 'pw_analysis_oa'
$dbuser = 'postgres'

# дефалтовые значения
$starttime = (get-date).Date.AddDays(-1)
$endtime   = (get-date).Date.AddSeconds(-1)
$datesuffix = $starttime.ToString('yyyyMMdd')

if ($args.length -ge 2) {
  $starttime = [DateTime]$args[0]
  if (!$?) { exit 1 }
  $endtime   = [DateTime]$args[1]
  if (!$?) { exit 1 }
  
  if ($args.length -ge 3) {
    $datesuffix = $args[2]
  }
  else {
    $datesuffix = 'from-{0:yyyyMMdd-HHmm}-to-{1:yyyyMMdd-HHmm}' -f $starttime, $endtime
  }
}

$starttimestr = $starttime.ToString('yyyy-MM-dd HH:mm:ss')
$endtimestr   = $endtime.ToString('yyyy-MM-dd HH:mm:ss')
$startdh = $starttime.ToString('yyyyMMdd')
$enddh   = $endtime.ToString('yyyyMMdd')

# ---------------------------------------------------------------------------------------
# Запрос по всем данным по читам

$sql = "
select cheattype, timestamp, pc.player, stp.id, clientip
from event_cheat e
  join sessiontoplayer stp on stp.id = e.sessiontoplayerid and stp.location = e.location
  join gamesession gs on gs.id = stp.gamesession and stp.location = gs.location
  join playercharacter pc on pc.id = stp.playercharacter and stp.location = pc.location 
where gs.timehierarchyid between $startdh and $enddh
  and gs.starttime between '$starttimestr' and '$endtimestr'
order by 1,2 "

$csvfile1 = "$pwd\files\Cheats-$datesuffix.csv"
exec-sql $sql $csvfile1

# ---------------------------------------------------------------------------------------
# Агрегированные данные по читам

$sql = "
select cheattype, count(*), count(distinct pc.player), count(distinct stp.id)
from event_cheat e
  join sessiontoplayer stp on stp.id = e.sessiontoplayerid and stp.location = e.location
  join gamesession gs on gs.id = stp.gamesession and stp.location = gs.location
  join playercharacter pc on pc.id = stp.playercharacter and stp.location = pc.location 
where gs.timehierarchyid between $startdh and $enddh
  and gs.starttime between '$starttimestr' and '$endtimestr'
group by cheattype
order by 1"

write 'executing query ' $sql
$counts = psql -h $dbhost -p $dbport -d $dbname -U $dbuser -c "COPY ($sql) TO STDOUT CSV"
$alldata = "Type`tCount`tS2p`tPlayers"
$counts |% {
  $data = $_.split(',')
  $alldata = "$alldata`n$($data[0])`t$($data[1])`t$($data[2])`t$($data[3])"
}

# ---------------------------------------------------------------------------------------
# Формирование Excel файла

# создание COM объекта Excel
$xc=New-Object -ComObject "Excel.Application"
write 'started Excel.Application'
$wb=$xc.Workbooks.Add()
$ws = $wb.Worksheets.item(1)

insert-to-excel $ws $ws.cells.item(1,1) $alldata
$ws.range($ws.cells.item(1,1),$ws.cells.item(1,4)).font.bold = $true

$col = 6
$counts |% {
  $data = $_.split(',')
  write-data-by-type $csvfile1 $ws $col $data[0]
  $col = $col + 4
}
$ws.cells.item(1,1).select()

# ---------------------------------------------------------------------------------------
# Сохранение документа

$xlsfile = "$pwd\files\Cheat-Reports-$datesuffix.xlsx"
if (test-path $xlsfile) {
  rm $xlsfile
  write "removed existing file $xlsfile"
}

$wb.SaveAs($xlsfile)
write 'created file ' $xlsfile
$wb.Close()
$xc.Quit()

write-host 'cheat-reporter executed in ' $exectime.elapsed
$exectime.stop()