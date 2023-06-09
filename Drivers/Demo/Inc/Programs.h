#pragma once

#include "Regulator.h"


typedef struct{
	void (*constructor)(void);
	void (*destructor)(void);
	void (*runner)(void);
}Program;

typedef struct{
	bool isStart;
	uint32_t globalTime;
	uint8_t currentProg;
	uint8_t currentPage;
	uint8_t currentCycle;
	uint8_t number_clicks_button5;
	float input_arg;
	float speed;
	float distanse;
	float progress;
	Program demo;
}EduBot;

extern Program demo;
extern EduBot robot;

void Robot_Init(void);

void ConstrctionProgram(void);

void DestrctionProgram(void);

void RunnerProgram1(void);
