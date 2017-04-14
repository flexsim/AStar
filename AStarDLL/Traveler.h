#include "AStarClasses.h"
#include "FlexsimDefs.h"
#include <list>
#include "AStarTypes.h"

namespace AStar {


class Traveler : public CouplingDataType
{
public:
	virtual const char* getClassFactory() override { return "AStar::Traveler"; }
	virtual void bind() override;

	bool isActive = false;
	std::list<Traveler*>::iterator activeEntry;
	TravelPath travelPath;
	double nodeWidth;

	AStarNavigator* getNavigator();
	TaskExecuter* getTE() { return partner()->ownerObject->objectAs(TaskExecuter); }
	void onReset();
	void navigatePath(TravelPath&& path, bool isDistQueryOnly);
	void onArrival();
	void updateLocation();

	class ArrivalEvent : public FlexSimEvent
	{
	public:
		ArrivalEvent() : FlexSimEvent() {}
		ArrivalEvent(Traveler* object, double time) : FlexSimEvent(object->holder, time, nullptr, 0) {}
		virtual const char* getClassFactory() override { return "AStar::Traveler::ArrivalEvent"; }
		virtual void execute() override { partner()->objectAs(Traveler)->onArrival(); }
	};
	ObjRef<ArrivalEvent> arrivalEvent;

};


}