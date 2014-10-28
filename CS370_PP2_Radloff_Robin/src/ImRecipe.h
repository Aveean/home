/*
 * ImRecipe.h
 *
 *  Created on:
 *      Author: wylder
 */

#ifndef IMRECIPE__H
#define IMRECIPE__H

#include "ImStage.h"
#include <vector>

//A recipe is a list of images and fx to apply to them.
class ImRecipe
{
public:
  ImRecipe(ImageId source);
  virtual ~ImRecipe();

  //Excute the recipe
  void Execute();
  
  //Clear all stages except the default stage
  void ClearStages();

  //Inserts a new stage into the recipe
  void InsertStage(ImStage *stage, uint position = -1);

  //Removes the stage at the specified location
  void RemoveStage(uint stage);

  //Moves a stage up or down by the delta
  void ModifyStage(uint stage, int delta);

  //Enable or disable a stage
  void EnableStage(uint stage, bool flag);

  //Add another result image to the recipe
  void AddResult(ImageId result);

  //Returns the stages being applied in this recipe
  const std::vector<ImStage *> & GetStages();

  //Returns the list of results from the recipe
  std::vector<ImageId> & GetResults();

  //Returns the source image in the pipeline from previous fx
  Image2D * GetSource();

  //Returns the image to store the main result in
  Image2D * GetResult();

  //Return the Id of the source image
  ImageId GetId();

private:
  //Source image
  ImageId mSource;

  //Sandbox images
  Image2D *mSandbox[2];

  //Stages of the recipe
  std::vector<ImStage *> mStages;

  //Results from stages
  std::vector<ImageId> mResults;
};

#endif
