#ifndef FLEXSIM_EVENT_H
#define FLEXSIM_EVENT_H

#include "couplingdatatype.h"
#include "treenode.h"

class FlexSimEvent : public CouplingDataType
{
	public:
	TreeNode* object() {return partner();}
	double time;
	NodeRef involved;
	int code;
	static const int DATA_SIZE = 68;
	char data[DATA_SIZE];
	__int64 eventcounter;

	FlexSimEvent() :
			time(0),
			involved(0),
			code(0) {
		data[0] = 0;
	}

	FlexSimEvent(TreeNode* object, double time, TreeNode* involved, int code, char* _data = 0) : 
			CouplingDataType(object),
			time(time),
			involved(involved),
			code(code){
		data[0] = 0;
		if (_data) {
			char* copyPoint = data;
			// I don't use strncpy because I don't want to be dependent on <string.h>
			while ((*(copyPoint++) = *(_data++)) != 0 && copyPoint - data < 68)
				;
			data[DATA_SIZE - 1] = 0;// make sure it's null terminated
		}
	}

	virtual void execute();
	virtual const char* getClassFactory(){return "FlexSimEvent";}
	virtual void bind();
	virtual void getDescription(char* toStr, size_t maxSize);
#ifdef FLEXSIM_ENGINE_COMPILE
	CallPoint* getListenerCallPoint(){return (CallPoint*)*((void**)&(data[0]));}
	bool isChildClass() {return *((void**)this) != *((void**)&childChecker);}
private:
	static FlexSimEvent childChecker;
#endif
};

#endif
