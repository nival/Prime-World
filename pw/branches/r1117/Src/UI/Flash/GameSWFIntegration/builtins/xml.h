/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is [Open Source Virtual Machine].
 *
 * The Initial Developer of the Original Code is
 * Adobe System Incorporated.
 * Portions created by the Initial Developer are Copyright (C) 2008
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Adobe AS3 Team
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

/* machine generated file -- do not edit */

#define AVMTHUNK_VERSION 5

namespace avmplus {
    class ArrayObject; //Array
    class String; //String
    class XMLNodeClass; //flash.xml::XMLNode$
    class XMLNodeObject; //flash.xml::XMLNode
    class XMLParserClass; //flash.xml::XMLParser$
    class XMLParserObject; //flash.xml::XMLParser
    class XMLTagClass; //flash.xml::XMLTag$
    class XMLTagObject; //flash.xml::XMLTag
}

namespace avmplus { namespace NativeID {

extern const uint32_t xml_abc_class_count;
extern const uint32_t xml_abc_script_count;
extern const uint32_t xml_abc_method_count;
extern const uint32_t xml_abc_length;
extern const uint8_t xml_abc_data[];
AVMTHUNK_DECLARE_NATIVE_INITIALIZER(xml)

/* classes */
const uint32_t abcclass_flash_xml_XMLNode = 0;
const uint32_t abcclass_flash_xml_XMLNodeType = 1;
const uint32_t abcclass_flash_xml_XMLParser = 2;
const uint32_t abcclass_flash_xml_XMLTag = 3;
const uint32_t abcclass_flash_xml_XMLDocument = 4;

/* methods */
const uint32_t flash_xml_XMLNode_private_escapeXML = 2;
const uint32_t flash_xml_XMLParser_getNext = 22;
const uint32_t flash_xml_XMLParser_startParse = 23;
const uint32_t flash_xml_XMLTag_value_get = 26;
const uint32_t flash_xml_XMLTag_value_set = 27;
const uint32_t flash_xml_XMLTag_type_set = 28;
const uint32_t flash_xml_XMLTag_type_get = 29;
const uint32_t flash_xml_XMLTag_empty_set = 30;
const uint32_t flash_xml_XMLTag_attrs_set = 31;
const uint32_t flash_xml_XMLTag_empty_get = 32;
const uint32_t flash_xml_XMLTag_attrs_get = 33;

extern AvmBox xml_s2a_os_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_xml_XMLNode_private_escapeXML_thunk  xml_s2a_os_thunk

extern AvmBox xml_v2a_ob_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_xml_XMLTag_empty_set_thunk  xml_v2a_ob_thunk

extern AvmBox xml_v2a_oa_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_xml_XMLTag_attrs_set_thunk  xml_v2a_oa_thunk

extern AvmBox xml_b2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_xml_XMLTag_empty_get_thunk  xml_b2a_o_thunk

extern AvmBox xml_u2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_xml_XMLTag_type_get_thunk  xml_u2a_o_thunk

extern AvmBox xml_a2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_xml_XMLTag_attrs_get_thunk  xml_a2a_o_thunk

extern AvmBox xml_v2a_ou_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_xml_XMLTag_type_set_thunk  xml_v2a_ou_thunk

extern AvmBox xml_v2a_osb_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_xml_XMLParser_startParse_thunk  xml_v2a_osb_thunk

extern AvmBox xml_v2a_os_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_xml_XMLTag_value_set_thunk  xml_v2a_os_thunk

extern AvmBox xml_s2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_xml_XMLTag_value_get_thunk  xml_s2a_o_thunk

extern AvmBox xml_i2a_oo_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_xml_XMLParser_getNext_thunk  xml_i2a_oo_thunk

class SlotOffsetsAndAsserts;
// flash.xml::XMLNode$
//-----------------------------------------------------------
class XMLNodeClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_XMLNodeClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::XMLNodeClassSlots EmptySlotsStruct_XMLNodeClass
//-----------------------------------------------------------

// flash.xml::XMLNode
//-----------------------------------------------------------
class XMLNodeObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
    REALLY_INLINE uint32_t get_nodeType() const { return m_nodeType; }
    void set_nodeType(uint32_t newVal);
    REALLY_INLINE XMLNodeObject* get_previousSibling() const { return m_previousSibling; }
    void set_previousSibling(XMLNodeObject* obj, XMLNodeObject* newVal);
    REALLY_INLINE XMLNodeObject* get_firstChild() const { return m_firstChild; }
    void set_firstChild(XMLNodeObject* obj, XMLNodeObject* newVal);
    REALLY_INLINE XMLNodeObject* get_nextSibling() const { return m_nextSibling; }
    void set_nextSibling(XMLNodeObject* obj, XMLNodeObject* newVal);
    REALLY_INLINE XMLNodeObject* get_parentNode() const { return m_parentNode; }
    void set_parentNode(XMLNodeObject* obj, XMLNodeObject* newVal);
    REALLY_INLINE ArrayObject* get_private__childNodes() const { return m_private__childNodes; }
    void set_private__childNodes(XMLNodeObject* obj, ArrayObject* newVal);
    REALLY_INLINE XMLNodeObject* get_lastChild() const { return m_lastChild; }
    void set_lastChild(XMLNodeObject* obj, XMLNodeObject* newVal);
    REALLY_INLINE AvmString get_nodeValue() const { return m_nodeValue; }
    void set_nodeValue(XMLNodeObject* obj, AvmString newVal);
    REALLY_INLINE AvmString get_nodeName() const { return m_nodeName; }
    void set_nodeName(XMLNodeObject* obj, AvmString newVal);
    REALLY_INLINE AvmBox get_private__attributes() const { return m_private__attributes; }
    void set_private__attributes(XMLNodeObject* obj, AvmBox newVal);
private:
    uint32_t m_nodeType;
    DRCWB(XMLNodeObject*) m_previousSibling;
    DRCWB(XMLNodeObject*) m_firstChild;
    DRCWB(XMLNodeObject*) m_nextSibling;
    DRCWB(XMLNodeObject*) m_parentNode;
    DRCWB(ArrayObject*) m_private__childNodes;
    DRCWB(XMLNodeObject*) m_lastChild;
    DRCWB(AvmString) m_nodeValue;
    DRCWB(AvmString) m_nodeName;
    ATOM_WB m_private__attributes;
};
REALLY_INLINE void XMLNodeObjectSlots::set_nodeType(uint32_t newVal) { m_nodeType = newVal; }
REALLY_INLINE void XMLNodeObjectSlots::set_previousSibling(XMLNodeObject* obj, XMLNodeObject* newVal)
{
    m_previousSibling.set(((ScriptObject*)obj)->gc(), obj, newVal);
}
REALLY_INLINE void XMLNodeObjectSlots::set_firstChild(XMLNodeObject* obj, XMLNodeObject* newVal)
{
    m_firstChild.set(((ScriptObject*)obj)->gc(), obj, newVal);
}
REALLY_INLINE void XMLNodeObjectSlots::set_nextSibling(XMLNodeObject* obj, XMLNodeObject* newVal)
{
    m_nextSibling.set(((ScriptObject*)obj)->gc(), obj, newVal);
}
REALLY_INLINE void XMLNodeObjectSlots::set_parentNode(XMLNodeObject* obj, XMLNodeObject* newVal)
{
    m_parentNode.set(((ScriptObject*)obj)->gc(), obj, newVal);
}
REALLY_INLINE void XMLNodeObjectSlots::set_private__childNodes(XMLNodeObject* obj, ArrayObject* newVal)
{
    m_private__childNodes.set(((ScriptObject*)obj)->gc(), obj, newVal);
}
REALLY_INLINE void XMLNodeObjectSlots::set_lastChild(XMLNodeObject* obj, XMLNodeObject* newVal)
{
    m_lastChild.set(((ScriptObject*)obj)->gc(), obj, newVal);
}
REALLY_INLINE void XMLNodeObjectSlots::set_nodeValue(XMLNodeObject* obj, AvmString newVal)
{
    m_nodeValue.set(((ScriptObject*)obj)->gc(), obj, newVal);
}
REALLY_INLINE void XMLNodeObjectSlots::set_nodeName(XMLNodeObject* obj, AvmString newVal)
{
    m_nodeName.set(((ScriptObject*)obj)->gc(), obj, newVal);
}
REALLY_INLINE void XMLNodeObjectSlots::set_private__attributes(XMLNodeObject* obj, AvmBox newVal)
{
    m_private__attributes.set(((ScriptObject*)obj)->gc(), obj, newVal);
}
#define DECLARE_SLOTS_XMLNodeObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
    protected: \
        REALLY_INLINE uint32_t get_nodeType() const { return m_slots_XMLNodeObject.get_nodeType(); } \
        REALLY_INLINE void set_nodeType(uint32_t newVal) { m_slots_XMLNodeObject.set_nodeType(newVal); } \
        REALLY_INLINE XMLNodeObject* get_previousSibling() const { return m_slots_XMLNodeObject.get_previousSibling(); } \
        REALLY_INLINE void set_previousSibling(XMLNodeObject* newVal) { m_slots_XMLNodeObject.set_previousSibling(this, newVal); } \
        REALLY_INLINE XMLNodeObject* get_firstChild() const { return m_slots_XMLNodeObject.get_firstChild(); } \
        REALLY_INLINE void set_firstChild(XMLNodeObject* newVal) { m_slots_XMLNodeObject.set_firstChild(this, newVal); } \
        REALLY_INLINE XMLNodeObject* get_nextSibling() const { return m_slots_XMLNodeObject.get_nextSibling(); } \
        REALLY_INLINE void set_nextSibling(XMLNodeObject* newVal) { m_slots_XMLNodeObject.set_nextSibling(this, newVal); } \
        REALLY_INLINE XMLNodeObject* get_parentNode() const { return m_slots_XMLNodeObject.get_parentNode(); } \
        REALLY_INLINE void set_parentNode(XMLNodeObject* newVal) { m_slots_XMLNodeObject.set_parentNode(this, newVal); } \
        REALLY_INLINE ArrayObject* get_private__childNodes() const { return m_slots_XMLNodeObject.get_private__childNodes(); } \
        REALLY_INLINE void set_private__childNodes(ArrayObject* newVal) { m_slots_XMLNodeObject.set_private__childNodes(this, newVal); } \
        REALLY_INLINE XMLNodeObject* get_lastChild() const { return m_slots_XMLNodeObject.get_lastChild(); } \
        REALLY_INLINE void set_lastChild(XMLNodeObject* newVal) { m_slots_XMLNodeObject.set_lastChild(this, newVal); } \
        REALLY_INLINE AvmString get_nodeValue() const { return m_slots_XMLNodeObject.get_nodeValue(); } \
        REALLY_INLINE void set_nodeValue(AvmString newVal) { m_slots_XMLNodeObject.set_nodeValue(this, newVal); } \
        REALLY_INLINE AvmString get_nodeName() const { return m_slots_XMLNodeObject.get_nodeName(); } \
        REALLY_INLINE void set_nodeName(AvmString newVal) { m_slots_XMLNodeObject.set_nodeName(this, newVal); } \
        REALLY_INLINE AvmBox get_private__attributes() const { return m_slots_XMLNodeObject.get_private__attributes(); } \
        REALLY_INLINE void set_private__attributes(AvmBox newVal) { m_slots_XMLNodeObject.set_private__attributes(this, newVal); } \
    private: \
        avmplus::NativeID::XMLNodeObjectSlots m_slots_XMLNodeObject
//-----------------------------------------------------------

// flash.xml::XMLParser$
//-----------------------------------------------------------
class XMLParserClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_XMLParserClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::XMLParserClassSlots EmptySlotsStruct_XMLParserClass
//-----------------------------------------------------------

// flash.xml::XMLParser
//-----------------------------------------------------------
class XMLParserObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_XMLParserObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::XMLParserObjectSlots EmptySlotsStruct_XMLParserObject
//-----------------------------------------------------------

// flash.xml::XMLTag$
//-----------------------------------------------------------
class XMLTagClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_XMLTagClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::XMLTagClassSlots EmptySlotsStruct_XMLTagClass
//-----------------------------------------------------------

// flash.xml::XMLTag
//-----------------------------------------------------------
class XMLTagObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_XMLTagObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::XMLTagObjectSlots EmptySlotsStruct_XMLTagObject
//-----------------------------------------------------------

} }
