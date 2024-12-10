/*
 * SaveForm.h
 *
 *  Created on: 2010-11-11
 *      Author: Pavel
 */

#ifndef SAVEFORM_H_
#define SAVEFORM_H_

#include <FBase.h>
#include <FUi.h>
#include <FGraphics.h>
#include <FIo.h>
#include <FMedia.h>
#include "Utils.h"

#include "IBaseForm.h"
#include "Track.h"


using namespace Tizen::Graphics;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Media;
using namespace Tizen::Base;

class SaveForm : public IBaseForm,
		public Tizen::Ui::IActionEventListener,
		public Tizen::Ui::ITextEventListener
{

public:
	SaveForm();
	virtual ~SaveForm();

	bool Initialize();
	result OnDraw();
	result OnInitializing();
	result OnTerminating();

	void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);
	void OnTextValueChanged(const Tizen::Ui::Control& source);
	void OnTextValueChangeCanceled(const Tizen::Ui::Control& source);

	void SaveToKml();
	void SaveToRss();

	result SaveFileRss(String __path, String __filename, String __extension);
	result SaveFileKml(String __path, String __filename, String __extension);

private:
	Tizen::Graphics::Bitmap* CreateBitmapText(String str, int width,int height,int size);
	void CreateDescription(Tizen::Io::File* file);

	static const int ID_SAVE_KML = 100;
	static const int ID_SAVE_RSS = 101;
	static const int ID_TO_MAINMENU = 102;
	static const int ID_LEFT_ARROW = 103;
	String _name;
	String _home;
	String _media;
	bool _success;
	Tizen::Graphics::Bitmap* _pBackground;
	Track* _pTrack;
	Tizen::Ui::Controls::EditField* _pEditField;
	Tizen::Graphics::EnrichedText* _pFormName;
	Tizen::Graphics::EnrichedText* _pFileName;

};

#endif /* SAVEFORM_H_ */
