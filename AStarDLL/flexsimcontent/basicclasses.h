#pragma once

namespace FlexSim {
class TreeNode;
class TreeNodeListHead;
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
class TextMesh;
class InstancedMesh;
class NodeRef;
template<class ObjType> class ObjRef;
class Bundle;
template<class ElementType> class HashTable;
class SqlDataSource;
class SqlQueryInterface;
class SqlQuery;
struct SqlCursor;
class SqlCursorAdvancer;
class Variant;
class VariantParams;
class VariantLValue;
class List;
class StatisticsCollector;
typedef char* (*CustomDisplayFunction)(TreeNode*, int);
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
class EventDataStruct;
class CodeEditor;
class Group;
class PowerPointInterface;
class PowerPointPresentation;
class PowerPointSlide;
class PowerPointShape;
class PowerPointLayout;
class SlidesArray;
class ShapesArray;
}

//class AviPlayer;
class Kinematic;
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

