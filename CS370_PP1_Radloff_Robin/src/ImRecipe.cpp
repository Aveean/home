#include "ImRecipe.h"
#include "MathLibrary.h"
#include "Image2D.h"


ImRecipe::ImRecipe(ImageId source)
{
  mSource = source;

  mSandbox[0] = new Image2D();
  mSandbox[1] = new Image2D();

  //Generate at least one result image
  Image2D *image = Image2D::newImage((mSource.mName + " :Post").c_str());
  AddResult(image->GetId());
}

ImRecipe::~ImRecipe()
{
  for (uint i = 0; i < mStages.size(); ++i)
    delete mStages[i];

  delete mSandbox[0];
  delete mSandbox[1];
}

//Excute the recipe
void ImRecipe::Execute()
{
  mSandbox[0]->CopyFrom(mSource);
  mSandbox[1]->CopyFrom(mSource);

  //Apply all active stages
  for (uint i = 0; i < mStages.size(); ++i)
  {
    if (mStages[i]->IsActive())
    {
      mStages[i]->Apply();
      std::swap(mSandbox[0],mSandbox[1]);
    }
  }

  ((Image2D*)mResults[0])->CopyFrom(mSandbox[0]);
}

//Erase all stages but default stage
void ImRecipe::ClearStages()
{
  //Clear all stages except the default stage
  for (uint i = 1; i < mStages.size(); ++i)
    delete mStages[i];

  ////Save the default stage
  //ImStage *stage = mStages[0];
  mStages.clear();
  //mStages.push_back(stage);
}

//Inserts a new stage into the recipe
void ImRecipe::InsertStage(ImStage *stage, uint position)
{
  //Save the original source into the stage
  stage->SetOwner(this);
  stage->Init();

  if (position < mStages.size())
  {
    //Insert it into the list
    std::vector<ImStage *>::iterator iter = mStages.begin();
    std::advance(iter,position);
    mStages.insert(iter, stage);
  }
  else
  {
    //Otherwise just append it to the back
    mStages.push_back(stage);
  }
}

//Removes the stage at the specified location
void ImRecipe::RemoveStage(uint index)
{
  //Removes and delete the stage
  if (index < mStages.size())
  {
    ImStage *stage = mStages[index];
    std::vector<ImStage *>::iterator iter = mStages.begin();
    std::advance(iter, index);
    mStages.erase(iter);
    delete stage;
  }
}

//Moves a stage up or down by the delta
void ImRecipe::ModifyStage(uint index, int delta)
{
  //If they're valid indices, swap them with each other
  if (index < mStages.size() && index + delta < mStages.size())
    std::swap(mStages[index],mStages[index+delta]);
}

//Enable or disable a stage
void ImRecipe::EnableStage(uint index, bool flag)
{
  if (index < mStages.size())
    mStages[index]->SetActive(flag);
}

//Add another result image to the recipe
void ImRecipe::AddResult(ImageId result)
{
  mResults.push_back(result);
}

//Returns the stages being applied in this recipe
const std::vector<ImStage *> & ImRecipe::GetStages()
{
  return mStages;
}

//Returns the list of results from the recipe
std::vector<ImageId> & ImRecipe::GetResults()
{
  return mResults;
}

//Returns the image to store the main result in
Image2D * ImRecipe::GetSource()
{
  return mSandbox[0];
}

//Return the Id of the source image
Image2D * ImRecipe::GetResult()
{
  return mSandbox[1];
}

//Return the Id of the source image
ImageId ImRecipe::GetId()
{
  return mSource;
}
