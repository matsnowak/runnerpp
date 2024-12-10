/*
 * AdUserData.h
 *
 *  Created on: 07.02.2011
 *      Author: Gerrit Alves
 */

#ifndef ADUSERDATA_H_
#define ADUSERDATA_H_

#include <FBase.h>

namespace Smaato
{
	namespace AdSDK
	{
		/*!
		  \brief Contains all the user data to be send to the server

		  The AdUserData is used to store all user supplied data for a particular ad space.
		  The provided data is passed on to the SOMA server to select the best ad for your ad space.
		  */
		class AdUserData {
		public:
			enum AdType { AdTypeImage = 0, AdTypeMedRect, AdTypeText, AdTypeAll };
			enum Gender { GenderNotSet = 0, GenderMale, GenderFemale };
			enum GenderSought { GenderSoughtNotSet = 0, GenderSoughtMale, GenderSoughtFemale, GenderSoughtBoth };
			enum MaritalStatus { MaritalStatusNotSet = 0, MaritalStatusSingle, MaritalStatusDivorced, MaritalStatusMarried };
			enum Ethnicity { EthnicityNotSet = 0, EthnicityWhite, EthnicityMiddleEastern, EthnicityBlack, EthnicityLatino, EthnicitySouthAsian, EthnicityOriental, EthnicityOther };
			enum Income { IncomeNotSet = 0, IncomeLt15 = 1, Income15to24 = 2, Income25to39 = 3, Income40to59 = 4, Income60to74 = 5, Income75to99 = 6, IncomeMt100 = 7 };
			enum Education { EducationNotSet = 0, EducationLtSecondary, EducationSecondary, EducationUniversity, EducationAdvanced };

		public:
			AdUserData();
			virtual ~AdUserData();

		public:
			AdType GetAdType() const;
			void SetAdType(AdType type);
			int GetAdSpaceId() const;
			void SetAdSpaceId(int newId);
			int GetPublisherId() const;
			void SetPublisherId(int newId);
			void SetAge(int age);
			void SetGender(Gender gender);
			void SetGenderSought(GenderSought genderSought);
			void SetEthnicity(Ethnicity ethnicity);
			void SetIncome(Income income);
			void SetMaritalStatus(MaritalStatus maritalStatus);
			void SetEducation(Education education);
			void SetKeywords(const Tizen::Base::String& keywords);
			void SetSearchString(const Tizen::Base::String& searchString);
			void SetCity(const Tizen::Base::String& city);
			void SetCountry(const Tizen::Base::String& country);
			void SetCountryCode(const Tizen::Base::String& countryCode);
			void SetState(const Tizen::Base::String& state);
			void SetZip(const Tizen::Base::String& zip);
			void SetDateOfBirth(Tizen::Base::DateTime dateOfBirth);
			void SetLatitude(double latitude);
			void SetLongitude(double longitude);
			void SetMaxHeight(int height);
			void SetMaxWidth(int width);

			int GetAge() const;
			Gender GetGender() const;
			GenderSought GetGenderSought() const;
			Ethnicity GetEthnicity() const;
			Income GetIncome() const;
			MaritalStatus GetMaritalStatus() const;
			Education GetEducation() const;
			const Tizen::Base::String& GetKeywords() const;
			const Tizen::Base::String& GetSearchString() const;
			const Tizen::Base::String& GetCity() const;
			const Tizen::Base::String& GetCountry() const;
			const Tizen::Base::String& GetCountryCode() const;
			const Tizen::Base::String& GetState() const;
			const Tizen::Base::String& GetZip() const;
			Tizen::Base::DateTime GetDateOfBirth() const;
			double GetLatitude() const;
			double GetLongitude() const;
			int GetMaxHeight() const;
			int GetMaxWidth() const;

			static Tizen::Base::String CompileAdTypeString(AdType type);
			static Tizen::Base::String CompileGenderString(Gender gender);
			static Tizen::Base::String CompileGenderSoughtString(GenderSought sought);
			static Tizen::Base::String CompileEthnicityString(Ethnicity ethnicity);
			static Tizen::Base::String CompileIncomeString(Income income);
			static Tizen::Base::String CompileMaritalStatusString(MaritalStatus status);
			static Tizen::Base::String CompileEducationString(Education education);

		private:
	        AdType                                          __pAdType;
	        int                                             __pAdSpaceId;
	        int                                             __pPublisherId;

	        int                                             __pAge;
	        Gender                                          __pGender;
	        GenderSought                                    __pGenderSought;
	        Ethnicity                                       __pEthnicity;
	        Income                                          __pIncome;
	        MaritalStatus                                   __pMaritalStatus;
	        Education                                       __pEducation;

	        Tizen::Base::String                               __pKeywords;
	        Tizen::Base::String                               __pSearchString;
	        Tizen::Base::String                               __pCity;
	        Tizen::Base::String                               __pCountry;
	        Tizen::Base::String                               __pCountryCode;
	        Tizen::Base::String                               __pZip;
	        Tizen::Base::DateTime                             __pDateOfBirth;
	        Tizen::Base::String                               __pState;

	        double                                          __pLatitude;
	        double                                          __pLongitude;

	        int 											__pMaxHeight;
	        int 											__pMaxWidth;
		};
	}
}

#endif /* ADUSERDATA_H_ */
