

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
	NodeRef& partner() { return *thePartner; }
	const NodeRef& partner() const { return *thePartner; }
	virtual char* toString(int verbose); 
	virtual Variant evaluate(VariantParams& params) { return partner().get(); }

	size_t partnerserialnumber;

	#ifdef FLEXSIM_ENGINE_COMPILE
		void disown(NodeRef& newPartner);
		void reown();
		size_t getSaveSize();
		bool save(std::ostream& stream);
		bool load(std::istream& stream);
		int save(char*& destination);
		int load(char*& source);

		int savexml(MSXML2::IXMLDOMDocumentPtr doc, MSXML2::IXMLDOMElementPtr parentnode);
		int loadxml(MSXML2::IXMLDOMNodePtr datanode);
	#endif
};

// COPYRIGHT © 2006   F L E X S I M   C O R P O R A T I O N .  ALL RIGHTS RESERVED.

