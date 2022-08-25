#pragma once

#include <stdio.h>
#include <Windows.h>
#include <time.h>

#define pushBuffer(size, buffer) _pushBuffer(size, buffer, __LINE__, __FILEW__)

class CRingBuffer {

public:

	CRingBuffer(unsigned int capacity);
	~CRingBuffer();

	void _pushBuffer(unsigned int size, const char* buffer, int line, const wchar_t* sourceFileName);
	bool popBuffer(unsigned int size);
	bool frontBuffer(unsigned int size, char* buffer);

	inline int getCapacity() {
		return _capacity;
	}

	inline int getRear() {
		return _rear;
	}

	inline int getFront() {
		return _front;
	}

	unsigned int getUsedSize();
	unsigned int getFreeSize();


	// ----- 링버퍼에 대한 직접적인 접근 -----
	char* getDirectRear();
	char* getDirectFront();

	unsigned int getDirectFreeSize();
	unsigned int getDirectUsedSize();

	bool moveFront(unsigned int);
	bool moveRear(unsigned int);

	char* getBufferStart(){return _buffer;}
	// ----------------------------------------

private:
	
	void resize(int size, int line, const wchar_t* sourceFileName);

private:

	char* _buffer;

	// 사용할 수 있는 buffer의 크기
	unsigned int _capacity;
	// capacity + 1, 실제로 할당받은 버퍼 크기
	unsigned int _actualCap;

	unsigned int _rear;
	unsigned int _front;

	// ------ 로깅용 ------
	wchar_t fileName[35];
	// --------------------

};