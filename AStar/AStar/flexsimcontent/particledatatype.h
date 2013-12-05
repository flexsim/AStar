

// COPYRIGHT © 2006   F L E X S I M   C O R P O R A T I O N .  ALL RIGHTS RESERVED.

#ifndef particledatatype_h
#define particledatatype_h

//class TreeNode; 

#include "treenode.h"

class ParticleDataType
{
public:
  
	ParticleDataType():
		version(0),
		red(1),
		green(1),
		blue(1),
		shapeindex(1),
		imageindex(1),
		_x(0),
		_y(0),
		_z(0),
		_sx(1),
		_sy(1),
		_sz(1),
		_rx(0),
		_ry(0),
		_rz(0),
		timecreation(0),
		timelastmove(0),
		data(0),
		type(0)
	{}


	TreeNode * holder;
	int version;

	int shapeindex;
	int imageindex;

	float red;
	float green;
	float blue;

	float _x;
	float _y;
	float _z;
	float _sx;
	float _sy;
	float _sz;
	float _rx;
	float _ry;
	float _rz;

	double timecreation;
	double timelastmove;

	void * data;
	BYTE type;

	#ifdef FLEXSIM_ENGINE_COMPILE
		size_t getSaveSize();

		int load(char*& source);
		int save(char*& destination);
		bool save(std::ostream& stream);
		bool load(std::istream& stream);
		int reset();
		int savexml(MSXML2::IXMLDOMDocumentPtr doc, MSXML2::IXMLDOMElementPtr parentnode);
		int loadxml(MSXML2::IXMLDOMNodePtr datanode);
   
		int datatostring(char *, int n);
		int stringtodata(char *);
	#endif
};


#endif
