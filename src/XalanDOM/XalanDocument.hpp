/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 1999 The Apache Software Foundation.  All rights 
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer. 
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:  
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Xalan" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written 
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation and was
 * originally based on software copyright (c) 1999, International
 * Business Machines, Inc., http://www.ibm.com.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */
#if !defined(XALANDOCUMENT_HEADER_GUARD_1357924680)
#define XALANDOCUMENT_HEADER_GUARD_1357924680



#include <XalanDOM/XalanDOMDefinitions.hpp>
#include <XalanDOM/XalanNode.hpp>



class XalanAttr;
class XalanCDATASection;
class XalanComment;
class XalanDocumentFragment;
class XalanDocumentType;
class XalanDOMImplementation;
class XalanElement;
class XalanEntityReference;
class XalanProcessingInstruction;
class XalanText;



/*
 * <meta name="usage" content="experimental"/>
 *
 * Base class for the DOM Document interface.
 *
 * This class is experimental and subject to change!!
 */

class XALAN_DOM_EXPORT XalanDocument : public XalanNode
{
public:

	XalanDocument();

	virtual
	~XalanDocument();

	// These interfaces are inherited from XalanNode...

	virtual XalanDOMString
	getNodeName() const = 0;

	/**
	 * Gets the value of this node, depending on its type.
	 */
	virtual XalanDOMString
	getNodeValue() const = 0;

	/**
	 * An enum value representing the type of the underlying object.
	 */
	virtual NodeType
	getNodeType() const = 0;

	/**
	 * Gets the parent of this node.
	 *
	 * All nodes, except <code>Document</code>,
	 * <code>DocumentFragment</code>, and <code>Attr</code> may have a parent.
	 * However, if a node has just been created and not yet added to the tree,
	 * or if it has been removed from the tree, a <code>null</code> Node
	 * is returned.
	 */
	virtual XalanNode*
	getParentNode() const = 0;

	/**
	 * Gets a <code>NodeList</code> that contains all children of this node.
	 *
	 * If there
	 * are no children, this is a <code>NodeList</code> containing no nodes.
	 * The content of the returned <code>NodeList</code> is "live" in the sense
	 * that, for instance, changes to the children of the node object that
	 * it was created from are immediately reflected in the nodes returned by
	 * the <code>NodeList</code> accessors; it is not a static snapshot of the
	 * content of the node. This is true for every <code>NodeList</code>,
	 * including the ones returned by the <code>getElementsByTagName</code>
	 * method.
	 */
	virtual const XalanNodeList*
	getChildNodes() const = 0;

	/**
	 * Gets the first child of this node.
	 *
	 * If there is no such node, this returns <code>null</code>.
	 */
	virtual XalanNode*
	getFirstChild() const = 0;

	/**
	 * Gets the last child of this node.
	 *
	 * If there is no such node, this returns <code>null</code>.
	 */
	virtual XalanNode*
	getLastChild() const = 0;

	/**
	 * Gets the node immediately preceding this node.
	 *
	 * If there is no such node, this returns <code>null</code>.
	 */
	virtual XalanNode*
	getPreviousSibling() const = 0;

	/**
	 * Gets the node immediately following this node.
	 *
	 * If there is no such node, this returns <code>null</code>.
	 */
	virtual XalanNode*
	getNextSibling() const = 0;

	/**
	 * Gets a <code>NamedNodeMap</code> containing the attributes of this node (if it
	 * is an <code>Element</code>) or <code>null</code> otherwise.
	 */
	virtual const XalanNamedNodeMap*
	getAttributes() const = 0;

	/**
	 * Gets the <code>Document</code> object associated with this node.
	 *
	 * This is also
	 * the <code>Document</code> object used to create new nodes. When this
	 * node is a <code>Document</code> or a <code>DocumentType</code>
	 * which is not used with any <code>Document</code> yet, this is
	 * <code>null</code>.
	 */
	virtual XalanDocument*
	getOwnerDocument() const = 0;

	//@}
	/** @name Cloning function. */
	//@{

	/**
	 * Returns a duplicate of this node.
	 *
	 * This function serves as a generic copy constructor for nodes.
	 *
	 * The duplicate node has no parent (
	 * <code>parentNode</code> returns <code>null</code>.).
	 * <br>Cloning an <code>Element</code> copies all attributes and their
	 * values, including those generated by the  XML processor to represent
	 * defaulted attributes, but this method does not copy any text it contains
	 * unless it is a deep clone, since the text is contained in a child
	 * <code>Text</code> node. Cloning any other type of node simply returns a
	 * copy of this node.
	 * @param deep If <code>true</code>, recursively clone the subtree under the
	 *	 specified node; if <code>false</code>, clone only the node itself (and
	 *	 its attributes, if it is an <code>Element</code>).
	 * @return The duplicate node.
	 */
#if defined(XALAN_NO_COVARIANT_RETURN_TYPE)
	virtual XalanNode*
#else
	virtual XalanDocument*
#endif
	cloneNode(bool deep) const = 0;

	//@}
	/** @name Functions to modify the DOM Node. */
	//@{

	/**
	 * Inserts the node <code>newChild</code> before the existing child node
	 * <code>refChild</code>.
	 *
	 * If <code>refChild</code> is <code>null</code>,
	 * insert <code>newChild</code> at the end of the list of children.
	 * <br>If <code>newChild</code> is a <code>DocumentFragment</code> object,
	 * all of its children are inserted, in the same order, before
	 * <code>refChild</code>. If the <code>newChild</code> is already in the
	 * tree, it is first removed.  Note that a <code>Node</code> that
	 * has never been assigned to refer to an actual node is == null.
	 * @param newChild The node to insert.
	 * @param refChild The reference node, i.e., the node before which the new
	 *	 node must be inserted.
	 * @return The node being inserted.
	 */
	virtual XalanNode*
	insertBefore(
			XalanNode*	newChild,
			XalanNode*	refChild) = 0;

	/**
	 * Replaces the child node <code>oldChild</code> with <code>newChild</code>
	 * in the list of children, and returns the <code>oldChild</code> node.
	 *
	 * If <CODE>newChild</CODE> is a <CODE>DocumentFragment</CODE> object,
	 * <CODE>oldChild</CODE> is replaced by all of the <CODE>DocumentFragment</CODE>
	 * children, which are inserted in the same order.
	 *
	 * If the <code>newChild</code> is already in the tree, it is first removed.
	 * @param newChild The new node to put in the child list.
	 * @param oldChild The node being replaced in the list.
	 * @return The node replaced.
	 */
	virtual XalanNode*
	replaceChild(
			XalanNode*	newChild,
			XalanNode*	oldChild) = 0;

	/**
	 * Removes the child node indicated by <code>oldChild</code> from the list
	 * of children, and returns it.
	 *
	 * @param oldChild The node being removed.
	 * @return The node removed.
	 */
	virtual XalanNode*
	removeChild(XalanNode*	oldChild) = 0;

	/**
	 * Adds the node <code>newChild</code> to the end of the list of children of
	 * this node.
	 *
	 * If the <code>newChild</code> is already in the tree, it is
	 * first removed.
	 * @param newChild The node to add.If it is a  <code>DocumentFragment</code>
	 *	 object, the entire contents of the document fragment are moved into
	 *	 the child list of this node
	 * @return The node added.
	 */
	virtual XalanNode*
	appendChild(XalanNode*	newChild) = 0;

	//@}
	/** @name Query functions. */
	//@{

	/**
	 *	This is a convenience method to allow easy determination of whether a
	 * node has any children.
	 *
	 * @return	<code>true</code> if the node has any children,
	 *	 <code>false</code> if the node has no children.
	 */
	virtual bool
	hasChildNodes() const = 0;


	//@}
	/** @name Set functions. */
	//@{


	/**
	 * Sets the value of the node.
	 *
	 * Any node which can have a nodeValue (@see getNodeValue) will
	 * also accept requests to set it to a string. The exact response to
	 * this varies from node to node -- Attribute, for example, stores
	 * its values in its children and has to replace them with a new Text
	 * holding the replacement value.
	 *
	 * For most types of Node, value is null and attempting to set it
	 * will throw DOMException(NO_MODIFICATION_ALLOWED_ERR). This will
	 * also be thrown if the node is read-only.
	 */
	virtual void
	setNodeValue(const XalanDOMString&		nodeValue) = 0;

	//@}
	/** @name Functions introduced in DOM Level 2. */
	//@{

	/**
	 * Puts all <CODE>Text</CODE>
	 * nodes in the full depth of the sub-tree underneath this <CODE>Node</CODE>, 
	 * including attribute nodes, into a "normal" form where only markup (e.g., 
	 * tags, comments, processing instructions, CDATA sections, and entity 
	 * references) separates <CODE>Text</CODE>
	 * nodes, i.e., there are no adjacent <CODE>Text</CODE>
	 * nodes. This can be used to ensure that the DOM view of a document is the 
	 * same as if it were saved and re-loaded, and is useful when operations 
	 * (such as XPointer lookups) that depend on a particular document tree 
	 * structure are to be used.
	 * <P><B>Note:</B> In cases where the document contains <CODE>CDATASections</CODE>, 
	 * the normalize operation alone may not be sufficient, since XPointers do 
	 * not differentiate between <CODE>Text</CODE>
	 * nodes and <CODE>CDATASection</CODE> nodes.</P>
	 */
	virtual void
	normalize() = 0;

	/**
	 * Tests whether the DOM implementation implements a specific
	 * feature and that feature is supported by this node.
	 * @param feature The string of the feature to test. This is the same
	 * name as what can be passed to the method <code>hasFeature</code> on
	 * <code>DOMImplementation</code>.
	 * @param version This is the version number of the feature to test. In
	 * Level 2, version 1, this is the string "2.0". If the version is not
	 * specified, supporting any version of the feature will cause the
	 * method to return <code>true</code>.
	 * @return Returns <code>true</code> if the specified feature is supported
	 * on this node, <code>false</code> otherwise.
	 */
	virtual bool
	supports(
			const XalanDOMString&	feature,
			const XalanDOMString&	version) const = 0;

	/**
	 * Get the <em>namespace URI</em> of
	 * this node, or <code>null</code> if it is unspecified.
	 * <p>
	 * This is not a computed value that is the result of a namespace lookup
	 * based on an examination of the namespace declarations in scope. It is
	 * merely the namespace URI given at creation time.
	 * <p>
	 * For nodes of any type other than <CODE>ELEMENT_NODE</CODE> and 
	 * <CODE>ATTRIBUTE_NODE</CODE> and nodes created with a DOM Level 1 method, 
	 * such as <CODE>createElement</CODE> from the <CODE>Document</CODE>
	 * interface, this is always <CODE>null</CODE>.
	 */
	virtual XalanDOMString
	getNamespaceURI() const = 0;

	/**
	 * Get the <em>namespace prefix</em>
	 * of this node, or <code>null</code> if it is unspecified.
	 */
	virtual XalanDOMString
	getPrefix() const = 0;

	/**
	 * Returns the local part of the <em>qualified name</em> of this node.
	 * <p>
	 * For nodes created with a DOM Level 1 method, such as
	 * <code>createElement</code> from the <code>Document</code> interface,
	 * it is null.
	 */
	virtual XalanDOMString
	getLocalName() const = 0;

	/**
	 * Set the <em>namespace prefix</em> of this node.
	 * <p>
	 * Note that setting this attribute, when permitted, changes 
	 * the <CODE>nodeName</CODE> attribute, which holds the <EM>qualified 
	 * name</EM>, as well as the <CODE>tagName</CODE> and <CODE>name</CODE> 
	 * attributes of the <CODE>Element</CODE> and <CODE>Attr</CODE>
	 * interfaces, when applicable.
	 * <p>
	 * Note also that changing the prefix of an 
	 * attribute, that is known to have a default value, does not make a new 
	 * attribute with the default value and the original prefix appear, since the 
	 * <CODE>namespaceURI</CODE> and <CODE>localName</CODE> do not change.
	 *
	 * @param prefix The prefix of this node.
	 * @exception DOMException
	 *	 INVALID_CHARACTER_ERR: Raised if the specified prefix contains
	 *							an illegal character.
	 * <br>
	 *	 NO_MODIFICATION_ALLOWED_ERR: Raised if this node is readonly.
	 * <br>
	 *	 NAMESPACE_ERR: Raised if the specified <CODE>prefix</CODE> is 
	 *		 malformed, if the specified prefix is "xml" and the 
	 *		 <CODE>namespaceURI</CODE> of this node is different from 
	 *		 "http://www.w3.org/XML/1998/namespace", if specified prefix is 
	 *		 "xmlns" and the <CODE>namespaceURI</CODE> is neither 
	 *		 <CODE>null</CODE> nor an empty string, or if the 
	 *		 <CODE>localName</CODE> is <CODE>null</CODE>.
	 */
	virtual void
	setPrefix(const XalanDOMString&	prefix) = 0;

	//@}

	// These interfaces are new to XalanDocument...

    /**
     * Creates an element of the type specified.
     *
     * Note that the instance returned
     * implements the Element interface, so attributes can be specified
     * directly  on the returned object.
     * @param tagName The name of the element type to instantiate.
     * @return A <code>Element</code> that reference the new element.
     */
    virtual XalanElement*
	createElement(const XalanDOMString&	tagName) = 0;

    /**
     * Creates an empty DocumentFragment object.
     *
     * @return A <code>DocumentFragment</code> that references the newly
     * created document fragment.
     */
	virtual XalanDocumentFragment*
	createDocumentFragment() = 0;

    /**
     * Creates a Text node given the specified string.
     *
     * @param data The data for the node.
     * @return A <code>Text</code> object that references the newly
     *  created text node.
     */
    virtual XalanText*
	createTextNode(const XalanDOMString&	data) = 0;

    /**
     * Creates a Comment node given the specified string.
     *
     * @param data The data for the comment.
     * @return A <code>Comment</code> that references the newly
     *  created comment node.
     */
    virtual XalanComment*
	createComment(const XalanDOMString&	data) = 0;

    /**
     * Creates a CDATASection node whose value  is the specified
     * string.
     *
     * @param data The data for the <code>CDATASection</code> contents.
     * @return A <code>CDATASection</code> object.
     * @exception DOMException
     *   NOT_SUPPORTED_ERR: Raised if this document is an HTML document.
     */
    virtual XalanCDATASection*
	createCDATASection(const XalanDOMString&	data) = 0;

    /**
     * Creates a ProcessingInstruction node given the specified
     * name and data strings.
     *
     * @param target The target part of the processing instruction.
     * @param data The data for the node.
     * @return A <code>ProcessingInstruction</code> that references the newly
     *  created PI node.
     * @exception DOMException
     *   INVALID_CHARACTER_ERR: Raised if an illegal character is specified.
     */
    virtual XalanProcessingInstruction*
	createProcessingInstruction(
			const XalanDOMString&	target,
			const XalanDOMString&	data) = 0;

    /**
     * Creates an Attr of the given name.
     *
     * Note that the
     * <code>Attr</code> instance can then be attached to an Element
     * using the <code>DOMElement::setAttribute()</code> method.
     * @param name The name of the attribute.
     * @return A new <CODE>Attr</CODE> 
     *       object with the <CODE>nodeName</CODE> attribute set to 
     *       <CODE>name</CODE>, and <CODE>localName</CODE>, <CODE>prefix</CODE>, 
     *       and <CODE>namespaceURI</CODE> set to 
     *       <CODE>null</CODE>.
     * @exception DOMException
     *   INVALID_CHARACTER_ERR: Raised if the specified name contains an
     *   illegal character.
     */
    virtual XalanAttr*
	createAttribute(const XalanDOMString&	name) = 0;

    /**
     * Creates an EntityReference object.
     *
     * @param name The name of the entity to reference.
     * @return A <code>EntityReference</code> that references the newly
     *  created EntityReference node.
     * @exception DOMException
     *   INVALID_CHARACTER_ERR: Raised if the specified name contains an
     *   illegal character.
     */
    virtual XalanEntityReference*
	createEntityReference(const XalanDOMString &name) = 0;

    //@}
    /** @name Getter functions */
    //@{
    /**
     * Get Document Type Declaration (see <code>DocumentType</code>) associated
     * with  this document.
     *
     * For documents without
     * a document type declaration this returns <code>null</code> reference object. The DOM Level
     *  1 does not support editing the Document Type Declaration, therefore
     * <code>docType</code> cannot be altered in any way.
     */
    virtual XalanDocumentType*
	getDoctype() const = 0;


    /**
     * Return the <code>DOMImplementation</code> object that handles this document.
     */
    virtual XalanDOMImplementation*
	getImplementation() const = 0;


    /**
     * Return a reference to the root element of the document.
     */
    virtual XalanElement*
	getDocumentElement() const = 0;

    /**
     * Returns a <code>NodeList</code> of all the elements with a
     * given tag name.  The returned node list is "live", in that changes
     * to the document tree made after a nodelist was initially
     * returned will be immediately reflected in the node list.
     *
     * The elements in the node list are ordered in the same order in which they
     * would be encountered in a
     * preorder traversal of the <code>Document</code> tree.
     * @param tagname The name of the tag to match on. The special value "*"
     *   matches all tags.
     * @return A reference to a NodeList containing all the matched
     *   <code>Element</code>s.
     */
    virtual XalanNodeList*
	getElementsByTagName(const XalanDOMString&		tagname) const = 0;

    //@}
    /** @name Functions introduced in DOM Level 2. */
    //@{

    /**
     * Imports a node from another document to this document. 
     * The returned node has no parent (<CODE>parentNode</CODE> is 
     * <CODE>null</CODE>). The source node is not altered or removed from the 
     * original document; this method creates a new copy of the source 
     * node.<BR>For all nodes, importing a node creates a node object owned by 
     * the importing document, with attribute values identical to the source 
     * node's <CODE>nodeName</CODE> and <CODE>nodeType</CODE>, plus the 
     * attributes related to namespaces (prefix and namespaces URI).
     *
     * <p><b>"Experimental - subject to change"</b></p>
     *
     * @param importedNode The node to import.
     * @param deep If <CODE>true</CODE>, recursively import the subtree under the 
     *      specified node; if <CODE>false</CODE>, import only the node itself, 
     *      as explained above. This does not apply to <CODE>Attr</CODE>, 
     *      <CODE>EntityReference</CODE>, and <CODE>Notation</CODE> nodes.
     * @return The imported node that belongs to this <CODE>Document</CODE>.
     * @exception DOMException
     *   NOT_SUPPORTED_ERR: Raised if the type of node being imported is 
     *                      not supported.
     */
    virtual XalanNode*
	importNode(
			XalanNode*	importedNode,
			bool		deep) = 0;

    /**
     * Creates an element of the given qualified name and 
     * namespace URI.
     *
     * <p><b>"Experimental - subject to change"</b></p>
     *
     * @param namespaceURI The <em>namespace URI</em> of
     *   the element to create.
     * @param qualifiedName The <em>qualified name</em>
     *   of the element type to instantiate.
     * @return A new <code>Element</code> object.
     * @exception DOMException
     *   INVALID_CHARACTER_ERR: Raised if the specified qualified name contains
     *                          an illegal character.
     * <br>
     *   NAMESPACE_ERR: Raised if the <CODE>qualifiedName</CODE> is 
     *      malformed, if the <CODE>qualifiedName</CODE> has a prefix and the 
     *      <CODE>namespaceURI</CODE> is <CODE>null</CODE> or an empty string, 
     *      or if the <CODE>qualifiedName</CODE> has a prefix that is "xml" and 
     *      the <CODE>namespaceURI</CODE> is different from 
     *      "http://www.w3.org/XML/1998/namespace".
     */
    virtual XalanElement*
	createElementNS(
			const XalanDOMString&	namespaceURI,
			const XalanDOMString&	qualifiedName) = 0;

    /**
     * Creates an attribute of the given qualified name and namespace
     * URI.
     *
     * <p><b>"Experimental - subject to change"</b></p>
     *
     * @param namespaceURI The <em>namespace URI</em> of
     *   the attribute to create.
     * @param qualifiedName The <em>qualified name</em>
     *   of the attribute to instantiate.
     * @return A new <code>Attr</code> object.
     * @exception DOMException
     *   INVALID_CHARACTER_ERR: Raised if the specified qualified name contains
     *                          an illegal character.
     * <br>
     *   NAMESPACE_ERR: Raised if the <CODE>qualifiedName</CODE> is 
     *      malformed, if the <CODE>qualifiedName</CODE> has a prefix and the 
     *      <CODE>namespaceURI</CODE> is <CODE>null</CODE> or an empty string, 
     *      if the <CODE>qualifiedName</CODE> has a prefix that is "xml" and the 
     *      <CODE>namespaceURI</CODE> is different from 
     *      "http://www.w3.org/XML/1998/namespace", if the 
     *      <CODE>qualifiedName</CODE> has a prefix that is "xmlns" and the 
     *      <CODE>namespaceURI</CODE> is different from 
     *      "http://www.w3.org/2000/xmlns/", or if the 
     *      <CODE>qualifiedName</CODE> is "xmlns" and the 
     *      <CODE>namespaceURI</CODE> is different from 
     *      "http://www.w3.org/2000/xmlns/".
     */
    virtual XalanAttr*
	createAttributeNS(
			const XalanDOMString& namespaceURI,
			const XalanDOMString& qualifiedName) = 0;

    /**
     * Returns a <code>NodeList</code> of all the <code>Element</code>s
     * with a given <em>local name</em> and
     * namespace URI in the order in which they would be encountered in a
     * preorder traversal of the <code>Document</code> tree.
     *
     * <p><b>"Experimental - subject to change"</b></p>
     *
     * @param namespaceURI The <em>namespace URI</em> of
     *   the elements to match on. The special value "*" matches all
     *   namespaces.
     * @param localName The <em>local name</em> of the
     *   elements to match on. The special value "*" matches all local names.
     * @return A new <code>NodeList</code> object containing all the matched
     *  <code>Element</code>s.
     */
    virtual XalanNodeList*
	getElementsByTagNameNS(
			const XalanDOMString&	namespaceURI,
			const XalanDOMString&	localName) const = 0;

    /**
     * Returns the <code>Element</code> whose ID is given by <code>elementId</code>.
     * If no such element exists, returns <code>null</code>.
     * Behavior is not defined if more than one element has this <code>ID</code>.
     * <P><B>Note:</B> The DOM implementation must have information that says 
     * which attributes are of type ID. Attributes with the name "ID" are not of 
     * type ID unless so defined. Implementations that do not know whether 
     * attributes are of type ID or not are expected to return 
     * <CODE>null</CODE>.</P>
     *
     * <p><b>"Experimental - subject to change"</b></p>
     *
     * @param elementId The unique <code>id</code> value for an element.
     * @return The matching element.
     */
    virtual XalanElement*
	getElementById(const XalanDOMString&	elementId) const = 0;

    //@}

protected:

	XalanDocument(const XalanDocument&	theSource);

	XalanDocument&
	operator=(const XalanDocument&	theSource);

	bool
	operator==(const XalanDocument&		theRHS) const;

private:
};



#endif	// !defined(XALANDOCUMENT_HEADER_GUARD_1357924680)
