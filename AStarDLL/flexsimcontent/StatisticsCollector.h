#pragma once

#include "datatypes.h"
#include "objectdatatype.h"
#include "flexsimevent.h"

#include <functional>
#include <map>

#define DATA_FORMAT_NONE 0
#define DATA_FORMAT_OBJECT 1
#define DATA_FORMAT_TIME 2
#define DATA_FORMAT_PERCENT 3

namespace FlexSim
{

#ifdef FLEXSIM_COMMANDS
visible treenode nodeaddsimpledata(treenode, SimpleDataType*, int);
#endif


#pragma region class SDTMember

template <class SDT>
class SDTMember
{
protected:
	TreeNode* memberNode;

public:
	SDT* operator->() {
		if (memberNode->dataType != DATA_SIMPLE) {
			memberNode->addSimpleData(new SDT, 1);
		}

		return memberNode->objectAs(SDT);
	}

	SDT& operator*() { return *(operator->()); }
	operator SDT*() { return operator->(); }
	operator TreeNode*&() { return memberNode; }
};

template <class CDT>
class CDTMember
{
protected:
	TreeNode* memberNode;

public:
	CDT* operator->() {
		if (memberNode->dataType != DATA_POINTERCOUPLING) {
			memberNode->addCouplingData(new CDT, 1);
		}

		return memberNode->objectAs(CDT);
	}

	CDT& operator*() { return *(operator->()); }
	operator CDT*() { return operator->(); }
	operator TreeNode*&() { return memberNode; }
};

class BundleMember
{
protected:
	TreeNode* memberNode;

public:
	Bundle* operator->() const { return memberNode->objectAs(Bundle); }
	Bundle& operator*() const { return *(operator->()); }
	operator Bundle*() const { return operator->(); }
	operator TreeNode*&() { return memberNode; }
};

#pragma endregion

#pragma region IDService
class IDServiceCore : public SimpleDataType
{
protected:
	typedef std::unordered_map<TreeNode*, std::pair<NodeRef, double>> IDMap;
	IDMap itemMap;
	double itemID = 1;
	IDMap::iterator itemMapEnd = itemMap.end();

public:
	class IDInfo : public CouplingDataType
	{
	public:
		// holder->partner() stores the reference to the object
		// holder's name stores the path
		double hash;
		ByteBlock path;

		virtual void bind() override
		{
			__super::bind();
			bindDouble(hash, true);
			bindByteBlock(path, true);
		}
		virtual const char* getClassFactory() override { return "IDServiceCoreIDInfo"; }
	};
protected:
	NodeListArray<IDInfo>::CouplingSdtSubNodeBindingType idInfoObjects;
	bool mapsBuilt = false;
	std::unordered_map<TreeNode*, IDInfo*> nodeIDMap;
	std::unordered_map<unsigned int, IDInfo*> idPathMap;

	std::unordered_map<TreeNode*, IDInfo*>::iterator nodeIDMapEnd = nodeIDMap.end();
	std::unordered_map<unsigned int, IDInfo*>::iterator idPathMapEnd = idPathMap.end();

	std::string getObjectHashPath(TreeNode* object);
	unsigned int hashPath(const char* path, size_t length);
	void buildIDInfoMaps();

	double getObjectID(TreeNode* object);
	double getItemID(TreeNode* item);

public:
	// The model IDService should not keep dead IDs.
	// The experimenter IDService, on the other hand, should,
	// because a replication might have created an object that
	// doesn't exist in the original.
	double keepDeadIDs = 0;

	void onReset();
	double getID(TreeNode* object);

	int isValueID(double id);
	TreeNode* getObjectFromID(double id);
	const char* getPathFromID(double id, const unsigned int maxDepth);

	void mergeWith(IDServiceCore* other);

	void clear();

	virtual void bind() override;
	virtual const char* getClassFactory() { return "IDServiceCore"; }
};

class IDService : public ObjectDataType
{
protected:
	static ObjRef<IDService> idService;
	static IDService& getIDService();

	ObjRef<IDServiceCore> __idServiceCore;
	TreeNode* __idServiceCoreNode;
	IDServiceCore& __getIDServiceCore();
	__declspec(property(get = __getIDServiceCore)) IDServiceCore& idServiceCore;

public:
	class IDServiceSQLSource : public SqlDataSource
	{
	public:
		virtual int getColID(int tableId, const char* colName, int& colFlags) override;
		virtual const char* enumerateColNames(int tableId, int colNum) override;
		virtual Variant getValue(int tableId, int row, int colId) override;
		// I don't need to set the value; collector tables are read-only for queries
		// I don't need to worry about table ID either
		virtual int getRowCount(int tableID) override;
		NodeRef itemInfoList;
		IDServiceSQLSource(IDService* idService);
	};

	double saved = 0;
	engine_export void enableExperimenterMode();
	engine_export void onReset();

	engine_export static double getID(TreeNode* object);

	engine_export static int isValueID(double id);
	engine_export static TreeNode* getObjectFromID(double id);
	engine_export static const char* getPathFromID(double id, int maxDepth);
	
	engine_export static Array getIDsAndPathsInBundle(TreeNode* bundleNode, const Variant& columns, int startEntry, int maxDepth);

	engine_export static void clear();
	engine_export void mergeWith(IDService* other);

	engine_export virtual void bindVariables() override;
	
	static IDService* create(TreeNode* parent);
};
#pragma endregion (classes IDService, IDServiceCore)

// This interface makes it easier to deal with the fact that both
// the statistics collector and the calculated table specify column
// formats (DATA_FORMAT_*)
class StatisticsCollector;
class CalculatedTable;
class ColumnFormatter : public ObjectDataType
{
public:
	virtual int getColumnFormat(int colNr) = 0;
	virtual Array getColumnFormats() = 0;
	virtual StatisticsCollector* toStatisticsCollector() { return nullptr; }
	virtual CalculatedTable* toCalculatedTable() { return nullptr; }
};

class StatisticsCollector : public ColumnFormatter
{
protected:
	typedef std::map<std::string, Variant> PropertyMap;
	class CollectedData
	{
	public:
		StatisticsCollector* collector = nullptr;

		// These are set in the event phase
		Group* group = nullptr;
		TreeNode* eventNode = nullptr;
		ObjectDataType* processFlowInstance = nullptr;
		std::string eventName;

		bool dataAvailable = false;
		bool rowValueAvailable = false;
		bool rowDataAvailable = false;

		// The row function iterates through all rows, setting the row object and number
		Variant rowValue;
		int rowNum;
		int rowValueIndex;

		bool colDataAvailable = false;
		// Then the row function iterates through all columns, setting the col number
		Variant colValue;
		int colNum;
		int colValueIndex;

		// Any additional properties are stored here
		PropertyMap properties;

		// This is called after every event is handled
		void clear();

		CollectedData() {}
		CollectedData(StatisticsCollector* collector) : collector(collector) {}
	};

	class CollectedDataInterface
	{
	protected:
		CollectedData* data = nullptr;
	public:
		CollectedDataInterface(CollectedData* data) : data(data) {}
		void construct(const CollectedDataInterface& other) { data = other.data; }
		CollectedDataInterface& operator =(const CollectedDataInterface& other) { data = other.data; return *this; }

		Group* __getGroup();
		TreeNode* __getEventNode();
		ObjectDataType* __getProcessFlowInstance();
		std::string __getEventName();
		Variant __getRowValue();
		int __getRowNumber();
		int __getRowValueIndex();
		Variant __getColValue();
		int __getColNumber();
		int __getColValueIndex();

		Variant __getCurrentValue();

		__declspec(property(get = __getGroup)) Group* group;
		__declspec(property(get = __getEventNode)) TreeNode* eventNode;
		__declspec(property(get = __getProcessFlowInstance)) ObjectDataType* processFlowInstance;
		__declspec(property(get = __getEventName)) std::string eventName;
		__declspec(property(get = __getRowObject)) Variant rowObject;
		__declspec(property(get = __getRowNumber)) int rowNumber;
		__declspec(property(get = __getRowValueIndex)) int rowValueIndex;
		__declspec(property(get = __getColValue)) Variant colValue;
		__declspec(property(get = __getColNumber)) int colNumber;
		__declspec(property(get = __getColValueIndex)) int colValueIndex;
		__declspec(property(get = __getCurrentValue)) Variant currentValue;

		Variant getProperty(const char* name, unsigned nameHash, bool dieHard);
		void setProperty(const char* name, unsigned nameHash, const Variant& value);

		static void bindInterface();
	};

	CollectedData __collectedData = CollectedData(this);

public:
	// Row/object map
	class NodeMapBinder : public SimpleDataType
	{
	public:
		std::unordered_map<TreeNode*, std::pair<NodeRef, int>> map;
		std::unordered_map<TreeNode*, std::pair<NodeRef, int>>::iterator mapEnd = map.end();
		void clear() { map.clear(); }
		virtual void bind() override;
		virtual const char* getClassFactory() { return "StatisticsCollectorNodeMapBinder"; }
	};

	class VariantMapBinder : public SimpleDataType
	{
	public:
		std::unordered_map<Variant, int, Variant::Hash> map;
		std::unordered_map<Variant, int, Variant::Hash>::iterator mapEnd = map.end();
		void clear() { map.clear(); }
#if defined FLEXSIM_COMMANDS
		virtual void bind()	{ __super::bind(); bindStlMap(map); }
#endif
		virtual const char* getClassFactory() { return "StatisticsCollectorVariantMapBinder"; }
	};


protected:
	SDTMember<NodeMapBinder> nodeRowMapData;
	SDTMember<VariantMapBinder> varRowMapData;

	std::pair<int, bool> getRowForVariant(const Variant& value, bool stopTracking);
	int addNewRow(const Variant& value);
	double willSort = 0;
	
	// This list keeps track of which rows are "active"
	// It is a list for quick removal and insertion;
	// a vector would be faster insertion, but much slower removal, and
	// removal happens very often.
	// Search may be O(n), but it is most likely that the 
	// search will look for elements at the begining
	// because earlier rows will deactivate before later rows.
	std::list<std::pair<int, Variant>> activeRowValueSet;
	TreeNode* _activeRowValueSetNode;
	double willDeactivate = 0;

	// This vector keeps a list of all rows that can be reused
	std::vector<int> reusableRows;
	TreeNode* _reusableRowsNode;
	double willReuseUntrackedRows = 0;

public:
	class EventReference;
	class ColumnSet;
	class Column : public SimpleDataType
	{
	public:
		enum ValueApplicationMode {
			OnEventOnly = 1,
			AtInitialize,
			Always,
		};

		double bundleFieldType = 1;
		double valueFormat = DATA_FORMAT_NONE;
		TreeNode* valueNode;
		Variant columnValue;
		double columnValueIndex = 0;

		virtual void bind() override;
		virtual const char* getClassFactory() override { return "StatisticsCollectorColumn"; }

		StatisticsCollector* __getCollector();
		__declspec(property(get = __getCollector)) StatisticsCollector* collector;

		double valueApplicationMode = (double)OnEventOnly;
		
		Variant getValue() { return valueNode->evaluate(); }
		int getBundleFieldType() { return (int)bundleFieldType;	};

		int getColumnFormat() { return (int)valueFormat; }
		bool isDynamic() { return valueApplicationMode == (double)Always; }

		virtual bool isClassType(const char* className) override {
			return strcmp(className, "StatisticsCollectorColumn") == 0;
		}

		static void eventAdder(TreeNode* x, EventReference* event);
		static void liveEventAdder(TreeNode* x, EventReference* event);
		static EventReference* eventGetter(TreeNode* x);
		NodeListArray<EventReference, eventAdder, eventGetter, 0> events;
		NodeListArray<EventReference, liveEventAdder, eventGetter, 0> liveEvents;

		virtual ColumnSet* toColumnSet() { return nullptr; }

		engine_export Variant isColumnSet(FLEXSIMINTERFACE) { return 0; }
	};

	class ColumnSet : public Column
	{
	public:
		TreeNode* setValue;

		virtual bool isClassType(const char* className) override {
			return strcmp(className, "StatisticsCollectorColumnSet") == 0;
		}

		virtual void bind() override;
		virtual const char* getClassFactory() override { return "StatisticsCollectorColumnSet"; }
		virtual ColumnSet* toColumnSet() override { return this; }

		engine_export Variant isColumnSet(FLEXSIMINTERFACE) { return 1; }
	};

	class EventParamProperty : public SimpleDataType
	{
	public:
		double enabled;
		ByteBlock paramName;
		double paramNumber;

		virtual void bind() override;
		virtual const char* getClassFactory() override { return "StatisticsCollectorEventParamProperty"; }
	};

	class CollectedDataProperty : public SimpleDataType
	{
	public:
		TreeNode* propertyValue;

		virtual void bind() override;
		virtual const char* getClassFactory() override { return "StatisticsCollectorCollectedDataProperty"; }
	};
	
	// This class represents the interface into OnEventOccurred in the StatisticsCollector
	// The listener classes should all have one of these (usually)
	class EventOccurredInfo : public SimpleDataType
	{
	public:
		NodeRef eventObject;
		ByteBlock eventName;
		ObjRef<Group> group;
		NodeRef instanceObject;
		NodeListArray<EventParamProperty>::ObjPtrType eventProperties;
		NodeRef condition;
		NodeListArray<CollectedDataProperty>::ObjPtrType collectedProperties;
		double stopTrackingRowValue = 0.0;
		NodeListArray<Column>::ObjPtrType columns;
		double flags = 0;

		TreeNode* savedProperties;

		virtual void bind() override;
		virtual const char* getClassFactory() override { return "StatisticsCollectorEventOccurredInfo"; }
	};

	class TimerEventReference;
	class TransientEventReference;
	class EventReference : public SimpleDataType
	{
	public:
		NodeRef object;
		ByteBlock eventName;

		double changeRule = 0;
		TreeNode* changeValue;

		double searchForObjects = 0;
		TreeNode* searchRequirements;

		// The view fills in this list using enumerateEvents
		TreeNode* eventList;

		SimpleDataType* getSDT();

		NodeListArray<EventParamProperty>::SdtSubNodeBindingType eventProperties;
		NodeListArray<CollectedDataProperty>::SdtSubNodeBindingType collectedProperties;

		TreeNode* condition;
		double stopTrackingRowValue = 0;

		enum ColumnSelectMode { ByLinks = 0, ByCode };

		double columnSelectMode = (double)ByLinks;
		TreeNode* selectColumnsCallback;

		static void columnAdder(TreeNode* x, Column* column);
		static Column* columnGetter(TreeNode* x);
		NodeListArray<Column, columnAdder, columnGetter, 0> columns;
		NodeListArray<Column, columnAdder, columnGetter, 0> liveColumns;

		virtual bool isTrackedVariableType();

		virtual void bind() override;
		virtual const char* getClassFactory() override { return "StatisticsCollectorEventReference"; }
		virtual bool isClassType(const char* className) {
			return strcmp(className, "StatisticsCollectorEventReference") == 0;
		}

		virtual const char* getType();
		virtual TimerEventReference* toTimerEventReference() { return nullptr; }
		virtual TransientEventReference* toTransientEventReference() { return nullptr; }
	};

	class TransientEventReference : public EventReference
	{
	public:
		// Most of the inherited fields specify the existing event
		// These additional fields specify information about the transient event
		TreeNode* transientObjectsCallback;
		ByteBlock transientEventName;
		TreeNode* transientEventList; // The view fills in this list
		double transientChangeRule = 0;
		TreeNode* transientChangeValue;
		TreeNode* transientCondition;

		NodeListArray<EventParamProperty>::SdtSubNodeBindingType transientEventProperties;

		virtual const char* getType() override;
		virtual TransientEventReference* toTransientEventReference() override { return this; }
		virtual void bind() override;
		virtual const char* getClassFactory() override { return "StatisticsCollectorTransientEventReference"; }
		virtual bool isClassType(const char* className) override {
			return strcmp(className, "StatisticsCollectorTransientEventReference") == 0;
		}
	};

	class EventReferenceListener : public FlexSimEvent
	{
	public:
		SDTMember<EventOccurredInfo> info;

		virtual void execute() override;
		virtual void bind() override;
		virtual const char* getClassFactory() override { return "StatisticsCollectorEventReferenceListener"; }

		// for listening to ProcessFlow instances
		Variant getEventTitle(FLEXSIMINTERFACE);
		Variant setInstanceObject(FLEXSIMINTERFACE);
	};

	class TransientEventReferenceListener : public FlexSimEvent
	{
	public:
		// This function creates a listener on the transient object
		NodeRef eventObject;
		NodeRef instanceObject;
		double flags;
		ObjRef<TransientEventReference> linkedEventReference;

		virtual void execute() override;
		virtual void bind() override;
		virtual const char* getClassFactory() override { return "StatisticsCollectorTransientEventReferenceListener"; }

		// for listening to ProcessFlow instances
		Variant getEventTitle(FLEXSIMINTERFACE);
		Variant setInstanceObject(FLEXSIMINTERFACE);
	};

	class TimerEventReference : public EventReference
	{
	public:
		double offsetTime = 0;
		double repeatSchedule = 0;
		double repeatInterval = 100;

		// The schedule should be a table
		// First column - time to fire
		// Additional columns - data to collect
		TreeNode* schedule;

		NodeListArray<CollectedDataProperty>::ObjPtrType collectedPropertiesList;
		NodeListArray<Column>::ObjPtrType columnsToUpdate;

		virtual void bind() override;
		virtual const char* getClassFactory() override { return "StatisticsCollectorTimerEventReference"; }

		virtual const char* getType() { return "Timer"; }

		virtual TimerEventReference* toTimerEventReference() override { return this; }
	};

	class TimerEventReferenceListener : public FlexSimEvent
	{
	public:
		ObjRef<TimerEventReference> linkedEventReference;
		double rowNumber;
		virtual void execute() override;
		virtual void bind() override;
		virtual const char* getClassFactory() { return "StatisticsCollectorTimerEventReferenceListener"; }
	};

#if (defined FLEXSIM_EXECUTIVE && defined FLEXSIM_FLEXSCRIPT_CPP)
	class TrackedVariableEventReferenceListener : public ValueChangeListener
	{
	public:
		SDTMember<EventOccurredInfo> info;

		virtual void onChangeRuleMet(const Variant& newValue, const Variant& oldValue) override;

		virtual void bind() override;
		virtual const char* getClassFactory() override { return "StatisticsCollectorTrackedVariableEventReferenceListener"; }

		// for listening to ProcessFlow instances
		Variant getEventTitle(FLEXSIMINTERFACE);
		Variant setInstanceObject(FLEXSIMINTERFACE);
	};
#endif

	class QuerySource : public SqlDataSource
	{
	public:
		virtual int getColID(int tableId, const char* colName, int& colFlags) override;
		virtual const char* enumerateColNames(int tableId, int colNum) override;
		virtual Variant getValue(int tableId, int row, int colId) override;
		// I don't need to set the value; collector tables are read-only for queries
		// I don't need to worry about table ID either
		virtual int getRowCount(int tableID) override;
		ObjRef<StatisticsCollector> collector;
		QuerySource(StatisticsCollector* collector) : collector(collector) {}
	};

	class DataSource : public Table::TableDataSource
	{
	protected:
		ObjRef<StatisticsCollector> curCollector;
		void throwError(std::string message) { throw message + " (for " + curCollector->holder->name + ")"; }
	public:
		DataSource(StatisticsCollector* curCollector) : curCollector(curCollector) {}
		bool isValid() { return (bool)curCollector; }

		virtual int getConstraints() const override { return READ_ONLY | BUNDLE_TYPES_ONLY; }
		engine_export virtual int __numRows() const override;
		engine_export virtual int __numCols() const override;

		virtual std::string __name() const override;

		virtual void addCol(int, int) override { throwError("Error: cannot add columns"); }
		virtual void addRow(int, int) override { throwError("Error: cannot add rows"); }
		virtual TreeNode* cell(const Variant&, const Variant&) override { throwError("Error: cannot get cell"); throw; }
		virtual void clear(int) { throwError("Error: cannot clear table"); }
		virtual void deleteCol(int) override { throwError("Error: cannot delete column"); }
		virtual void deleteRow(int) override { throwError("Error: cannot delete row"); }
		// executeCell is okay
		virtual std::string getColHeader(int colNum) override;
		// getRowHeader is okay
		virtual void moveCol(int, int) override { throwError("Error: cannnot move column"); }
		virtual void moveRow(int, int) override { throwError("Error: cannnot move row"); }
		virtual void setColHeader(int, const char*) override { throwError("Error: cannnot set column header"); }
		virtual void setRowHeader(int, const char*) override { throwError("Error: cannnot set row header"); }
		virtual void setSize(int, int, int, int) override { throwError("Error: cannnot set size"); }
		virtual void sort(const Variant&, const Variant&) override { throwError("Error: cannnot sort"); }
		virtual void swapCols(int, int) override { throwError("Error: swap columns"); }
		virtual void swapRows(int, int) override { throwError("Error: swap rows"); }

		engine_export virtual Variant getValue(int row, int col) override;
		virtual void setValue(int row, int col, const Variant& val) override { throwError("Error: cannnot set value"); }
	};

	std::shared_ptr<Table::TableDataSource> getTableDataSource();
protected:
	std::shared_ptr<Table::TableDataSource> dataSource;

protected:
	NodeListArray<CollectedDataProperty>::SdtSubNodeBindingType sharedProperties;
	static bool checkNodeForSDTType(TreeNode* obj, const char* classType);

	// This class is for allocating on the stack first, since that is usually the case,
	// and only on the heap if neccessary. It gets used in the onEventOccured() function
	template <class T, int BUFFER_SIZE = 64>
	class Buffer
	{
	protected:
		T stackBuffer[BUFFER_SIZE];
		std::unique_ptr<T[]> bigBuffer;

		T* buffer = stackBuffer;
		int _size = 0;
		int maxSize = BUFFER_SIZE;

	public:
		T& operator[](int index) { 
#ifdef _DEBUG
			if (index < 0 || index > _size)
				throw "index out of bounds";
#endif
			return buffer[index]; 
		}

		void reserve(int count) {
#ifdef _DEBUG
			if (_size > 0)
				throw "must reserve before entries are added";
#endif
			if (count > maxSize)  {
				bigBuffer = std::make_unique<T[]>(count);
				buffer = bigBuffer.get();
				maxSize = count;
			}
		}

		void push_back(T value) { 
#ifdef _DEBUG
			if (_size == maxSize) 
				throw "cannot add more values to buffer"; 
#endif
			buffer[_size++] = value; 
		}
		int size() { return _size; }
	};

public:
	double enabled = 1;
	double ignoreWarmup = 0;
	double inErrorState = 0;
	double changeCount;
	double saved = 0;
	double storeDataOnDrive = 0;
	double reuseUntrackedRows = 0;

	double resetRowMode = 0;
	ByteBlock resetRowProperty;

	enum RowMode { Add = 1, Assert, Enumerate };
	double rowMode = (double)Add;
	TreeNode* rowTableObjects;
	TreeNode* rowTable;
	ByteBlock rowProperty;
	TreeNode* rowSortInfo;
	
	NodeRef instanceObject;
	double objectFormatMaxDepth = 0;

	double lastUpdateTime = 0;
	double updateSinceReset = 0;
	NodeRef lastUpdateEvent;

	NodeListArray<EventReference>::SdtSubNodeBindingType eventReferences;
	NodeListArray<Column>::SdtSubNodeBindingType columns;
	NodeListArray<Column>::SdtSubNodeBindingType liveColumns;
	NodeListArray<Column>::ObjPtrType dynamicColumns;

	
	NodeListArray<FlexSimEvent>::CouplingSdtPtrType liveListeners;

	BundleMember data;
	TreeNode* rowScores;

	engine_export TreeNode* addEventReference();
	engine_export TreeNode* addTimerEventReference();
	engine_export TreeNode* addTransientEventReference();
	engine_export const char* getEventReferenceType(TreeNode* eventReference);
	engine_export void updateEventReferenceParams(TreeNode* eventReference);
	engine_export void updateTransientEventReferenceParams(TreeNode* eventReference, TreeNode* paramTable);
	void applyParamTableToProperties(TreeNode* paramTableNode, NodeListArray<EventParamProperty>::SdtSubNodeBindingType& eventProperties);
	void applyUnkownParamsToProperties(NodeListArray<EventParamProperty>::SdtSubNodeBindingType& eventProperties);
	engine_export TreeNode* getEventReferenceObject(TreeNode* eventReference);
	engine_export TreeNode* addPropertyToEventReference(TreeNode* eventReference);
	engine_export TreeNode* addSharedProperty();
	engine_export TreeNode* addRowSortInfo();

protected:
	void addColumnInternal(Column* newColumn, std::string prefix);
public:
	engine_export TreeNode* addColumn();
	engine_export TreeNode* addColumnSet();

	engine_export void linkColumnAndEvent(TreeNode* column, TreeNode* eventRef);
	engine_export void unlinkColumnAndEvent(TreeNode* column, TreeNode* eventRef);
	engine_export void unlinkAllEvents(TreeNode* column);
	engine_export void unlinkAllColumns(TreeNode* eventRef);

	engine_export Array getEventsForColumn(TreeNode* column);

	engine_export TreeNode* addRowTableObject(TreeNode* object);
	void updateRowTable();

	void onEventOccurred(EventOccurredInfo& info, CallPoint* listenerCP);
	void onPreTransientEvent(TransientEventReference* eventReference, TreeNode* eventObject, TreeNode* instanceObject, double flags, CallPoint* listenerCP);

	engine_export void update();

	engine_export Array getUniquePropertyNames();

	engine_export CollectedDataInterface __getCollectedData() { return CollectedDataInterface(&__collectedData); }
	__declspec(property (get = __getCollectedData)) CollectedDataInterface collectedData;

	engine_export TreeNode* __getData() { return data; }

	engine_export const char* __getRowObjectsProperty() { return rowProperty.getBuffer(); }
	engine_export void __setRowObjectsProperty(const char* prop) { rowProperty.write(prop); }

	engine_export int __getRowMode() { return (int)rowMode; }
	engine_export void __setRowMode(int value) { rowMode = value; }

	engine_export TreeNode* __getInstanceObject() { return instanceObject; }
	engine_export void __setInstanceObject(TreeNode* obj) { instanceObject = obj; }

	engine_export int getRowForValue(const Variant& value);

	engine_export operator Table();
	engine_export operator TreeNode*() { return holder; }

	// These methods allow access to some column metadata
	engine_export int getColumnFormat(int columnNr) override;
	engine_export Array getColumnFormats() override;

	engine_export static StatisticsCollector* createGlobal();
	engine_export static StatisticsCollector* getGlobal(const Variant& id);

	engine_export void onReset();
	engine_export void onPostReset();
	engine_export void applySettings();
	void onConfigure();
	void clearCollector();
	void setResetValues();
	void createLiveComponents();
	void createColumns();
	void createListeners();
	void setInfoColumns(EventOccurredInfo* info, EventReference* linkedEvent, TreeNode* eventObject, const char* eventName);
	void setInfo(EventOccurredInfo* info, EventReference* linkedEvent, TreeNode* eventObject, const char* eventName, TreeNode* instanceObject, int flags);
	void setTransientInfo(EventOccurredInfo* info, TransientEventReference* linkedEvent, TreeNode* eventObject, const char* eventName, int flags);
	void listenToEventNode(EventReference* ref, TreeNode* eventNode, TreeNode* eventObject, const char* eventName, TreeNode* instanceObject, int flags);
	void listenToTransientEventNode(TransientEventReference *ref, TreeNode* eventNode, TreeNode* eventObject, const char* eventName, int flags, const PropertyMap& cachedProperties);
	void createEvents();
	engine_export void onRunWarm();
	// double onStartSimulation() override;

	// Events
protected:
	TreeNode* onRowAdded = nullptr;
	TreeNode* onRowUpdated = nullptr;
	Array columnsUpdated;
	Array previousValues;
public:

	// getEventInfo
	engine_export virtual TreeNode* getEventInfoObject(const char* eventTitle);

	// Bind
	engine_export virtual void bindEvents() override;
	engine_export virtual void bindVariables() override;
	engine_export virtual void bindInterface() override;

	// ID Service functions
	engine_export static double getID(TreeNode* object) { return IDService::getID(object); }

	engine_export static int isValueID(double id) { return IDService::isValueID(id); }
	engine_export static TreeNode* getObjectFromID(double id) { return IDService::getObjectFromID(id); }
	engine_export static const char* getPathFromID(double id, int maxDepth = 0) { 
		return IDService::getPathFromID(id, maxDepth);
	}

	engine_export static void clearIDs() { IDService::clear(); }

	engine_export Variant getDBExportColumnExpression(const char* colName, int dbDataType);

	engine_export bool isSuitableForLiveUpdates();

	virtual StatisticsCollector* toStatisticsCollector() { return this; }
};

class CalculatedTable : public ColumnFormatter
{
protected:
	bool shouldUpdate() const;

public:
	class Timer : public FlexSimEvent
	{
	public:
		virtual void execute() override;
		virtual const char* getClassFactory() { return "CalculatedTableTimer"; }
	};

	class QuerySource : public SqlDataSource
	{
	public:
		virtual int getColID(int tableId, const char* colName, int& colFlags) override;
		virtual const char* enumerateColNames(int tableId, int colNum) override;
		virtual Variant getValue(int tableId, int row, int colId) override;
		// I don't need to set the value; collector tables are read-only for queries
		// I don't need to worry about table ID either
		virtual int getRowCount(int tableID) override;
		ObjRef<CalculatedTable> table;
		QuerySource(CalculatedTable* table) : table(table) {}
	};

	class DataSource : public Table::TableDataSource
	{
	protected:
		ObjRef<CalculatedTable> table;
		void throwError(std::string message) { throw message + " (for " + table->holder->name + ")"; }
	public:
		DataSource(CalculatedTable* table) : table(table) {}
		bool isValid() { return (bool)table; }

		virtual int getConstraints() const override { return READ_ONLY | BUNDLE_TYPES_ONLY; }
		engine_export virtual int __numRows() const override;
		engine_export virtual int __numCols() const override;

		virtual std::string __name() const override;

		virtual void addCol(int, int) override { throwError("Error: cannot add columns"); }
		virtual void addRow(int, int) override { throwError("Error: cannot add rows"); }
		virtual TreeNode* cell(const Variant&, const Variant&) override { throwError("Error: cannot get cell"); throw; }
		virtual void clear(int) { throwError("Error: cannot clear table"); }
		virtual void deleteCol(int) override { throwError("Error: cannot delete column"); }
		virtual void deleteRow(int) override { throwError("Error: cannot delete row"); }
		// executeCell is okay
		virtual std::string getColHeader(int colNum) override;
		// getRowHeader is okay
		virtual void moveCol(int, int) override { throwError("Error: cannnot move column"); }
		virtual void moveRow(int, int) override { throwError("Error: cannnot move row"); }
		virtual void setColHeader(int, const char*) override { throwError("Error: cannnot set column header"); }
		virtual void setRowHeader(int, const char*) override { throwError("Error: cannnot set row header"); }
		virtual void setSize(int, int, int, int) override { throwError("Error: cannnot set size"); }
		virtual void sort(const Variant&, const Variant&) override { throwError("Error: cannnot sort"); }
		virtual void swapCols(int, int) override { throwError("Error: swap columns"); }
		virtual void swapRows(int, int) override { throwError("Error: swap rows"); }

		engine_export virtual Variant getValue(int row, int col) override;
		virtual void setValue(int row, int col, const Variant& val) override { throwError("Error: cannnot set value"); }
	};

	std::shared_ptr<Table::TableDataSource> dataSource;
	std::shared_ptr<Table::TableDataSource> getTableDataSource();

	// The event listener, if doing a live query from a Statistics Collector
	class TableChangeListener : public FlexSimEvent
	{
	public:
		enum Type { None = 0, SCRowAdded, SCRowUpdated, Invalid };
		double type;
		ByteBlock tableName;
		
		TableChangeListener() {}
		TableChangeListener(Type type, const char* tableName);

		virtual void execute() override;

		virtual void bind() override;
		virtual const char* getClassFactory() override { return "CalculatedTableTableChangeListener"; }
		virtual bool isClassType(const char* className) { return strcmp(className, getClassFactory()) == 0; }
	};

	// Inputs
	ByteBlock query;
	enum UpdateMode { Manual = 0, ByInterval = 1, Always = 2, LazyInterval = 3 };
	double updateMode = 0;
	double updateInterval = 0;
	double enabled = 1;
	double updateCount = 0;
	double displayTimeAsText = 0;
	double objectFormatMaxDepth = 0;

	TreeNode* formatList;

	// Internal state
	TreeNode* queryNode;

	// I only add listeners if:
	//   * the query only involves statistics collectors
	//   * the update mode is always
	//   * the "update" is called
	NodeListArray<TableChangeListener>::CouplingSdtPtrType liveListeners;
	double liveUpdateFailed = 0;

	// This gets set for unrecoverable errors (sql build or query errors)
	double buildFailed = 0;
	ByteBlock cachedQuery;

	// and here's the last update time
	double lastUpdateTime = -1;
	double updateSinceReset = 0;
	NodeRef lastUpdateEvent;

	// and here's where the result gets dumped
	BundleMember data;

	engine_export static CalculatedTable* getGlobal(const Variant& queryTable);

	// OnReset - build the sql query, and run it for the first time
	engine_export void onReset();

	bool isQueryBuildable();

	// update runs the query, and dumps the table
	engine_export void update(int force = 0);
	void updateFormatList();

	engine_export int getColumnFormat(int columnNr) override;
	engine_export Array getColumnFormats() override;

	engine_export int dependsOnExperimentData();

	engine_export virtual void bindVariables() override;

	void onSourceRowAdded(const char* tableName);
	void onSourceValueChanged(const char* tableName, int row, int col, const Variant& oldValue);

	virtual CalculatedTable* toCalculatedTable() { return this; }
};

}