import MigratorsFramework as MF

applicatorNameOld = "ForbidApplicator"
applicatorNameNew = "FlagsApplicator"

def renameApplicatorFunc(text):
    text = text.replace(applicatorNameOld, applicatorNameNew)
    return text

def main():
    MF.run(applicatorNameOld, renameApplicatorFunc)
    print "done"

if __name__ == "__main__":
    main()