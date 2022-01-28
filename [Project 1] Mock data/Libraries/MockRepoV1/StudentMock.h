#pragma once
#include"Student.h"
#include"TelephoneMock.h"
#include"FullNameMock.h"
#include"CitizenIdMock.h"
#include"Telephone.h"
#include"EmailMock.h"
#include"HcmAddressMock.h"
#include"BirthdayMock.h"

class StudentMock {
private:
	Random _rng;
	vector<wstring> _studentIds;
	FullNameMock _studentNames;
	CitizenIdMock _citizenIds;
	TelephoneMock _telephones;
	EmailMock _emails;
	HcmAddressMock _addresses;
	BirthdayMock _dobs;
public:
	StudentMock();

	Student next();
};