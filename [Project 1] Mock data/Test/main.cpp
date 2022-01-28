#include<iostream>
#include <io.h>    //_setmode()
#include <fcntl.h> //_O_WTEXT

#include<StudentMock.h>

using namespace std;

int saveStudentsToFile(vector<Student>, string);

int main() {
	_setmode(_fileno(stdout), _O_WTEXT); 

	Random rng;
	StudentMock studentStore;
	int n = rng.nextInt(5, 20);
	vector<Student> students;
	vector<Student> studentOnFebruary;
	vector<Student> studentUseViettel;
	vector<Student> studentUseGmail;
	vector<Student> studentLiveInDistrict1;

#pragma region CREATE AND SAVE N RANDOM STUDENTS
	//generate n random students
	for (int i = 0; i < n; ++i) {
		Student student = studentStore.next();
		students.push_back(student);
	}
	//save n students to students.txt
	saveStudentsToFile(students, "text_files//students.txt");
	wcout << L"Save " << n << " random students' information to file text_files/students.txt successfully !\n";
#pragma endregion

#pragma region FIND AND SAVE STUDENTS THAT BORN IN FEBRUARY
	//Find all students that have birthday on February
	for (auto student : students) {
		if (student.checkBirthMonth(2)) {
			studentOnFebruary.push_back(student);
		}
	}
	//save February students to file
	if (saveStudentsToFile(studentOnFebruary, "text_files//students_born_in_February.txt"))
		wcout << studentOnFebruary.size() << L" students who are born in February are found and saved in text_files/students_born_in_February.txt\n";
	else
		wcout << L"No students are born in February\n";
#pragma endregion

#pragma region FIND AND SAVE STUDENTS HAVE VIETTEL NUMBER
	//find all students that have Viettel number
	for (auto student : students) {
		if (student.checkMobileNetwork(L"Viettel"))
			studentUseViettel.push_back(student);
	}
	//save students who use Viettel number to student_use_Viettel.txt
	if (saveStudentsToFile(studentUseViettel, "text_files//students_use_Viettel.txt"))
		wcout << studentUseViettel.size() << L" students who have Viettel number are found and saved in text_files/students_use_Viettel.txt\n";
	else
		wcout << L"No students use Viettel number\n";
#pragma endregion

#pragma region FIND AND SAVE STUDENTS LIVING IN DISTRICT 1
	//find all students that live in District 1
	for (auto student : students) {
		if (student.checkDistrict(L"Quận 1"))
			studentLiveInDistrict1.push_back(student);
	}
	//save students who live in District 1 to student_use_Viettel.txt
	if (saveStudentsToFile(studentLiveInDistrict1, "text_files//students_live_in_district_1.txt"))
		wcout << studentLiveInDistrict1.size() << L" students who live in District 1 are found and saved in text_files/students_live_in_district_1.txt\n";
	else
		wcout << L"No students live in District 1\n";
#pragma endregion

#pragma region FIND AND SAVE STUDENTS HAVE GMAILS
	//find all students who use gmails
	for (auto student : students) {
		if (student.isUsingGmail())
			studentUseGmail.push_back(student);
	}
	//save these students with gmails to students_use_gmails.txt
	if (saveStudentsToFile(studentUseGmail, "text_files//students_use_gmails.txt"))
		wcout << studentUseGmail.size() << L" students who use gmail are found and saved in text_files/students_use_gmails.txt\n";
	else
		wcout << L"No students use gmails\n";
#pragma endregion

	return 0;
}

int saveStudentsToFile(vector<Student> studentVec, string fname) {
	wofstream fout(fname);
	locale loc(locale(), new codecvt_utf8<wchar_t>);
	
	fout.imbue(loc);

	if (studentVec.empty()) {
		fout << L"No such students found";
		fout.close();

		return 0;
	}
	else {
		for (int i = 0; i < studentVec.size() - 1; ++i)
			fout << studentVec[i] << endl << endl;
		fout << studentVec.back();

		fout.close();
	}
	
	return 1;
}
