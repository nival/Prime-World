package flash.xml
{

    [native(cls="XMLNodeClass", instance="XMLNodeObject", methods="auto")]
    public class XMLNode extends Object
    {
        public var previousSibling:XMLNode;
        public var parentNode:XMLNode;
        public var nextSibling:XMLNode;
        public var firstChild:XMLNode;
        private var _childNodes:Array;
        public var nodeValue:String;
        public var nodeType:uint;
        public var lastChild:XMLNode;
        public var nodeName:String;
        private var _attributes:Object;

        public function XMLNode(type:uint, value:String)
        {
            this.init(type, value);
            return;
        }// end function

        private native function escapeXML(value:String) : String;

        private function init(type:uint, value:String) : void
        {
            this.nodeType = type;
            if (type == 1)
            {
                this.nodeName = value;
            }
            else
            {
                this.nodeValue = value;
            }
            return;
        }// end function

        public function get namespaceURI() : String
        {
            if (this.nodeName == null)
            {
                return null;
            }
            var _loc_1:* = String(this.prefix);
            return this.getNamespaceForPrefix(_loc_1);
        }// end function

        public function get prefix() : String
        {
            if (this.nodeName == null)
            {
                return null;
            }
            var _loc_1:* = this.nodeName.indexOf(":");
            if (_loc_1 != -1)
            {
                return this.nodeName.substring(0, _loc_1);
            }
            return "";
        }// end function

        public function get attributes() : Object
        {
            if (this._attributes == null)
            {
                this._attributes = {};
            }
            return this._attributes;
        }// end function

        public function appendChild(node:XMLNode) : void
        {
            var _loc_2:XMLNode = this;
            while (_loc_2)
            {
                
                if (_loc_2 === node)
                {
                    Error.throwError(Error, 2103);
                }
                _loc_2 = _loc_2.parentNode;
            }
            if (node.parentNode === this)
            {
                return;
            }
            node.removeNode();
            if (this.lastChild === null)
            {
                this.firstChild = node;
            }
            else
            {
                this.lastChild.nextSibling = node;
            }
            node.previousSibling = this.lastChild;
            node.nextSibling = null;
            node.parentNode = this;
            this.lastChild = node;
            if (this._childNodes !== null)
            {
                this._childNodes.push(node);
            }
            return;
        }// end function

        public function insertBefore(node:XMLNode, before:XMLNode) : void
        {
            var _loc_3:uint = 0;
            if (before === null)
            {
                return this.appendChild(node);
            }
            if (before.parentNode === this)
            {
            }
            if (node.parentNode === this)
            {
                Error.throwError(Error, 2102);
            }
            node.removeNode();
            if (before.previousSibling === null)
            {
                this.firstChild = node;
            }
            else
            {
                before.previousSibling.nextSibling = node;
            }
            node.previousSibling = before.previousSibling;
            node.nextSibling = before;
            before.previousSibling = node;
            node.parentNode = this;
            if (this._childNodes !== null)
            {
                _loc_3 = 0;
                while (_loc_3 < this._childNodes.length)
                {
                    
                    if (this._childNodes[_loc_3] == before)
                    {
                        this._childNodes.splice(_loc_3, 0, node);
                        return;
                    }
                    _loc_3 = _loc_3 + 1;
                }
            }
            else
            {
                return;
            }
            Error.throwError(Error, 2102);
            return;
        }// end function

        public function getNamespaceForPrefix(prefix:String) : String
        {
            var _loc_2:String = null;
            var _loc_3:String = null;
            for (_loc_2 in this._attributes)
            {
                
                if (_loc_2.indexOf("xmlns") == 0)
                {
                    if (_loc_2.charCodeAt(5) == 58)
                    {
                        _loc_3 = _loc_2.substring(6);
                        if (_loc_3 == prefix)
                        {
                            return this._attributes[_loc_2];
                        }
                        continue;
                    }
                    if (prefix.length == 0)
                    {
                        return this._attributes[_loc_2];
                    }
                }
            }
            if (this.parentNode !== null)
            {
                return this.parentNode.getNamespaceForPrefix(prefix);
            }
            return null;
        }// end function

        public function set attributes(value:Object) : void
        {
            this._attributes = value;
            return;
        }// end function

        public function hasChildNodes() : Boolean
        {
            return this.firstChild != null;
        }// end function

        public function get childNodes() : Array
        {
            var _loc_1:XMLNode = null;
            if (this._childNodes == null)
            {
                this._childNodes = new Array();
                _loc_1 = this.firstChild;
                while (_loc_1 != null)
                {
                    
                    this._childNodes.push(_loc_1);
                    _loc_1 = _loc_1.nextSibling;
                }
            }
            return this._childNodes;
        }// end function

        public function get localName() : String
        {
            if (this.nodeName == null)
            {
                return null;
            }
            var _loc_1:* = this.nodeName.indexOf(":");
            if (_loc_1 != -1)
            {
                return this.nodeName.substring((_loc_1 + 1));
            }
            return this.nodeName;
        }// end function

        public function getPrefixForNamespace(ns:String) : String
        {
            var _loc_2:String = null;
            for (_loc_2 in this._attributes)
            {
                
                if (_loc_2.indexOf("xmlns") == 0)
                {
                    if (this._attributes[_loc_2] == ns)
                    {
                        if (_loc_2.charCodeAt(5) == 58)
                        {
                            return _loc_2.substring(6);
                        }
                        return "";
                    }
                }
            }
            if (this.parentNode !== null)
            {
                return this.parentNode.getPrefixForNamespace(ns);
            }
            return null;
        }// end function

        public function toString() : String
        {
            var _loc_2:String = null;
            var _loc_3:XMLNode = null;
            var _loc_1:String = "";
            if (this.nodeType == XMLNodeType.ELEMENT_NODE)
            {
                if (this.nodeName != null)
                {
                    _loc_1 = _loc_1 + ("<" + this.nodeName);
                }
                for (_loc_2 in this._attributes)
                {
                    
                    _loc_1 = _loc_1 + (" " + _loc_2 + "=\"" + this.escapeXML(String(this._attributes[_loc_2])) + "\"");
                }
                if (this.nodeName != null)
                {
                    if (this.hasChildNodes())
                    {
                        _loc_1 = _loc_1 + ">";
                    }
                    else
                    {
                        _loc_1 = _loc_1 + " />";
                    }
                }
                if (this.hasChildNodes())
                {
                    _loc_3 = this.firstChild;
                    while (_loc_3 != null)
                    {
                        
                        _loc_1 = _loc_1 + _loc_3.toString();
                        _loc_3 = _loc_3.nextSibling;
                    }
                    if (this.nodeName != null)
                    {
                        _loc_1 = _loc_1 + ("</" + this.nodeName + ">");
                    }
                }
            }
            else
            {
                _loc_1 = _loc_1 + this.escapeXML(this.nodeValue);
            }
            return _loc_1;
        }// end function

        public function removeNode() : void
        {
            var _loc_1:int = 0;
            if (this.parentNode === null)
            {
                return;
            }
            if (this.previousSibling === null)
            {
                this.parentNode.firstChild = this.nextSibling;
            }
            else
            {
                this.previousSibling.nextSibling = this.nextSibling;
            }
            if (this.nextSibling === null)
            {
                this.parentNode.lastChild = this.previousSibling;
            }
            else
            {
                this.nextSibling.previousSibling = this.previousSibling;
            }
            if (this.parentNode._childNodes !== null)
            {
                _loc_1 = 0;
                while (_loc_1 < this.parentNode._childNodes.length)
                {
                    
                    if (this.parentNode._childNodes[_loc_1] == this)
                    {
                        this.parentNode._childNodes.splice(_loc_1, 1);
                        break;
                    }
                    _loc_1 = _loc_1 + 1;
                }
            }
            this.parentNode = null;
            this.previousSibling = null;
            this.nextSibling = null;
            return;
        }// end function

        public function cloneNode(deep:Boolean) : XMLNode
        {
            var _loc_3:String = null;
            var _loc_4:XMLNode = null;
            var _loc_2:* = new XMLNode(this.nodeType, this.nodeType == XMLNodeType.ELEMENT_NODE ? (this.nodeName) : (this.nodeValue));
            if (this._attributes !== null)
            {
                _loc_2.attributes = {};
                for (_loc_3 in this._attributes)
                {
                    
                    _loc_2.attributes[_loc_3] = this._attributes[_loc_3];
                }
            }
            if (deep)
            {
                _loc_4 = this.firstChild;
                while (_loc_4 != null)
                {
                    
                    _loc_2.appendChild(_loc_4.cloneNode(true));
                    _loc_4 = _loc_4.nextSibling;
                }
            }
            return _loc_2;
        }// end function

    }
}
