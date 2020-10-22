#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

using namespace std;

void* parseCommand(char*, char*, char*);
vector<string> split(const string &s, char delimeter);