/*
 Написать программу, которая будет считывать данные студентов из файла ( Фамилия оценка за контрольную, оценки за
 домашнее задание) и выводить в два отдельных файла людей, которые получили и не получили проходной балл (25% оценки
 считается по контрольной(первая оценка после фамилии), остальное на основе среднего арифметического/медианы  домашних
 заданий). Предоставить возможность сортировки учащихся по алфавиту и по их баллам. Каждую группу вывести в отдельный
 файл.

Использовать struck и вектора.

До кодревью заливать в тестовую ветку.

пример файла

Иванов 5 5 5 5 5 5 5 5 5
Петров 3 5 5 5 5 5 5 0 5
Сидоров 5 0 0 0 0 0 0 0 0
 */

/*
 view is such a Vector that if view[0]=3;view[1]=12;
 then students[3] will be printed first.Then students[12] will be printed

 */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


#define IN_FILE_NAME "input.txt"
#define OUT_P_FILE_NAME "passed.txt"
#define OUT_NP_FILE_NAME "not_passed.txt"

#define PASSING_SCORE 3


enum class SortBy {
	name, score
};
enum class SortOrder {
	ascending, descending
};

typedef std::ifstream InFile;
typedef std::ofstream OutFile;
typedef std::string String;
template<typename T> using Vector=std::vector<T>;


struct Student {
	String name;
	Vector<int> scores;
	float score;
};

void readAndCalcScore(InFile &iFile, Vector<Student> &students) {
	String tmpName;
	int tmpScore;
	while (iFile >> tmpName) {
		students.push_back({tmpName, Vector<int>(), 0.0});
		while (iFile >> tmpScore) {
			(students.back().scores).push_back(tmpScore);
		}
		for (int s:students.back().scores) students.back().score += s;
		students.back().score /= students.back().scores.size();
//		iFile.ignore();
		std::cin.clear();
	}
}


#define SORTBY(field)\
if(sortBy==SortBy::field){\
if(order==SortOrder::ascending){\
std::sort(students.begin(),students.end(),[](const Student &a, const Student &b){\
return a.field>b.field;\
});\
}\
if(order==SortOrder::descending) {\
std::sort(students.begin(),students.end(),[](const Student &a, const Student &b){\
return a.field<b.field;\
});\
}\
}

void inline sort(Vector<Student> &students, Vector<int> &view, const SortBy &sortBy, const SortOrder &order) {
	SORTBY(name)
	SORTBY(score)
}

//Split students into passed (on the left to returned iterator)
// and not-passed (on the right to returned iterator) based on passingScore
//
Vector<Student>::iterator split(const Vector<Student> &students, const float passingScore) {

}

//NOT ALLOWED:, а жаль(
//void inline print(const Vector<Student> &students, OutFile &oFile, const auto &begin = students.begin(),
//				  const auto &end = students.end()) {
void inline print(const Vector<Student> &students, OutFile &oFile, Vector<Student>::const_iterator begin,
				  Vector<Student>::const_iterator end) {
	for (auto i = begin; i != end; i++) {
		oFile << i->name;
		oFile << " | " << i->score << " |";
		for (auto score:i->scores) oFile << " " << score;
		oFile << std::endl;
	}
}

void inline print(const Vector<Student> &students, OutFile &oFile) {
	print(students, oFile, students.begin(), students.end());
}

int main() {
	InFile iFile(IN_FILE_NAME);
	OutFile oPFile(OUT_P_FILE_NAME);
	OutFile oNPFile(OUT_NP_FILE_NAME);
	Vector<Student> students;
	readAndCalcScore(iFile, students);
	print(students, oPFile);
	return 0;
}

