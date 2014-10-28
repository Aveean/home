#include "InvertStage.h"
#include "ImRecipe.h"
#include "IFXPropertyPanel.h"

/////////////////////////////////////////////////////////////////////
InvertStage::InvertStage()
{
}

/////////////////////////////////////////////////////////////////////
void InvertStage::Init()
{
  //IFXCheckBox<InvertStage> *checkbox = new IFXCheckBox<InvertStage>(_T("Enable"),this,(&InvertStage::SetActive));

  //mProperties->AddItem(checkbox);
}

/////////////////////////////////////////////////////////////////////
void InvertStage::Apply()
{
  Image2D *source = GetOwner()->GetSource();
  Image2D *result = GetOwner()->GetResult();

  if (source)
  {
    for (uint y = 0; y < source->GetHeight(); ++y)
    {
      for (uint x = 0; x < source->GetWidth(); ++x)
      {
        for (uint d = 0; d < source->GetDepth(); ++d)
          result->SetData(x,y,d,255-source->GetData(x,y,d));
      }
    }
  }
}

/////////////////////////////////////////////////////////////////////
ImStage * InvertStage::Clone()
{
  return new InvertStage();
}
