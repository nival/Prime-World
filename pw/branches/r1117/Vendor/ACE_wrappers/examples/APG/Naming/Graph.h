// $Id: Graph.h 80826 2008-03-04 14:51:23Z wotte $

#ifndef GRAPH_H
#define GRAPH_H

#include "Graphable_Element.h"

class Graph
  {
  public:
    Graph()
    {
    }

    void graph( char * filename, Graphable_Element_List & data );
  };

#endif /* GRAPH_H */
