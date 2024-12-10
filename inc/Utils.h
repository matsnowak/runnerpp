/*
 * Utils.h
 *
 *  Created on: 2011-11-17
 *      Author: Pavel
 */

#ifndef UTILS_H_
#define UTILS_H_
#include <FGraphics.h>
#include <FSystem.h>
#include <FBaseString.h>
#include <FApp.h>

static Tizen::Graphics::Font* GetPavelFont(Tizen::Graphics::FontStyle style,int size){
	Tizen::Graphics::Font* tmp = new Tizen::Graphics::Font();
	Tizen::Base::String str;
	Tizen::Base::String ukr(L"ukr");
	Tizen::Base::String rus(L"rus");
	Tizen::System::SettingInfo::GetValue("Language", str);
//	if(str.Equals(ukr) || str.Equals(rus)){
//		tmp->Construct(App::GetInstance()->GetAppRootPath()+L"/res/Fonts/damase.ttf",style,size);
//	} else {
	tmp->Construct(Tizen::App::App::GetInstance()->GetAppRootPath() +  L"/res/Fonts/RawengulkSans.ttf" , style,size);
//	}
	return tmp;
}

#endif /* UTILS_H_ */
