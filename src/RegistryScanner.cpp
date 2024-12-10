/*
 * RegistryScanner.cpp
 *
 *  Created on: 2010-07-20
 *      Author: Pavel
 */


#include "RegistryScanner.h"
#include <FApp.h>
RegistryScanner::RegistryScanner() {
}

RegistryScanner::~RegistryScanner() {
	Save();
}

bool
RegistryScanner::Construct(){
	String str(L"/data/Options.ini");
	_reg.Construct(Tizen::App::App::GetInstance()->GetAppRootPath()+str,true);//tworzy jak nie istnieje
}

bool
RegistryScanner::SetUP(){
	_reg.AddSection(L"Vibe");
		_reg.AddValue(L"Vibe",L"_isActivated",1);
		_reg.AddValue(L"Vibe",L"_vibrationLevel",50);
		_reg.AddValue(L"Vibe",L"_vibrationDistance",500);
	_reg.AddSection(L"Personalities");
		_reg.AddValue(L"Personalities","_height",0);
		_reg.AddValue(L"Personalities","_weight",0);
	return Save();
}

bool
RegistryScanner::SetSection(String __section){
	_section=__section;
}

String
RegistryScanner::GetSection(){
	return _section;
}

bool
RegistryScanner::RemoveSection(String __section){
	result r=_reg.RemoveSection(__section);
	if(r==E_SECTION_NOT_FOUND){
		AppLog("Nie znaleziono sekcji do usuniecia");
		return false;
	}
	return true;
}


bool
RegistryScanner::Set(String __key,int __value){
	result r=_reg.SetValue(_section,__key,__value);
	if(E_KEY_NOT_FOUND == r || E_SECTION_NOT_FOUND==r){
		AppLog("SetINT:Nie znaleziono klucza lub nie znaleziono sekcji");
		return false;
	}
	return true;
}

bool
RegistryScanner::Set(String __key,double __value){
	result r=_reg.SetValue(_section,__key,__value);
	if(E_KEY_NOT_FOUND == r || E_SECTION_NOT_FOUND==r){
		AppLog("SetDOUBLE:Nie znaleziono klucza lub nie znaleziono sekcji");
		return false;
	}
	return true;
}

bool
RegistryScanner::Set(String __key,float __value){
	result r=_reg.SetValue(_section,__key,__value);
	if(E_KEY_NOT_FOUND == r || E_SECTION_NOT_FOUND==r){
		AppLog("SetFLOAT:Nie znaleziono klucza lub nie znaleziono sekcji");
		return false;
	}
	return true;
}

bool
RegistryScanner::Set(String __key,String __value){
	result r=_reg.SetValue(_section,__key,__value);
	if(E_KEY_NOT_FOUND == r || E_SECTION_NOT_FOUND==r){
		AppLog("SetSTRING:Nie znaleziono klucza lub nie znaleziono sekcji");
		return false;
	}
	return true;
}

bool
RegistryScanner::Set(String __key,bool __value){
	result r;
	if(__value==true)r=_reg.SetValue(_section,__key,1);
	else r=_reg.SetValue(_section,__key,0);
	if(E_KEY_NOT_FOUND == r || E_SECTION_NOT_FOUND==r){
		AppLog("SetSTRING:Nie znaleziono klucza lub nie znaleziono sekcji");
		return false;
	}
	return true;
}

bool
RegistryScanner::Add(String __key,int __value){
	result r=_reg.AddValue(_section,__key,__value);
	if(E_SUCCESS==r) return true;
	else if(E_KEY_ALREADY_EXIST ==r)AppLog("Key juz istnieje");
	else if(E_SECTION_NOT_FOUND==r)AppLog("Blad Sekcji");
	return false;
}

bool
RegistryScanner::Add(String __key,double __value){
	result r=_reg.AddValue(_section,__key,__value);
	if(E_SUCCESS==r) return true;
	else if(E_KEY_ALREADY_EXIST ==r)AppLog("Key juz istnieje");
	else if(E_SECTION_NOT_FOUND==r)AppLog("Blad Sekcji");
	return false;
}

bool
RegistryScanner::Add(String __key,float __value){
	result r=_reg.AddValue(_section,__key,__value);
	if(E_SUCCESS==r) return true;
	else if(E_KEY_ALREADY_EXIST ==r)AppLog("Key juz istnieje");
	else if(E_SECTION_NOT_FOUND==r)AppLog("Blad Sekcji");
	return false;
}

bool
RegistryScanner::Add(String __key,String __value){
	result r=_reg.AddValue(_section,__key,__value);
	if(E_SUCCESS==r) return true;
	else if(E_KEY_ALREADY_EXIST ==r)AppLog("Key juz istnieje");
	else if(E_SECTION_NOT_FOUND==r)AppLog("Blad Sekcji");
	return false;
}

bool
RegistryScanner::Add(String __key,bool __value){
	result r;
	if(__value==true)r=_reg.AddValue(_section,__key,1);
	else r=_reg.AddValue(_section,__key,0);
	if(E_SUCCESS==r) return true;
	else if(E_KEY_ALREADY_EXIST ==r)AppLog("Key juz istnieje");
	else if(E_SECTION_NOT_FOUND==r)AppLog("Blad Sekcji");
	return false;
}

int
RegistryScanner::GetInt(String __key){
	int returningValue;
	result r=_reg.GetValue(_section,__key,returningValue);
	if(E_KEY_NOT_FOUND == r || E_SECTION_NOT_FOUND==r){
		AppLog("GetInt:Nie znaleziono klucza lub nie znaleziono sekcji");
		return 0;
	}
	return returningValue;
}

double
RegistryScanner::GetDouble(String __key){
	double returningValue;
	result r=_reg.GetValue(_section,__key,returningValue);
	if(E_KEY_NOT_FOUND == r || E_SECTION_NOT_FOUND==r){
		AppLog("GetDouble:Nie znaleziono klucza lub nie znaleziono sekcji");
		return 0;
	}
	return returningValue;
}

float
RegistryScanner::GetFloat(String __key){
	float returningValue;
	result r=_reg.GetValue(_section,__key,returningValue);
	if(E_KEY_NOT_FOUND == r || E_SECTION_NOT_FOUND==r){
		AppLog("GetInt:Nie znaleziono klucza lub nie znaleziono sekcji");
		return 0;
	}
	return returningValue;
}

String
RegistryScanner::GetString(String __key){
	String returningValue;
	result r=_reg.GetValue(_section,__key,returningValue);
	if(E_KEY_NOT_FOUND == r || E_SECTION_NOT_FOUND==r){
		AppLog("GetInt:Nie znaleziono klucza lub nie znaleziono sekcji");
		return returningValue;
	}
	return returningValue;
}

bool
RegistryScanner::GetBool(String __key){
	int returningValue;
	result r=_reg.GetValue(_section,__key,returningValue);
	if(E_KEY_NOT_FOUND == r || E_SECTION_NOT_FOUND==r){
		AppLog("GetInt:Nie znaleziono klucza lub nie znaleziono sekcji");
		return false;
	}
	if(returningValue==1) return true;
	else return false;
}

bool
RegistryScanner::Save(){
	result r=_reg.Flush();
	if(r==E_SUCCESS) return true;
	else if(r==E_ILLEGAL_ACCESS) AppLog("Nie mozna zapisac-brak dostepu");
	else if(r==E_MAX_EXCEEDED) AppLog("Nie mozna zapisac-zbyt duzo otwartych plikow");
	else if(r==E_IO) AppLog("Nie mozna zapisac-blad pliku/urzadzenia");
	return false;
}

