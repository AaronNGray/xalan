// Base header file.  Must be first.
#include <Include/PlatformDefinitions.hpp>



#include <cassert>

#if defined(XALAN_CLASSIC_IOSTREAMS)
#include <iostream.h>
#else
#include <iostream>
#endif



#if !defined(NDEBUG) && defined(_MSC_VER)
#include <crtdbg.h>
#endif



#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>



#include <Include/XalanAutoPtr.hpp>



#include <XalanDOM/XalanDocument.hpp>
#include <XalanDOM/XalanElement.hpp>



#include <PlatformSupport/XalanOutputStreamPrintWriter.hpp>
#include <PlatformSupport/XalanStdOutputStream.hpp>



#include <XMLSupport/FormatterToXML.hpp>



#include <XercesParserLiaison/FormatterToXercesDOM.hpp>
#include <XercesParserLiaison/XercesDOMFormatterWalker.hpp>



#include <XalanTransformer/XalanTransformer.hpp>



XALAN_USING_STD(cerr)
XALAN_USING_STD(cout)
XALAN_USING_STD(endl)

XALAN_USING_XERCES(DOMDocument)

XALAN_USING_XALAN(XalanCompiledStylesheet)
XALAN_USING_XALAN(XalanParsedSource)
XALAN_USING_XALAN(XalanTransformer)



void
serialize(const DOMDocument&	theDocument)
{
	XALAN_USING_XALAN(XalanStdOutputStream)
	XALAN_USING_XALAN(XalanOutputStreamPrintWriter)
	XALAN_USING_XALAN(FormatterToXML)
	XALAN_USING_XALAN(XercesDOMFormatterWalker)

	// Create an output stream and a PrintWriter for the
	// output
	XalanStdOutputStream			theStream(cout);
	XalanOutputStreamPrintWriter	thePrintWriter(theStream);

	// We're going to serialize XML...
	FormatterToXML	theFormatter(thePrintWriter);

	// Do pretty-printing...
	theFormatter.setDoIndent(true);

	theFormatter.setIndent(2);

	XercesDOMFormatterWalker	theWalker(theFormatter);

	// This will walk the document and send
	// events to the FormatterToXML.
	theWalker.traverse(&theDocument);
}



int
transformAndSerialize(
			XalanTransformer&				theTransformer,
			const XalanParsedSource&		theParsedSource,
			const XalanCompiledStylesheet&	theStylesheet)
{
	XALAN_USING_XERCES(DOMDocument)
	XALAN_USING_XERCES(DOMImplementation)
	XALAN_USING_XALAN(FormatterToXercesDOM)
	XALAN_USING_XALAN(XalanAutoPtr)

	// This is the document which we'll build...
	const XalanAutoPtr<DOMDocument>		theDocument(DOMImplementation::getImplementation()->createDocument());
	assert(theDocument.get() != 0);

	// This is a class derived from FormatterListener, which
	// we'll hook up to Xalan's output stage...
	FormatterToXercesDOM	theFormatter(theDocument.get(), 0);

	// Do the transformation...
	int		theResult =
		theTransformer.transform(
			theParsedSource,
			&theStylesheet,
			theFormatter);

	if (theResult != 0)
	{
		cerr << "Error transforming: "
			 << theTransformer.getLastError()
			 << endl;
	}
	else
	{
		serialize(*theDocument.get());
	}

	return theResult;
}



int
main(
			int				argc,
			const char*		argv[])
{
#if !defined(NDEBUG) && defined(_MSC_VER)
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
#endif

	int		theResult = 0;

	if (argc != 3)
	{
		cerr << "Usage: TransformToXercesDOM XMLFilePath XSLFilePath" << endl;

		theResult = -1;
	}
	else
	{
		try
		{
			XALAN_USING_XERCES(XMLPlatformUtils)

			XMLPlatformUtils::Initialize();

			XalanTransformer::initialize();

			{

				XalanTransformer	theTransformer;

				const XalanParsedSource*	theParsedSource = 0;

				theResult = theTransformer.parseSource(argv[1], theParsedSource);

				if (theResult != 0)
				{
					cerr << "Error parsing source document: "
						 << theTransformer.getLastError()
						 << endl;
				}
				else
				{
					assert(theParsedSource != 0);

					const XalanCompiledStylesheet*	theCompiledStylesheet = 0;

					theResult = theTransformer.compileStylesheet(argv[2], theCompiledStylesheet);

					if (theResult != 0)
					{
						cerr << "Error compiling stylesheet: "
							 << theTransformer.getLastError()
							 << endl;
					}
					else
					{
						theResult =
							transformAndSerialize(theTransformer, *theParsedSource, *theCompiledStylesheet);
					}
				}
			}

			XalanTransformer::terminate();

			XMLPlatformUtils::Terminate();
		}
		catch(...)
		{
			cerr << "Exception caught!" << endl;

			theResult = -1;
		}
	}

	return theResult;
}
