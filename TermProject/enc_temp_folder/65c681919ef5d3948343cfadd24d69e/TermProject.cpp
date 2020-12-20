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
	//consoleMsg�� ����
	void setConsoleMsg(string msg) {
		this->consoleMsg = msg;
	}
	//������ consolemsg�� �ҷ���
	string getConsoleMsg() {
		this->consoleMsg;
	}
	//file�� �̸����� file�� ������
	void setFile(string filename) {
		this->filename = filename;
	}
	//��µ� page�� startline�� ������
	int getStartLine() {
		return this->startLine;
	}
	void setStartLine(int line) {
		this->startLine = line;
	}
	//���� page�� startline
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

	//line ������ buffer�� ����
	vector<string> fileToLine() {
		buffer = {};
		
		ifstream file;
		file.open(filename);
		
		//file�� �������ʾ������� ��¹�
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
			cBuffer = ""; //75���� ������ �������� cBuffer
			charNum = 0;

			//��¹��� ���ΰ� 75byte�̹Ƿ� <=75
			//������ �������ʰ� word�� ����Ǵ��߿� 75�� ������ �������� �Ѱ��ش�.
			while (charNum <=75) {
				file.get(c);
				
				//������ �������� ����� word�� cBuffer�� �־��ְ� word����ֱ�
				if (c == ' ') {
					cBuffer = cBuffer + word;
					cBuffer = cBuffer + c;
					word = "";
				}

				//file�� ������ �����ִ� word���� �� ����
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
			//buffer vector�� push
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
			
			//buffer�� ���� �����Ҷ� ���
			if (LineIndex < buffer.size()) {
				cout << lineNum << "|" << buffer[LineIndex] << endl;
				
			}
			//buffer�� ������� ��츦 ����� ����·� ���
			else {
				cout << lineNum << "|" << endl;
			}
			lineNum++;
		}

		string input;
		cout << "---------------------------------------------------------------------------------------------------------" << endl;
		cout << "n:����������, p:����������, i:����, d:����, c:����, s:ã��, t:����������" << endl;
		cout << "---------------------------------------------------------------------------------------------------------" << endl;
		cout << "(�ָܼ޽���) " << consoleMsg << endl;
		cout << "---------------------------------------------------------------------------------------------------------" << endl;
		cout << "�Է�:";
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
				
				//���ڷ� �޾����� �͵��� vector�� �־� �����ش�.
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

	//n�� �Է��ؼ� ���������� ����ϱ�
	void nCommand() {
		//���� page�� ���� line�� buffer index
		int curStartLine = output->getcurStartLine();
		//���� page�� ������ �Ǿ���� line�� index
		int startLine = output->getStartLine();

		//���� �������� ���� ���
		if ((curStartLine + 20) > (output->getFileBuffer().size())) {
			output->setConsoleMsg("There is no next page.");
		}
		else {
			int nextpageStartLine = curStartLine + 20;
			output->setcurStartLine(nextpageStartLine);
		}
	}

	//p�� �Է��ؼ� ���������� ����ϱ�
	void pCommand() {
		int curStartLine = output->getcurStartLine();
		int startLine = output->getStartLine();

		//�̹� ù�������� ��� 
		if (curStartLine == 0) {
			output->setConsoleMsg("This is the first page!");
			return;
		}
		//������������ ���� ���
		if ((curStartLine - 20) <0) {
			output->setConsoleMsg("There is no previous page.");
		}
		else {
			int previouspageStartLine = curStartLine - 20;
			output->setcurStartLine(previouspageStartLine);
		}
	}

	void iCommand(vector<string> vFactor){
		//���� : ���ڰ� 3�� �� �޾����� �ʾ�����
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
		
		//���ٿ� 75byte�� ������ ����
		if (addWord.size() > 75) {
			output->setConsoleMsg("Please follow the format!");
			return;
		}

		//���� : line�� ������ ���������� 
		if(!(0<=lineNum<=20)){
			output->setConsoleMsg("Please follow the format!");
			return;
		}
		string findLine = buffer[lineNum-1];
		int count = 0;
		//�ڸ� ã���� addWord�� �߰����ְ� break
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
		//�ٵ��Ҵµ��� �ִ°��� ã���������� = wordNum�� ��������
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

		//���� : line�� ������ ���������� 
		if (!(0 <= lineNum <= 20)) {
			output->setConsoleMsg("Please follow the format!");
			return;
		}
		string findLine = buffer[lineNum - 1];
		int count = 0;
		int deleteIndex;
		int deleteIndex2;
		//�ڸ� ã���� addWord�� �߰����ְ� break
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
		//�ٵ��Ҵµ��� �ִ°��� ã���������� = wordNum�� ��������
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