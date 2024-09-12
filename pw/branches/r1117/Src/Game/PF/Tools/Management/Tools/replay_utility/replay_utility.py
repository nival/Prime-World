# -"- coding: utf-8 -"-
from flask import Flask, request
import ujson, glob, os, re
import ConfigParser
import argparse

app = Flask(__name__)
app.secret_key = 'secret_key'

#config section
app.secret_key = 'another_secret_key'
FULL_PATH= os.path.dirname(os.path.abspath(__file__))

config = ConfigParser.ConfigParser()
config.read(os.path.join(FULL_PATH, 'config.cfg'))
replays_dir = config.get('DEFAULT', 'replays_dir')

def files_search(files_dir, wildcard, level1="*", level2="*"):
    fileList = []
    search_paths = os.path.join(files_dir, level1)
    if level2 != "*":
        search_paths = os.path.join(search_paths, level2)

    search_paths = glob.glob(search_paths)
    for search_path in search_paths:
        for root, subFolders, files in os.walk(search_path):
            for file in files:
                if re.search(wildcard, file):
                    fileList.append(os.path.relpath(os.path.join(root, file), files_dir))
    return fileList

@app.route('/get_replays', methods=['GET', 'POST'])
def show_replays():
    if request.method == 'POST':
        if request.form['SessionId']:
            fs_args = {"wildcard" : request.form['SessionId']}
            if request.form['hostname']:
                fs_args["level1"] = request.form['hostname']
            if request.form['date']:
                fs_args["level2"] = request.form['date']
            session_list = files_search(replays_dir, **fs_args)
            if len(session_list) <= 10:
                return ujson.dumps({"replays": session_list})
            else:
                return ujson.dumps({"ec":1, "error": "Too many entries found with this SessionId. Please try another one."})
        else:
            return ujson.dumps({"ec": 2, "error": "SessionId is empty or not valid"})
    else:
        return ujson.dumps({"ec": 3, "error": "Bad action"})

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Search replay utility')

    parser.add_argument('--port', type=int, help='port for processing request')
    parser.add_argument('--host', help='service host')
    args = parser.parse_args()
    #app.run(debug=True)
    if args.host and args.port:
        app.run(host=args.host, port=args.port)
    elif args.host and not args.port:
        app.run(host=args.host)
    elif not args.host and args.port:
        app.run(port=args.port)
    else:
        app.run()