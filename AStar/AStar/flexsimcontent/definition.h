	
string unboundFunctions;

void handleunboundfunction()
{
	// if the EX() command was bound correctly then call EX
	if(EXalias != reinterpret_cast<_EXalias>(&handleunboundfunction))
		EXalias((char*)unboundFunctions.c_str(), "Throwing...", 1);
	else 
	{
	// otherwise do a windows message box
		static int messageshownalready = 0;
		if(!messageshownalready)
		{
			// so that you don't get a million error messages.
			messageshownalready = 1;
			MessageBox(0, unboundFunctions.c_str(), "Error Calling Unbound DLL Function", MB_OK);
		}
	}
	throw 0;
}

HMODULE flexSimModule;
typedef void* (*_getflexsimexportedfunction)(char* functionname);
void* defaultgetflexsimexportedfunction(char* functionname)
{
	void* thefunction = GetProcAddress(flexSimModule, functionname);
	return thefunction;
}

#if defined COMPILING_FLEXSIM_CONTENT || defined COMPILING_MODULE_DLL
void ObjectDataType::cleanup()
{
	odtcleanup(this);
}
void ObjectDataType::initialize()
{
	odtinitialize(this);
}
int ObjectDataType::bindstructure(TreeNode* x, unsigned int flags)
{
	return odtbindstructure(this, x, flags);
}
void ObjectDataType::bindVariableByName(const char* name, double& val)    { odtbindvariablebynamealias1(this, name, val); }
void ObjectDataType::bindVariableByName(const char* name, ByteBlock& val) { odtbindvariablebynamealias2(this, name, val); }
void ObjectDataType::bindVariableByName(const char* name, NodeRef& val)   { odtbindvariablebynamealias3(this, name, val); }
void ObjectDataType::bindVariableByName(const char* name, TreeNode*& val) { odtbindvariablebynamealias4(this, name, val); }

void SimpleDataType::bind(int bindMode)
{
	return sdtbind(this, bindMode);
}

TreeNode* SimpleDataType::getBindTree()
{
	return sdtgetbindtree(this);
}

void SimpleDataType::bindDoubleByName(const char* name, double& val, int asSubNode)
{
	sdtbinddoublebyname(this, name, val, asSubNode);
}

void SimpleDataType::bindByteBlockByName(const char* name, ByteBlock& val, int asSubNode)
{
	sdtbindbyteblockbyname(this, name, val, asSubNode);
}

void SimpleDataType::bindNodeRefByName(const char* name, NodeRef& val, int asSubNode)
{
	sdtbindnoderefbyname(this, name, val, asSubNode);
}


TreeNode* SimpleDataType::bindByName(const char* name, int asSubNode, int dataType, int * added)
{
	return sdtbindbyname(this, name, asSubNode, dataType, added);
}

void SimpleDataType::bindFlexSimValueByName(const char* name, double& val)
{
	sdtbindflexsimvaluebyname(this, name, val);
}

void SimpleDataType::bindNodePtrByName(const char* name, TreeNode*& val)
{
	sdtbindnodeptrbyname(this, name, val);
}

void SimpleDataType::bindObjPtrByName(const char* name, SimpleDataType*& val)
{
	sdtbindobjptrbyname(this, name, val);
}

void SimpleDataType::bindSubNodeByName(const char* name, TreeNode*& val, int dataType)
{
	sdtbindsubnodebyname(this, name, val, dataType);
}
int SimpleDataType::getBindMode() 
{
	return sdtgetbindmode();
}
bool SimpleDataType::isDisplayVerbose()
{
	return sdtisdisplayverbose();
}
void SimpleDataType::appendToDisplayStr(const char* text)
{
	return sdtappendtodisplaystr(text);
}
char* SimpleDataType::toString(int verbose)
{
	return sdttostring(this, verbose);
}
Variant& SimpleDataType::getCurValue() 
{
	return sdtgetcurvalue();
}
const char* SimpleDataType::getCurValueName() 
{
	return sdtgetcurvaluename();
}
Variant SimpleDataType::getValue(const char* name){return sdtgetvalue(this, name);}
void SimpleDataType::setValue(const char* name, Variant value){sdtsetvalue(this, name, value);}

char* CouplingDataType::toString(int verbose)
{
	return couplingtostring(this, verbose);
}

int TreeNode::cleanup()
{
	llcleanup(this);
	return 0;
}
void TreeNode::initialize()
{
	llinitialize(this);
}

double* TreeNode::safedatafloat()
{
	if(datatype == DATA_FLOAT)
		return dataasdouble;
	else 
	{
		static double failsafefloat;
		failsafefloat = 0;
		return &failsafefloat;
	}
}

ByteBlock* TreeNode::safedatabyteblock()
{
	if(datatype == DATA_BYTEBLOCK)
		return dataasbyteblock;
	else 
	{
		static ByteBlock failsafebyteblock;
		failsafebyteblock = "";
		return &failsafebyteblock;
	}
}


char* ByteBlock::getStaticBlock()
{
	return bbgetstaticblock();
}

void ByteBlock::write(const char *source) {byteblock_write1(this, source);}
void ByteBlock::write(const char *source, size_t intsize, bool nullterminate) { byteblock_write2(this, source, intsize, nullterminate); }
void ByteBlock::append(const char* source) { return byteblock_append(this, source); }
bool ByteBlock::setSize(size_t size) { return byteblock_setsize(this, size); }
unsigned int ByteBlock::getSize() const { return byteblock_getsize((ByteBlock*)this); }
char * ByteBlock::getBuffer() { return byteblock_getbuffer(this); }

void FlexSimEvent::execute()
{
	flexsimeventexecute(this);
}
void FlexSimEvent::bind()
{
	flexsimeventbind(this);
}
void FlexSimEvent::getDescription(char* toStr, size_t maxSize)
{
	flexsimeventgetdescription(this, toStr, maxSize);
}

void Mesh::init(unsigned int _nrVerts, unsigned int _perVertFlags, unsigned int _generalFlags)
	{ mesh_init(this, _nrVerts, _perVertFlags, _generalFlags); }
void Mesh::bind()
	{ mesh_bind(this); }
void Mesh::cleanup(bool isDestructor)
	{ mesh_cleanup(this, isDestructor); }
void Mesh::defineVertexAttribs(unsigned int  attribId, float* verts)
	{ mesh_definevertexattribs(this, attribId, verts); }
unsigned int Mesh::addCustomVertexAttrib(const char* name, int componentsPerVertex, GLenum type, bool isNormalized)
	{ return mesh_addcustomvertexattrib(this, name, componentsPerVertex, type, isNormalized); }
unsigned int Mesh::setVertexAttrib(unsigned int vertIndex, unsigned int attribId, float* vert)
	{ return mesh_setvertexattrib(this, vertIndex, attribId, vert); }
void Mesh::setMeshAttrib(unsigned int attribId, float* vert)
	{ mesh_setmeshattrib(this, attribId, vert); }
int Mesh::addVertex()
	{ return mesh_addvertex(this); }
void Mesh::draw(int drawMode, int vertOffset, int vertCount, int vertStride)
	{ mesh_draw(this, drawMode, vertOffset, vertCount, vertStride); }

void IndexedMesh::bind()
	{ indexedmesh_bind(this); }
void IndexedMesh::defineIndexBuffer(int nr, unsigned int * buffer)
	{ indexedmesh_defineindexbuffer(this, nr, buffer); }
unsigned int IndexedMesh::addIndex(unsigned int index)
	{ return indexedmesh_addindex(this, index); }
void IndexedMesh::draw(int drawMode, int start, int count, int stride)
	{ indexedmesh_draw(this, drawMode, start, count); }
void IndexedMesh::cleanupIndexBuffer(bool isDestructor)
	{ indexedmesh_cleanupindexbuffer(this, isDestructor); }

QueryCallback defQueryCallback([]() -> Variant {return 0;});

#endif