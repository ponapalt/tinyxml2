#include "tinyxml2.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined( WIN32 )
	#include <crtdbg.h>
	_CrtMemState startMemState;
	_CrtMemState endMemState;
#endif

using namespace tinyxml2;
int gPass = 0;
int gFail = 0;

bool XmlTest (const char* testString, const char* expected, const char* found, bool noEcho )
{
	bool pass = !strcmp( expected, found );
	if ( pass )
		printf ("[pass]");
	else
		printf ("[fail]");

	if ( noEcho )
		printf (" %s\n", testString);
	else
		printf (" %s [%s][%s]\n", testString, expected, found);

	if ( pass )
		++gPass;
	else
		++gFail;
	return pass;
}


bool XmlTest( const char* testString, int expected, int found, bool noEcho )
{
	bool pass = ( expected == found );
	if ( pass )
		printf ("[pass]");
	else
		printf ("[fail]");

	if ( noEcho )
		printf (" %s\n", testString);
	else
		printf (" %s [%d][%d]\n", testString, expected, found);

	if ( pass )
		++gPass;
	else
		++gFail;
	return pass;
}


int main( int argc, const char* argv )
{
	#if defined( WIN32 )
		_CrtMemCheckpoint( &startMemState );
	#endif	

#if 0 
	{
		static const char* test = "<!--hello world\n"
			                      "          line 2\r"
			                      "          line 3\r\n"
			                      "          line 4\n\r"
			                      "          line 5\r-->";

		XMLDocument doc;
		doc.Parse( test );
		doc.Print();
	}
#endif
#if 0
	{
		static const char* test[] = {	"<element />",
									    "<element></element>",
										"<element><subelement/></element>",
									    "<element><subelement></subelement></element>",
									    "<element><subelement><subsub/></subelement></element>",
									    "<!--comment beside elements--><element><subelement></subelement></element>",
									    "<!--comment beside elements, this time with spaces-->  \n <element>  <subelement> \n </subelement> </element>",
									    "<element attrib1='foo' attrib2=\"bar\" ></element>",
									    "<element attrib1='foo' attrib2=\"bar\" ><subelement attrib3='yeehaa' /></element>",
										"<element>Text inside element.</element>",
										"<element><b></b></element>",
										"<element>Text inside and <b>bolded</b> in the element.</element>",
										"<outer><element>Text inside and <b>bolded</b> in the element.</element></outer>",
										"<element>This &amp; That.</element>",
										"<element attrib='This&lt;That' />",
										0
		};
		for( int i=0; test[i]; ++i ) {
			XMLDocument doc;
			doc.Parse( test[i] );
			doc.Print();
			printf( "----------------------------------------------\n" );
		}
	}
#endif
#if 0
	{
		static const char* test = "<element>Text before.</element>";
		XMLDocument doc;
		doc.Parse( test );
		XMLElement* root = doc.FirstChildElement();
		XMLElement* newElement = doc.NewElement( "Subelement" );
		root->InsertEndChild( newElement );
		doc.Print();
	}
	{
		XMLDocument* doc = new XMLDocument();
		static const char* test = "<element><sub/></element>";
		doc->Parse( test );
		delete doc;
	}
#endif
	{
		// Build:
		//		<element>
		//			<!--comment-->
		//			<sub attrib="1" />
		//			<sub attrib="2" />
		//			<sub attrib="3" />
		//		<element>

		XMLDocument* doc = new XMLDocument();
		doc->InsertEndChild( doc->NewElement( "element" ) );
		doc->Print();
		delete doc;
	}

	#if defined( WIN32 )
		_CrtMemCheckpoint( &endMemState );  
		//_CrtMemDumpStatistics( &endMemState );

		_CrtMemState diffMemState;
		_CrtMemDifference( &diffMemState, &startMemState, &endMemState );
		_CrtMemDumpStatistics( &diffMemState );
	#endif

	printf ("\nPass %d, Fail %d\n", gPass, gFail);
	return 0;
}