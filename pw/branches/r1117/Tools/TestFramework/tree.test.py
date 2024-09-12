import unittest
import templates
from ComponentsSystem import utils
import sln
import BuildProject

def getChildrenForDepth( root, dep ):
  depth = dep
  current_nodes = [root]

  while depth:
    current_res = []
    for node in current_nodes:
      for child in node.children:
        current_res.append( child )
    current_nodes = current_res
    depth = depth - 1

  return current_nodes


def isFilterInTree( root, filtername, dep ):
  for child in getChildrenForDepth( root, dep ):
    if child.filtername == filtername:
      return True, child

  return False, None


def addFilterToTree( child, filtername ):
  child.children.append( FileFilterTree( filtername, [], [] ) )
  return child.children[-1]


def addFileToTree( root, file ):
  res = False
  child = root
  for fidx in xrange( 0, len(file.filter) ):
    res, tempchild = isFilterInTree( child, file.filter[fidx], 1 )
    if not res:
      child = addFilterToTree( child, file.filter[fidx] )
    else:
      child = tempchild

  child.files.append( file )

class Test(unittest.TestCase):

  def test2( self ):
    files = []
    files.append( BuildProject.FileInfo( 'test.cpp', [] ) )
    ffs = ''
    ffs = utils.generateFileFilterTree( files )
    assert ffs.files[0].file == 'test.cpp'

  def test3( self ):
    files = []
    files.append( BuildProject.FileInfo( 'test.cpp', [] ) )
    files.append( BuildProject.FileInfo( 'test2.cpp', ['test'] ) )
    ffs = ''
    ffs = utils.generateFileFilterTree( files )
    assert ffs.files[0].file == 'test.cpp'
    assert ffs.children[0].files[0].file == 'test2.cpp'
    assert ffs.children[0].filtername == 'test'

  def test4( self ):
    files = []
    files.append( BuildProject.FileInfo( 'test.cpp', [] ) )
    files.append( BuildProject.FileInfo( 'lol.cpp', [] ) )
    files.append( BuildProject.FileInfo( 'test1.cpp', ['test1','test'] ) )
    files.append( BuildProject.FileInfo( 'test2.cpp', ['test2','test'] ) )
    ffs = ''
    ffs = utils.generateFileFilterTree( files )
    string = ''
    string = sln.generateFileFilterTreeText( string, ffs )
    assert ffs.files[0].file == 'test.cpp'
    assert ffs.files[1].file == 'lol.cpp'
    assert ffs.children[0].filtername == 'test1'
    assert ffs.children[1].filtername == 'test2'
    assert ffs.children[0].children[0].filtername == 'test'
    assert ffs.children[1].children[0].filtername == 'test'
    assert ffs.children[0].children[0].files[0].file == 'test1.cpp'
    assert ffs.children[1].children[0].files[0].file == 'test2.cpp'


unittest.main()