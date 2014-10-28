/*
 * ImStage.h
 *
 *  Created on: ९ जून २०११
 *      Author: pushpak
 */

#ifndef IMSTAGE_H_
#define IMSTAGE_H_

#include "Image2D.h"

class IFXPropertyPanel;
class ImRecipe;

class ImStage {
public:
	ImStage();
	virtual ~ImStage();

  virtual bool IsActive();
	virtual void SetActive( bool active );

	virtual void SetOwner( ImRecipe *owner );
  virtual void Init() {}
  virtual void Apply() = 0;

	virtual ImStage * Clone() = 0;
  virtual const char * GetLabel() const = 0;
  virtual void InitProperties() {}

  IFXPropertyPanel * BuildProperties(wxWindow *parent);
  IFXPropertyPanel * GetProperties();

protected:
  ImRecipe *GetOwner();

private:
    bool mActive;
    ImRecipe *mOwner;
    IFXPropertyPanel *mProperties;
};

#endif /* IMSTAGE_H_ */
