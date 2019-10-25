#pragma once
#include "basicmacros.h"
#include "simpledatatype.h"
#ifdef FLEXSIM_ENGINE_COMPILE
#include "CL/cl.h"
#else 
typedef void* cl_mem;
typedef void* cl_command_queue;
typedef void* cl_program;
typedef void* cl_kernel;
#ifndef GL_ARB_cl_event
typedef void* cl_context;
#endif
typedef void* cl_device_id;
#endif

namespace FlexSim {

class engine_export OpenCL
{
private:
	static const int MAX_PLATFORMS = 16;
	static const int MAX_DEVICES = 16;

	#ifdef FLEXSIM_ENGINE_COMPILE
	bool isInitialized = false;
	struct Platform {
		cl_platform_id id;
		cl_uint numDevices;
		cl_device_id devices[MAX_DEVICES];
	};
	cl_uint numPlatforms;
	Platform platforms[MAX_PLATFORMS];

	#endif

	OpenCL() {}
	void initialize();
	static void contextErrorCallback(const char* error, const void* privateInfo, size_t size, void* data);
public:


	static const int MEM_READ_WRITE = (1 << 0);
	static const int MEM_WRITE_ONLY = (1 << 1);
	static const int MEM_READ_ONLY = (1 << 2);
	static const int MEM_USE_HOST_PTR = (1 << 3);
	static const int MEM_ALLOC_HOST_PTR = (1 << 4);
	static const int MEM_COPY_HOST_PTR = (1 << 5);

	static const int DEVICE_TYPE_DEFAULT = (1 << 0);
	static const int DEVICE_TYPE_CPU = (1 << 1);
	static const int DEVICE_TYPE_GPU = (1 << 2);
	static const int DEVICE_TYPE_ACCELERATOR = (1 << 3);
	static const int DEVICE_TYPE_CUSTOM = (1 << 4);
	static const int DEVICE_TYPE_ALL = 0xFFFFFFFF;

	static const int QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE = (1 << 0);
	static const int QUEUE_PROFILING_ENABLE = (1 << 1);

	typedef void* PlatformID;

	static OpenCL instance;
	class Program;
	class CommandQueue;

	class engine_export Buffer {
		friend class Program;
		friend class CommandQueue;
		private:
		cl_mem mem;
		Buffer(cl_mem mem) : mem(mem) {}
	public:
		~Buffer();
		Buffer(const Buffer&);
		Buffer& operator = (const Buffer& other) { this->~Buffer(); ::new(this) Buffer(other); return *this; }
	};
	class engine_export CommandQueue
	{
		friend class Program;
	private:
		Program* program;
		cl_command_queue queue;
		CommandQueue(Program* program, cl_command_queue queue) : program(program), queue(queue) {}

	public:
		CommandQueue();
		CommandQueue(const CommandQueue& other);
		~CommandQueue();
		CommandQueue& operator = (const CommandQueue& other) { this->~CommandQueue(); ::new(this) CommandQueue(other); return *this; }
		int writeBuffer(Buffer& buffer, bool blocking, size_t offset, size_t sizeInBytes, const void* fromBuffer);
		int readBuffer(Buffer& buffer, bool blocking, size_t offset, size_t sizeInBytes, void* toBuffer);
		void enqueue(size_t totalSize, size_t workGroupSize);
		void flush();
		void finish();
	};

	class engine_export Program {
		friend class OpenCL;
	private:
		cl_program program = nullptr;
		cl_kernel kernel = nullptr;
		cl_context context = nullptr;
		cl_device_id deviceID = nullptr;
		Program() {}

	public:
		~Program();
		Program(const Program&);
		Program& operator = (const Program& other) { this->~Program(); ::new(this) Program(other); return *this; }


		void setKernelArg(int argNum, int sizeInBytes, void* arg);
		void setKernelArg(int argNum, Buffer& buffer);
		Buffer createBuffer(int memFlags, int size, void* hostPtr = nullptr);
		CommandQueue createCommandQueue(int flags = 0);
		bool isValid();
	};
private:
	Program createProgram(int numSources, const char** sources, const char* kernelName, int deviceType);
public:
	Program createProgram(const char* source, const char* kernelName, int deviceType) 
	{
		return createProgram(1, &source, kernelName, deviceType);
	}
};

}