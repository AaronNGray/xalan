// Base header file.  Must be first.
#include <Include/PlatformDefinitions.hpp>



#if defined(XALAN_CLASSIC_IOSTREAMS)
#include <fstream.h>
#include <iostream.h>
#else
#include <fstream>
#include <iostream>
#endif



#include <xercesc/util/PlatformUtils.hpp>



#include <PlatformSupport/DOMStringHelper.hpp>
#include <PlatformSupport/XalanOutputStreamPrintWriter.hpp>
#include <PlatformSupport/XalanStdOutputStream.hpp>



#include <XSLT/TraceListenerDefault.hpp>



#include <XalanTransformer/XalanTransformer.hpp>



int
main(
			int				argc,
			const char*		argv[])
{
#if !defined(XALAN_NO_NAMESPACES)
	using std::cerr;
	using std::endl;
#if defined(XALAN_STRICT_ANSI_HEADERS)
	using std::strcmp;
#endif
#endif

	// TraceListener flags...
	bool traceTemplates = false;
	bool traceTemplateChildren = false;
	bool traceGenerationEvent = false;
	bool traceSelectionEvent = false;

	if (argc < 2 || argc > 5)
	{
		cerr << "Usage: TraceListen [+ 1 or more of following] -tt -tg -ts -ttc" << endl;

		return -1;
	}

	// Set the TraceListener flags...
	for (int i = 1;	i < argc;	i ++)
	{
		if(!strcmp("-tt", argv[i]))
		{
			traceTemplates = true;
		}
		else if(!strcmp("-tg", argv[i]))
		{
			traceGenerationEvent = true;
		}
		else if(!strcmp("-ts", argv[i]))
		{
			traceSelectionEvent = true;
		}
		else if(!strcmp("-ttc", argv[i]))
		{
			traceTemplateChildren = true;
		}
		else
		{
  			cerr << "Usage: TraceListen [+ 1 or more of following] -tt -tg -ts -ttc" << endl;

			return -1;
		}
	} 
 
	try
	{
		// Initialize Xerces...
		XMLPlatformUtils::Initialize();

		// Initialize Xalan...
		XalanTransformer::initialize();

		{
			// Create a XalanTransformer.
			XalanTransformer	theXalanTransformer;

			const XalanDOMString	theXMLFileName("birds.xml");
			const XalanDOMString	theXSLFileName("birds.xsl");

			// Our input sources...
			const XSLTInputSource	theInputSource(c_wstr(theXMLFileName));
			const XSLTInputSource	theStylesheetSource(c_wstr(theXSLFileName));

			// Our output target...
			const XalanDOMString	theOutputFile("birds.out");
			XSLTResultTarget		theResultTarget(theOutputFile);

			// Set up a diagnostic writer to be used by the TraceListener...
			XalanStdOutputStream			theStdErr(cerr);
			XalanOutputStreamPrintWriter	diagnosticsWriter(theStdErr);

			// Make sure that error reporting, which includes any TraceListener output
			// does not throw exceptions when transcoding, since that could result in
			// an exception being thrown while another exception is active.  In particular,
			// characters that the TraceListener writes might not be representable in the
			// local code page.
			theStdErr.setThrowTranscodeException(false);

			// Set up the TraceListener... 
			TraceListenerDefault		theTraceListener(				
					diagnosticsWriter,
					traceTemplates,
					traceTemplateChildren,
					traceGenerationEvent,
					traceSelectionEvent);

			// Add the TraceListener to the XalanTransformer instance...
			theXalanTransformer.addTraceListener(&theTraceListener);

			// Our input files assume the executable will be run
			// from same directory as the input files.
			const int	theResult = theXalanTransformer.transform("birds.xml", "birds.xsl", "birds.out");

			if(theResult != 0)
			{
				cerr << "TraceListen Error: \n" << theXalanTransformer.getLastError()
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
	catch(...)
	{
		cerr << "Exception caught!  Exiting..." << endl;
	}

	return 0;
}
