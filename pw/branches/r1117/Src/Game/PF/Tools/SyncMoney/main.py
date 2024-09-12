import os
import win32com.client
import sys

def createExcel():
    app = None
    try:
        app = win32com.client.Dispatch("Excel.Application.11") # Excel2003
    except Exception:
        try:
            app = win32com.client.Dispatch("Excel.Application.10") # ExcelXP
        except Exception:
            try:
                app = win32com.client.Dispatch("Excel.Application.9") #Excel 2000
            except Exception:
                try:
                    app = win32com.client.Dispatch("Excel.Application.8")# Excel 97
                except Exception:
                    app = win32com.client.Dispatch("Excel.Application") #Excel 5.0?
                    # Or raise "No Office ..."
    return app

def ParseAmount(content, newAmount):
    if newAmount:
        s = 'New amount for account "'
    else:
        s = 'Initial amount for account "'
    index = content.find(s)
    if index >= 0:
        content = content[index+len(s):]
        index = content.find('":')
        if index >= 0:
            endIndex = content[index+2:].find('\r\n')
            if endIndex >=0:
                amount = float(content[index+2:index+2+endIndex])
            else:
                amount = float(content[index+2:])
            return (True, amount)
    return (False, 0)
    
class ZZima:

    def __init__(self, serviceUrl, serviceName, servicePassword=''):
        self.args = [
            'main.exe',
            '--serviceUrl',
            serviceUrl,
            '--serviceName',
            serviceName,
        ]
        if servicePassword:
            self.args.append('--servicePassword')
            self.args.append(servicePassword)
            
    def SetUser(self, user):
        self.user = user            
        
    def Do(self, operation, *args):
        infoName = self.user.strip()+'.txt'
        _args = self.args+['--user', self.user]
        if operation:
            _args.extend(['--'+operation]+list(args))
        _args.extend(['>', infoName])            
        result = False
        content = ''
        retCode = os.system(' '.join(_args))
        if retCode == 0:
            if os.path.isfile(infoName):
                content = open(infoName, 'rb').read()
                result = True
        os.remove(infoName)
        return (result, content)
        

def LoadValue(zzima):
    succeeded, content = zzima.Do(None)
    if succeeded:
        return ParseAmount(content, False)
    return (False, 0)

def SaveValue(zzima, amount):
    succeeded, content = zzima.Do('set', str(amount))
    if succeeded:
        return ParseAmount(content, True)
    return (False, 0)

def main():    
    url = r"http://SITE/ZZServiceWeb.asmx?WSDL"
    project = r'pw'
    zzima = ZZima(url, project)
    excel = createExcel()
    #excel.Visible = 1
#    excel.Workbooks.Open('People.xls')

    loadValue = True
    if len(sys.argv) > 1:
        if sys.argv[1] == 'save':
            loadValue = False
    else:
        print 'Usage: main.py [save/load]'
        return
        

    if not excel.ActiveSheet:
        print 'Error: no active sheet found'
        return
                
    row = 2
    while True:
        name = excel.ActiveSheet.Cells(row, 1).Value
        if name:
            col = 5
            valuePrinted = False  
            while True:
                nick = excel.ActiveSheet.Cells(row, col).Value
                if type(nick) == float or type(nick) == int:
                    nick = str(nick)
                    index = nick.find('.')
                    if index >= 0:
                        nick = nick[:index]
                if nick:
                    zzima.SetUser(nick)
                    col += 1
                    if not valuePrinted:
                        print name 
                        valuePrinted = True
                    print ' '*4, nick,
                    succeded = False
                    if loadValue:
                        succeded, amount = LoadValue(zzima)    
                        if not succeded:
                            amount = None
                        excel.ActiveSheet.Cells(row, 2).Value = amount
                    else:
                        amount = excel.ActiveSheet.Cells(row, 2).Value
                        if amount != None:
                            succeded, amount = SaveValue(zzima, amount)
                    if succeded:
                        print 'OK'
                    else:
                        print                    
                else:
                    break    
            row += 1
        else:        
            break
            
main()            