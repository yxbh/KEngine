#include <KEngine/Common/JSONReader.hpp>
#include <KEngine/Dev/dbg.hpp>
#include <fstream>
#include <functional>

namespace ke
{

bool JSONReader::load(const std::string & p_rPath)
{
    std::ifstream json_file;
    json_file.open(p_rPath);

    if (!json_file)
    {
        ke::Debug::printError("JSONReader::Load : failed to load file at \"" + p_rPath + '\"');
        return false;
    }

    char c_buf;
    std::string json_doc; json_doc.reserve(8192);
    while (json_file.get(c_buf))
        json_doc += c_buf;
    json_file.clear();
    json_file.close();

    return this->parse(json_doc);
}

bool JSONReader::parse(const std::string & p_rJSONDoc)
{
    if (m_Loaded)
        ke::Debug::printWarning("JSONReader::Parse : Reader reloading with another json code.");

    try
    {
        m_Node = libjson::parse(p_rJSONDoc.c_str());
    }
    catch (std::exception & e)
    {
        ke::Debug::printError("JSONReader::Parse : failure to parse json! Error msg: " + std::string(e.what()));
        return false;
    }

    m_Loaded = true;
    return true;
}

std::string JSONReader::dumpToString(void)
{
    // make a copy and set cursor back to root object first.
    JSONReader reader_img(*this);
    while (reader_img.pointToParentMember());

    // declare a string and reserve some space for performance.
    std::string dump_str; dump_str.reserve(8192);

    // define an awesome recursive lambda to fill in the dump string.
    std::function<void(void)> recursive_dump_func = [&recursive_dump_func, &dump_str, &reader_img]() -> void
    {
        if (!reader_img.traverseThisMember() || reader_img.isTypeNull())
            return;

        dump_str += reader_img.getElementName();
        dump_str += " : ";
        dump_str += reader_img.getValueAsString();
        dump_str += '\n';

        if (reader_img.isTypeArray() || reader_img.isTypeNode())
        {
            recursive_dump_func();
            reader_img.pointToParentMember();
        }

        while (reader_img.pointToNextMember())
        {
            dump_str += reader_img.getElementName();
            dump_str += " : ";
            dump_str += reader_img.getValueAsString();
            dump_str += '\n';

            if (reader_img.isTypeArray() || reader_img.isTypeNode())
            {
                recursive_dump_func();
                reader_img.pointToParentMember();
            }
        }
    }; // /recursive_dump_func

    // call the lambda function.
    recursive_dump_func();

    // return the dump string.
    return dump_str;
}

bool JSONReader::isTypeString(void)
{
    if (!this->atRoot())
        return m_TreeITStack.top().iterator->type() == JSON_STRING;
    return m_Node.type() == JSON_STRING;
}

bool JSONReader::isTypeNumber(void)
{
    if (!this->atRoot())
        return m_TreeITStack.top().iterator->type() == JSON_NUMBER;
    return m_Node.type() == JSON_NUMBER;
}

bool JSONReader::isTypeBoolean(void)
{
    if (!this->atRoot())
        return m_TreeITStack.top().iterator->type() == JSON_BOOL;
    return m_Node.type() == JSON_BOOL;
}

bool JSONReader::isTypeArray(void)
{
    if (!this->atRoot())
        return m_TreeITStack.top().iterator->type() == JSON_ARRAY;
    return m_Node.type() == JSON_ARRAY;
}

bool JSONReader::isTypeNode(void)
{
    if (!this->atRoot())
        return m_TreeITStack.top().iterator->type() == JSON_NODE;
    return m_Node.type() == JSON_NODE;
}

bool JSONReader::isTypeNull(void)
{
    if (!this->atRoot())
        return m_TreeITStack.top().iterator->type() == JSON_NULL;
    return m_Node.type() == JSON_NULL;
}

JSONReader::SizeType JSONReader::getChildrenCount(void) const
{
    if (this->atRoot())
        return m_Node.size();
    return m_TreeITStack.top().iterator->size();
}

bool JSONReader::hasChildren(void) const
{
    if (this->atRoot())
        return !m_Node.empty();
    return !m_TreeITStack.top().iterator->empty();
}

JSONReader::StringType JSONReader::getValueAsString(void) const
{
    if (!this->atRoot())
        return m_TreeITStack.top().iterator->as_string().c_str();
    return m_Node.as_string().c_str();
}

JSONReader::NumberType JSONReader::getValueAsNumber(void) const
{
    if (!this->atRoot())
        return m_TreeITStack.top().iterator->as_float();
    return m_Node.as_float();
}

JSONReader::IntegerType JSONReader::getValueAsInt(void) const
{
    if (!this->atRoot())
        return m_TreeITStack.top().iterator->as_int();
    return m_Node.as_int();
}

JSONReader::FloatType JSONReader::getValueAsDouble(void) const
{
    if (!this->atRoot())
        return m_TreeITStack.top().iterator->as_float();
    return m_Node.as_float();
}

JSONReader::BooleanType JSONReader::getValueAsBoolean(void) const
{
    if (!this->atRoot())
        return m_TreeITStack.top().iterator->as_bool();
    return m_Node.as_bool();
}

bool JSONReader::atRoot(void) const
{
    return m_TreeITStack.empty();
}

bool JSONReader::traverseThisMember(void)
{
    // make sure it's an array first.
    if (!this->isTypeArray() && !this->isTypeNode())
        return false;

    // create a new record in the stack.
    if (this->atRoot()) //
        m_TreeITStack.push(tree_record(m_Node, m_Node.begin()));
    else
        m_TreeITStack.push(tree_record(*m_TreeITStack.top().iterator, m_TreeITStack.top().iterator->begin()));

    // check if array is empty.
    if (m_TreeITStack.top().iterator == m_TreeITStack.top().parent_member.end())
        return false;
    return true;
}

bool JSONReader::pointToNextMember(void)
{
    // cursor pointing to the root or the parent node is not an array or we are already at the last child.
    if (this->atRoot()
            || (m_TreeITStack.top().parent_member.type() != JSON_ARRAY && m_TreeITStack.top().parent_member.type() != JSON_NODE)
            || m_TreeITStack.top().iterator == m_TreeITStack.top().parent_member.end()
       )
        return false;

    // increment iterator
    ++(m_TreeITStack.top().iterator);

    // did we reach the end?
    if (m_TreeITStack.top().iterator == m_TreeITStack.top().parent_member.end())
        return false;
    return true;
}

bool JSONReader::pointToPreviousMember(void)
{
    // cursor pointing to the root or the parent node is not an array or we are already at the first child.
    if (this->atRoot()
            || (m_TreeITStack.top().parent_member.type() != JSON_ARRAY && m_TreeITStack.top().parent_member.type() != JSON_NODE)
            || m_TreeITStack.top().iterator == m_TreeITStack.top().parent_member.begin()
       )
        return false;

    // decrement iterator
    --(m_TreeITStack.top().iterator);

    // did we reach the beginning?
    if (m_TreeITStack.top().iterator == m_TreeITStack.top().parent_member.begin())
        return true; // don't actually need this statement since the first if statement protects us from going too much forward.
    return true;
}

bool JSONReader::pointToParentMember(void)
{
    if (this->atRoot())
        return false;
    m_TreeITStack.pop();
    return true;
}

bool JSONReader::pointToChildElement(const std::string p_NameKey)
{
    // if we are at root member/object.
    if (this->atRoot())
    {
        JSONNode::const_iterator it(m_Node.find(p_NameKey.c_str()));

        // if not found.
        if (it == m_Node.end()) // not found
            return false;

        // found.
        m_TreeITStack.push(tree_record(m_Node, it));
        return true;
    }

    JSONNode::const_iterator it(m_TreeITStack.top().iterator->find(p_NameKey.c_str()));
    if (it == m_TreeITStack.top().iterator->end())
        return false;

    // found.
    m_TreeITStack.push(tree_record(*m_TreeITStack.top().iterator, it));
    return true;
}

JSONReader::StringType JSONReader::getElementName(void) const
{
    if (this->atRoot())
        return m_Node.name().c_str();
    else
        return m_TreeITStack.top().iterator->name().c_str();
}

} // KE ns