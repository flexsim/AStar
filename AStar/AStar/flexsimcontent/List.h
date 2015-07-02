#pragma once

#include "basicclasses.h"
#include "objectdatatype.h"
#include "couplingdatatype.h"
#include "byteblock.h"
#include <unordered_map>


class List : public ObjectDataType
{
	friend SimpleDataType* engine_createsdtderivative(char* classname, TreeNode* holder);
public:
	int repaintMatchId = 0;
	// flags for pulling
	static const int ALLOCATE_ALL_OR_NOTHING = 0x1;
	static const int PARSE_QUERY = 0x2;
	static const int PULL_ENTRY_NODES = 0x4;
	static const int DO_NOT_REMOVE = 0x8;
	static const int DO_NOT_BACK_ORDER = 0x10;
	static const int PULL_BACK_ORDERS = 0x20;
	static const int DO_NOT_FULFILL = 0x40;

	static const int COL_ID_VALUE = INT_MAX - 1;
	static const int COL_ID_PULLER = INT_MAX - 2;
	static const int COL_ID_REQUESTED = INT_MAX - 3;
	static const int COL_ID_REQUIRED = INT_MAX - 4;
	List() : defaultDataSource(0), backOrderQueueStrategyDataSource(0), defaultBackOrderDataSource(0) {}

	class CallbackInfo
	{
	public:
		CallbackInfo() {}
		CallbackInfo(treenode callbackNode, const Variant& p1, const Variant& p2, const Variant& p3, const Variant& p4, const Variant& p5,
			const Variant& p6, const Variant& p7, const Variant& p8, const Variant& p9, const Variant& p10);
		static const int PARAM_ALLOCATED = -496432586;
		static const int PARAM_NUM_REQUIRED_STILL = -496432587;
		static const int PARAM_NUM_REQUESTED_STILL = -496432588;
		void bind(SimpleDataType* entry);
		void evaluate(Variant allocated, int numRequiredStill, int numRequestedStill);
		treenode callbackNode;
		int allocatedParam;
		int numRequiredParam;
		int numRequestedParam;
		Variant params[10];
	};
	class CallbackInfoWrapper
	{
	public:
		CallbackInfoWrapper() {}
		~CallbackInfoWrapper() { if (info) info->~CallbackInfo(); }
		void bind(SimpleDataType* entry);
		CallbackInfo* info = 0;
		// I want to have callbackInfo part of this class, but without the
		// requirement of calling new to get it, and without requiring
		// it to initialize members on every entry constructor call, so I define
		// a properly size buffer and initialize it when it is needed
		char extraCallbackInfoBuffer[sizeof(CallbackInfo)];
		void setListener(treenode callbackNode, const Variant& p1 = Variant(), const Variant& p2 = Variant(), const Variant& p3 = Variant(), const Variant& p4 = Variant(), const Variant& p5 = Variant(), 
			const Variant& p6 = Variant(), const Variant& p7 = Variant(), const Variant& p8 = Variant(), const Variant& p9 = Variant(), const Variant& p10 = Variant());
	};
	class Entry : public CouplingDataType
	{
		friend class List;
		friend class ListViewDataSource;
	public:
		Entry(size_t numFields);
		Entry() {}
		CallbackInfoWrapper callbackInfo;
	private:
		virtual const char* getClassFactory() { return "ListEntry"; }
		virtual void bind();
		std::vector<Variant> staticFields;
		double pushTime;
		Variant value;
	};

	class Field : public SimpleDataType
	{
		friend class List;
		friend class ListViewDataSource;
	public:
		engine_export virtual void bind() override;
		double isDynamic;
		double staticIndex;
		virtual Variant evaluateOnAdd(Entry* entry, const VariantParams& params) { return Variant(); }
		virtual Variant evaluateOnQuery(Entry* entry, const Variant& requester) { return Variant(); }
		virtual bool needsPuller() { return false; }
	};

	class LabelField : public Field
	{
		virtual const char* getClassFactory() override { return "ListLabelField"; }
		virtual Variant evaluateOnAdd(Entry* entry, const VariantParams& params) override;
		virtual Variant evaluateOnQuery(Entry* entry, const Variant& requester) override;
	};
	class ExpressionField : public Field
	{
		treenode expression;
		virtual void bind() override;
		virtual const char* getClassFactory() { return "ListExpressionField"; }
		virtual Variant evaluateOnAdd(Entry* entry, const VariantParams& params) override;
		virtual Variant evaluateOnQuery(Entry* entry, const Variant& requester) override;
		virtual bool needsPuller() override;
	};
	class PushArgumentField : public Field
	{
		double paramNum;
		virtual void bind() override;
		virtual const char* getClassFactory() override { return "ListPushArgumentField"; }
		virtual Variant evaluateOnAdd(Entry* entry, const VariantParams& params) override;
	};
	class ListSqlDataSource : public SqlDataSource
	{
	public:
		ListSqlDataSource() {}
		ListSqlDataSource(List* list) : list(list) {}
		virtual const char* getClassFactory() override { return "ListSqlDataSource"; }
		virtual void bind() override;
		virtual int getColId(int tableId, const char* colName) override;
		void reset();
		virtual const char* enumerateColNames(int tableId, int colNum) override;
		virtual Variant getValue(int tableId, int row, int colId) override;
		virtual int getTableId(const char* tableName) override;
		virtual int getRowCount(int tableId) override;

		TreeNode* curPuller = 0;
		List* list;
		TreeNode* sqlParse = 0;
		std::vector<std::string> labelNames;
		void assertSQLParse();
		static const int VALUE_TABLE = 0;
		static const int PULLER_TABLE = 1;
	};
	class ListBackOrderSqlDataSource : public ListSqlDataSource
	{
	public:
		ListBackOrderSqlDataSource() : ListSqlDataSource() {}
		ListBackOrderSqlDataSource(List* list) : ListSqlDataSource(list) {}
		virtual const char* getClassFactory() override { return "ListBackOrderSqlDataSource"; }
		virtual void bind() override;
		virtual int getColId(int tableId, const char* colName) override;
		virtual Variant getValue(int tableId, int row, int colId) override;
		virtual int getRowCount(int tableId) override;
		int curEntryRow = 0;
	};

	class BackOrder : public ListSqlDataSource
	{
	public:
		BackOrder() {}
		BackOrder(List* list, int numRequested, int numRequired, int numFulfilled,
			const Variant& puller, const Variant& partitionId, int flags, ListSqlDataSource* originalDelegate)
			: ListSqlDataSource(list), numRequested(numRequested), numRequired(numRequired), numFulfilled(numFulfilled),
			puller(puller), partitionId(partitionId), flags(flags), originalDelegate(originalDelegate)
		{
			orderTime = time();
			incrementalAllocation = !(flags & List::ALLOCATE_ALL_OR_NOTHING);
			isOnPartition = (partitionId.type != VariantType::Null && partitionId != 0.0);
		}
		virtual const char* getClassFactory() override { return "ListBackOrder"; }
		virtual void bind() override;
		int numFulfilled;
		int numRequired;
		int numRequested;
		double orderTime;
		Variant puller;
		Variant partitionId;
		bool isOnPartition;
		int flags;
		bool incrementalAllocation;
		int numAddedEntries = 0;
		ListSqlDataSource* originalDelegate;
		bool checkFulfill(int& numAdded);
		virtual int getRowCount(int tableId) override;
		virtual Variant getValue(int tableId, int row, int colId) override;
		CallbackInfoWrapper callbackInfo;
	};

	struct PushResult
	{
		Variant returnVal;
		std::unique_ptr<std::vector<Variant>> returnArray;
		int numResults = 0;
		void addToResult(const Variant& puller);
		Variant getResult();
	};

	class ListStatisticSet : public StatisticSet
	{
	public:
		Variant partitionId;

		virtual const char* getClassFactory() override { return "ListStatisticSet"; }
		virtual void bind() override { StatisticSet::bind(); bindVariant(partitionId); }
	};

	NodeListArray<Field>::SdtSubNodeType fields;
	NodeListArray<Entry>::CouplingSdtSubNodeType entries;
	NodeListArray<BackOrder>::SdtSubNodeType backOrders;
	NodeListArray<>::SubNodeType backOrderPartitions;
	NodeListArray<>::SubNodeType entryPartitions;
	NodeListArray<Entry>::CouplingSdtSubNodeType removedEntries;
	TreeNode* contentsOnReset;

	NodeListArray<ListStatisticSet>::SdtSubNodeBindingType entryPartitionStatistics;
	NodeListArray<ListStatisticSet>::SdtSubNodeBindingType backOrderPartitionStatistics;
	
	TreeNode* entryStatisticsNode;
	StatisticSet* getEntryStatistics();

	TreeNode* backOrderStatisticsNode;
	StatisticSet* getBackOrderStatistics();

	engine_export virtual Variant parseStatisticString(const string& statString, int mode, Variant data);

	ByteBlock listType;	
protected:
	std::vector<int> staticFields;
	std::vector<int> dynamicFields;
	void cacheFieldIndices();
	Variant push(const VariantParams& params);
	static Variant curPuller;

	class PartitionHash
	{
	public:
		size_t operator() (const Variant& pullerKey);
	};
	typedef std::unordered_map<Variant, TreeNode*, PartitionHash> PartitionHashTable;
	typedef std::unordered_map<Variant, ListStatisticSet*, PartitionHash> PartitionStatsTable;
	
	PartitionStatsTable entryStatsIndex;
	PartitionStatsTable backOrderStatsIndex;
	void removePartition(PartitionHashTable& hashTable, const Variant& partitionId);


	ListSqlDataSource* defaultDataSource;
	NodeListArray<ListSqlDataSource>::SdtSubNodeBindingType parsedQueries;
	/// <summary>	boolean whether the list should cache queries. </summary>
	double cacheQueries;
	std::unordered_map<const char*, ListSqlDataSource*, CharStrHash, CharStrEquals> queryCache;

	ByteBlock backOrderQueueStrategy;
	ListBackOrderSqlDataSource* defaultBackOrderDataSource;
	ListBackOrderSqlDataSource* backOrderQueueStrategyDataSource;
	TreeNode* backOrderQueueStrategyDataSourceNode;
	NodeListArray<ListBackOrderSqlDataSource>::SdtSubNodeBindingType parsedBackOrderQueries;
	std::unordered_map<const char*, ListSqlDataSource*, CharStrHash, CharStrEquals> backOrderQueryCache;

	void buildQueryCache();
	PartitionHashTable entryPartitionIndex;
	PartitionHashTable backOrderPartitionIndex;
	void buildPartitionIndex();
	TreeNode* assertPartition(TreeNode* container, const Variant& partitionId, PartitionHashTable& hashTable, TreeNode* statsContainer, PartitionStatsTable& statsTable);

public:
	static bool isVariantNonNull(const Variant& partitionId);
	Variant getResult(int numMatches, SqlQuery* q, const Variant& puller, bool removeEntries, bool incrementalAllocation, int numAdded, const Variant& partitionId, bool getEntryNodes);
	TreeNode* getBackOrderList(const Variant& partitionId);
	TreeNode* getEntryList(const Variant& partitionId);
	virtual void bindVariables();
	virtual void onReset();
	virtual int getFieldId(const char* fieldName);
	virtual Variant getEntryValue(int entryIndex, int fieldId);
	virtual const char* enumerateColNames(int colNum);
	engine_export Variant push(const Variant& involved);
	engine_export Variant push(const Variant& involved, const Variant& partitionId);
	engine_export Variant push(const Variant& involved, const Variant& partitionId, const Variant& p1);
	engine_export Variant push(const Variant& involved, const Variant& partitionId, const Variant& p1, const Variant& p2);
	engine_export Variant push(const Variant& involved, const Variant& partitionId, const Variant& p1, const Variant& p2, const Variant& p3);
	engine_export Variant push(const Variant& involved, const Variant& partitionId, const Variant& p1, const Variant& p2, const Variant& p3, const Variant& p4, const Variant& p5 = Variant(), const Variant& p6 = Variant(),
		const Variant& p7 = Variant(), const Variant& p8 = Variant());

private:
	ListSqlDataSource* processQuery(const char* sqlQuery, int flags, TreeNode* parsedContainer, bool isBackOrderQuery);
	inline Variant pull(SqlQuery* q, int requestNum, int requireNum, const Variant& puller, const Variant& partitionId, int flags);
	inline Variant pullBackOrders(SqlQuery* q, int requestNum, const Variant& value, const Variant& partitionId, int flags);
	Variant pullBackOrders(const char* sqlQuery, int requestNum, const Variant& value, const Variant& partitionId, int flags);
	Variant pullBackOrders(TreeNode* cachedQuery, int requestNum, const Variant& value, const Variant& partitionId, int flags);
public:
	engine_export Variant pull(const char* sqlQuery, int requestNum, int requireNum, const Variant& puller = Variant(), const Variant& partitionId = Variant(), int flags = 0);
	engine_export Variant pull(TreeNode* cachedQuery, int requestNum, int requireNum, const Variant& puller = Variant(), const Variant& partitionId = Variant(), int flags = 0);
	engine_export virtual void dumpStatisticSets(TreeNode* container);

	engine_export void listenToEntry(treenode entry, treenode callback, const Variant& p1);
};

#ifdef FLEXSIM_ENGINE_COMPILE
engine_export Variant listpush(const char* listName, const Variant& involved);
engine_export Variant listpush(treenode list, const Variant& involved);
engine_export Variant listpush(const char* listName, const Variant& involved, const Variant& partitionId, const Variant& p1, const Variant& p2,
                                            const Variant& p3, const Variant& p4, const Variant& p5, const Variant& p6,
                                            const Variant& p7, const Variant& p8);
engine_export Variant listpush(treenode list, const Variant& involved);
engine_export Variant listpush(treenode list, const Variant& involved, const Variant& partitionId, const Variant& p1, const Variant& p2,
                                            const Variant& p3, const Variant& p4, const Variant& p5, const Variant& p6,
                                            const Variant& p7, const Variant& p8);
engine_export void listaddlistener(treenode entry, treenode callbackNode, const Variant& p1 = Variant(), const Variant& p2 = Variant(), const Variant& p3 = Variant(), const Variant& p4 = Variant(), const Variant& p5 = Variant(),
	const Variant& p6 = Variant(), const Variant& p7 = Variant(), const Variant& p8 = Variant(), const Variant& p9 = Variant(), const Variant& p10 = Variant());
engine_export treenode listbackorders(TreeNode* listNode, const Variant& partitionId);
engine_export treenode listentries(TreeNode* listNode, const Variant& partitionId);
engine_export Variant listpull(TreeNode* listNode, TreeNode* cachedQuery, int requestNum = 1, int requireNum = 1, const Variant& puller = Variant(), const Variant& partitionId = Variant(), int flags = 0);
engine_export Variant listpull(TreeNode* listNode, const char* query, int requestNum = 1, int requireNum = 1, const Variant& puller = Variant(), const Variant& partitionId = Variant(), int flags = 0);
engine_export Variant listpull(const char* listName, TreeNode* cachedQuery, int requestNum = 1, int requireNum = 1, const Variant& puller = Variant(), const Variant& partitionId = Variant(), int flags = 0);
engine_export Variant listpull(const char* listName, const char* query, int requestNum = 1, int requireNum = 1, const Variant& puller = Variant(), const Variant& partitionId = Variant(), int flags = 0);
#endif
