import os

def checkSyntax(_path):
    path = os.path.abspath(_path)

    for root, dirs, files in os.walk(path):
        for name in files:
            if name.endswith('.php'):
                os.system(r'php -l %s' % os.path.join(root, name))

checkSyntax('../../application')
checkSyntax('../../misc')