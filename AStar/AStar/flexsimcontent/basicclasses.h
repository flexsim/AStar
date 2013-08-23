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
class ParticleDataType;
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
// auto_array_ptr is patterned after std::auto_ptr, but it "owns" an array allocated with new[]
template<class ElementType> class auto_array_ptr;
template<class ElementType> class HashTable;
template<class RefType> class SafeRef;
typedef SafeRef<TreeNode> NodeRef;
template<class ObjType> class ObjRef;
class Bundle;
struct CommandInfoStruct;
class FlexSimValue;
typedef double (*FSfptr)(CallPoint*);
class UserWindowStyle;
class Mesh;
class IndexedMesh;
class SqlDelegate;
extern void* flexsimmalloc(size_t);
extern void * flexsimrealloc(void* memory, size_t size);
extern void flexsimfree(void * p);


