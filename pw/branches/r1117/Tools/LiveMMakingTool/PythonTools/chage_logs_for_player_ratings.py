import csv
import json
import sys

#Путь к логу который будет обрабатываться
LOG_FILE = "d:\\TEMP\\LOGS\\NUM_TASK\\unpack_logs\\UniServer-10.7-0.170.09.80128-2016.02.07-00.00.00-livemmaking.json(12).txt"
# путь к файлу, в котором будут содержаться новые данные по правильным player_ratings в формaте csv в виде <auid>;<player_rating>
INPUT_FILE = 'input_data.csv'
#Имя файла результата
OUTPUT_LOGFILE = LOG_FILE + ".output"

def update_dict(data, members_key, user_key, pr_key):
    if members_key in data:
        for x in data[members_key]:
            if x[user_key] in players:
                x[pr_key] = players[x[user_key]]

players = dict()
with open(INPUT_FILE, 'rb') as csvfile:
    rows = csv.reader(csvfile, delimiter=';', quotechar='|')
    for row in rows:
        if len(row) == 2:
            players[int(row[0])] = int(row[1])

with open(OUTPUT_LOGFILE, 'w') as output_logfile:
    with open(LOG_FILE) as logfile:
        lines = logfile.readlines()
        l = len(lines)
        for i, line in enumerate(lines):
            if i > 1:
                sdict = json.loads(line)

                if "RequestQueued" in sdict:
                    update_dict(sdict["RequestQueued"], "members", "mmId", "prating")

                if "PushingGame" in sdict:
                    update_dict(sdict["PushingGame"], "members", "userId", "pRating")

                output_logfile.write(json.dumps(sdict) + "\n")

            else:
                output_logfile.write(line + "\n")
            sys.stdout.write("\r {0:.2f}% was completed ...".format((float(i + 1)/l) * 100))
            sys.stdout.flush()

