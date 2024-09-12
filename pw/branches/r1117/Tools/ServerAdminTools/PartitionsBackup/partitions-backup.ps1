if (-not (test-path "$pwd\tables")) { md "$pwd\tables" }

$dbhost = 'localhost'
$dbname = 'pw_analysis'

# tables and their storage interval (in days)
$tables = @{
  'event_assist'      = 20;
  'event_damage'      = 14;
  'event_death'       = 20;
  'event_exceedingsteptime' = 30;
  'event_kill'        = 20;
  'event_naftaincome' = 14;
  'event_timeslice'   = 14;
  'resourcelog'       = 30;
  'talentjoinsession' = 20;
}

function dh2date ($dh) {
  return [DateTime]::Parse("$($dh.Substring(0,4))-$($dh.Substring(4,2))-$($dh.Substring(6,2))")
}

function execsql ($sql) {
  return psql -h $dbhost -p 5432 -d $dbname -U postgres -c $sql
}

function execsqlcopy ($sql) {
  return execsql "COPY ($sql) TO STDOUT CSV"
}


# repeat for every partitioned table
$tables.Keys |% {
  
  # get oldest partition for the table
  $data = execsqlcopy "
    SELECT min(substring(c.relname from E'........$')::integer)
    FROM pg_inherits
      JOIN pg_class c ON (inhrelid=c.oid)
      JOIN pg_class p ON (inhparent=p.oid)
    WHERE p.relname = '$_'"

  $startdate = dh2date $data
  
  # get last aggregated partition
  $data = execsqlcopy "
    SELECT min(datehierarchy)
    FROM $_ t
      JOIN sys_aggregation_ranges s 
        ON t.id = s.lastid AND t.location = s.location
    WHERE s.tablename = '$_'"

  # determine last partition to drop  
  $enddate = (get-date).AddDays(-$tables[$_])
  if ($data -ne '') {
    $tmpdate = (dh2date $data).AddDays(-1)
    if ($tmpdate -lt $enddate ) { $enddate = $tmpdate }
  }  

  if ($startdate -gt $enddate) {
    write-host "$_ : $startdate > $enddate, nothing to do here"
    return
  }

  write-host "$_ $($startdate.tostring('yyyyMMdd'))..$($enddate.tostring('yyyyMMdd'))"

  # dump'n'drop every partition in the range  
  for ($date = $startdate; $date -le $enddate; $date = $date.AddDays(1)) {
    $table = "$($_)_$($date.tostring('yyyyMMdd'))"
    
    # check if table is empty
    $tableisempty = (execsqlcopy "SELECT 1 FROM partitions.$table LIMIT 1") -eq $null
    
    # if table is not empty - make a backup from it
    if (-not $tableisempty -and -not (test-path "$pwd\tables\$table.backup")) {
      write-host dump $table
      pg_dump -h $dbhost -U postgres -Fc -t partitions.$table -f tables\$table.backup $dbname
    }
    
    # drop partition
    if ($tableisempty -or (test-path "$pwd\tables\$table.backup")) {
      write-host DROP $table
      execsql "DROP TABLE partitions.$table CASCADE;"
    }
  }

}