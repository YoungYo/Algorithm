#pragma once
#include "print.h"
template <typename T> struct Print //函数对象：倍增一个T类对象
   {  void operator() ( T& e ) { cout << e; }  }; //假设T可直接倍增
