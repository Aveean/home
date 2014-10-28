/*
 * ImStage.cpp
 *
 *  Created on: ९ जून २०११
 *      Author: pushpak
 */

#include "ImStage.h"
#include "IFXPropertyPanel.h"

ImStage::ImStage()
{
  mActive = false;

  //mPanel = NULL;
  mProperties = new IFXPropertyPanel();
}

ImStage::~ImStage()
{
  delete mProperties;
}

void ImStage::SetOwner(ImRecipe *owner)
{
  //Save the owning recipe
  mOwner = owner;
}

bool ImStage::IsActive()
{
    return mActive;
}

void ImStage::SetActive( bool active )
{
    mActive = active;
}

IFXPropertyPanel * ImStage::BuildProperties(wxWindow *parent)
{
  //Clear all previous properties
  mProperties->Create(parent);

  //Have the stage add in it's controls
  InitProperties();

  //Do final setup
  mProperties->Finalize();

  return mProperties;
}

ImRecipe *ImStage::GetOwner()
{
  return mOwner;
}

IFXPropertyPanel *ImStage::GetProperties()
{
  return mProperties;
}
