#pragma once
#include "objectdatatype.h"
#include <set>

#if defined FLEXSIM_ENGINE_COMPILE
#include "locator.h"
#endif

namespace FlexSim
{

class Group : public ObjectDataType
{
public:	
	Group() {}
	static Group* global(const char* name);

	int isMember(treenode object, int recursive = 0);
	void addMember(treenode object);
	void removeMember(treenode object);
	int length();
	int indexOf(treenode object);	
	Array toFlatArray();

	ObjectDataType* operator [] (int index);

	//Not FlexScript accessible
	int findFlatRank(treenode object);
	Array toFlatGroupArray();

private:
	bool visited;
	
	virtual void bindVariables() override;
	engine_export virtual void bindInterface() override;

	static TreeNode* getGroupAtt(ObjectDataType* other) { return other->assertAttribute("Groups", 0); }
	NodeListArray<ObjectDataType, NodeListArray<ObjectDataType>::CustomCouplingAdder<getGroupAtt>>::ObjCouplingType members;
	
	int isMemberRecursive(treenode object);

	void buildMemberArray(Array& arr, std::set<treenode>& set);
	void buildGroupArray(Array& arr);
	void markGroupsUnvisited();

	operator treenode() { return holder; };
	operator Variant() { return holder; };
};

}