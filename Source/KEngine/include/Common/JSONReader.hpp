#pragma once
// libJSON lib
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4100) // unreferenced formal parameter.
#pragma warning(disable : 4127) // conditional expression is constant.
#endif
#include "libjson_7.6.1/libjson.h"
#ifdef _MSC_VER
#pragma warning(pop)
#endif
#include <string>
#include <stack>
#include "IJSONReader.hpp"

namespace ke
{

/** class JSONReader
    A IJSONReader implementation which itself wraps around libjson.
*/
class JSONReader
    : public IJSONReader
{
public:
    using JSONResourceType  = JSONNode;
    using ArrayType         = JSONResourceType;
    using NodeType          = JSONResourceType;

    /** class tree_record
        A record of a parent JSON member & child JSON member relationship.
    */
    struct tree_record
    {
        const JSONResourceType & parent_member;
        JSONNode::const_iterator iterator;
        tree_record(const JSONResourceType & p_rParentNode, JSONNode::const_iterator p_It)
            : parent_member(p_rParentNode), iterator(p_It) {};
        tree_record(const tree_record & p_rRecord)
            : tree_record(p_rRecord.parent_member, p_rRecord.iterator) {};
        JSONReader & operator = (const tree_record & p_rRecord) = delete;
    }; // tree_record struct

private:
    bool                                    m_Loaded = false;  // loaded json code.
    JSONResourceType                        m_Node;
    bool                                    m_AtRoot = true;
    std::stack<tree_record>                 m_TreeITStack;

public:
    // omit ctor & dtor declaration because default versions will work.

    /** load & parse json file at path.
        @return false if failure. */
    virtual bool load(const std::string & p_rPath) final;
    /** load string with json code int it.
        @return false if failure. */
    virtual bool parse(const std::string & p_rJSONDoc) final;
    /** @return a string dump of all the contents from the json doc.*/
    virtual std::string dumpToString(void) final;

    /** @return true if current pointered to member value is a string. */
    virtual bool isTypeString(void) final;
    /** @return true if current pointered to member value is a number. */
    virtual bool isTypeNumber(void) final;
    /** @return true if current pointered to member value is a boolean. */
    virtual bool isTypeBoolean(void) final;
    /** @return true if current pointered to member value is an array. */
    virtual bool isTypeArray(void) final;
    /** @return true if current pointered to member value is a JSON node. */
    virtual bool isTypeNode(void) final;
    /** @return true if current pointered to member value is null/blank. */
    virtual bool isTypeNull(void) final;

    /** @return the number of child elements the current element has. */
    virtual SizeType getChildrenCount(void) const final;
    /** @return true if the current pointed to element has any children elements. */
    virtual bool hasChildren(void) const final;

    /** @return current pointed to json node as a string. */
    virtual StringType getValueAsString(void) const final;
    /** @return current pointed to json node as a number. */
    virtual NumberType getValueAsNumber(void) const final;
    /** @return current pointed to json node as an integer. */
    virtual IntegerType getValueAsInt(void) const final;
    /** @return current pointed to json node as a double. */
    virtual FloatType getValueAsDouble(void) const final;
    /** @return current pointed to json node as a boolean. */
    virtual BooleanType getValueAsBoolean(void) const final;

    /** @return true if cursor is point to the root object. */
    virtual bool atRoot(void) const final;
    /** point cursor to the first Member/child of this member.
        @return true if this member contains multiple members or the value is an non-empty array. */
    virtual bool traverseThisMember(void) final;
    /** point cursor to the parent member's next child member from this member if the parent is an array or member.
        @return false if there's no more. */
    virtual bool pointToNextMember(void) final;
    /** point cursor to the parent member's previous child member from this member if the parent is an array or member.
        @return false if there's no more. */
    virtual bool pointToPreviousMember(void) final;
    /** point cursor to the parent node of the currently pointed to json member.
        @return false if current pointed to node is the parent. */
    virtual bool pointToParentMember(void) final;
    /** find the child element with the specified key name, and point the cursor to it.
        @return true if found.*/
    virtual bool pointToChildElement(const std::string p_NameKey) final;

    /** @return name of the current element. */
    virtual StringType getElementName(void) const final;

}; // JSONReader class

} // KE ns