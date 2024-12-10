/*
 * ILockedForm.h
 *
 *  Created on: 2010-11-08
 *      Author: Mateusz
 */

#ifndef ILOCKEDFORM_H_
#define ILOCKEDFORM_H_




/**
 * @class ILockedForm
 * Interfejs reprezentujcy cos, co mo¿na blokowac i odblokowac
 */
class ILockedForm {

public:
	/**
	 * Zablokuj
	 * @param argf parametr do przekazania
	 */
	virtual void Lock(int lockReason) = 0;

	/**
	 * Odblokuj
	 * @param argf parametr do przekazania
	 */
	virtual void Unlock(int lockReason) = 0;

	/**
	 * Wysylamy cos
	 *
	 */
	virtual void SendSomethingToForm(int something) = 0;
};

#endif /* ILOCKEDFORM_H_ */
