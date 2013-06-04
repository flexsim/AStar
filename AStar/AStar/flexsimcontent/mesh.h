#pragma once

#include "basicclasses.h"
#include "simpledatatype.h"

class Mesh : public SimpleDataType
{
public:
	Mesh(int flags) : nrVerts(0), vertByteStride(0), flags(flags), perMeshAttribs(0), perVertexAttribs(0), 
			vertBuffer(0), vbo(0), vao(0), maxBufferSize(0), isDirty(true) 
	{
		// initialize the per mesh color attribs' alpha to 1
		perMeshAmbient[3] = perMeshDiffuse[3] = perMeshSpecular[3] = perMeshEmissive[3] = 255;
	}
	Mesh() : nrVerts(0), vertByteStride(0), flags(0), perMeshAttribs(0), perVertexAttribs(0), 
			vertBuffer(0), vbo(0), vao(0), maxBufferSize(0), isDirty(true)
	{
		// initialize the per mesh color attribs' alpha to 1
		perMeshAmbient[3] = perMeshDiffuse[3] = perMeshSpecular[3] = perMeshEmissive[3] = 255;
	}
	~Mesh() {cleanup(true);}

	unsigned int perMeshAttribs;
	unsigned int perVertexAttribs;
	unsigned int flags;

	// nrVerts: the number of vertices in this mesh
	int nrVerts;

protected:
// stock vertex attributes are id'd with the high-order 2 bytes
#define MESH_STOCK_ATTRIB_MASK 0xffff0000
// custom vertex attributes are id'd with the low-order 2 bytes (to-do: implement custom vertex attribs once we get to that point)
#define MESH_CUSTOM_ATTRIB_MASK 0x0000ffff

#define MESH_POSITION               0x0
#define MESH_TEX_COORD1             0x0010000
#define MESH_TEX_COORD2             0x0020000
#define MESH_TEX_COORD3             0x0040000
#define MESH_NORMAL                 0x0080000
#define MESH_AMBIENT                0x0100000
#define MESH_DIFFUSE                0x0200000
#define MESH_DIFFUSE4               0x0400000
#define MESH_AMBIENT_AND_DIFFUSE    0x0800000
#define MESH_AMBIENT_AND_DIFFUSE4   0x1000000
#define MESH_SPECULAR               0x2000000
#define MESH_SHININESS              0x4000000
#define MESH_EMISSIVE               0x8000000

#define MESH_COLOR_ATTRIBS (MESH_AMBIENT | MESH_DIFFUSE | MESH_DIFFUSE4 | MESH_AMBIENT_AND_DIFFUSE \
				| MESH_AMBIENT_AND_DIFFUSE4 | MESH_SPECULAR | MESH_SHININESS | MESH_EMISSIVE)

#define MESH_STATIC_DRAW 0x1
#define MESH_DYNAMIC_DRAW 0x2
#define MESH_INDEXED 0x4
#define MESH_FORCE_CLEANUP 0x8
// MESH_IN_MEMORY: (not implemented, just an idea at this point) means the mesh is not bound to the tree, 
// which means it can delete its buffers once copied into the open gl objects
#define MESH_IN_MEMORY 0x8

	// vertStride: the number of floats contained in one vertex (vertex data is interleaved)
	int vertByteStride;
	// nrCustomAttribs: the number of custom vertex attributes stored in the vertBuffer
	int nrCustomAttribs;

	// texCoordOffset: the number of floats from the start of a vertex that represents the start of the texture coordinate
	unsigned char texCoordOffset;
	// normalOffset: the number of floats from the start of a vertex that represents the start of the normal
	unsigned char normalOffset;
	// ambientOffset: the number of floats from the start of a vertex that represents the start of the ambient color
	unsigned char ambientOffset;
	// diffuseOffset: the number of floats from the start of a vertex that represents the start of the diffuse color
	unsigned char diffuseOffset;
	// specularOffset: the number of floats from the start of a vertex that represents the start of the specular color
	unsigned char specularOffset;
	// shininessOffset: the number of floats from the start of a vertex that represents the start of the shininess
	unsigned char shininessOffset;
	// emissiveOffset: the number of floats from the start of a vertex that represents the start of the emissive color
	unsigned char emissiveOffset;
	// customAttribOffsets: an array of offsets to custom attributes in the vertBuffer
	unsigned char customAttribOffsets[16];
	// customAttribLocations: an array that defines custom attribute locations
	unsigned char customAttribLocations[16];

	static float temporaryColorCopy[4];
	static float* copyColor(unsigned char * from);

	static const int STATIC_BLOCK_SIZE = 44;
	union {
		struct {
			float perMeshTexCoord[3];
			float perMeshNormal[3];
			unsigned char perMeshAmbient[4];
			unsigned char perMeshDiffuse[4];
			unsigned char perMeshSpecular[4];
			unsigned char perMeshEmissive[4];
			float perMeshShininess[1];
		};
		unsigned char allStatics[STATIC_BLOCK_SIZE];
	};

	unsigned int vbo;
	unsigned int vao;
	unsigned int maxBufferSize;
	unsigned char* vertBuffer;
	bool isDirty;

	typedef void (*CopyCallback)(void* copyPoint, float* inVerts, int componentsPerVertex, int nrVerts, int vertByteStride);
	static void copyFloatAttribs(void* copyPoint, float* inVerts, int componentsPerVertex, int nrVerts, int vertByteStride);
	static void copyColorAttribs(void* copyTo, float* inVerts, int componentsPerVertex, int nrVerts, int vertByteStride);
	struct AttribCopier {
		int componentsPerVertex;
		int bytesPerComponent;
		CopyCallback copier;
		void* copyPoint;
	};
	AttribCopier getCopier(int attribId);

	typedef void (*ReadCallback)(void* readPoint, float* outVert);
	ReadCallback getReader(unsigned int attribId);
	static void readColorVertex(void* readPoint, float* outVert);
	static void readFloatVertex(void* readPoint, float* outVert);

	static unsigned int setColorMaterial;

	// prepareDraw(): called from one of two places. 
	// 1. if vertex array objects are available, then it will
	//    be called just after defining the vertex buffers, meaning 
	//    just once until the vertices are redefined again.
	// 2. if vertex array objects aren't available, then it will
	//    be called as part of each draw
	// prepareDraw() essentially enables all the client states for 
	// what is needed, and binds to the proper buffers
	void prepareDraw(int stride);
	void applyAttribs();
	void resetAttribs();
	void cleanupDraw();
	// defineGLObjects(): defines the vertex array object. Call this one, and it will call defineVBO
	void defineGLObjects();
	// defineVBO(): defines the vertex buffer object. IndexedMesh will override this to additionally
	// define the index buffer
	void defineVBO();

public:
	void cleanup(bool deleteGLObjects = false);
	virtual const char* getClassFactory() {return "Mesh";}
	virtual void bind();
	void init(unsigned int nrVerts, unsigned int perVertexAttribs = 0, unsigned int perMeshAttribs = 0, unsigned int flags = 0);
	void defineVertexAttribs(unsigned int attribId, float* verts);
	void setVertexAttrib(unsigned int vertIndex, unsigned int attribId, float* vert);
	int addVertex();
	void draw(int drawMode, int vertOffset = 0, int vertCount = 0, int vertStride = 0);
	float* getVertexAttrib(unsigned int vertIndex, unsigned int attribId);
};

class IndexedMesh : public Mesh
{
public:
	IndexedMesh() : Mesh(MESH_INDEXED), nrIndices(0), maxIndexBufferSize(0), indexBuffer(0), indexVBO(0){}
	~IndexedMesh()  {cleanupIndexBuffer(true);}
	virtual const char* getClassFactory() {return "IndexedMesh";}
	virtual void bind();

	void defineIndexBuffer(int nr, unsigned int * buffer);
	void defineIndexBuffer(int nr, int* buffer) {defineIndexBuffer(nr, (unsigned int*) buffer);}
	
	unsigned int addIndex(unsigned int index);

	void draw(int drawMode, int start = 0, int count = 0);
	void cleanupIndexBuffer(bool isDestructor = false);
	unsigned int vertexForIndex(unsigned int index);

protected:
	unsigned int nrIndices;
	unsigned int maxIndexBufferSize;
	unsigned int* indexBuffer;
	unsigned int indexVBO;
	void defineVBO();
	void prepareDraw();
	// defineGLObjects(): defines the vertex array object. Call this one, and it will call defineVBO
	void defineGLObjects();
};

#define MESH_PER_VERTEX_ATTRIBS 1
#define MESH_PER_MESH_ATTRIBS 2
#define MESH_FLAGS 3
#define MESH_NR_VERTS 4
#define MESH_GET_INDEX 5

#ifdef FLEXSIM_ENGINE_COMPILE

visible void mesh(treenode meshnode, unsigned int perVertexAttribs, unsigned int perMeshAttribs, unsigned int flags);
visible int  meshaddvertex(treenode meshnode);
visible void meshsetvertexattrib(treenode meshnode, unsigned int vertIndex, unsigned int attribId, float p1, float p2=0, float p3=0, float p4=0);
visible void meshdraw(treenode meshnode, int drawMode, int offset, int count, int stride=0);
visible int meshaddindex(treenode meshnode, unsigned int index);
visible double meshinfo(treenode meshnode, unsigned int type, unsigned int index=0, unsigned int param=0);

#endif