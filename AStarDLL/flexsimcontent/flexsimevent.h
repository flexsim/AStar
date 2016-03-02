#ifndef FLEXSIM_EVENT_H
#define FLEXSIM_EVENT_H

#include "couplingdatatype.h"
#include "treenode.h"

namespace FlexSim {

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

	engine_export virtual void execute();
	virtual const char* getClassFactory(){return "FlexSimEvent";}
	engine_export virtual void bind();
	engine_export virtual void getDescription(char* toStr, size_t maxSize);
protected:
	CallPoint* getListenerCallPoint(){return (CallPoint*)*((void**)&(data[0]));}
#ifdef FLEXSIM_ENGINE_COMPILE
public:
	bool isChildClass() {return *((void**)this) != *((void**)&childChecker);}
private:
	static FlexSimEvent childChecker;
#endif
};


class ValueChangeListener : public FlexSimEvent
{
public:
	enum ChangeRule {
		Change = 0,
		Increase = 1,
		Decrease = 2,
		ArriveAtValue = 3,
		IncreaseToValue = 4,
		DecreaseToValue = 5,
		IncreaseToOrThroughValue = 6,
		DecreaseToOrThroughValue = 7,
		FirstIncrease = 8,
		FirstDecrease = 9
	};
	ValueChangeListener() {}
	void setFirstOldOldValue()
	{
		if (changeRule == FirstIncrease)
			oldOldValue = DBL_MAX;
		else if (changeRule == FirstDecrease)
			oldOldValue = -DBL_MAX;
	}
	ValueChangeListener(ChangeRule changeRule, double changeValue) : changeRule(changeRule), changeValue(changeValue)
	{
		setFirstOldOldValue();
	}
	ValueChangeListener(ChangeRule changeRule) : changeRule(changeRule), changeValue(0.0)
	{
		setFirstOldOldValue();
	}

	ChangeRule changeRule;
	double changeValue;
	double oldOldValue = 0;
	engine_export virtual void bind() override;
	virtual void onChangeRuleMet(const Variant& newValue, const Variant& oldValue) {}
	engine_export virtual void execute() override;
	engine_export static bool isRuleMetForInitialValue(ChangeRule changeRule, double changeValue, double initialValue);
};

}

#endif
