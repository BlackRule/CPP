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

using InFile=std::ifstream;
using OutFile=std::ofstream;
using String=std::string;
template<typename T> using Vector=std::vector<T>;


void readAndCalcScore(InFile &iFile, Vector<Student> &students) {
	String tmpName;
	int tmpScore;
	while (iFile >> tmpName) {
		students.emplace_back(Student{tmpName, Vector(), 0.0});
		while (iFile >> tmpScore) {
			(students.end()->scores).push_back(tmpScore);
		}
		for (int s:students.end()->scores) students.end()->score += s;
		students.end()->score /= students.end()->scores.size();
	}
}


void qsortView(const Vector<Student> &vec, Vector<int> &view, int a, int b,
			   int (*cmp)(const Student &a, const Student &b)) {
	int l = a, r = b, m, tmp;
	//m=random[a;b]
	srand((unsigned) time(NULL));
	m = (rand() % (b - a)) + a;
	do {
		while (cmp(vec[view[l]], vec[view[m]]) < 0) l++;
		while (cmp(vec[view[r]], vec[view[m]]) > 0) r--;
		if (l <= r) {
			if (cmp(vec[view[l]], vec[view[r]]) > 0) std::swap(view[l], view[r]);
			l++;
			r--;
		}
	} while (l <= r);
	if (l < b)
		qsortView(vec, view, l, b, cmp);
	if (a < r)
		qsortView(vec, view, a, r, cmp);
}

#define COMPARATOR(field, Field)\
int comaparatorAscending ## Field(const Student &a, const Student &b) {\
if (a.field == b.field) return 0;\
if (a.field > b.field) return 1;\
else return -1;\
}\
\
int comaparatorDescending ## Field(const Student &a, const Student &b) {\
    return -comaparatorAscending ## Field(a, b);\
}\


COMPARATOR(name, Name)

COMPARATOR(score, Score)

enum class SortBy {
	name, score
};
enum class SortOrder {
	ascending, descending
};


#define SORTBY(field, Field)\
if(sortBy==SortBy::field){\
if(order==SortOrder::ascending) qsortView(students, view, 0, view.size(), comaparatorAscending##Field);\
if(order==SortOrder::descending) qsortView(students, view, 0, view.size(), comaparatorDescending##Field);\
}

void inline sort(const Vector<Student> &students, Vector<int> &view, const SortBy &sortBy, const SortOrder &order) {
	SORTBY(name, Name)
	SORTBY(score, Score)
}

//Split ascendingScoreView of students to notPassedView and PassedView based on passingScore
//(ascendingScoreView is a view of students sorted by score in ascending order)
void split(const Vector<Student> &students, const Vector<int> &ascendingScoreView,
		   Vector<int> &notPassedView, Vector<int> &PassedView, const float passingScore) {

}

void inline print(const Vector<Student> &students, const Vector<int> &view, OutFile &oFile) {
	for (auto i:view) {
		oFile << students[i].name;
		oFile << " | " << students[i].score << " |";
		for (auto score:students[i].scores) oFile << " " << score;
		oFile << std::endl;
	}
}

int main() {
	InFile iFile(IN_FILE_NAME);
	OutFile oPFile(OUT_P_FILE_NAME);
	OutFile oNPFile(OUT_NP_FILE_NAME);
	Vector<String> studentsNames;
	Vector<Vector<int> > studentsScoreVectors;
	Vector<Vector<float> > studentsScores;

	readAndCalcScore(iFile, students);

	return 0;
}

