import xlrd
import xlwt
from xlwt import Workbook

inputfile = 'data.xlsx'
outputfile = 'result.xls'

step = 300

reasons = {
  4: 'ByClient',
  5: 'ByServer',
  6: 'TimedOut',
  7: 'ByCheatAttempt',
  8: 'ByClientIntentionally',
  9: 'TimedOutOnReconnect',
  10: 'DisconnectedByAsync',
  11: 'RefusedToReconnect',
}

#reading
B = xlrd.open_workbook(inputfile)
sheet = B.sheet_by_index(0)

rheader = sheet.row_values(0)
print 'Header: \n' + str(rheader) + '\n'

timeline = {}

for rownum in range(1, sheet.nrows):
  row = sheet.row_values(rownum)
  (svcid, tid) = (row[0], int(row[1]))
  (hour, min, sec) = (row[2], row[3], row[4])
  (gameid, uid) = (int(row[5], 16), int(row[6]))
  status = int(row[7])
  
  if not (status in reasons) :
    continue

  print 'Data. svcid=%s, tid=%d, time=%02d:%02d:%02d, gameid=%x, uid=%d, status=%d' % (svcid, tid, hour, min, sec, gameid, uid, status)
  time = hour * 3600 + min * 60 + sec
  stepidx = int( time / step )
  if stepidx in timeline :
    node = timeline[stepidx]
  else :
    node = {}
    timeline[stepidx] = node

  if status in node :
    node[status].append(uid)
  else :
    node[status] = [uid]

#writing
wb = Workbook()
ws = wb.add_sheet('result')
wheader = ws.row(0)
wheader.write(0, 'Time')
wheader.write(1, 'Total')
reasonidx = 0
for status in reasons:
  wheader.write( 2 + reasonidx, reasons[status] )
  reasonidx += 1

if len( timeline ):
  steps = sorted(timeline.keys())
  print 'Steps: %s' % steps
  R = range(steps[0],steps[-1] + 1)
  print 'range: %s' % R
  rowidx = 1
  for stepidx in R:
    time = stepidx * step
    row = ws.row( rowidx )
    hour = int( time / 3600 )
    min = int( time - hour * 3600 ) / 60
    row.write( 0, '%02d:%02d' % (hour, min) )

    reasonidx = 0
    total = 0
    for status in reasons:
      count = 0
      if stepidx in timeline:
        node = timeline[stepidx]
        if status in node:
          count = len( node[status] )
          total += count
      row.write( 2 + reasonidx, count )
      reasonidx += 1
    row.write( 1, total )

    rowidx += 1

print 'Data:\n'
print timeline

wb.save(outputfile)
