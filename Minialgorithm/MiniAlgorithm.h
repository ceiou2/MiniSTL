//MiniAlgorithm.h
#pragma once
#ifndef MINI_ALGORITHM_H
#define MINI_ALGORITHM_H

#include<cstddef>

int min(int a,int b){
  if(a<b)return a;
  return b;
}

size_type min(size_type a,size_type b){
  if(a<b)return a;
  return b;
}


#endif
