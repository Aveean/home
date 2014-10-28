/*
 * InvertStage.h
 *
 *  Created on:
 *      Author: Wylder
 */


#ifndef INVERTSTAGE__H
#define INVERTSTAGE__H

#include "ImStage.h"

class InvertStage : public ImStage
{
public:
  InvertStage();
  
  void Init();
  
  void Apply();
  ImStage * Clone();

  const char * GetLabel() const { return "Invert Stage"; }
};

#endif
