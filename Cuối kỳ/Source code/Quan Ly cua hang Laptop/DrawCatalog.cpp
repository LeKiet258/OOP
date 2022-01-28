#include"DrawCatalog.h"
#include"Rectangle.h"


void DrawCatalog::resetVariables() {
	_indent = 2;
	_brandChoice = _laptopChoice = 0;
}

void DrawCatalog::drawFrameBrands() {
	class Rectangle rec(_frameBrand[0], _frameBrand[1]);
	rec.draw();
}

void DrawCatalog::drawFrameLaptops() {
	class Rectangle rec(_frameLaptop[0], _frameLaptop[1]);
	rec.draw();
}

void DrawCatalog::drawInstruction(int code) {
	vector<wstring> instructions;
	class Rectangle rec;

	if (code == 0) 
		instructions = { L"[w/s]: Di chuyển lên/xuống", L"[t]: Thêm hãng", L"[x]: Xóa hãng", L"[f]: Sửa hãng", L"[Enter]: Chọn hãng", L"[Esc]: Trở lại Menu" };
	else if (code == 1) 
		instructions = { L"[w/s]: Di chuyển lên/xuống", L"[t]: Thêm Laptop", L"[x]: Xóa laptop", L"[Enter]: Xem và sửa thông số laptop", L"[Esc]: Trở lại" };
	else if (code == 2) 
		instructions = { L"[t]: Thêm thông tin", L"[x]: Xóa thông tin", L"[f]: Sửa thông tin", L"[Esc]: Trở lại "};

	//clear old instruction frame
	clearRegion(_frameInstruction[0], _frameInstruction[1]);

	int maxMessageLen = longestStringLength(instructions);
	int yEnd = _frameInstruction[0].y() + instructions.size() + 1;
	int yStart = _frameInstruction[0].y();
	int xStart = (consoleWidth - (maxMessageLen + 5)) / 2 + 1;
	int xEnd = xStart + maxMessageLen + 3;
	_frameInstruction[0] = { xStart, yStart };
	_frameInstruction[1] = { xEnd, yEnd };

	rec = class Rectangle(_frameInstruction[0], _frameInstruction[1]);
	rec.draw();
	for (int i = 0; i < instructions.size(); ++i) {
		gotoXY(xStart + 2, yStart + i + 1);
		std::wcout << instructions[i];
	}
}

void DrawCatalog::clearFrameInstruction() {
	clearRegion(Point(_frameInstruction[0].x() - 10, _frameInstruction[0].y()),
		Point(_frameInstruction[1].x() + 10, _frameInstruction[1].y()));
}

void DrawCatalog::clearFrameLaptopsContent() {
	clearRegion(Point(_frameLaptop[0].x() + 1, _frameLaptop[0].y() + 1),
		Point(_frameLaptop[1].x() - 1, _frameLaptop[1].y() - 1));
}


void DrawCatalog::drawButtonDownBrand() {
	int x = _frameBrand[0].x() + ((_frameBrand[1].x() - _frameBrand[0].x())) / 2;
	gotoXY(x, _frameBrand[1].y() + 1);
	std::wcout << L"▼";
}

void DrawCatalog::drawButtonUpBrand() {
	int x = _frameBrand[0].x() + ((_frameBrand[1].x() - _frameBrand[0].x())) / 2;
	gotoXY(x, _frameBrand[0].y() - 1);
	std::wcout << L"▲";
}

void DrawCatalog::drawButtonUpLaptops() {
	int x = _frameLaptop[0].x() + ((_frameLaptop[1].x() - _frameLaptop[0].x())) / 2;
	gotoXY(x, _frameLaptop[0].y() - 1);
	std::wcout << L"▲";
}

void DrawCatalog::drawButtonDownLaptops() {
	int x = _frameLaptop[0].x() + ((_frameLaptop[1].x() - _frameLaptop[0].x())) / 2;
	gotoXY(x, _frameLaptop[1].y() + 1);
	std::wcout << L"▼";
}

void DrawCatalog::clearButtonDownBrand() {
	int x = _frameBrand[0].x() + ((_frameBrand[1].x() - _frameBrand[0].x())) / 2;
	gotoXY(x, _frameBrand[1].y() + 1);
	std::wcout << L" ";
}

void DrawCatalog::clearButtonUpBrand() {
	int x = _frameBrand[0].x() + ((_frameBrand[1].x() - _frameBrand[0].x())) / 2;
	gotoXY(x, _frameBrand[0].y() - 1);
	std::wcout << L" ";
}

void DrawCatalog::clearButtonUpLaptops() {
	int x = _frameLaptop[0].x() + ((_frameLaptop[1].x() - _frameLaptop[0].x())) / 2;
	gotoXY(x, _frameLaptop[0].y() - 1);
	std::wcout << L" ";
}

void DrawCatalog::clearButtonDownLaptops() {
	int x = _frameLaptop[0].x() + ((_frameLaptop[1].x() - _frameLaptop[0].x())) / 2;
	gotoXY(x, _frameLaptop[1].y() + 1);
	std::wcout << L" ";
}

void DrawCatalog::clearFrameBrandContent() {
	clearRegion(Point(_frameBrand[0].x() + 1, _frameBrand[0].y() + 1),
		Point(_frameBrand[1].x() - 1, _frameBrand[1].y() - 1));
}

void DrawCatalog::viewBrands(int start, int end) {
	vector<wstring> brands = _catalog->brands();
	//start = 0;
	end = min(brands.size(), end);

	if (_brandChoice >= end) {
		end = _brandChoice + 1;
		start = end - 18;
	}
	else if (_brandChoice < start) {
		--start;
		--end;
	}

	if (end < brands.size())
		drawButtonDownBrand();
	else if (end == brands.size())
		clearButtonDownBrand();
	if (start > 0)
		drawButtonUpBrand();
	else if (start == 0)
		clearButtonUpBrand();

	vector<wstring> display = vector(brands.begin() + start, brands.begin() + end);
	for (int i = 0; i < display.size(); ++i) {
		gotoXY(_frameBrand[0].x() + _bullet.length() + 3, _frameBrand[0].y() + i + 1);
		int _choice = _brandChoice - start;
		std::wcout << display[i];
	}
}

int DrawCatalog::brandProcessing() {
	vector<wstring> brands = _catalog->brands();
	char keyboard = ' ';
	vector<wstring> display;
	int start = 0;
	int end = 18;
	bool reviewBrand = 0;
	bool reviewLaptop = 1;

	drawFrameTitle(L"DANH MỤC");
	clearFrameInstruction(); //clear old instructions (if any)
	drawInstruction(0);
	drawFrameLaptops();
	viewBrands(start, end);
	drawFrameBrands();

	while (keyboard != ESC) { 
		if (_brandChoice >= end) {
			end = _brandChoice + 1;
			start = end - 18;
			reviewBrand = 1;
		}
		else if (_brandChoice < start) {
			--start;
			--end;
			reviewBrand = 1;
		}
		else if (brands.size() == 18) {
			start = 0;
			end = 18;
		}

		gotoXY(_frameBrand[0].x() + _indent, _frameBrand[0].y() + _brandChoice - start + 1);
		std::wcout << _bullet;
		
		//draw arrows
		if (end < brands.size() && end - start <= 18) drawButtonDownBrand();
		else if(end == brands.size()) clearButtonDownBrand();
		if (start > 0) drawButtonUpBrand();
		else if(start == 0) clearButtonUpBrand();

		if (reviewBrand) { //redisplay
			clearFrameBrandContent();
			display = vector(brands.begin() + start, brands.begin() + end/*min(end, brands.size())*/);

			for (int i = 0; i < display.size(); ++i) {
				gotoXY(_frameBrand[0].x() + _bullet.length() + 3, _frameBrand[0].y() + i + 1);
				std::wcout << display[i];
			}
			reviewBrand = 0;
		}
		if (reviewLaptop) {
			viewLaptops();
			reviewLaptop = 0;
		}

		if (_kbhit()) {
			keyboard = _getch();

			if ((keyboard == 'w' || keyboard == 'W') && _brandChoice > 0) {
				//remove current _bullet
				gotoXY(_frameBrand[0].x() + _indent, _frameBrand[0].y() + _brandChoice - start + 1);
				std::wcout << L"  ";
				
				_brandChoice--;
				reviewLaptop = 1;
			}
			else if ((keyboard == 's' || keyboard == 'S') && _brandChoice < brands.size() - 1) {
				//remove current _bullet
				gotoXY(_frameBrand[0].x() + _indent, _frameBrand[0].y() + _brandChoice - start + 1);
				std::wcout << L"  ";

				_brandChoice++;
				reviewLaptop = 1;
			}
			else if (keyboard == 't' || keyboard == 'T') {
				wstring newName;
				Laptop laptop;

				cursortype();
				drawFrameEdit(L"Thêm tên hãng:");
				std::getline(wcin, newName); 
				clearFrameEdit(L"Thêm tên hãng:");
				nocursortype();

				//update source of truth
				_catalog->addBrand(newName); 
				_catalog->addLaptop(-1);
				//update brands
				brands.push_back(newName); 

				reviewBrand = 1;
			}
			else if ((keyboard == 'x' || keyboard == 'X') && !brands.empty()) {
				//update source of truth
				_catalog->removeLaptopOfBrand(_brandChoice);
				_catalog->removeBrand(_brandChoice);
				//update brands
				brands.erase(brands.begin() + _brandChoice);
				reviewBrand = reviewLaptop = 1;

				end = min(brands.size(), start + 18);

				if (_brandChoice == brands.size()) {
					--_brandChoice;
					start -= (start > 0 ? 1 : 0);
				}
			}
			else if (keyboard == 'f' || keyboard == 'F') { //sửa thông tin laptop
				wstring newName;
				
				cursortype();
				drawFrameEdit(L"Sửa tên hãng thành:");
				std::getline(wcin, newName); 
				clearFrameEdit(L"Sửa tên hãng thành:");
				nocursortype();

				//redisplay the chosen brand 
				int redispl_x = _frameBrand[0].x() + 2 * _indent + 1,
					redispl_y = _frameBrand[0].y() + _brandChoice + 1;
				gotoXY(redispl_x, redispl_y);
				clearRegion(Point(redispl_x, redispl_y), Point(_frameBrand[1].x() - 1, redispl_y)); //clear that line
				gotoXY(redispl_x, redispl_y);
				std::wcout << newName;

				//update
				_catalog->changeBrand(_brandChoice, newName); //update source of truth
				brands = _catalog->brands(); //update brands
			}
			else if (keyboard == ENTER) {
				char kb = ' ';
				bool drawAllFrames = 0;
				drawInstruction(1);

				while (kb != ESC) {
					if (drawAllFrames || kb == 1) {
						drawFrameTitle(L"DANH MỤC");
						
						clearFrameInstruction(); 
						drawInstruction(1);
						
						drawFrameBrands();
						viewBrands(start, end);

						gotoXY(_frameBrand[0].x() + _indent, _frameBrand[0].y() + _brandChoice - start + 1);
						std::wcout << _bullet;
						
						drawFrameLaptops();
						viewLaptops();
					}
					kb = laptopsProcessing();

					if (kb == ENTER) {
						clrscr();
						singleLaptopProcessing();
						clrscr();
						drawAllFrames = 1;
					}
				}
				if (_laptopChoice > 17) 
					reviewLaptop = 1;
				_laptopChoice = 0; //reset

				clearFrameInstruction(); //clear old instructions (if any)
				drawInstruction(0);
			}
		}
	}
	return keyboard;
}

void DrawCatalog::viewLaptops() {
	vector<Laptop> laptops = _catalog->laptopsOfBrand(_brandChoice);
	clearFrameLaptopsContent();

	if (!laptops.empty()) {
		int n = min(laptops.size(), 18);
		if (n < laptops.size())
			drawButtonDownLaptops();
		else if (laptops.size() < 18)
			clearButtonDownLaptops();

		for (int i = 0; i < n; ++i) {
			gotoXY(_frameLaptop[0].x() + 2 * _indent + 1, _frameLaptop[0].y() + i + 1);
			std::wcout << laptops[i].name();
		}
	}
	else {
		gotoXY(_frameLaptop[0].x() + 2*_indent+1, _frameLaptop[0].y() + 1);
		std::wcout << L"Chưa có laptop nào !";
	}
}

int DrawCatalog::laptopsProcessing() {
	vector<Laptop> laptopsOfBrand =_catalog->laptopsOfBrand(_brandChoice);

	char keyboard = ' ';
	vector<Laptop> display;
	int start = 0;
	int end = min(laptopsOfBrand.size(), 18);
	bool reviewLaptop = 0;

	while (keyboard != ENTER && keyboard != ESC) {
		if (laptopsOfBrand.empty()) {
			gotoXY(_frameLaptop[0].x() + 2*_indent+1, _frameLaptop[0].y() + 1);
			std::wcout << L"Chưa có laptop nào !";
		}

		if (_laptopChoice >= end && !laptopsOfBrand.empty()) {
			end = _laptopChoice + 1;
			start = end - 18;
			reviewLaptop = 1;
		}
		else if (_laptopChoice < start && !laptopsOfBrand.empty()) {
			--start;
			--end;
			reviewLaptop = 1;
		}

		if (_laptopChoice < 0) _laptopChoice = 0;
		gotoXY(_frameLaptop[0].x() + _indent, _frameLaptop[0].y() + _laptopChoice - start + 1);
		std::wcout << _bullet;

		if (end < laptopsOfBrand.size()) drawButtonDownLaptops();
		else clearButtonDownLaptops();
		if (start > 0) drawButtonUpLaptops();
		else clearButtonUpLaptops();

		if (reviewLaptop) {
			clearFrameLaptopsContent();
			display = vector(laptopsOfBrand.begin() + start, laptopsOfBrand.begin() + end);

			for (int i = 0; i < display.size(); ++i) {
				gotoXY(_frameLaptop[0].x() + 2 * _indent + 1, _frameLaptop[0].y() + i + 1);
				std::wcout << display[i].name();
			}
			reviewLaptop = 0;
		}

		if (_kbhit()) {
			keyboard = _getch();

			if (!laptopsOfBrand.empty()) {
				if ((keyboard == 'w' || keyboard == 'W') && _laptopChoice > 0) {
					//remove current _bullet
					gotoXY(_frameLaptop[0].x() + _indent, _frameLaptop[0].y() + _laptopChoice - start + 1);
					std::wcout << L"  ";

					_laptopChoice--;
				}
				else if ((keyboard == 's' || keyboard == 'S') && _laptopChoice < laptopsOfBrand.size() - 1) {
					//remove current _bullet
					gotoXY(_frameLaptop[0].x() + _indent, _frameLaptop[0].y() + _laptopChoice - start + 1);
					std::wcout << L"  ";

					_laptopChoice++;
				}
				else if ((keyboard == 'x' || keyboard == 'X')) {
					//update source of truth
					_catalog->removeLaptop(_brandChoice, _laptopChoice);
					//update laptopsOfBrand
					laptopsOfBrand.erase(laptopsOfBrand.begin() + _laptopChoice);

					reviewLaptop = 1;
					end = min(laptopsOfBrand.size(), 18);

					if (_laptopChoice == laptopsOfBrand.size()) {
						start -= (start > 0 ? 1 : 0);
						_laptopChoice--;
					}
				}
			}
			if (keyboard == 't' || keyboard == 'T') {
				clrscr();
				int x = (consoleWidth - 70) / 2 + 1;
				int y = (consoleHeight - 14) / 2 + 1;
				class Rectangle rec(Point(x, y), Point(x + 69, y + 13));
				rec.draw();
				wstring msg = L"NHẬP THÔNG TIN CƠ BẢN CHO 1 LAPTOP";
				wstring msg1 = L"ĐÃ THÊM LAPTOP !";
				vector<wstring> v = {
					L"Nhập tên laptop: ", L"Nhập CPU: ", L"Nhập RAM (GB): ", L"Nhập cấu hình (inch): ",
					L"Nhập thông tin ổ cứng: ", L"Nhập khối lượng (kg): ", L"Nhập hệ điều hành: ",
					L"Nhập card VGA: ", L"Nhập giá (VND): ", L"Nhập số lượng tồn kho: ",
				};
				Laptop newLaptop;
				wstring tmp;

				gotoXY((consoleWidth - msg.length()) / 2 + 1, y + 1);
				wcout << msg;
				gotoXY(x + _indent, y + 2);
				wcout << L"Hãng (không đổi): " << _catalog->brand(_brandChoice);
				newLaptop.changeSpec(0, _catalog->brand(_brandChoice));

				cursortype();
				for (int i = 0; i < v.size(); ++i) {
					gotoXY(x + _indent, y + i + 3);
					wcout << v[i];
					std::getline(wcin, tmp);
					fflush(stdin);
					newLaptop.changeSpec(i + 1, tmp);
				}
				nocursortype();
				gotoXY((consoleWidth - msg1.length()) / 2 + 1, y + 14);
				wcout << msg1;

				Sleep(1000);

				//update source of truth
				_catalog->addLaptop(_brandChoice, newLaptop);

				clrscr();
				return 1;
			}
			else if (keyboard == ENTER && laptopsOfBrand.empty()) //not allow a brand with no laps to continue using enter
				keyboard = ' ';
		}
	}

	if (keyboard == ESC) {
		gotoXY(_frameLaptop[0].x() + _indent, _frameLaptop[0].y() + _laptopChoice - start + 1);
		std::wcout << L"  ";
		//clearButtonDownLaptops();
		clearButtonUpLaptops();
	}
	return keyboard;
}

void DrawCatalog::clearFrameSpecsContent() {
	clearRegion(Point(_frameLaptopSpecs[0].x() + 1, _frameLaptopSpecs[0].y() + 1),
		Point(_frameLaptopSpecs[1].x() - 1, _frameLaptopSpecs[1].y() - 1));
}

int DrawCatalog::singleLaptopProcessing() {
	Laptop lap = _catalog->laptopsOfBrand(_brandChoice)[_laptopChoice]; //err: &_catalog->laptopsOfBrand(_brandChoice)[_laptopChoice]
	vector<vector<wstring>> specs = lap.toString();

	//kiểm soát khung frame phải expand khi specs.n có nhiều hơn 11 tt
	int n = lap.totalProperties();
	int yEnd = _frameLaptopSpecs[0].y() + n + 1;
	class Rectangle rec(_frameLaptopSpecs[0], Point(_frameLaptopSpecs[1].x(), yEnd));
	rec.draw();
	//-----------
	char keyboard = ' ';
	int choice = 0;
	bool reviewSpecs = 0;
	bool expandFrame = 0;
	bool shrinkFrame = 0;

	drawFrameTitle(L"THÔNG SỐ LAPTOP");
	drawInstruction(2);

	//view laptop specs
	for (int i = 0; i < specs.size(); ++i) {
		gotoXY(_frameLaptopSpecs[0].x() + 2 * _indent + 1, _frameLaptopSpecs[0].y() + i + 1);
		std::wcout << specs[i][0] << L": " << specs[i][1];
	}

	while (keyboard != ESC) { 
		if (expandFrame) {
			//clear the last line
			clearRegion(Point(_frameLaptopSpecs[0].x() + 1, _frameLaptopSpecs[1].y()),
				Point(_frameLaptopSpecs[1].x() - 1, yEnd));

			//expand _frameLaptopSpecs
			yEnd++;
			rec = class Rectangle(_frameLaptopSpecs[0], Point(_frameLaptopSpecs[1].x(), yEnd));
			rec.draw();

			expandFrame = 0;
		}
		else if (shrinkFrame) {
			//clear the last line
			clearRegion(Point(_frameLaptopSpecs[0].x(), _frameLaptopSpecs[1].y()),
				Point(_frameLaptopSpecs[1].x(), yEnd));
			
			yEnd--;
			rec = class Rectangle(_frameLaptopSpecs[0], Point(_frameLaptopSpecs[1].x(), yEnd));
			rec.draw();

			shrinkFrame = 0;
		}

		if (reviewSpecs) {
			clearFrameSpecsContent();

			for (int i = 0; i < specs.size(); ++i) {
				gotoXY(_frameLaptopSpecs[0].x() + 2 * _indent + 1, _frameLaptopSpecs[0].y() + i + 1);
				std::wcout << specs[i][0] << L": " << specs[i][1];
			}
			reviewSpecs = 0;
		}

		gotoXY(_frameLaptopSpecs[0].x() + _indent, _frameLaptopSpecs[0].y() + choice + 1);
		std::wcout << _bullet;

		if (_kbhit()) {
			keyboard = _getch();

			if ((keyboard == 'w' || keyboard == 'W') && choice > 0) {
				//remove current _bullet
				gotoXY(_frameLaptopSpecs[0].x() + _indent, _frameLaptopSpecs[0].y() + choice + 1);
				std::wcout << L"  ";

				choice--;
			}
			else if ((keyboard == 's' || keyboard == 'S') && choice < specs.size() - 1) {
				gotoXY(_frameLaptopSpecs[0].x() + _indent, _frameLaptopSpecs[0].y() + choice + 1);
				std::wcout << L"  ";

				choice++;
			}
			else if (keyboard == 't' || keyboard == 'T') {
				wstring field, input;
				wstring msg = L"THÊM THÔNG TIN";
				
				gotoXY((consoleWidth - msg.length()) / 2 + 1, _frameInstruction[1].y() + 2);
				wcout << msg;
				drawFrameField();
				cursortype();
				std::getline(wcin, field);
				drawFrameInput();
				std::getline(wcin, input);
				clearFrameField();
				clearFrameInput();
				gotoXY((consoleWidth - msg.length()) / 2 + 1, _frameInstruction[1].y() + 2);
				for (int i = 0; i < msg.length(); ++i)
					wcout << L" ";
				nocursortype();

				//update
				lap.addSpec({ field, input });
				specs.push_back({ field, input });
				////update source of truth
				_catalog->setLaptop(_brandChoice, _laptopChoice, lap);

				reviewSpecs = expandFrame = 1;
			}
			else if (keyboard == 'x' || keyboard == 'X') {
				if (choice == 0) {
					wstring msg = L"KHÔNG THỂ XÓA HÃNG SẢN XUẤT !";
					gotoXY((consoleWidth - msg.length()) / 2 + 1, _frameLaptopSpecs[0].y() - 1);
					wcout << msg;
					Sleep(1000);
					gotoXY((consoleWidth - msg.length()) / 2 + 1, _frameLaptopSpecs[0].y() - 1);
					for (int i = 0; i < msg.length(); ++i)
						wcout << L" ";
				}
				else {
					//update laptop
					lap.changeSpec(choice, L"");
					//update source of truth
					_catalog->setLaptop(_brandChoice, _laptopChoice, lap);
					//update specs
					if (0 <= choice && choice <= 10)
						specs[choice][1] = L"";
					else {
						specs.erase(specs.begin() + choice);
						--choice;
						shrinkFrame = 1;
					}

					reviewSpecs = 1;
				}
			}
			else if (keyboard == 'f' || keyboard == 'F') { //sửa thông tin laptop
				if (choice == 0) {
					wstring msg = L"KHÔNG THỂ SỬA HÃNG SẢN XUẤT !";
					gotoXY((consoleWidth - msg.length()) / 2 + 1, _frameLaptopSpecs[0].y() - 1);
					wcout << msg;
					Sleep(1000);
					gotoXY((consoleWidth - msg.length()) / 2 + 1, _frameLaptopSpecs[0].y() - 1);
					for (int i = 0; i < msg.length(); ++i)
						wcout << L" ";
				}
				else {
					wstring message = L"Sửa " + specs[choice][0] + L" thành:";
					int startX = (consoleWidth - (message.length() + 53)) / 2 + 1;
					int startY = (consoleHeight - (_frameLaptopSpecs[0].y() - _frameInstruction[1].y())) / 2 + 1;
					wstring newInfo;

					cursortype();
					drawFrameEdit(message, Point(startX, startY), Point(startX + message.length() + 53, startY + 2));
					std::getline(wcin, newInfo);
					clearRegion(Point(startX, startY), Point(startX + message.length() + 53, startY + 2));
					nocursortype();

					//redisplay the chosen brand 
					int redispl_x = _frameLaptopSpecs[0].x() + 4 + specs[choice][0].length() + 3,
						redipl_y = _frameLaptopSpecs[0].y() + choice + 1;
					gotoXY(redispl_x, redipl_y);
					clearRegion(Point(redispl_x, redipl_y), Point(_frameLaptopSpecs[1].x() - 1, redipl_y)); //clear that line
					gotoXY(redispl_x, redipl_y);
					std::wcout << newInfo;

					//update laptop
					lap.changeSpec(choice, newInfo);
					//update source of truth
					_catalog->setLaptop(_brandChoice, _laptopChoice, lap);
					//update specs
					specs[choice][1] = newInfo;
				}
			}
		}
	}
	return keyboard; 
}

void DrawCatalog::drawFrameField() {
	drawFrameEdit(L"Trường:   ", _frameField[0], _frameField[1]);
}

void DrawCatalog::drawFrameInput() {
	drawFrameEdit(L"Thông tin:", _frameInput[0], _frameInput[1]);
}

void DrawCatalog::clearFrameField() {
	clearRegion(_frameField[0], _frameField[1]);
}

void DrawCatalog::clearFrameInput() {
	clearRegion(_frameInput[0], _frameInput[1]);
}