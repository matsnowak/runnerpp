/*
 * Options->cpp
 *
 *  Created on: 2010-07-20
 *      Author: Pavel
 */

#include "Options.h"

Options::Options() {
}

Options::~Options() {
	if(_save){
		SaveChanges();
	}
	delete _reg;
}

void
Options::Construct(){
	_reg = new RegistryScanner();
	_reg->Construct();
}

void
Options::SaveChanges(){
	_reg->Save();
}

bool
Options::GetVibe_isActivated(){
	_reg->SetSection(L"Vibe");
	return _reg->GetInt(L"_isActivated");
}

bool
Options::SetVibe_isActivated(bool __value){
	_reg->SetSection(L"Vibe");
	_save=true;
	return _reg->Set(L"_isActivated",__value);
}

int
Options::GetVibe_vibrationLevel(){
	_reg->SetSection(L"Vibe");
	return _reg->GetInt(L"_vibrationLevel");
}

bool
Options::SetVibe_vibrationLevel(int __value){
	_reg->SetSection(L"Vibe");
	_save=true;
	return _reg->Set(L"_vibrationLevel",__value);
}

int
Options::GetVibe_vibrationDistance(){
	_reg->SetSection(L"Vibe");
	return _reg->GetInt(L"_vibrationDistance");
}

bool
Options::SetVibe_vibrationDistance(int __value){
	_reg->SetSection(L"Vibe");
	_save=true;
	return _reg->Set(L"_vibrationDistance",__value);
}



int
Options::GetPersonalities_weight(){
	_reg->SetSection(L"Personalities");
	return _reg->GetInt(L"_weight");
}

bool
Options::SetPersonalities_weight(int __value){
	_reg->SetSection(L"Personalities");
	_save=true;
	return _reg->Set(L"_weight",__value);
}

int
Options::GetPersonalities_height(){
	_reg->SetSection(L"Personalities");
	return _reg->GetInt(L"_height");
}
bool
Options::SetPersonalities_height(int __value){
	_reg->SetSection(L"Personalities");
	_save=true;
	return _reg->Set(L"_height",__value);
}


