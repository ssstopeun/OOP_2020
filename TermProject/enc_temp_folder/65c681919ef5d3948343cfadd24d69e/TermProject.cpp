#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

class ScreenOutput {
private:
	static ScreenOutput* instances;
	vector<string> buffer;
	string consoleMsg = "";
	string filename;
	int startLine;
	int curStartLine;
	
	ScreenOutput() {
		consoleMsg = "";
	}

public:
	vector<string> getFileBuffer() {
		return this->buffer;
	}
	void setFileBuffer(vector<string> buf) {
		this->buffer = buf;
	}
	//consoleMsg를 설정
	void setConsoleMsg(string msg) {
		this->consoleMsg = msg;
	}
	//설정된 consolemsg를 불러옴
	string getConsoleMsg() {
		this->consoleMsg;
	}
	//file의 이름으로 file을 정해줌
	void setFile(string filename) {
		this->filename = filename;
	}
	//출력될 page의 startline을 가져옴
	int getStartLine() {
		return this->startLine;
	}
	void setStartLine(int line) {
		this->startLine = line;
	}
	//현재 page의 startline
	int getcurStartLine() {
		return this->curStartLine;
	}
	void setcurStartLine(int line) {
		this->curStartLine = line;
	}


	
	
	static ScreenOutput* instance() {
		if (!instances)
			instances = new ScreenOutput;
		return instances;
	}

	void rewriteFile() {
		ofstream outStream;
		outStream.open(filename,ios::out);
		if (outStream.fail()) {
			cout << "file openning failed" << endl;
			exit(1);
		}
		int size = 0;
		while (size < buffer.size()) {
			outStream<<buffer.at(size);
			size++;
		}
		outStream.close();
	}

	//line 단위로 buffer에 저장
	vector<string> fileToLine() {
		buffer = {};
		
		ifstream file;
		file.open(filename);
		
		//file이 열리지않았을때의 출력문
		if (file.fail()) {
			cout << "file openning failed" << endl;
			exit(1);
		}
		
		string cBuffer = "";
		string word = "";
		int charNum = 0;
		int lineNum = 0;
		char c;

		while (!file.eof()) {
			cBuffer = ""; //75이하 단위로 저장해줄 cBuffer
			charNum = 0;

			//출력문의 세로가 75byte이므로 <=75
			//공백을 만나지않고 word가 저장되던중에 75가 넘으면 다음으로 넘겨준다.
			while (charNum <=75) {
				file.get(c);
				
				//공백을 만났을땐 저장된 word를 cBuffer에 넣어주고 word비워주기
				if (c == ' ') {
					cBuffer = cBuffer + word;
					cBuffer = cBuffer + c;
					word = "";
				}

				//file이 끝나고도 남아있는 word저장 후 종료
				if (!word.empty() && file.eof()) {
					cBuffer = cBuffer + word;
					word = "";
					break;
				}
				
				else {
					word = word + c;
				}
				charNum++;
			}
			//buffer vector에 push
			buffer.push_back(cBuffer);

		}
		file.close();
		return buffer;
	}
	string printScreen() {
		this->setStartLine(curStartLine);
		int lineNum = 1;
		while (lineNum <= 20) {
			int LineIndex = curStartLine + lineNum - 1;
			
			//buffer에 글이 존재할때 출력
			if (LineIndex < buffer.size()) {
				cout << lineNum << "|" << buffer[LineIndex] << endl;
				
			}
			//buffer가 비어있을 경우를 대비해 빈상태로 출력
			else {
				cout << lineNum << "|" << endl;
			}
			lineNum++;
		}

		string input;
		cout << "---------------------------------------------------------------------------------------------------------" << endl;
		cout << "n:다음페이지, p:이전페이지, i:삽입, d:삭제, c:변경, s:찾기, t:저장후종료" << endl;
		cout << "---------------------------------------------------------------------------------------------------------" << endl;
		cout << "(콘솔메시지) " << consoleMsg << endl;
		cout << "---------------------------------------------------------------------------------------------------------" << endl;
		cout << "입력:";
		cin >> input;
		cout << "---------------------------------------------------------------------------------------------------------" << endl;
		return input;
	}
};

ScreenOutput* ScreenOutput::instances = 0;

class Remote {
private:
	string file;
	ScreenOutput* output;
	vector<string> buffer;

public:
	Remote(string file) {
		this->file = file;
		output = ScreenOutput::instance();
		output->setFile(file);
		buffer = output->fileToLine();
	}

	void power() {
		while (true) {
			string input = str();

			string command;
			command = input.substr(0, 1);
			if (command == "n") { nCommand(); }
			else if (command == "p") { pCommand(); }
			else if (command == "t") { tCommand(); }
			else if (command == "i" || command == "d" || command == "s" || command == "c") {
				
				//인자로 받아지는 것들을 vector에 넣어 보내준다.
				string factor = input.substr(2, input.size() - 3);
				istringstream s(factor);
				string stringbuffer;
				vector<string> vFactor;
				while (getline(s, stringbuffer, ',')) {
					vFactor.push_back(stringbuffer);
				}


				if ((input.substr(1, 1) != "(") || (input.substr(input.size() - 1, 1) != ")")) {
					output->setConsoleMsg("Please follow the format!");
				}
				if (command == "i") { iCommand(vFactor); }
				if (command == "d") { dCommand(vFactor); }
			}
		}
		
	}
	string str() {
		buffer = output->getFileBuffer();
		string input = output->printScreen();
		output->setConsoleMsg("");
		return input;
	}

	//n을 입력해서 다음페이지 출력하기
	void nCommand() {
		//현재 page의 시작 line의 buffer index
		int curStartLine = output->getcurStartLine();
		//다음 page의 시작이 되어야할 line의 index
		int startLine = output->getStartLine();

		//다음 페이지가 없는 경우
		if ((curStartLine + 20) > (output->getFileBuffer().size())) {
			output->setConsoleMsg("There is no next page.");
		}
		else {
			int nextpageStartLine = curStartLine + 20;
			output->setcurStartLine(nextpageStartLine);
		}
	}

	//p를 입력해서 이전페이지 출력하기
	void pCommand() {
		int curStartLine = output->getcurStartLine();
		int startLine = output->getStartLine();

		//이미 첫페이지인 경우 
		if (curStartLine == 0) {
			output->setConsoleMsg("This is the first page!");
			return;
		}
		//이전페이지가 없는 경우
		if ((curStartLine - 20) <0) {
			output->setConsoleMsg("There is no previous page.");
		}
		else {
			int previouspageStartLine = curStartLine - 20;
			output->setcurStartLine(previouspageStartLine);
		}
	}

	void iCommand(vector<string> vFactor){
		//예외 : 인자가 3개 다 받아지지 않았을때
		if (3 < vFactor.size()) {
			output->setConsoleMsg("Please follow the format!");
			return;
		}
		int lineNum;
		int wordNum;
		std::stringstream x(vFactor[0]);
		x >> lineNum;
		std::stringstream y(vFactor[1]);
		y >> wordNum;
		string addWord = vFactor[2];
		
		//한줄에 75byte가 넘으면 오류
		if (addWord.size() > 75) {
			output->setConsoleMsg("Please follow the format!");
			return;
		}

		//예외 : line이 범위에 맞지않을때 
		if(!(0<=lineNum<=20)){
			output->setConsoleMsg("Please follow the format!");
			return;
		}
		string findLine = buffer[lineNum-1];
		int count = 0;
		//자리 찾으면 addWord를 추가해주고 break
		for (int i = 0; i < findLine.size(); i++) {
			if (findLine[i] == ' ') {
				count++;
			}
			if (count == wordNum+1) {
				findLine = findLine.insert(i+1, addWord + " ");
				buffer[lineNum-1] =findLine;
				break;
			}
		}
		//다돌았는데도 넣는곳을 찾지못했을때 = wordNum의 범위오류
		if (count >= 75) {
			output->setConsoleMsg("Please follow the format!");
			return;
		}
		
		output->setFileBuffer(buffer);
		output->rewriteFile();
	}
	void dCommand(vector<string> vFactor){
		if (2 < vFactor.size()) {
			output->setConsoleMsg("Please follow the format!");
			return;
		}
		int lineNum;
		int wordNum;
		std::stringstream x(vFactor[0]);
		x >> lineNum;
		std::stringstream y(vFactor[1]);
		y >> wordNum;

		//예외 : line이 범위에 맞지않을때 
		if (!(0 <= lineNum <= 20)) {
			output->setConsoleMsg("Please follow the format!");
			return;
		}
		string findLine = buffer[lineNum - 1];
		int count = 0;
		int deleteIndex;
		int deleteIndex2;
		//자리 찾으면 addWord를 추가해주고 break
		for (int i = 0; i < findLine.size(); i++) {
			if (findLine[i] == ' ') {
				count++;
			}
			if (count == wordNum) {
				deleteIndex = i;
				count++;
			}
			if (count == wordNum+2) {
				deleteIndex2 = i;
				break;
			}
		}
		//다돌았는데도 넣는곳을 찾지못했을때 = wordNum의 범위오류
		if (count >= 75) {
			output->setConsoleMsg("Please follow the format!");
			return;
		}
		findLine.erase(deleteIndex, deleteIndex2 - deleteIndex-2);
		buffer[lineNum - 1] = findLine;

		output->setFileBuffer(buffer);
		output->rewriteFile();
	}
	void tCommand() {
		output->rewriteFile();
		exit(0);
	}

};

int main() {
	string file = "C:\\Users\\User\\Desktop\\test.txt";
	Remote remote(file);
	remote.power();
}