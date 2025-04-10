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

#ifndef __XMLDOC_HPP__
#define __XMLDOC_HPP__

#include <ostream>
#include <vector>
#include <map>
#include <string>




  class XmlNode_t {
  public:
    enum {
      WS_AMOUNT = 2,
      EMPTY_NODE = 1,
      NON_EMPTY_NODE = 0
    };

  protected:

    size_t m_depth;

    bool m_empty;

    std::string m_name;
    std::string m_text;

    typedef std::vector< std::pair< std::string, std::string> > VectorAttributes_t;
    typedef std::map< std::string, size_t> MapAttributes_t;

    VectorAttributes_t m_attributes;
    MapAttributes_t m_mapAttributes;

    typedef std::vector< XmlNode_t *> VectorNodePtrs_t;
    typedef std::multimap< std::string, size_t> MultiMapNodes_t;

    XmlNode_t *mp_parent;
    XmlNode_t *mp_prev;
    XmlNode_t *mp_next;

    VectorNodePtrs_t m_nodes;
    MultiMapNodes_t m_mapNodes;


  public:
    XmlNode_t( const std::string &p_name = "", size_t p_depth = 0);
    XmlNode_t( const XmlNode_t &p_xmlNode);

    XmlNode_t &operator =( const XmlNode_t &p_xmlNode);

    virtual ~XmlNode_t();

  private:
    void deallocateNodes( void);

  public:
    void clear( void);

    XmlNode_t &getParent( void) const;
    void setParent( XmlNode_t &p_parent);
    void setParent( XmlNode_t *p_parent);


    XmlNode_t &getPrev( void) const;
    void setPrev( XmlNode_t &p_prev);
    void setPrev( XmlNode_t *p_prev);

    XmlNode_t &getNext( void) const;
    void setNext( XmlNode_t &p_next);
    void setNext( XmlNode_t *p_next);

    const std::string &getName( void) const;
    void setName( const std::string &p_name, bool p_empty = XmlNode_t::EMPTY_NODE);

    const std::string &getText( void) const;
    void setText( const std::string &p_text);

    size_t getDepth( void) const;
    void setDepth( size_t p_depth);
    
    bool isTextNode( void) const;
    bool isRootNode( void) const;

    XmlNode_t &addNode( XmlNode_t *p_xmlNode = NULL);
    XmlNode_t &addNode( const std::string &p_name, bool p_empty);

    void addAttribute( const std::string &p_name, const std::string &p_value);
    bool getAttribute( const std::string &p_name, std::string &p_result) const;

    void setEmpty( bool p_empty);
    bool empty( void) const;

    XmlNode_t *getNode( const std::string &p_name, size_t p_index = 0) const;

    void getAllChildren( XmlNode_t::VectorNodePtrs_t &p_children);
    void findSelfOrChildren( const std::string &p_name, XmlNode_t::VectorNodePtrs_t &p_children, bool p_lazyRelativeMatch = false);
    void findAny( const std::string &p_name, XmlNode_t::VectorNodePtrs_t &p_children);
    void findDirectChildren( const std::string &p_name, XmlNode_t::VectorNodePtrs_t &p_children);

    bool operator ==( const XmlNode_t &p_xmlNode) const;

    friend std::ostream &operator <<( std::ostream &p_ostream, const XmlNode_t &p_xmlNode);

  };

  class XmlDoc_t {
  protected:
    //std::string m_version;
    //std::string m_encoding;

    XmlNode_t m_rootNode;

    bool m_processEnvAndBody;
    bool m_lazyRelativeMatch;

  public:
    XmlDoc_t( const XmlNode_t &p_xmlNode = XmlNode_t());

    void clear( void);

    void setProcessEnvAndBody( bool p_processEnvAndBody);
    bool getProcessEnvAndBody( void) const;

    void setLazyRelativeMatch( bool p_lazyRelativeMatch);
    bool getLazyRelativeMatch( void) const;

    XmlNode_t &setRootNode( const XmlNode_t &p_xmlNode);

    XmlNode_t &getRootNode( void);
    const XmlNode_t &getRootNode( void) const;

    friend std::ostream &operator <<( std::ostream &p_ostream, const XmlDoc_t &p_xmlDoc);

    bool xpath( const std::string &p_xpath, std::vector< std::string> &p_results, size_t p_index = 0);

  };


#endif
