// Base header file.  Must be first.
#include <Include/PlatformDefinitions.hpp>



#include <cmath>
#include <ctime>
#if defined(XALAN_CLASSIC_IOSTREAMS)
#include <iostream.h>
#else
#include <iostream>
#endif



#include <xercesc/util/PlatformUtils.hpp>



#include <XalanTransformer/XalanTransformer.hpp>



#include <XPath/Function.hpp>
#include <XPath/XObjectFactory.hpp>



XALAN_USING_XALAN(Function)
XALAN_USING_XALAN(XPathExecutionContext)
XALAN_USING_XALAN(XalanDOMString)
XALAN_USING_XALAN(XalanNode)
XALAN_USING_XALAN(StaticStringToDOMString)
XALAN_USING_XALAN(XObjectPtr)



// This class defines a function that will return the square root
// of its argument.
class FunctionSquareRoot : public Function
{
public:

	/**
	 * Execute an XPath function object.  The function must return a valid
	 * object.  Extension functions should override this version of execute(),
	 * rather than one of the other calls designed for a specific number of
	 * arguments.
	 *
	 * @param executionContext executing context
	 * @param context          current context node
	 * @param args             vector of pointers to XObject arguments
	 * @param locator		   Locator for the XPath expression that contains the function call
	 * @return                 pointer to the result XObject
	 */
	virtual XObjectPtr
	execute(
			XPathExecutionContext&			executionContext,
			XalanNode*						context,
			const XObjectArgVectorType&		args,
			const LocatorType*				locator) const
	{
		if (args.size() != 1)
		{
			executionContext.error(getError(), context, locator);
		}

		assert(args[0].null() == false);	

#if defined(XALAN_STRICT_ANSI_HEADERS)
		using std::sqrt;
#endif

		return executionContext.getXObjectFactory().createNumber(sqrt(args[0]->num()));
	}

#if !defined(XALAN_NO_USING_DECLARATION)
	using Function::execute;
#endif

	/**
	 * Create a copy of the function object.
	 *
	 * @return pointer to the new object
	 */
#if defined(XALAN_NO_COVARIANT_RETURN_TYPE)
	virtual Function*
#else
	virtual FunctionSquareRoot*
#endif
	clone() const
	{
		return new FunctionSquareRoot(*this);
	}

protected:

	/**
	 * Get the error message to report when
	 * the function is called with the wrong
	 * number of arguments.
	 *
	 * @return function error message
	 */
	const XalanDOMString
	getError() const
	{
		return StaticStringToDOMString(XALAN_STATIC_UCODE_STRING("The square-root() function accepts one argument!"));
	}

private:

	// Not implemented...
	FunctionSquareRoot&
	operator=(const FunctionSquareRoot&);

	bool
	operator==(const FunctionSquareRoot&) const;
};



// This class defines a function that will return the cube
// of its argument.
class FunctionCube : public Function
{
public:

	/**
	 * Execute an XPath function object.  The function must return a valid
	 * object.  Extension functions should override this version of execute(),
	 * rather than one of the other calls designed for a specific number of
	 * arguments.
	 *
	 * @param executionContext executing context
	 * @param context          current context node
	 * @param args             vector of pointers to XObject arguments
	 * @param locator		   Locator for the XPath expression that contains the function call
	 * @return                 pointer to the result XObject
	 */
	virtual XObjectPtr
	execute(
			XPathExecutionContext&			executionContext,
			XalanNode*						context,
			const XObjectArgVectorType&		args,
			const LocatorType*				locator) const
	{
		if (args.size() != 1)
		{
			executionContext.error(getError(), context, locator);
		}

		assert(args[0].null() == false);	

#if defined(XALAN_STRICT_ANSI_HEADERS)
		using std::pow;
#endif

		return executionContext.getXObjectFactory().createNumber(pow(args[0]->num(), 3));
	}

#if !defined(XALAN_NO_USING_DECLARATION)
	using Function::execute;
#endif

	/**
	 * Create a copy of the function object.
	 *
	 * @return pointer to the new object
	 */
#if defined(XALAN_NO_COVARIANT_RETURN_TYPE)
	virtual Function*
#else
	virtual FunctionCube*
#endif
	clone() const
	{
		return new FunctionCube(*this);
	}

protected:

	/**
	 * Get the error message to report when
	 * the function is called with the wrong
	 * number of arguments.
	 *
	 * @return function error message
	 */
	const XalanDOMString
	getError() const
	{
		return StaticStringToDOMString(XALAN_STATIC_UCODE_STRING("The cube() function accepts one argument!"));
	}

private:

	// Not implemented...
	FunctionCube&
	operator=(const FunctionCube&);

	bool
	operator==(const FunctionCube&) const;
};



// This class defines a function that runs the C function
// asctime() using the current system time.
class FunctionAsctime : public Function
{
public:

	/**
	 * Execute an XPath function object.  The function must return a valid
	 * object.  Extension functions should override this version of execute(),
	 * rather than one of the other calls designed for a specific number of
	 * arguments.
	 *
	 * @param executionContext executing context
	 * @param context          current context node
	 * @param args             vector of pointers to XObject arguments
	 * @param locator		   Locator for the XPath expression that contains the function call
	 * @return                 pointer to the result XObject
	 */
	virtual XObjectPtr
	execute(
			XPathExecutionContext&			executionContext,
			XalanNode*						context,
			const XObjectArgVectorType&		args,
			const LocatorType*				locator) const
	{
		if (args.size() != 0)
		{
			executionContext.error(getError(), context, locator);
		}

#if defined(XALAN_STRICT_ANSI_HEADERS)
		using std::time;
		using std::time_t;
		using std::localtime;
		using std::asctime;
		using std::strlen;
#endif

		time_t	theTime;

		time(&theTime);

		char* const	theTimeString = asctime(localtime(&theTime));
		assert(theTimeString != 0);

		// The resulting string has a newline character at the end,
		// so get rid of it.
		theTimeString[strlen(theTimeString) - 1] = '\0';

		return executionContext.getXObjectFactory().createString(XalanDOMString(theTimeString));
	}

#if !defined(XALAN_NO_USING_DECLARATION)
	using Function::execute;
#endif

	/**
	 * Create a copy of the function object.
	 *
	 * @return pointer to the new object
	 */
#if defined(XALAN_NO_COVARIANT_RETURN_TYPE)
	virtual Function*
#else
	virtual FunctionAsctime*
#endif
	clone() const
	{
		return new FunctionAsctime(*this);
	}

protected:

	/**
	 * Get the error message to report when
	 * the function is called with the wrong
	 * number of arguments.
	 *
	 * @return function error message
	 */
	const XalanDOMString
	getError() const
	{
		return StaticStringToDOMString(XALAN_STATIC_UCODE_STRING("The asctime() function accepts one argument!"));
	}

private:

	// Not implemented...
	FunctionAsctime&
	operator=(const FunctionAsctime&);

	bool
	operator==(const FunctionAsctime&) const;
};



int
main(
			int				argc,
			const char*		/* argv */[])
{
	XALAN_USING_STD(cerr)
	XALAN_USING_STD(endl)

	int	theResult = 0;

	if (argc != 1)
	{
		cerr << "Usage: ExternalFunction"
			 << endl
			 << endl;
	}
	else
	{
		XALAN_USING_XERCES(XMLPlatformUtils)

		XALAN_USING_XALAN(XalanTransformer)

		// Call the static initializer for Xerces.
		XMLPlatformUtils::Initialize();

		// Initialize Xalan.
		XalanTransformer::initialize();

		{
			// Create a XalanTransformer.
			XalanTransformer	theXalanTransformer;

			// The namespace for our functions...
			const XalanDOMString	theNamespace("http://ExternalFunction.xalan-c++.xml.apache.org");

			// Install the functions in the local space.  They will only
			// be installed in this instance, so no other instances
			// will know about them...
			theXalanTransformer.installExternalFunction(
				theNamespace,
				XalanDOMString("asctime"),
				FunctionAsctime());

			theXalanTransformer.installExternalFunction(
				theNamespace,
				XalanDOMString("square-root"),
				FunctionSquareRoot());

			theXalanTransformer.installExternalFunction(
				theNamespace,
				XalanDOMString("cube"),
				FunctionCube());

			// Do the transform.
			theResult = theXalanTransformer.transform("foo.xml", "foo.xsl", "foo.out");
    
			if(theResult != 0)
			{
				cerr << "ExternalFunction Error: \n" << theXalanTransformer.getLastError()
					 << endl
					 << endl;
			}
		}

		// Terminate Xalan...
		XalanTransformer::terminate();

		// Terminate Xerces...
		XMLPlatformUtils::Terminate();

		// Clean up the ICU, if it's integrated...
		XalanTransformer::ICUCleanUp();
	}

	return theResult;
}
