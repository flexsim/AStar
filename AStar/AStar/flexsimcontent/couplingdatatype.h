

// COPYRIGHT © 2006   F L E X S I M   C O R P O R A T I O N .  ALL RIGHTS RESERVED.

#pragma once

#ifdef FLEXSIM_ENGINE_COMPILE
	#include "msxml3.h"
#endif

#include "basicclasses.h"
#include "basicutils.h"
#include "simpledatatype.h"

class CouplingDataType : public SimpleDataType
{
private:
	NodeRef* thePartner;
	NodeRef localPartner;
public:
  
	CouplingDataType() : localPartner(0), thePartner(&localPartner), partnerserialnumber(0)
	{}
	CouplingDataType(TreeNode* x) : localPartner(x), thePartner(&localPartner), partnerserialnumber(0)
	{}
	~CouplingDataType(){}
	NodeRef& partner(){return *thePartner;}  

	size_t partnerserialnumber;

	#ifdef FLEXSIM_ENGINE_COMPILE
		void disown(NodeRef& newPartner);
		void reown();
		long unsigned int couplinggetsavesize(long unsigned int * savesize);
		bool couplingsave(std::ostream& stream);
		bool couplingload(std::istream& stream);
		int couplingsave(char* destination, long unsigned int * bytepos);
		int couplingload(char* source     , long unsigned int * bytepos);

		int couplingsavexml(MSXML2::IXMLDOMDocumentPtr doc, MSXML2::IXMLDOMElementPtr parentnode);
		int couplingloadxml(MSXML2::IXMLDOMNodePtr datanode);
	#endif
};

// COPYRIGHT © 2006   F L E X S I M   C O R P O R A T I O N .  ALL RIGHTS RESERVED.

