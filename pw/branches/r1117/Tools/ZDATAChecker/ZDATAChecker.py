import os
from os import path
import re
import sys
from collections import defaultdict

def basic_printer(s):
    print s

class InfoPrinter(object):

    def __init__(self, printer = basic_printer):
        self.errors_no = 0
        self.warnings_no = 0
        self.files_no = 0
        self.files = []
        self.printer = printer

        self.new_class = False
        self.new_file = False
        self.fname = ''
        self.current_file_clean = True

    def clear(self):
        self.__init__()

    def set_file_name(self, fname):
        self.fname = fname
        self.new_file = True
        self.current_file_clean = True

    def set_class_info(self, cls_name, bases):
        self.cls_name = cls_name
        self.bases = bases
        self.new_class = True

    def flush_info(self):
        if self.new_file:
            self.printer('\n' + self.fname)
            self.new_file = False
            self.files_no += 1
            self.files.append(self.fname)
        if self.new_class:
            self.printer("  " + self.cls_name + " : " + str(self.bases))
            self.new_class = False

    def message(self, msg, todo):
        self.flush_info()
        s = '    ' + msg + '.  TODO: ' + todo if todo != '' else '    ' + msg
        self.printer(s)

    def warning(self, warning, todo = ''):
        self.message('warning: ' + warning, todo)
        self.warnings_no += 1
        self.current_file_clean = False

    def error(self, error, todo = ''):
        self.message('error: ' + error, todo)
        self.errors_no += 1
        self.current_file_clean = False

    def result(self):
        print '\nFiles: {0}, errors: {1}, warnings: {2}'.format(self.files_no, self.errors_no, self.warnings_no)
        #for f in self.files:
        #    print f



def cls_content_end(text):
    lc, rc, ind = 0, 0, 0
##    stack = []
    start_pattern = r'{'
    end_pattern = r'}'
    while ind < len(text):
        start = text[ind:].find(start_pattern)
        start = ind + start if start != -1 else -1
        end = text[ind:].find(end_pattern)
        end = ind + end if end != -1 else -1
        if start != -1 and (start < end or end == -1):  # start_pattern found earlier
            lc += 1
            ind = start + len(start_pattern)
        elif end != -1:  # end_pattern found earlier
            ind = end + len(end_pattern)
            rc += 1
        else:  # nothing found.
            print "    ERROR in class parsing!!!!"
            return -1 # error
        if lc == rc:
            break;
    return ind

##class_finder = re.compile("(class\s*(?P<cn>\w+))(?=[\s*:$])(?P<cb>.*$)", re.MULTILINE)
##bases_finder = re.compile("\s*public\s*(?P<cb>[\w,]+)")
##zdata_ = re.compile("ZDATA_\s*\(\s*(?P<zb>\w+)")
##zparent_finder = re.compile("ZPARENT\s*\(\s*(?P<zb>\w+)")

##base_exceptions = ['CNetPacket', 'IFileSystem', 'CObjectBase']
base_exceptions = ['CNetPacket', 'IFileSystem', 'CObjectBase']
warning_printer = InfoPrinter()
class ClsParser(object):
    def __init__(self):
        self.class_finder = re.compile("((class|struct)\s+(?P<cn>\w+))(?=\s*[:$])(?P<cb>.*?{)", re.MULTILINE | re.DOTALL)
        self.class_finder = re.compile("((class|struct)\s+(?P<cn>\w+))\s*(?=[^,;\w*&>])(?P<cb>.*?{)", re.MULTILINE | re.DOTALL)
        base = "(?P<b>[\w:<>]+)"
        base = "(?P<b>[\w:]+(?:<.*?>)?)"
        self.bases_finder = re.compile("\s*(?:public|private|protected)\s+" + base)
        self.zdata_ = re.compile("ZDATA_\s*\(\s*" + base)
        self.zparent_finder = re.compile("ZPARENT\s*\(\s*" + base)
        self.zparent_nocrc_finder = re.compile("ZNOPARENT\s*\(\s*" + base)
        self.ampersand_field_finder = re.compile("Add\s*\(\s*(?P<n>[0-9]+)\s*,\s*&(?P<f>\w+)\s*\);")
        self.ampersand_field_finder = re.compile("Add\s*\(\s*(?P<n>[0-9]+)\s*,\s*(?:&\s*\(\s*\*[^&]*)?&(?P<f>\w+)\s*\)+;")


        self.ampersand_bases_finder = re.compile("Add\s*\(\s*(?P<n>[0-9]+)\s*,\s*\(\s*" + base + "\s*\*\s*\)\s*this")
##        self.ampersand_nocrc_fields_finder = re.compile("if\s*\(\s*!\s*f\.IsChecksum\s*\(\s*\)\s*\)\s*\{(?P<anf>[^}]+)\}")
        self.ampersand_nocrc_fields_finder = re.compile("if\s*\(\s*!\s*f\.IsChecksum\s*\(\s*\)\s*\)\s*\{(?P<anf>[^}]+)\}")

    def parse_cls(self, text):
        res = re.search(self.class_finder, text)
        ##    print res.group(0)
        if res == None:
            return False
        self.cls_name = res.group('cn')
        ttext = text[res.end() - 1:]
        cls_end = cls_content_end(ttext)
        self.cls_content = ttext[:cls_end]
        self.text = text[:res.start()] + ttext[cls_end:]
        bases = res.group('cb')
    ##   bases_finder = re.compile("public\s*\w+")
        self.bases = re.findall(self.bases_finder, bases)

        base_finder = re.compile("(?P<b>\w+)\s*<.*,") # t<a, b>  ->  t
        for i, b in enumerate(self.bases):
            if b in base_exceptions:
                self.bases.remove(b)
            res = re.search(base_finder, b)
            if res != None:
                self.bases[i] = res.group('b')
    ##        bases_finder = re.compile("public\s*(?P<cb>\w+)")
    ##        bases = [re.search(bases_finder, b).group('cb') for b in bases]
    ##        print bases
            ##print cls_content
        return True

    def get_cls(self):
        return self.cls_name, self.bases, self.cls_content

    def set_cls(self, cls_name, bases, cls_content):
        self.cls_name = cls_name
        self.bases = bases
        self.cls_content = cls_content

    def get_text(self):
        return self.text

    def parse_zbases(self, cls_content):
##        res = re.search(self.zparent_nocrc_finder, cls_content)
        nocrcbases = re.findall(self.zparent_nocrc_finder, cls_content)

        for b in nocrcbases:
            if b in base_exceptions:
                nocrcbases.remove(b)

        res = re.search(self.zdata_, cls_content)
        zbases = []
        if res == None:
            if cls_content.find("ZDATA") != -1 and self.bases != nocrcbases:
##                print "    warning: class with parents should have ZDATA_"
                warning_printer.warning('class with bases should have ZDATA_')
        else:
            zbase = res.group('b')
            zbases = [zbase] + re.findall(self.zparent_finder, cls_content)

        for b in zbases:
            if b in base_exceptions:
                zbases.remove(b)

        return zbases, nocrcbases

    def parse_zfields(self, cls_content):
        zfields_txt = cls_content[cls_content.find("ZDATA"):cls_content.find("ZEND")]
        nocrc_fields_txt = ''

        if zfields_txt.find("ZNOCRC") != -1:
            if zfields_txt.find("ZNOCRCEND") == -1:
##                print "    warning: no ZNOCRCEND"
                warning_printer.error('no ZNOCRCEND')
            else:
                nocrc_fields_txt = zfields_txt[zfields_txt.find("ZNOCRC"):zfields_txt.find("ZNOCRCEND")]
##                zfields_txt = zfields_txt[:zfields_txt.find("ZNOCRC")] + zfields_txt[zfields_txt.find("ZNOCRCEND"):]
                return self.parse_fields(zfields_txt[:zfields_txt.find("ZNOCRC")]) + self.parse_fields(nocrc_fields_txt) + self.parse_fields(zfields_txt[zfields_txt.find("ZNOCRCEND"):])
        return self.parse_fields(zfields_txt)

    def parse_fields(self, fields_txt):
        fields_txt = fields_txt.split("\n")
        fields = []
        for f in fields_txt[1:]:
            if f.find(')') != -1:
                if f.find('ZPARENT') == -1 and f.find('ZNOPARENT') == -1:
##                    print "    warnig: no functions between ZDATA and ZEND, please"
                    warning_printer.warning('no functions between ZDATA and ZEND, please')
            elif f.find(';') != -1:
                f = f[:f.find(';')]
                template_finder = re.compile("<\s*.*>")
                f = re.sub(template_finder, "", f)
                ww = f.split(',')  # int a, b, c
                for wf in ww:
                    words = wf.split()
##                    if len(words) > 0:

                    fields.append(words[-1])
        return fields

    def parse_ampersand(self, cls_content):
        ampersand_txt = cls_content[cls_content.find("ZEND"):]
        ampersand_nocrc_fields = {}
        res = re.search(self.ampersand_nocrc_fields_finder, ampersand_txt)
        if res != None:
            ampersand_nocrc_txt = res.group('anf')
            ampersand_txt = ampersand_txt[:res.start()] + ampersand_txt[res.end():]
            ampersand_nocrc_fields = re.findall(self.ampersand_field_finder, ampersand_nocrc_txt)
            ampersand_nocrc_fields = dict([(f, int(n)) for n, f in ampersand_nocrc_fields])

        if ampersand_txt.find("{") == -1 or ampersand_txt.find("{") > ampersand_txt.find(";"):  # custom operator in .cpp
            ampersand_txt = ''
        else:
            ampersand_txt = ampersand_txt[:ampersand_txt.rfind("}")]
        ampersand_fields = re.findall(self.ampersand_field_finder, ampersand_txt)
        ampersand_fields = dict([(f, int(n)) for n, f in ampersand_fields])
        ampersand_fields.update(ampersand_nocrc_fields)
        ampersand_bases = re.findall(self.ampersand_bases_finder, ampersand_txt)
        ampersand_bases = dict([(b, int(n)) for n, b in ampersand_bases])

        if cls_content.find("ZONSERIALIZE") != -1:
            onserialize_finder = re.compile("\s*OnSerialize\s*\(\s*")
            res = re.search(onserialize_finder, ampersand_txt)
            if res == None:
##                print "    warning: OnSerialize not called"
                if ampersand_txt == '':  # there are two valid situations: custom operator or OnSerialize method called.
##                    return True, ampersand_bases, ampersand_fields, ampersand_nocrc_fields
                    return True, ampersand_bases, ampersand_fields
                warning_printer.error('OnSerialize not called')
##        return False, ampersand_bases, ampersand_fields, ampersand_nocrc_fields
        return False, ampersand_bases, ampersand_fields

cls_parser = ClsParser()

def process_object_methods(fname, get_text, cls_name, cls_content, title):
    class ObjectMethodsFinder(object):
        def __init__(self, cls_name, cls_content, get_text):
            self.cls_name = cls_name
            self.cls_content = cls_content
            self.get_text = get_text
            self.found = False
            self.worldobject_finder = re.compile(title + "(_NM)?(_2)?\s*\(\s*" + cls_name + "[^\w]")

        def __call__(self, fname):
            cpp_text = self.get_text(fname)
            self.find_object_methods(cpp_text)

        def find_object_methods(self, cpp_text):
            res = re.search(self.worldobject_finder, cpp_text)
            if res != None:
                self.found = True
    ##        print "    warning: no", title
##                warning_printer.error('no ' + title)

##    try:
##        cpp_file = open(fname)
##        cpp_text = cpp_file.read()
##    except IOError, e:
##        fname = fname_base + '.c'
##        try:
##            cpp_file = open(fname)
##            cpp_text = cpp_file.read()
##        except:
####            print "    warning: no matching .cpp file"
##            warning_printer.error('no matching .cpp file. It should be present and contain REGISTER_WORLD_OBJECT or REGISTER_SAVELOAD_CLASS macro')
##            return
##        else:
##            cpp_file.close()
##    else:
##        cpp_file.close()
    # if the class contains pure virtual functions it is never instatiated
    pure_virtual_finder = re.compile("\)\s*=\s*0\s*;")
    res = re.search(pure_virtual_finder, cls_content)
    if res != None:
        return

    fname_base = fname[:fname.find('.h')]
    fname = fname_base + '.cpp'

    omf = ObjectMethodsFinder(cls_name, cls_content, get_text)
    cpp_text = get_text(fname)
    if not cpp_text:
        fname = fname_base + '.c'
        cpp_text = get_text(fname)
    if not cpp_text:
        dir_name = os.path.dirname(fname)
        for fn in os.listdir(dir_name):
            fn = os.path.join(dir_name, fn)
            if os.path.isfile(fn):
                omf(fn)
                if omf.found == True:
                    break
##        os.walk(dir_name, omf, None)
    else:
        omf.find_object_methods(cpp_text)

    if omf.found == False:
        warning_printer.error('no ' + title)

##        warning_printer.error('no matching .cpp file. It should be present and contain REGISTER_WORLD_OBJECT or REGISTER_SAVELOAD_CLASS macro')

def process_text(fname, get_text):
    cls_name, bases, cls_content = cls_parser.get_cls()
##    text = cls_content
    while cls_parser.parse_cls(cls_content): # nested classes
        cls_content = cls_parser.get_text()
        process_text(fname, get_text)

    cls_parser.set_cls(cls_name, bases, cls_content) # restoring after recursion
##    if cls_name == None: # no more classes in the file
##        return text
    if cls_content.find("ZDATA") == -1:
        return
##    print "  " + cls_name, ":", bases
    warning_printer.set_class_info(cls_name, bases)

    nocrcbases = []
    if bases:
        zbases, nocrcbases = cls_parser.parse_zbases(cls_content)
        if sorted(bases) != sorted(zbases + nocrcbases):
##            print "    warning: class bases:", bases, "bases in zdata:", zbases
            warning = 'class bases: ' +  str(bases) + ". Bases in zdata: " + str(zbases)
            if nocrcbases != []:
                warning += ', bases with no crc: ' + str(nocrcbases)
            warning_printer.warning(warning, 'add all class bases to zdata')


##    zfields, nocrc_fields = cls_parser.parse_zfields(cls_content)
    zfields = cls_parser.parse_zfields(cls_content)

##    skip_ampersand, ampersand_bases, ampersand_fields, ampersand_nocrc_fields = cls_parser.parse_ampersand(cls_content)
    skip_ampersand, ampersand_bases, ampersand_fields = cls_parser.parse_ampersand(cls_content)
    if not skip_ampersand:
##        process_ampersand(bases, ampersand_bases, nocrcbases, zfields, ampersand_fields, nocrc_fields, ampersand_nocrc_fields)
        process_ampersand(bases, ampersand_bases, nocrcbases, zfields, ampersand_fields)

    if cls_content.find("ZONSERIALIZE") != -1 and not skip_ampersand:
        onserialize_finder = re.compile("void\s+OnSerialize\s*\(\s*IBinSaver\s*&\s*")
        res = re.search(onserialize_finder, cls_content)
        if res == None:
##            print "    warning: no OnSerialize method"
            warning_printer.error('no OnSerialize method')
            
    if cls_content.find("DONOT_REGISTER_SAVELOAD_CLASS") == -1:
      if cls_content.find("WORLD_OBJECT_METHODS_WITH_CLIENT") != -1:
          process_object_methods(fname, get_text, cls_name, cls_content, "REGISTER_WORLD_OBJECT_WITH_CLIENT_NM")
      elif cls_content.find("WORLD_OBJECT_METHODS") != -1:
          process_object_methods(fname, get_text, cls_name, cls_content, "[REGISTER_WORLD_OBJECT|REGISTER_WORLD_OBJECT_NM]")
      elif cls_content.find("OBJECT_METHODS") != -1:
          process_object_methods(fname, get_text, cls_name, cls_content, "REGISTER_SAVELOAD_CLASS")

##def process_ampersand(bases, ampersand_bases, nocrcbases, zfields, ampersand_fields, nocrc_fields, ampersand_nocrc_fields):
def process_ampersand(bases, ampersand_bases, nocrcbases, zfields, ampersand_fields):
    nb = 0 # in case bases is []
    offset = 1
    exIdList = [ampersand_bases.get(b, -2) for b in base_exceptions]
    for nb, b in enumerate(bases):
        id_found = ampersand_bases.get(b, -1)
        # handle id shift if human whenever adds one of exception classes to ZDATA()
        for exId in exIdList:
            if nb+offset == exId:
                nb += 1
                break
        if not b in nocrcbases:
            if  id_found != nb + offset:
##            print "    warning:", b, "id should be:", nb + 1, "id found:", ampersand_bases.get(b, -1)
                id_found_str = 'id found: {0}'.format(id_found) if id_found != -1 else 'no id found'
                warning_printer.error(b + " id should be: " + str(nb + 1) + ', ' + id_found_str, 'run PropertySerializer macro')
        else:
            offset -= 1
            if id_found != -1:
                warning_printer.error("class {0} is marked with ZNOCRCPARENT, so it mustn't appear in ampersand operator".format(b), 'run PropertySerializer macro')

    process_ampersand_fields(zfields, ampersand_fields, nb - len(nocrcbases))
##    start_id = ampersand_fields.values()[0] if len(ampersand_fields) > 0 else 0
##    if nocrc_fields != '':

def process_ampersand_fields(fields, ampersand_fields, offset):
    for nf, f in enumerate(fields):
        id_found = ampersand_fields.get(f, -1)
        id_needed = nf + 2 + offset
        if id_found < id_needed:
##            print "    warning:", f, "id should be:", nf + nb + 2, "id found:", ampersand_fields.get(f, -1)
            id_found_str = 'id found: {0}'.format(id_found) if id_found != -1 else 'no id found'
            warning_printer.error(f + " id should be: " + str(id_needed) + ', ' + id_found_str, 'run PropertySerializer macro')


def read_from_file(fname):
    try:
        fh = open(fname, 'r')
        text = fh.read()
    except:
        text = ''
    else:
        fh.close()
    return text


def process(fname, get_text=read_from_file):
    text = get_text(fname)
    lines = text.split("\n")
    for i in xrange(len(lines)):
        comment = lines[i].find('//')
        if comment != -1:
            lines[i] = lines[i][:comment]
        lines[i] += '\n'
    text = ''.join(lines)

    if text.find("ZDATA") == -1:
        return True

    if fname.find('EaselMinigame') != -1:
        pass
##    print fname
    warning_printer.set_file_name(fname)

    while cls_parser.parse_cls(text):
        text = cls_parser.get_text()
        process_text(fname, get_text)
    return warning_printer.current_file_clean

CompStrErrFiles = []
EmptyCompiledStrPattern = '<compiledString></compiledString>'
def checkCompiledStrings(arg, dirname, names):
    for fname in names:
        if fname.endswith('.xdb'):
            fullName = path.join(dirname, fname)
            text = read_from_file(fullName)
            if text.find(EmptyCompiledStrPattern) >= 0: #try to find empty compiled string
                CompStrErrFiles.append(fullName)

def visit(arg, dirname, names):
    for n in names:
        if n.endswith('.h') or n.endswith('.hpp'):
            process(path.join(dirname, n))

class RedirectStdoutTo:
    def __init__(self, out_new):
        self.out_new = out_new

    def __enter__(self):
        self.out_old = sys.stdout
        sys.stdout = self.out_new

    def __exit__(self, *args):
        sys.stdout = self.out_old

def run():
    #Check ZDATA
    warning_printer.clear()
    src_path = path.normpath(path.join(path.dirname(__file__), '../../Src'))
    print src_path
    path.walk(src_path, visit, None)
    warning_printer.result()

    #print '\n\n-----------------------\n\n'

    #Check compiled strings
    #data_path = path.normpath(path.join(path.dirname(__file__), '../../Data'))
    #print "List of files containig empty complied formula strings ( " + EmptyCompiledStrPattern + " ): \n"
    #path.walk(data_path, checkCompiledStrings, None)
    #for fileName in CompStrErrFiles:
    #    print fileName
    print "\n\nDone"

    #return warning_printer.errors_no + warning_printer.warnings_no + len(CompStrErrFiles)
    return warning_printer.errors_no + warning_printer.warnings_no

def runToFile(fName):
    with open(fName, mode='w') as a_file: # Python 2.6 can only use one context manager
        with RedirectStdoutTo(a_file):
            return run()

if __name__ == "__main__":
    ret = runToFile("ZDATACheckerReport.txt")
    sys.exit(ret)