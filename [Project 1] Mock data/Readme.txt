1, Thông tin sinh viên
	- Họ tên: Lê Kiệt
	- MSSV: 19120554
2, Điểm mong muốn: 9.0+
3, Functions
	* Hàm đã làm được: tất cả các hàm của mỗi class trong Slide OOP 04
	* 1 số thay đổi so với Slide: 
		- Sử dụng wstring xuyên suốt thay vì string
	* Hàm bổ sung: 	
		- Bổ sung toán tử "<<" dành cho class: Address, DateTime, FullName, Student, Telephone
		- Đối với class DateTime, có thêm các hàm 
			+ Hàm static: currentDay() và currentMonth() để lấy ngày và tháng tính tới hiện tại
				static int currentDay();
				static int currentMonth();
			+ Hàm kiểm tra ngày/tháng/năm có vượt quá ngày hiện tại (hỗ trợ cho class BirthdayMock sau này): 
				bool isValidNow();
		- Đối với class BirthdayMock: hàm next() có thêm đoạn code để kiểm tra ngày tháng năm sinh tạo ngẫu nhiên có hợp lệ (nghĩa là
không vượt quá ngày hiện tại), nếu vi phạm thì lại ngẫu nhiên 1 ngày tháng năm sinh khác
		- Đối với class FullName & FullNameMock: 
				+ Đọc và xử lý được tên Tiếng Việt có dấu
		- Đối với class Student: có thê các hàm để hỗ trợ giải các bài tập Slide OOP 04/trang 66
			+ bool checkBirthMonth(int m); 				-> Kiểm tra sinh viên có tháng sinh là m hay không
			+ bool checkMobileNetwork(wstring ispName); -> Kiểm tra sinh viên có dùng mạng ispName không (VD: Viettel)
			+ bool checkDistrict(wstring dist) ;		-> Kiểm tra sinh viên có sống ở quận dist không
			+ bool isUsingEmail();						-> Kiểm tra sinh viên có sử dụng gmail không
		
		- 1 số hàm helper được định nghĩa trong file Utils.h
			+ getAccentVietnameseLetters(): đọc file accentVietnameseLetters.txt và lấy các ký tự Tiếng Việt thêm dấu cả thường và hoa
và lưu vào trong object kiểu map<wchar_t, vector<wchar_t>>. Với mỗi dòng trong 	accentVietnameseLetters.txt được hiểu như sau:
				<Ký tự thuần không dấu> <Các ký tự có dấu>
				VD: a á à ã ạ ả ă ắ ặ ẳ ẵ â ẩ ậ ấ ầ ẫ 
				• 'a': ký tự thuần không dấu -> là kiểu wchar_t trong map 
				• [á à ã ạ ả ă ắ ặ ẳ ẵ â ẩ ậ ấ ầ ẫ]: Các ký tự có dấu của 'a' -> là kiểu vector<wchar_t> trong map 
			+ toNonAccentVietnamese(wstring ws): chuyển chuỗi Tiếng Việt có dấu (VD: Đoàn Ưng Hà) sang Tiếng Việt không dấu (VD: Doan Ung Ha)
		➼ Mục đích: hỗ trợ việc tạo email. VD: Đoàn Ưng Hà sẽ có email là DUHa@gmail.com thay vì ĐƯHa@gmail.com
			
		- Đối với class HcmAddressMock: _streets và _wards có kiểu map<wstring, vector<wstring>>: với mỗi quận (wstring trong map) sẽ chỉ có vài 
đường và phường (vector<wstring> trong map) thuộc về quận đó, tránh trường hợp random ra đường A của cả 3-4 quận
			
	*Đọc các file text
		- class CitizenIdMock: thuộc tính _cityCodes lấy mã của 63 tỉnh thành trong city_codes.txt
		- class EmailMock: thuộc tính _domains lấy 20 tên miền trong domains_email.txt
		- class FullNameMock: lấy họ, tên lót (nam + nữ), tên (nam + nữ) từ 6 files sau, mỗi file hỗ trợ 20+ họ/tên lót/tên: 
			+ female_first_names.txt
			+ female_middle_names.txt
			+ male_first_names.txt
			+ male_middle_names.txt
		- class HcmAddressMock: lấy tên đường, tên quận, tên phường từ các file HCM_streets.txt, HCM_districts.txt, HCM_wards.txt; riêng file HCM_streets.txt 
hỗ trợ 100+ tên đường
		- class StudentMock: thuộc tính _studentIds lấy dữ liệu từ student_ids.txt, hỗ trợ 100+ mã số sinh viên	

4, class Student và StudentMock UML (trong Slide để trống)
	*Student:
		|-----------------------------------------------------------------------------------------|
		|	Student																				  |
		|-----------------------------------------------------------------------------------------|
		|  - _studentId: wstring                                                                  |
		|  - _fullName: FullName                                                                  |
		|  - _citizenId: wstring                                                                  |
		|  - _telephone: Telephone                                                                |
		|  - _email: wstring                                                                      |
		|  - _address: Address                                                                    |
		|  - _birthday: DateTime                                                                  |
		|-----------------------------------------------------------------------------------------|
		|  + Student()                                                                            |
		|  + Student(wstring, FullName, wstring, Telephone, wstring, Address, DateTime)           |
		|  + checkBirthMonth(int m): bool                                                         |
		|  + checkMobileNetwork(wstring ispName): bool                                            |
		|  + checkDistrict(wstring dist): bool                                                    |
		|  + isUsingEmail(): bool                                                                 |
		|-----------------------------------------------------------------------------------------|                                                                                         |
			
	*StudentMock:
	
		|------------------------------------------------|
		|	StudentMock									 |
		|------------------------------------------------|
		|  - _rng: Random                      		     |
		|  - _studentIds: vector<wstring>                |
		|  - _studentNames: FullNameMock                 |
		|  - _citizenIds: CitizenIdMock                  |
		|  - _telephones: TelephoneMock                  |
		|  - _emails: EmailMock                      	 |
		|  - _addresses: HcmAddressMock                  |
		|  - _dobs: BirthdayMock                         |
		|------------------------------------------------|
		|  + StudentMock()                               |
		|  + next(): Student           					 |
		|------------------------------------------------|                                                                                         |
	
			