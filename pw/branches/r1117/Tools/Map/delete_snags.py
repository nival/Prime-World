import os, re, xml.dom, xml.dom.minidom, random, types

def getText(nodelist):
    rc = ""
    for node in nodelist:
        if node.nodeType == node.TEXT_NODE:
            rc = rc + node.data
    return rc

def setText( element, sometext ):
	for node in element.childNodes:
		if node.nodeType == node.TEXT_NODE:
			node.nodeValue = sometext

def getElementData( element ):
	return getText( element[0].childNodes )

def getIntData( element ):
	return int(getElementData( element ))

def getFloatData( element ):
	return float(getElementData( element ))

def getFloatData1( element ):
	return float(getText( element.childNodes ))

filename = "pf.admp.xdb"

#newtrees = [ "/Terrain/Trees/MSO/_02.TREE", "/Terrain/Trees/MSO/_03.TREE", "/Terrain/Trees/MSO/_04.TREE", "/Terrain/Trees/MSO/_05.TREE" ]

print "Processing: ", filename

file = open(filename, "r")
xmldoc = xml.dom.minidom.parse(file)
file.close()

terrainElements = xmldoc.getElementsByTagName( "objects" )[0]
item_nodes = terrainElements.getElementsByTagName( "Item" )

for tnode in item_nodes:
  if len( tnode.getElementsByTagName( "gameObject" ) ) == 0:
    continue
  go_node = tnode.getElementsByTagName( "gameObject" )[0]
  if ( go_node.getAttribute( "href" ).find( "Terrain/Snags" ) >= 0 ):
    terrainElements.removeChild( tnode )

file = open( filename, "wb+" )
file.write( "\xEF\xBB\xBF" + xmldoc.toxml( encoding = "utf-8" ) )
file.close()
