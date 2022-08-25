#pragma once

#include <stdio.h>
#include <Windows.h>
#include <time.h>

#define pushBuffer(size, buffer) _pushBuffer(size, buffer, __LINE__, __FILEW__)

class CRingBuffer {

public:

	CRingBuffer(unsigned int capacity);
	~CRingBuffer();

	bool _pushBuffer(unsigned int size, const char* buffer, int line, const wchar_t* sourceFileName);
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

	char* getDirectPush();
	char* getDirectFront();

	unsigned int getUsedSize();
	unsigned int getFreeSize();

	unsigned int getDirectFreeSize();
	unsigned int getDirectUsedSize();

	bool moveFront(unsigned int);
	bool moveRear(unsigned int);

	char* getBufferStart(){return _buffer;}

	char* getRearPtr(){return &_buffer[_rear];}
	char* getFrontPtr(){return &_buffer[_front];}

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

	wchar_t fileName[35];

};