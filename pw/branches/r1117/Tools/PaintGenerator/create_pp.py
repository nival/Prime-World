# Reads 'paint.xls' and generates PainterParamsXX.xdb files using PainterParams.xdb template (with single Item in fragments node)
# requires 'xlrd' lib

import xml.dom.minidom, xlrd, string, uuid;

def getElementsByTagNameImmediate(parent, name):
    rc = [];
    for node in parent.childNodes:
        if node.nodeType == node.ELEMENT_NODE and \
            (name == "*" or node.tagName == name):
            rc.append(node)
    return rc

def setText( nodeM, str ):
    for node in nodeM.childNodes:
        if node.nodeType == node.TEXT_NODE:
            node.nodeValue = str;

path = "/MiniGames/Minigame02/Paint/Paint05/";
levels = 16;
xmldata = xml.dom.minidom.parse( "PainterParams.xdb" );
copyDocElement = xmldata.documentElement;

book = xlrd.open_workbook( "paint.xls" );
sh = book.sheet_by_index( 0 );
#fragments = sh.ncols - 1;
prevcolor = "";
pos = 1;
k = 10000.0 / 1024.0;
prevfragments = 0;
pm = 0;

for level in range( levels ):
	filename = "PainterParams%02d" % level;
	internalfn = path + filename;
	fullname = filename + ".xdb";
	fragments = len( sh.row( 0 ) ) - 2;
	for f in range( fragments ):
		if sh.cell_value( rowx = level + 4, colx = f + 1 ) == "":
			fragments = f;
			break;
	if ( prevfragments != fragments ):
		pm = pm + 1;
		prevfragments = fragments;

	print fragments;
	
	listFragments = copyDocElement.getElementsByTagName( "listFragments" )[0];
	items = getElementsByTagNameImmediate( listFragments, "Item" );

	for frag in range( fragments ):
		if frag >= len( items ):
			newNode = items[0].cloneNode( True );
			listFragments.appendChild( newNode );
		else:
			newNode = items[frag];
		
		color = sh.cell_value( rowx = 1, colx = frag + 1 );
		
		if ( prevcolor == color ):
			pos = pos + 1;
		else:
			prevcolor = color;
			pos = 1;
		
		setText( newNode.getElementsByTagName( "fragmentColor" )[0], color );
		setText( newNode.getElementsByTagName( "pointColor" )[0], color );
		setText( newNode.getElementsByTagName( "xCoord" )[0], "%d" % ( sh.cell_value( rowx = 2, colx = frag + 1 ) * k ) );
		setText( newNode.getElementsByTagName( "yCoord" )[0], "%d" % ( sh.cell_value( rowx = 3, colx = frag + 1 ) * k ) );
		setText( newNode.getElementsByTagName( "pointCapacity" )[0], "%d" % sh.cell_value( rowx = level + 4, colx = frag + 1 ) );
		setText( newNode.getElementsByTagName( "paintFragmentId" )[0], str( frag ) );
		newNode.getElementsByTagName( "Item" )[0].setAttribute( "href", internalfn );
		newNode.getElementsByTagName( "Item" )[0].setAttribute( "id", str( uuid.uuid4() ) );
		#newNode.getElementsByTagName( "completeEffectMaterial" )[0].setAttribute( "href", "%sFX%s%02d.MTRL" % (path, color, pos) );
		newNode.getElementsByTagName( "completeEffectMaterial" )[0].setAttribute( "href", "/MiniGames/Minigame02/Paint/Paint05/FXblack01.MTRL" );
	
	copyDocElement.getElementsByTagName( "paintMaterial" )[0].setAttribute( "href", path + ( "PaintMaterial%d.MTRL" % pm ) );
	file = open( fullname, "wb+" );
	file.write( "\xEF\xBB\xBF" + xmldata.toxml( encoding="utf-8" ) );
	file.close();	

