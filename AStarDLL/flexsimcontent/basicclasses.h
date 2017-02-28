#pragma once

namespace FlexSim {
class TreeNode;
typedef TreeNode* treenode;
class ByteBlock;
class CouplingDataType;
class CallPoint;
class FlexSimEvent;
class ObjectDataType;
class SimpleDataType;
class TrackedVariable;
class EventBinding;
class StatisticBinding;
class Mesh;
class IndexedMesh;
class NodeRef;
template<class ObjType> class ObjRef;
class Bundle;
template<class ElementType> class FlexSimCVector;
template<class ElementType> class HashTable;
class SqlDataSource;
class SqlQuery;
class Variant;
class VariantParams;
class VariantLValue;
class List;
typedef char* (*customdisplayfunction)(TreeNode*, int);
class SplineCache;
class TableViewDataSource;
class BundleViewDataSource;
class ListViewDataSource;
class UndoRecord;
class DebuggerUIDelegate;
class DebugInstance;
class FlexScriptCode;
class CppCode;
class FlexScriptDebugInstance;
struct PropertyBinding;
struct Property; 
struct SelfBoundProperty;

}

//class AviPlayer;
class Kinematic;
class EventDataStruct;
class TreeWin;
class ScenePositionCache;
class PortDrawCache;
class Cuboid;
class FRECT;
class ViewPoint;
class VisualFeatureTag;
class VisualFeatureTagList;
class PortRecord;
class SplinePoint;
class FlexSimWebBrowser;
class ExperimentChildManager;
class ConsoleWin;
class UserWindowStyle;
class TableView;


#pragma push_macro("engine_export")
#ifdef FLEXSIM_ENGINE_COMPILE
#define engine_export __declspec(dllexport)
#else
#define engine_export __declspec(dllimport)
#endif

#ifndef NO_AUTO_USE_FLEXSIM_NAMESPACE
using namespace FlexSim;
#endif

extern "C" engine_export void* flexsimmalloc(size_t);
extern "C" engine_export void * flexsimrealloc(void* memory, size_t size);
extern "C" engine_export void flexsimfree(void * p);

#pragma pop_macro("engine_export")

