# -"- coding: utf-8 -"-
import os, re, glob

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




