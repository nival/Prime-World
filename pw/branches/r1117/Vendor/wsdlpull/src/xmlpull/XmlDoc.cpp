/* 
 * wsdlpull - A C++ parser  for WSDL  (Web services description language)
 * XmlNode_t and XmlDoc_t for the WsdlParser
 * Copyright (C) 2009 Daniel Rodriguez
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "xmlpull/XmlDoc.h"



  ////////////////////////////////////////////////////////////
  // XmlNode_t
  ////////////////////////////////////////////////////////////

  XmlNode_t::XmlNode_t( const std::string &p_name, size_t p_depth)
  {
    m_name = p_name;
    m_depth = p_depth;

    m_empty = p_name.empty();

    mp_parent = NULL;
    mp_prev = NULL;
    mp_next = NULL;
  }

  XmlNode_t::XmlNode_t( const XmlNode_t &p_xmlNode)
  {
    *this = p_xmlNode;
  }

  XmlNode_t &
  XmlNode_t::operator =( const XmlNode_t &p_xmlNode)
  {
    m_name = p_xmlNode.m_name;
    m_text = p_xmlNode.m_text;
    m_depth = p_xmlNode.m_depth;

    m_empty = p_xmlNode.m_empty;

    mp_parent = NULL;
    mp_prev = NULL;
    mp_next = NULL;

    m_attributes = p_xmlNode.m_attributes;
    m_mapAttributes = p_xmlNode.m_mapAttributes;

    m_mapNodes = p_xmlNode.m_mapNodes;

    this->deallocateNodes();

    for( size_t l_i = 0; l_i < p_xmlNode.m_nodes.size(); l_i++) {

      XmlNode_t *l_tmpNode = new XmlNode_t( *( p_xmlNode.m_nodes[ l_i]));

      l_tmpNode->setParent( this);

      if( l_i > 0) {
	l_tmpNode->setPrev( m_nodes.back());
        m_nodes.back()->setNext( l_tmpNode);
      }
      m_nodes.push_back( l_tmpNode);
    }

    return *this;
  }

  XmlNode_t::~XmlNode_t()
  {
    this->deallocateNodes();
  }

  void
  XmlNode_t::deallocateNodes( void)
  {
    for( size_t l_i = 0; l_i < m_nodes.size(); l_i++)
      delete m_nodes.at( l_i);
    m_nodes.clear();
  }

  void
  XmlNode_t::clear( void)
  {
    m_name.clear();
    m_text.clear();

    m_depth = 1;

    m_empty = true;

    mp_parent = NULL;
    mp_prev = NULL;
    mp_next = NULL;

    m_attributes.clear();
    m_mapAttributes.clear();

    this->deallocateNodes();
    m_mapNodes.clear();
  }

  XmlNode_t &
  XmlNode_t::getParent( void) const
  {
    return *mp_parent;
  }

  void
  XmlNode_t::setParent( XmlNode_t &p_parent)
  {
    mp_parent = &p_parent;
  }

  void
  XmlNode_t::setParent( XmlNode_t *p_parent)
  {
    mp_parent = p_parent;
  }

  XmlNode_t &
  XmlNode_t::getPrev( void) const
  {
    return *mp_prev;
  }

  void
  XmlNode_t::setPrev( XmlNode_t &p_prev)
  {
    mp_prev = &p_prev;
  }

  void
  XmlNode_t::setPrev( XmlNode_t *p_prev)
  {
    mp_prev = p_prev;
  }

  XmlNode_t &
  XmlNode_t::getNext( void) const
  {
    return *mp_next;
  }

  void
  XmlNode_t::setNext( XmlNode_t &p_next)
  {
    mp_next = &p_next;
  }

  void
  XmlNode_t::setNext( XmlNode_t *p_next)
  {
    mp_next = p_next;
  }

  const std::string &
  XmlNode_t::getName( void) const
  {
    return m_name;
  }

  void
  XmlNode_t::setName( const std::string &p_name, bool p_empty)
  {
    m_name = p_name;
    m_empty = p_empty;
  }

  const std::string &
  XmlNode_t::getText( void) const
  {
    return m_text;
  }

  size_t
  XmlNode_t::getDepth( void) const
  {
    return m_depth;
  }

  void
  XmlNode_t::setDepth( size_t p_depth)
  {
    m_depth = p_depth;
  }

  bool
  XmlNode_t::isRootNode( void) const
  {
    return mp_parent == NULL;
  }

  bool
  XmlNode_t::isTextNode( void) const
  {
    return m_nodes.empty();
  }

  XmlNode_t &
  XmlNode_t::addNode( const std::string &p_name, bool p_empty)
  {
    XmlNode_t *l_xmlNode = new XmlNode_t( p_name);
    l_xmlNode->setEmpty( p_empty);
    return this->addNode( l_xmlNode);
  }
    
  XmlNode_t &
  XmlNode_t::addNode( XmlNode_t *p_xmlNode)
  {

    m_text.clear();

    XmlNode_t *l_xmlNode = p_xmlNode;

    if( l_xmlNode == NULL)
      l_xmlNode = new XmlNode_t();

    l_xmlNode->setParent( this);

    if( m_nodes.empty() == false) {

      l_xmlNode->setPrev( m_nodes.back());
      m_nodes.back()->setNext( l_xmlNode);

    }

    l_xmlNode->setDepth( m_depth + 1);
    m_nodes.push_back( l_xmlNode);

    m_mapNodes.insert( std::make_pair( l_xmlNode->getName(), m_nodes.size() - 1));

    return *l_xmlNode;
  }
  
  void
  XmlNode_t::addAttribute( const std::string &p_name, const std::string &p_value)
  {
    m_attributes.push_back( std::make_pair( p_name, p_value));

    m_mapAttributes.insert( std::make_pair( p_name, m_attributes.size() - 1));
  }

  bool
  XmlNode_t::getAttribute( const std::string &p_name, std::string &p_result) const
  {
    MapAttributes_t::const_iterator l_it = m_mapAttributes.find( p_name);
    if( l_it == m_mapAttributes.end())
      return false;
    size_t l_index = (*l_it).second;
    p_result = m_attributes[ l_index].second;
    return true;
  }

  void
  XmlNode_t::setText( const std::string &p_text)
  {
    m_nodes.clear();

    m_text = p_text;
  }

  void
  XmlNode_t::setEmpty( bool p_empty)
  {
    m_empty = p_empty;
  }

  bool
  XmlNode_t::empty( void) const
  {
    return m_empty;
  }

  XmlNode_t *
  XmlNode_t::getNode( const std::string &p_name, size_t p_index) const
  {

    std::pair<MultiMapNodes_t::const_iterator, MultiMapNodes_t::const_iterator> l_itRange;
    l_itRange = m_mapNodes.equal_range( p_name);

    MultiMapNodes_t::const_iterator &l_itFirst = l_itRange.first;
    MultiMapNodes_t::const_iterator &l_itLast = l_itRange.second;

    XmlNode_t *l_resultNode = NULL;

    size_t l_index = 0;

    while( l_itFirst != l_itLast) {

      if( l_index == p_index) {

	l_resultNode = m_nodes[ (*l_itFirst).second];
	break;
      }
      ++l_index;
      ++l_itFirst;
    }

    return l_resultNode;
  }

  void
  XmlNode_t::getAllChildren( XmlNode_t::VectorNodePtrs_t &p_children)
  {
    p_children = m_nodes;
  }

  void
  XmlNode_t::findDirectChildren( const std::string &p_name, XmlNode_t::VectorNodePtrs_t &p_children)
  {
    for( size_t l_i = 0; l_i < m_nodes.size(); l_i++){

      if( p_name == m_nodes[ l_i]->getName())
	p_children.push_back( m_nodes[ l_i]);
    }
  }

  void
  XmlNode_t::findSelfOrChildren( const std::string &p_name, XmlNode_t::VectorNodePtrs_t &p_children, bool p_lazyRelativeMatch)
  {

    if( m_name == p_name) {
      p_children.push_back( this);
      return;
    }

    if( p_lazyRelativeMatch == true) {

      for( size_t l_i = 0; l_i < m_nodes.size(); l_i++){

	m_nodes[ l_i]->findSelfOrChildren( p_name, p_children, p_lazyRelativeMatch);

      }
    }
  }

  void
  XmlNode_t::findAny( const std::string &p_name, XmlNode_t::VectorNodePtrs_t &p_children)
  {
    if( m_name == p_name)
      p_children.push_back( this);

    for( size_t l_i = 0; l_i < m_nodes.size(); l_i++){

      m_nodes[ l_i]->findAny( p_name, p_children);

    }
  }

  bool
  XmlNode_t::operator ==( const XmlNode_t &p_xmlNode) const
  {
    return m_name == p_xmlNode.m_name;
  }

  std::ostream &
  operator <<( std::ostream &p_ostream, const XmlNode_t &p_xmlNode)
  {
    p_ostream << std::string( ( p_xmlNode.m_depth - 1) * XmlNode_t::WS_AMOUNT, ' ');

    // Output Start tag
    p_ostream << "<" << p_xmlNode.m_name;

    // Attributes
    for( size_t l_i = 0; l_i < p_xmlNode.m_attributes.size(); l_i++) {
      p_ostream << " "
		<< p_xmlNode.m_attributes[ l_i].first
		<< "=\"" << p_xmlNode.m_attributes[ l_i].second
		<< "\"";
    }
    // Close Start tag
    p_ostream << ">";

    // Output Text or child nodes
    if( p_xmlNode.isTextNode() == true) {
      // Output Text
      p_ostream << p_xmlNode.m_text;
    } else {
      p_ostream << std::endl;
      for( size_t l_i = 0; l_i < p_xmlNode.m_nodes.size(); l_i++) {
	// Output child nodes
	p_ostream << *( p_xmlNode.m_nodes[ l_i]);
      }
    }

    if( p_xmlNode.isTextNode() == false)
      p_ostream << std::string( ( p_xmlNode.m_depth - 1)* XmlNode_t::WS_AMOUNT, ' ');

    // Output End tag
    p_ostream << "</" << p_xmlNode.m_name << ">" << std::endl;

    return p_ostream;
  }

  ////////////////////////////////////////////////////////////
  // XmlDoc_t
  ////////////////////////////////////////////////////////////

  XmlDoc_t::XmlDoc_t( const XmlNode_t &p_xmlNode)
  {
    m_rootNode = p_xmlNode;

    m_processEnvAndBody = false;
    m_lazyRelativeMatch = true;
  }

  void
  XmlDoc_t::clear( void)
  {
    // m_version.clear();
    // m_encoding.clear();
    m_rootNode.clear();
  }

  void
  XmlDoc_t::setProcessEnvAndBody( bool p_processEnvAndBody)
  {
    m_processEnvAndBody = p_processEnvAndBody;
  }

  bool
  XmlDoc_t::getProcessEnvAndBody( void) const
  {
    return m_processEnvAndBody;
  }

  void
  XmlDoc_t::setLazyRelativeMatch( bool p_lazyRelativeMatch)
  {
    m_lazyRelativeMatch = p_lazyRelativeMatch;
  }

  bool
  XmlDoc_t::getLazyRelativeMatch( void) const
  {
    return m_lazyRelativeMatch;
  }

  XmlNode_t &
  XmlDoc_t::setRootNode( const XmlNode_t &p_xmlNode)
  {
    m_rootNode = p_xmlNode;
    return m_rootNode;
  }

  XmlNode_t &
  XmlDoc_t::getRootNode( void)
  {
    return m_rootNode;
  }

  const XmlNode_t &
  XmlDoc_t::getRootNode( void) const
  {
    return m_rootNode;
  }

  bool
  XmlDoc_t::xpath( const std::string &p_xpath, std::vector< std::string> &p_results, size_t p_index)
  {

    std::vector< XmlNode_t *> l_nodeSet[ 2];
    size_t l_curSetIndex = 0;

    // Seed Initial Set of nodes: either skip /Envelope/Body
    // or be it envelope
    if( m_processEnvAndBody == true) {
      l_nodeSet[ l_curSetIndex].push_back( &m_rootNode);
    } else {

      // /Envelope is the root node, no need to look for it
      // Get his first child: "Body"
      XmlNode_t *l_tmpNode = m_rootNode.getNode( "Body");

      // This shouldn't happen, as there /Envelope/Body
      // should always be there
      if( l_tmpNode == NULL)
	return false;

      // Insert all children under /Envelope/Body
      l_tmpNode->getAllChildren( l_nodeSet[ l_curSetIndex]);

      // If no children ... bail out
      if( l_nodeSet[ l_curSetIndex].empty() == true)
	return false;
    }

    std::string l_name, l_xpath;
    std::string::size_type l_slashPos = 0;
    std::string::size_type l_nonSlashPos = 0;
    size_t l_matchCounter = 0;
    bool l_matchAny = false;
    bool l_matchAttribute = false;
    bool l_lazyRelativeMatch = false;

    // Check if root match is sought
    if( p_xpath.find( "/") == 0 && p_xpath.find( "//") != 0) {

      // Find the name token
      l_slashPos = p_xpath.find( "/", 1);
      l_name = p_xpath.substr( 1, l_slashPos - 1);

      // Check the already seeded set
      for( size_t l_i = 0; l_i < l_nodeSet[ l_curSetIndex].size(); l_i++) {

	XmlNode_t *l_tmpNode = l_nodeSet[ l_curSetIndex][ l_i];

	// If a name match is found, seed the alternate set
	if( l_name == l_tmpNode->getName())
	  l_nodeSet[ !l_curSetIndex].push_back( l_tmpNode);
      }

      // Switch the main and alternate sets
      l_curSetIndex = !l_curSetIndex;

      // If root match was expected but the set is empty
      // we may safely return false
      if( l_nodeSet[ l_curSetIndex].empty() == true)
	return false;

      // Else, indicate that a match was found. This disables "lazyEvaluationMatch"
      ++l_matchCounter;
    }

    // Record the xpath expression before entering the main search loop
    l_xpath = p_xpath;

    // Do exit when we reach the End of String
    while( l_slashPos != std::string::npos) {

      // Until we see a double slash, we will not match any single node
      l_matchAny = false;
      // The local lazyRelativeMatch is false and can only once be true
      // During the first match and when the global lazyRelativeMatch is set
      l_lazyRelativeMatch = false;

      // Reduce the xpath expression to purge the already consumed tokens
      l_xpath = l_xpath.substr( l_slashPos);

      // If no further input is available ... break away
      if( l_xpath.empty() == true)
	break;

      l_slashPos = l_xpath.find( "/");

      if( l_slashPos == 0) {

	// Slash found at the beginning of the string

	// Check for a "matchAny" doubleslash
	if( l_xpath.find( "//") == 0)
	  l_matchAny = true;

	// Locate the start of the token after the slash(es)
	l_nonSlashPos = l_xpath.find_first_not_of( "/");

	// Check if there are any characters left
	// This could well be a trailing slash
	if( l_nonSlashPos == std::string::npos)
	  break;

	// Locate next slash after the token
	l_slashPos = l_xpath.find( "/", l_nonSlashPos);

	// Retrieve the token
	l_name = l_xpath.substr( l_nonSlashPos, l_slashPos - l_nonSlashPos);

      } else {

	// Next slash is somewhere in the middle of the xpath expression
	// or there are no further slashes ( l_slashPos == npos)
	// in any case the substr is from 0 to l_slashPos
	l_name = l_xpath.substr( 0, l_slashPos);

	// If no match has been done, then allow lazyRelativeMatch
	// to act (if so configured)
	if( l_matchCounter == 0 && m_lazyRelativeMatch == true)
	  l_lazyRelativeMatch = true;
      }

      // Indicate that a match happened (to avoid lazyRelativeMatch)
      ++l_matchCounter;

      // If no token is found ... bail out
      if( l_name.empty() == true)
	break;

      // Check if attribute values are sought
      if( l_name[ 0] == '@') {

	// Mark the fact that an attribut is sought
	l_matchAttribute = true;
	// Purge the "@" from the token
	l_name = l_name.substr( 1);

	// break away, since the previous token has been a match
	// and attributes are not matched in the xml tree
	// but rather extracted from the last set of matched nodes
	break;
      }

      // Clear the alternate set, as we are in a loop
      l_nodeSet[ !l_curSetIndex].clear();

      for( size_t l_i = 0; l_i < l_nodeSet[ l_curSetIndex].size(); l_i++) {

	XmlNode_t *l_tmpNode = l_nodeSet[ l_curSetIndex][ l_i];

	// Match any node according to "name" if sought
	if( l_matchAny == true)
	  l_tmpNode->findAny( l_name, l_nodeSet[ !l_curSetIndex]);
	// if lazyRelative is acting, go down the tree looking for the first match of "name"
	else if( l_lazyRelativeMatch == true)
	  l_tmpNode->findSelfOrChildren( l_name, l_nodeSet[ !l_curSetIndex], l_lazyRelativeMatch);
	// in any other case, see if any direct children matches "name"
	else
	  l_tmpNode->findDirectChildren( l_name, l_nodeSet[ !l_curSetIndex]);
      }

      // Swap the sets
      l_curSetIndex = !l_curSetIndex;

      // If no node is selected ... exit happily
      if( l_nodeSet[ l_curSetIndex].empty() == true)
	return false;
    }

    // A nodeSet should be in place, so we should be able to fill the results

    for( size_t l_i = 0; l_i < l_nodeSet[ l_curSetIndex].size(); l_i++) {

      XmlNode_t *l_tmpNode = l_nodeSet[ l_curSetIndex][ l_i];

      // According to W3C standards, nodes start at "1"
      // So we use p_index == 0 to mark that we take all nodes
      // If p_index != 0, then we will only return one result
      if( p_index == 0 || ( l_i == ( p_index - 1))) {
      
	if( l_matchAttribute == false) {
	  // Fill results with text from the node
	  p_results.push_back( l_tmpNode->getText());
	} else {
	  // Extract the attribute and add it to the results
	  std::string l_tmpAttr;
	  if( l_tmpNode->getAttribute( l_name, l_tmpAttr) == true)
	    p_results.push_back( l_tmpAttr);
	}
      }
    }

    // Tell the world if any results is being delivered back
    return ( p_results.empty() == false);
  }

  std::ostream &
  operator <<( std::ostream &p_ostream, const XmlDoc_t &p_xmlDoc)
  {
    // p_ostream << "<?xml version=\"" << m_version << "\" encoding=\"" << m_encoding << "\"" << std::endl;
    p_ostream << p_xmlDoc.m_rootNode;

    return p_ostream;
  }


