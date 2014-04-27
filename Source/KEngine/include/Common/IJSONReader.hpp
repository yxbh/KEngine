#pragma once
#include <string>

namespace ke
{

/** class IJSONReader
    An interface which defines a JSON reader class and it's operations.

    The interface defines a set of member functions for loading and parsing a JSON document and traversing within the resulting document
    with out the need to use iterators or multiple objects.
*/
class IJSONReader
{
public:
    using StringType    = std::string;
    using NumberType    = double;
    using IntegerType   = long int;
    using FloatType     = double;
    using BooleanType   = bool;
    using ArrayType     = void;
    using NodeType      = void;
    using SizeType      = unsigned;

public:
    IJSONReader(void) = default;
    IJSONReader(const IJSONReader &) = default;
    virtual IJSONReader & operator = (const IJSONReader &) = default;
    virtual ~IJSONReader(void) = default;

    /** parse json file at path.
    @return false if failure. */
    virtual bool parse(const std::string & p_rPath) = 0;
    /** load string with json code int it.
    @return false if failure. */
    virtual bool load(const std::string & p_rPath) = 0;
    /** @return a string dump of all the contents from the json doc.*/
    virtual std::string dumpToString(void) = 0;

    /** @return true if current pointered to member value is a string. */
    virtual bool isTypeString(void) = 0;
    /** @return true if current pointered to member value is a number. */
    virtual bool isTypeNumber(void) = 0;
    /** @return true if current pointered to member value is a boolean. */
    virtual bool isTypeBoolean(void) = 0;
    /** @return true if current pointered to member value is an array. */
    virtual bool isTypeArray(void) = 0;
    /** @return true if current pointered to member value is a JSON node. */
    virtual bool isTypeNode(void) = 0;
    /** @return true if current pointered to member value is null/blank. */
    virtual bool isTypeNull(void) = 0;

    /** @return the number of child elements the current element has. */
    virtual SizeType getChildrenCount(void) const = 0;
    /** @return true if the current pointed to element has any children elements. */
    virtual bool hasChildren(void) const = 0;

    /** @return current pointed to json node as a string. */
    virtual StringType getValueAsString(void) const = 0;
    /** @return current pointed to json node as a number. */
    virtual NumberType getValueAsNumber(void) const = 0;
    /** @return current pointed to json node as a number. */
    virtual IntegerType getValueAsInt(void) const = 0;
    /** @return current pointed to json node as a number. */
    virtual FloatType getValueAsDouble(void) const = 0;
    /** @return current pointed to json node as a boolean. */
    virtual BooleanType getValueAsBoolean(void) const = 0;

    /** @return true if cursor is point to the root object. */
    virtual bool atRoot(void) const = 0;
    /** point cursor to the first Member/child of this member.
    @return true if this member contains multiple members or the value is an non-empty array. */
    virtual bool traverseThisMember(void) = 0;
    /** point cursor to the parent member's next child member from this member if the parent is an array or member.
    @return false if there's no more. */
    virtual bool pointToNextMember(void) = 0;
    /** point cursor to the parent member's previous child member from this member if the parent is an array or member.
    @return false if there's no more. */
    virtual bool pointToPreviousMember(void) = 0;
    /** point cursor to the parent member of the currently pointed to json member.
    @return false if current pointed to node is the parent. */
    virtual bool pointToParentMember(void) = 0;
    /** find the child element with the specified key name, and point the cursor to it.
        @return true if found.*/
    virtual bool pointToChildElement(const std::string p_NameKey) = 0;

    /** @return name of the current element. */
    virtual StringType getElementName(void) const = 0;

}; // IJSONReader class.

} // KE ns