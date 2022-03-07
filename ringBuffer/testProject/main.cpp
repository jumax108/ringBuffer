#include <stdio.h>
#include <Windows.h>
#include <thread>

#include "../headers/ringBuffer.h"
#pragma comment(lib, "../release/ringBuffer")

char data[] = "1234567890 ";
constexpr int len = 11;

unsigned __stdcall pushFunc(void* arg);
unsigned __stdcall popFunc(void* arg);


CRingBuffer ringBuffer(30);

int main(){

	_beginthreadex(nullptr, 0, pushFunc, nullptr, 0, nullptr);
	_beginthreadex(nullptr, 0, popFunc, nullptr, 0, nullptr);

	Sleep(INFINITE);

	return 0;
}

unsigned __stdcall pushFunc(void* arg){

	int pushedSize = 0;
	int pushAbleSize = len;

	for(;;){
		
		int pushSize = rand() % pushAbleSize + 1;

		while(ringBuffer.getFreeSize() < pushSize);

		ringBuffer.push(pushSize, data + pushedSize);

		if(pushAbleSize == pushSize){
			pushedSize = 0;
			pushAbleSize = len;
		} else {
			pushAbleSize -= pushSize;
			pushedSize += pushSize;
		}

	}

	return 0;
}

unsigned __stdcall popFunc(void* arg){

	char buf[40];
	for(;;){

		while(ringBuffer.getUsedSize() == 0);

		ZeroMemory(buf, 40);

		int popSize = ringBuffer.getUsedSize();

		ringBuffer.front(popSize, buf);
		ringBuffer.pop(popSize);

		printf("%s",buf);

	}

	return 0;
}