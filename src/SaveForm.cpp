/*
 * SaveForm.cpp
 *
 *  Created on: 2010-11-11
 *      Author: Pavel
 */

#include "SaveForm.h"
#include "FormMgr.h"
#include "RunnerPP.h"
#include <FIo.h>
#include <FBase.h>
#include <FContent.h>

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Media;
using namespace Tizen::Graphics;
using namespace Tizen::Io;
using namespace Tizen::Base::Collection;
using namespace Tizen::Content;

SaveForm::SaveForm() :
		_home(Tizen::App::App::GetInstance()->GetAppDataPath()), _media(
				Tizen::System::Environment::GetMediaPath() + "Others/"), _pBackground(
				null), _pFormName(null), _pFileName(null) {
}

SaveForm::~SaveForm() {
	// TODO Auto-generated destructor stub
}

result SaveForm::OnInitializing(void) {
	Image image;
	image.Construct();
	_pBackground = image.DecodeN(
			Tizen::App::App::GetInstance()->GetAppRootPath()
					+ "/res/background.png", BITMAP_PIXEL_FORMAT_ARGB8888);

	String str;
	Application* pApp = Application::GetInstance();

	Bitmap* pToMainMenuBitmap = image.DecodeN(
			Tizen::App::App::GetInstance()->GetAppRootPath()
					+ "/res/toMainMenu.png", BITMAP_PIXEL_FORMAT_ARGB8888);

	Button *pToMainMenu = new Button();
	pToMainMenu->Construct(Rectangle(285, 1130, 150, 90));
	AddControl(*pToMainMenu);
	pToMainMenu->AddActionEventListener(*this);
	pToMainMenu->SetActionId(ID_TO_MAINMENU);
	pToMainMenu->SetNormalBitmap(Point(0, 0), *pToMainMenuBitmap);
	pToMainMenu->SetNormalBackgroundBitmap(*pToMainMenuBitmap);
	delete pToMainMenuBitmap;

	Bitmap* pLeftArrowBitmap = image.DecodeN(
			Tizen::App::App::GetInstance()->GetAppRootPath()
					+ "/res/leftArrow.png", BITMAP_PIXEL_FORMAT_ARGB8888);

	Button *pLeftArrow = new Button();
	pLeftArrow->Construct(Rectangle(0, 1130, 150, 90));
	AddControl(*pLeftArrow);
	pLeftArrow->AddActionEventListener(*this);
	pLeftArrow->SetActionId(ID_LEFT_ARROW);
	pLeftArrow->SetNormalBitmap(Point(0, 0), *pLeftArrowBitmap);
	pLeftArrow->SetNormalBackgroundBitmap(*pLeftArrowBitmap);
	delete pLeftArrowBitmap;

	pApp->GetAppResource()->GetString("IDS_SAVE_TO_KML", str);

	Bitmap* pSaveToKmlBitmap = CreateBitmapText(str, 350 * SCALE_FACTOR,
			80 * SCALE_FACTOR, 30 * SCALE_FACTOR);

	Button *pSaveToKml = new Button();
	pSaveToKml->Construct(
			Rectangle(60 * SCALE_FACTOR, 400 * SCALE_FACTOR, 350 * SCALE_FACTOR,
					80 * SCALE_FACTOR));
	AddControl(*pSaveToKml);
	pSaveToKml->AddActionEventListener(*this);
	pSaveToKml->SetActionId(ID_SAVE_KML);
	pSaveToKml->SetNormalBitmap(Point(0, 0), *pSaveToKmlBitmap);
	pSaveToKml->SetNormalBackgroundBitmap(*pSaveToKmlBitmap);
	delete pSaveToKmlBitmap;

	pApp->GetAppResource()->GetString("IDS_SAVE_TO_RSS", str);
	Bitmap* pSaveToRssBitmap = CreateBitmapText(str, 350 * SCALE_FACTOR,
			80 * SCALE_FACTOR, 30 * SCALE_FACTOR);

	Button *pSaveToRss = new Button();
	pSaveToRss->Construct(
			Rectangle(60 * SCALE_FACTOR, 520 * SCALE_FACTOR, 350 * SCALE_FACTOR,
					80 * SCALE_FACTOR));
	AddControl(*pSaveToRss);
	pSaveToRss->AddActionEventListener(*this);
	pSaveToRss->SetActionId(ID_SAVE_RSS);
	pSaveToRss->SetNormalBitmap(Point(0, 0), *pSaveToRssBitmap);
	pSaveToRss->SetNormalBackgroundBitmap(*pSaveToRssBitmap);
	delete pSaveToRssBitmap;

	_pEditField = new EditField();

	_pEditField->Construct(
			Rectangle(40 * SCALE_FACTOR, 270 * SCALE_FACTOR, 400 * SCALE_FACTOR,
					80 * SCALE_FACTOR), EDIT_FIELD_STYLE_NORMAL,
			INPUT_STYLE_FULLSCREEN, true, 25, GROUP_STYLE_NONE);
	_pEditField->AddTextEventListener(*this);
	AddControl(*_pEditField);

	_pFormName = new EnrichedText();
	_pFormName->Construct(Dimension(480 * SCALE_FACTOR, 100 * SCALE_FACTOR));
	_pFormName->SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
	_pFormName->SetVerticalAlignment(TEXT_ALIGNMENT_MIDDLE);
	_pFormName->SetTextWrapStyle(TEXT_WRAP_NONE);

	Font *pFont = GetPavelFont(FONT_STYLE_PLAIN, 50 * SCALE_FACTOR);

	pApp->GetAppResource()->GetString("IDS_SAVE_TRACK", str);
	TextElement *text = new TextElement();
	text->Construct(str);
	text->SetFont(*pFont);
	text->SetTextColor(Color::COLOR_WHITE);
	_pFormName->Add(*text);

	delete pFont;

	_pFileName = new EnrichedText();
	_pFileName->Construct(Dimension(480 * SCALE_FACTOR, 50 * SCALE_FACTOR));
	_pFileName->SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
	_pFileName->SetVerticalAlignment(TEXT_ALIGNMENT_MIDDLE);
	_pFileName->SetTextWrapStyle(TEXT_WRAP_NONE);

	pFont = GetPavelFont(FONT_STYLE_PLAIN, 30 * SCALE_FACTOR);

	pApp->GetAppResource()->GetString("IDS_FILE_NAME", str);
	text = new TextElement();
	text->Construct(str);
	text->SetFont(*pFont);
	text->SetTextColor(Color::COLOR_WHITE);
	_pFileName->Add(*text);
	delete pFont;

	RunnerPP* run = static_cast<RunnerPP*>(Application::GetInstance());
	_pTrack = run->GetTrack();

	DateTime date;
	date.SetValue(_pTrack->GetStarTime().GetTicks());

	_name.Append(date.GetDay());
	_name.Append("-");
	_name.Append(date.GetMonth());
	_name.Append("-");
	_name.Append(date.GetYear());
	_name.Append("-");
	_name.Append(date.GetHour());
	_name.Append("h");
	_name.Append(date.GetMinute());
	_name.Append("m");

	_pEditField->SetText(_name);

	return GetLastResult();
}

result SaveForm::OnTerminating(void) {
	if (_pBackground != null)
		delete _pBackground;
	if (_pFormName) {
		_pFormName->RemoveAllTextElements(true);
		delete _pFormName;
	}
	if (_pFileName) {
		_pFileName->RemoveAllTextElements(true);
		delete _pFileName;
	}
	return E_SUCCESS;
}

bool SaveForm::Initialize() {
	Form::Construct(FORM_STYLE_NORMAL | FORM_STYLE_INDICATOR);
	return true;
}

result SaveForm::OnDraw(void) {
	result r = E_SUCCESS;

	Canvas* pCanvas = GetCanvasN();
	if (pCanvas != null) {
		pCanvas->DrawBitmap(
				Rectangle(0, 60, GetClientAreaBounds().width,
						GetClientAreaBounds().height), *_pBackground);
		pCanvas->DrawText(Point(0, (150 * SCALE_FACTOR) + 30), *_pFormName);
		pCanvas->DrawText(Point(0, 250 * SCALE_FACTOR), *_pFileName);
		delete pCanvas;
	}

	return r;

}
void SaveForm::OnTextValueChanged(const Tizen::Ui::Control& source) {
	_name = _pEditField->GetText();
	_name.Trim();
}

void SaveForm::OnTextValueChangeCanceled(const Tizen::Ui::Control& source) {
	//lol ?
}

void SaveForm::OnActionPerformed(const Tizen::Ui::Control& source,
		int actionId) {
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	FormMgr *pFormMgr = static_cast<FormMgr *>(pFrame->GetControl("FormMgr"));
	switch (actionId) {
	case ID_TO_MAINMENU:
		if (pFormMgr != null)
			pFormMgr->SendUserEvent(FormMgr::REQUEST_EXIT_TO_MAINMENU, null);
		break;
	case ID_LEFT_ARROW:
		if (pFormMgr != null)
			pFormMgr->SendUserEvent(FormMgr::REQUEST_TRACKSTATSFORM, null);
		break;
	case ID_SAVE_RSS:
		SaveToRss();
		break;
	case ID_SAVE_KML:
		SaveToKml();
		break;
	default:
		break;
	}
}
void DisplayMsg(String msg, String top) {
	MessageBox box;
	box.Construct(top, msg, MSGBOX_STYLE_OK, 30000);
	box.SetTitleTextColor(Color(250, 250, 250, 250));
	int i;
	box.ShowAndWait(i);
}

result SaveForm::SaveFileKml(String __path, String __filename, String __extension) {
	File* m_File = new File();
	String m_full_name = __path + __filename + "." + __extension;
	String message = "";
	String str = "";
	Application* pApp = Application::GetInstance();
	result r = m_File->Construct(m_full_name, L"w+");

	if (IsFailed(r)) {
		pApp->GetAppResource()->GetString("IDS_ERROR_MSG_CANNOT_CREATE", str);
		message.Append(str);
		message.Append(" " +__filename + "." + __extension);
		DisplayMsg(message, "Error!");
		if (m_File)
			delete m_File;
		return r;
	} else {

		/// Create this shit here!!!
		DateTime date;
		date.SetValue(_pTrack->GetStarTime().GetTicks());

		String runningDate;
		runningDate.Append(date.GetDay());
		runningDate.Append("-");
		runningDate.Append(date.GetMonth());
		runningDate.Append("-");
		runningDate.Append(date.GetYear());
		runningDate.Append("  ");
		runningDate.Append(date.GetHour());
		runningDate.Append("h");
		runningDate.Append(date.GetMinute());
		runningDate.Append("m");

		//ladujemy koordynaty !
		TrackPoint* point;

		IEnumeratorT<TrackPoint*>* pIterator;
		pIterator = _pTrack->GetEnumeratorN();

		String longitude;
		String latitude;
		String altitude;
		m_File->Write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
		m_File->Write("\n<kml xmlns=\"http://www.opengis.net/kml/2.2\">");
		m_File->Write("\n  <Document>");
		m_File->Write("\n    <name>");
		str.Clear();
		pApp->GetAppResource()->GetString("IDS_RUN_FROM", str);

		m_File->Write(str);
		m_File->Write(runningDate);
		m_File->Write("</name>");
		m_File->Write("\n    <description>");

		CreateDescription (m_File);

		m_File->Write("</description>");
		m_File->Write("\n    <Style id=\"runnerPP\">");
		m_File->Write("\n      <LineStyle>");
		m_File->Write("\n        <color>7f00ffff</color>");
		m_File->Write("\n        <width>4</width>");
		m_File->Write("\n      </LineStyle>");
		m_File->Write("\n      <PolyStyle>");
		m_File->Write("\n        <color>7f00ffff</color>");
		m_File->Write("\n      </PolyStyle>");
		m_File->Write("    </Style>");
		m_File->Write("    <Placemark>");
		m_File->Write("      <name>");
		str.Clear();
		pApp->GetAppResource()->GetString("IDS_RUN_FROM", str);
		m_File->Write(str);
		m_File->Write(" : ");
		m_File->Write(" ");
		m_File->Write(runningDate);
		m_File->Write("</name>");
		m_File->Write("\n      <description>");
		CreateDescription(m_File);
		m_File->Write("</description>");
		m_File->Write("\n      <styleUrl>#runnerPP</styleUrl>");
		m_File->Write("\n      <LineString>");
		m_File->Write("\n        <extrude>1</extrude>");
		m_File->Write("\n        <tessellate>1</tessellate>");
		m_File->Write(
				"\n        <altitudeMode>clampToGround</altitudeMode>");
		m_File->Write("\n        <coordinates>");

		pIterator->Reset();
		while (pIterator->MoveNext() == E_SUCCESS) { //wskazuje na pierwszy
			pIterator->GetCurrent(point);

			longitude.Format(9, L"%f", point->GetLongitude());
			latitude.Format(9, L"%f", point->GetLatitude());
			altitude.Append(point->GetAltitude());
			m_File->Write("\n		  ");
			m_File->Write(longitude);
			m_File->Write(",");
			m_File->Write(latitude);
			m_File->Write(",");
			m_File->Write(altitude);
			altitude.Clear();
			longitude.Clear();
			latitude.Clear();
		}

		m_File->Write(
				"\n        </coordinates>\n      </LineString>\n    </Placemark>\n  </Document>\n</kml>");

		/// ~~

		r = m_File->Flush();
		if (IsFailed(r)) {
			pApp->GetAppResource()->GetString("IDS_ERROR_MSG_NIE_ZAPISAL", str);
			message.Append(str);
			message.Append(" " +__filename + "." + __extension);
			DisplayMsg(message, "Error!");
		} else {
			pApp->GetAppResource()->GetString("IDS_FILE_SUCCESS", str);
			message.Append(str);
			message.Append(" " +__filename + "." + __extension);
			DisplayMsg(message, "Success!");
		}
		if (m_File)
			delete m_File;
		return r;
	}
}

result SaveForm::SaveFileRss(String __path, String __filename,
		String __extension) {
	File* m_File = new File();
	String m_full_name = __path + __filename + "." + __extension;
	String message = "";
	String str = "";
	Application* pApp = Application::GetInstance();
	result r = m_File->Construct(m_full_name, L"w+");

	if (IsFailed(r)) {
		pApp->GetAppResource()->GetString("IDS_ERROR_MSG_CANNOT_CREATE", str);
		message.Append(str);
		message.Append(" " +__filename + "." + __extension);
		DisplayMsg(message, "Error!");
		if (m_File)
			delete m_File;
		return r;
	} else {

		/// Create this shit here!!!
		DateTime date;
		date.SetValue(_pTrack->GetStarTime().GetTicks());

		String runningDate;
		runningDate.Append(date.GetDay());
		runningDate.Append("-");
		runningDate.Append(date.GetMonth());
		runningDate.Append("-");
		runningDate.Append(date.GetYear());
		runningDate.Append("  ");
		runningDate.Append(date.GetHour());
		runningDate.Append("h");
		runningDate.Append(date.GetMinute());
		runningDate.Append("m");

		//ladujemy koordynaty !
		TrackPoint* point;

		IEnumeratorT<TrackPoint*>* pIterator;
		pIterator = _pTrack->GetEnumeratorN();

		String longitude;
		String latitude;
		String altitude;
		m_File->Write("<?xml version=\"1.0\" encoding=\"utf-8\"?>");
		m_File->Write(
				"\n<feed xmlns=\"http://www.w3.org/2005/Atom\" \n xmlns:georss=\"http://www.georss.org/georss\">");
		m_File->Write("\n<title>");
		pApp->GetAppResource()->GetString("IDS_RUN_FROM", str);
		m_File->Write(str);
		m_File->Write(" : ");
		m_File->Write(runningDate);
		m_File->Write(" </title>");
		m_File->Write("\n <subtitle>");

		CreateDescription(m_File);

		m_File->Write("</subtitle>");
		m_File->Write(
				"\n<author> \n <name>RunnerPP</name> \n</author> \n<entry>");
		m_File->Write("\n<title>");
		pApp->GetAppResource()->GetString("IDS_RUN_FROM", str);
		m_File->Write(str);
		m_File->Write(" : ");
		m_File->Write(runningDate);
		m_File->Write("</title>");
		m_File->Write("\n<georss:line>");

		pIterator->Reset();
		while (pIterator->MoveNext() == E_SUCCESS) { //wskazuje na pierwszy
			pIterator->GetCurrent(point);

			longitude.Format(9, L"%f", point->GetLongitude());
			latitude.Format(9, L"%f", point->GetLatitude());
			m_File->Write("\n");
			m_File->Write(latitude);
			m_File->Write(" ");
			m_File->Write(longitude);
			longitude.Clear();
			latitude.Clear();
		}

		m_File->Write("\n</georss:line> \n</entry>\n</feed>\n</xml>");
		/// ~~

		r = m_File->Flush();
		if (IsFailed(r)) {
			pApp->GetAppResource()->GetString("IDS_ERROR_MSG_NIE_ZAPISAL", str);
			message.Append(str);
			message.Append(" " +__filename + "." + __extension);
			DisplayMsg(message, "Error!");
		} else {
			pApp->GetAppResource()->GetString("IDS_FILE_SUCCESS", str);
			message.Append(str);
			message.Append(" " +__filename + "." + __extension);
			DisplayMsg(message, "Success!");
		}
		if (m_File)
			delete m_File;
		return r;
	}
}

void SaveForm::SaveToKml() {
	SaveFileKml(_media, _name, "kml");
}

void SaveForm::SaveToRss() {
	SaveFileRss(_media, _name, L"rss");
}

Bitmap*
SaveForm::CreateBitmapText(String str, int width, int height, int size) {
	Canvas canvas;
	canvas.Construct(Rectangle(0, 0, width, height));
	Font* Font = GetPavelFont(FONT_STYLE_BOLD, size);

	EnrichedText eText;
	eText.Construct(Dimension(width, height));
	eText.SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
	eText.SetVerticalAlignment(TEXT_ALIGNMENT_MIDDLE);
	eText.SetTextWrapStyle(TEXT_WRAP_WORD_WRAP);

	TextElement text;
	text.Construct(str);
	text.SetFont(*Font);
	text.SetTextColor(Color::COLOR_WHITE);
	eText.Add(text);

	canvas.DrawText(Point(0, 0), eText);
	Bitmap* bit = new Bitmap();
	bit->Construct(canvas, Rectangle(0, 0, width, height));
	delete Font;
	return bit;
}

void SaveForm::CreateDescription(File* savingFile) {
	String info;
	String str;
	Application* pApp = Application::GetInstance();

	pApp->GetAppResource()->GetString("IDS_TIME", str);
	info.Append(str);
	info.Append(" : ");
	info.Append(_pTrack->GetTotalTime().GetHours());
	info.Append("h ");
	info.Append(_pTrack->GetTotalTime().GetMinutes());
	info.Append("m ");
	info.Append(_pTrack->GetTotalTime().GetSeconds());
	info.Append("s");
	savingFile->Write(info);

	info.Clear();
	info.Append("\n");
	str.Clear();
	pApp->GetAppResource()->GetString("IDS_DISTANCE", str);
	info.Append(str);
	info.Append(" : ");
	info.Append((float) _pTrack->GetDistance() / 1000);
	info.Append(" km");
	savingFile->Write(info);

	info.Clear();
	info.Append("\n");
	str.Clear();
	pApp->GetAppResource()->GetString("IDS_CALORIES", str);
	info.Append(str);
	info.Append(" : ");
	info.Append(_pTrack->GetCalories());
	info.Append(" kcal");
	savingFile->Write(info);

	info.Clear();
	info.Append("\n");
	str.Clear();
	pApp->GetAppResource()->GetString("IDS_MAX_SPEED", str);
	info.Append(str);
	info.Append(" : ");
	info.Append(_pTrack->GetMaxSpeed());
	info.Append(" km/h\n");
	savingFile->Write(info);

	info.Clear();
	str.Clear();
	pApp->GetAppResource()->GetString("IDS_AVRAGE_SPEED", str);
	info.Append(str);
	info.Append(" : ");
	info.Append(_pTrack->GetAvrageSpeed());
	info.Append(" km/h");
	savingFile->Write(info);

	info.Clear();
	str.Clear();
	pApp->GetAppResource()->GetString("IDS_HEIGHT_DIFFRENCE", str);
	info.Append(str);
	info.Append(" : ");
	info.Append(_pTrack->GetMaxAltitude() - _pTrack->GetMinAltitude());
	info.Append(" m");
	savingFile->Write(info);
}

