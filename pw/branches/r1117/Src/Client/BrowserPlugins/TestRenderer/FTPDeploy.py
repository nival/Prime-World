#-*- coding: cp1251 -*-
import os
import sys
from ftplib import FTP

def main():
    if len(sys.argv) > 1:
        fileName = sys.argv[1];
    else:
        fileName = ".\\..\\..\\..\\_Debug\\TestRenderer.dll"
    file = open(fileName, "rb")
    
    ftp = FTP("www.d-inter.ru")
    ftp.login("driver", "site")
    ftp.set_pasv(True)
    ftp.storbinary("STOR " + "nivaltest/" + os.path.basename(fileName), file)
    ftp.quit()
    
    file.close()
    print "File: '" + fileName + "'is uploaded"
    
if __name__ == "__main__":
    main()