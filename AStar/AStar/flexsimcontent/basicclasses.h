#pragma once
class TreeNode;
typedef TreeNode* treenode;
class ByteBlock;
class CouplingDataType;
class AviPlayer;
class CallPoint;
class Kinematic;
class FlexSimEvent;
class EventDataStruct;
class TreeWin;
class ObjectDataType;
class SimpleDataType;
class MoveTableChunk;
struct MoveRecord;
struct StateRecord;
class StateTableChunk;
class ScenePositionCache;
class PortDrawCache;
class Cuboid;
class FRECT;
class ViewPoint;
class VisualFeatureTag;
class VisualFeatureTagList;
class UndoRecordStruct;
class PortRecord;
class SplinePoint;
class SplineCache;
class FlexSimWebBrowser;
class ExperimentChildManager;
typedef char* (*customdisplayfunction)(TreeNode*, int);
class ConsoleWin;
template<class ElementType> class FlexSimCVector;
template<class ElementType> class HashTable;
class NodeRef;
template<class ObjType> class ObjRef;
class Bundle;
class UserWindowStyle;
class Mesh;
class IndexedMesh;
class SqlDataSource;
class SqlQuery;
class FlexScriptCode;
class CppCode;
namespace Compiler {
	struct ASTNodeVector;
	struct AbstractSyntaxTree;
	struct ASTNode;
	struct CommandInfoStruct;
	struct ClassInfo;
	struct FlexScriptLambda;
};
class Variant;
class VariantParams;
class TableView;
class TableViewDataSource;
class BundleViewDataSource;
class List;

#pragma push_macro("engine_export")
#ifdef FLEXSIM_ENGINE_COMPILE
#define engine_export __declspec(dllexport)
#else
#define engine_export __declspec(dllimport)
#endif

extern "C" engine_export void* flexsimmalloc(size_t);
extern "C" engine_export void * flexsimrealloc(void* memory, size_t size);
extern "C" engine_export void flexsimfree(void * p);

#pragma pop_macro("engine_export")

