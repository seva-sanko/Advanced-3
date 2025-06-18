// Контейнеры STL: 
//deque, stack, queue, priority_queue
//set, multiset, map, multimap
//Итераторы. Стандартные алгоритмы. Предикаты.

#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <algorithm>
#include <iterator>
#include <deque>
#include "MyString.h"
#include "Func.cpp"
#include "Rect.h"


using namespace std;
#define	  stop __asm nop

bool Pred1_1(const Point& point) {
	int n = 2; // допустимое отклонение для координаты 
	int m = 3;  
	return (point.getX() >= -n && point.getX() <= n) && (point.getY() >= -m && point.getY() <= m);
}

void toLowercase(std::string& str) {
	std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
		return std::tolower(c);
		});
}

int main()
{
	setlocale(LC_ALL, "rus");
	//Очередь с двумя концами - контейнер deque
	// 
	//Создайте пустой deque с элементами типа Point. С помощью
	//assign заполните deque копиями элементов вектора. С помощью
	//разработанного Вами в предыдущем задании универсального шаблона
	//выведите значения элементов на печать
	std::deque<Point> pointDeque;

	std::vector<Point> pointVector = { Point(1, 2), Point(3, 4), Point(5, 6) };
	pointDeque.assign(pointVector.begin(), pointVector.end());

	std::cout << "Point deque: ";
	PrintDeque(pointDeque);


	//Создайте deque с элементами типа MyString. Заполните его значениями
	//с помощью push_back(), push_front(), insert()
	//С помощью erase удалите из deque все элементы, в которых строчки
	//начинаются с 'A' или 'a'

	std::deque<MyString> stringDeque;

	stringDeque.push_back(MyString("whoo"));
	stringDeque.push_front(MyString("files"));
	stringDeque.insert(stringDeque.begin() + 1, MyString("aligator"));

	std::cout << "String deque before erasing: ";
	PrintDeque(stringDeque);

	auto it = std::remove_if(stringDeque.begin(), stringDeque.end(), [](const MyString& str) {
		const char* s = str.GetString();
		return (s[0] == 'A' || s[0] == 'a');
	});
	stringDeque.erase(it, stringDeque.end());

	std::cout << "String deque after erasing: ";
	PrintDeque(stringDeque);


	////////////////////////////////////////////////////////////////////////////////////


	//Напишите шаблон функции для вывода значений stack, queue, priority_queue
	//Подумайте, как "получать" данное "с верхушки"?
	//Что происходит с контейнерами после вывода значений?

	std::stack<int> intStack;
	intStack.push(1);
	intStack.push(2);
	intStack.push(3);

	std::cout << "Stack: ";
	PrintStack(intStack);

	std::queue<double> doubleQueue;
	doubleQueue.push(1.1);
	doubleQueue.push(2.2);
	doubleQueue.push(3.3);

	std::cout << "Queue: ";
	PrintQueue(doubleQueue);

	std::priority_queue<char> charPriorityQueue;
	charPriorityQueue.push('b');
	charPriorityQueue.push('a');
	charPriorityQueue.push('c');

	std::cout << "Priority Queue: ";
	PrintPriorityQueue(charPriorityQueue);


	////////////////////////////////////////////////////////////////////////////////////
	//stack

	//Создайте стек таким образом, чтобы
	//а) элементы стека стали копиями элементов вектора
	//б) при выводе значений как вектора, так и стека порядок значений был одинаковым 

	std::vector<int> vec = { 1, 2, 3, 4, 5 };
	std::stack<int> intStack2(std::deque<int>(vec.begin(), vec.end()));

	std::cout << "Vector: ";
	for (const auto& elem : vec) {
		std::cout << elem << " ";
	}
	std::cout << std::endl;

	std::cout << "Stack: ";
	PrintStack(intStack2);


	//Сравнение и копирование стеков
	//а) создайте стек и любым способом задайте значения элементов
	//б) создайте новый стек таким образом, чтобы он стал копией первого
	//в) сравните стеки на равенство
	//г) модифицируйте любой из стеком любым образом (push, pop, top)
	//д) проверьте, какой из стеков больше (подумайте, какой смысл вкладывается в такое сравнение)
	{
		std::stack<int> stack1;
		stack1.push(1);
		stack1.push(2);
		stack1.push(3);

		std::stack<int> stack2 = stack1;

		bool equal = (stack1 == stack2);
		std::cout << "Stacks are equal: " << std::boolalpha << equal << std::endl;

		stack1.push(4);
		stack1.pop(); // Удаляем верхний элемен

		if (stack1.size() > stack2.size()) {
			std::cout << "Stack 1 is bigger." << std::endl;
		}
		else if (stack1.size() < stack2.size()) {
			std::cout << "Stack 2 is bigger." << std::endl;
		}
		else {
			std::cout << "Stacks are of equal size." << std::endl;
		}

		//stop

	}


	////////////////////////////////////////////////////////////////////////////////////
	//queue

	//Создайте очередь, которая содержит указатели на объекты типа Point,
	//при этом явно задайте базовый контейнер.
	//Измените значения первого и последнего элементов посредством front() и back()
	//Подумайте, что требуется сделать при уничтожении такой очереди?
	{
		std::deque<Point*> pointQueue;

		Point* p1 = new Point(1, 1);
		Point* p2 = new Point(2, 2);
		Point* p3 = new Point(3, 3);
		pointQueue.push_back(p1);
		pointQueue.push_back(p2);
		pointQueue.push_back(p3);

		pointQueue.front()->setX(10);
		pointQueue.back()->setY(20);

		std::cout << "First point: (" << pointQueue.front()->getX() << ", " << pointQueue.front()->getY() << ")" << std::endl;
		std::cout << "Last point: (" << pointQueue.back()->getX() << ", " << pointQueue.back()->getY() << ")" << std::endl;

		for (auto ptr : pointQueue) {
			delete ptr;
		}

	}
	////////////////////////////////////////////////////////////////////////////////////
	//priority_queue
	//а) создайте очередь с приоритетами, которая будет хранить адреса строковых литералов - const char*
	//б) проинициализируйте очередь при создании с помощью вспомогательного массива с элементами const char*
	//в) проверьте "упорядоченность" значений (с помощью pop() ) - если они оказываются не упорядоченными, подумайте:
	//		что сравнивается при вставке?


	{
		const char* strArray[] = { "apple", "banana", "orange", "grape", "pear" };

		std::priority_queue<const char*> stringPriorityQueue;

		for (const auto& str : strArray) {
			stringPriorityQueue.push(str);
		}

		while (!stringPriorityQueue.empty()) {
			std::cout << stringPriorityQueue.top() << std::endl;
			stringPriorityQueue.pop();
		}
		/*Если элементы в приоритетной очереди оказываются не упорядоченными, это может быть вызвано неправильным порядком сравнения при вставке элементов.
		При вставке элементов в приоритетную очередь с помощью push(), стандартный шаблон std::priority_queue использует функциональный объект по умолчанию
		std::less<T>, который сравнивает элементы в порядке возрастания. Однако, в данном случае, элементы являются указателями на строки(const char*),
		и сравнение будет происходить между адресами строковых литералов, а не самих строк. Таким образом, при вставке элементов в приоритетную очередь,
		адреса строковых литералов будут сравниваться, а не их содержимое. Если строковые литералы размещены в памяти в неупорядоченном порядке, то и
		при вставке в приоритетную очередь они будут располагаться в неупорядоченном порядке.*/
		//stop
	}


	////////////////////////////////////////////////////////////////////////////////////
	//set
	//a) создайте множество с элементами типа Point - подумайте, что необходимо определить
	//		в классе Point (и каким образом)
	//б) распечатайте значения элементов с помощью шаблона, реализованного в предыдущей лаб. работе
	//в) попробуйте изменить любое значение...
	//г) Создайте два множества, которые будут содержать одинаковые значения
	//		типа int, но занесенные в разном порядке
	//д) Вставьте в любое множество диапазон элементов из любого другого
	//	контейнера, например, элементов массива	(что происходит, если в массиве имеются дубли?)

	std::set<Point> pointSet;

	std::cout << "Elements of pointSet:" << std::endl;
	PrintContainer(pointSet);

	//if (!pointSet.empty()) {
	//	auto it = pointSet.begin();
	//	it->getX() = 10; // Не компилируется, т.к. метод getX() возвращает константное значение
	//}

	std::set<int> set1 = { 1, 4, 3, 2, 5 };
	std::set<int> set2 = { 3, 5, 1, 4, 2 };

	std::cout << "Elements of set1:" << std::endl;
	for (const auto& elem : set1) {
		std::cout << elem << " ";
	}
	std::cout << std::endl;

	std::cout << "Elements of set2:" << std::endl;
	for (const auto& elem : set2) {
		std::cout << elem << " ";
	}
	std::cout << std::endl;

	//  (вставка может не произойти, если элементы уже существуют в множестве)
	int arr[] = { 1, 2, 3, 4, 5, 1, 2, 6 }; // массив с дубликатами
	set1.insert(std::begin(arr), std::end(arr));

	std::cout << "Elements of set1 after insertion:" << std::endl;
	for (const auto& elem : set1) {
		std::cout << elem << " ";
	}
	std::cout << std::endl;


	////////////////////////////////////////////////////////////////////////////////////
	//multiset




	////////////////////////////////////////////////////////////////////////////////////
	//map	
	//а) создайте map, который хранит пары "фамилия, зарплата" - pair<const char*, int>,
	//	при этом строки задаются строковыми литералами
	//б) заполните контейнер значениями посредством operator[] и insert()
	//в) распечатайте содержимое

	//е) замените один из КЛЮЧЕЙ на новый (была "Иванова", вышла замуж => стала "Петрова")

	{
		std::map<const char*, int> salaryMap;

		// заполняем посредством operator[] и insert()
		salaryMap["Иванова"] = 50000;  // используем operator[]
		salaryMap.insert(std::make_pair("Петров", 60000));
		salaryMap.insert(std::make_pair("Сидорова", 70000));
		salaryMap["Козлова"] = 55000;

		std::cout << "Содержимое map:" << std::endl;
		for (const auto& pair : salaryMap) {
			std::cout << pair.first << ": " << pair.second << std::endl;
		}

		// Поскольку ключи хранятся как const char*, нам нужно удалить и вставить новую пару
		const char* oldKey = "Иванова";
		const char* newKey = "Петрова";
		auto it = salaryMap.find(oldKey);
		if (it != salaryMap.end()) {
			int salary = it->second;
			salaryMap.erase(it); // Удаляем старую пару
			salaryMap[newKey] = salary; // Вставляем новую пару с новым ключом
		}

		// вновь распечатываем содержимое после замены ключа
		std::cout << "\nСодержимое map после замены ключа:" << std::endl;
		for (const auto& pair : salaryMap) {
			std::cout << pair.first << ": " << pair.second << std::endl;
		}
	}


	////////////////////////////////////////////////////////////////////////////////////
	//multimap
	//а) создайте "англо-русский" словарь, где одному и тому же ключу будут соответствовать
	//		несколько русских значений - pair<string,string>, например: strange: чужой, странный...
	//б) Заполните словарь парами с помощью метода insert или проинициализируйте с помощью 
	//		вспомогательного массива пара (пары можно конструировать или создавать с помощью шаблона make_pair)
	//в) Выведите все содержимое словаря на экран
	//г) Выведите на экран только варианты "переводов" для заданного ключа. Подсказка: для нахождения диапазона
	//		итераторов можно использовать методы lower_bound() и upper_bound()

	{
		std::map<std::string, std::string> dictionary;


		dictionary.insert(std::make_pair("C++", "много кода"));
		dictionary.insert(std::make_pair("alphabet", "алфавит"));
		dictionary.insert(std::make_pair("book", "книга"));
		dictionary.insert(std::make_pair("cat", "кот"));
		dictionary.insert(std::make_pair("dog", "собака"));
		// std::pair<std::string, std::string> words[] = {
		//     {"strange", "чужой, странный"},
		//     {"apple", "яблоко"},
		//     {"book", "книга"},
		//     {"cat", "кот"},
		//     {"dog", "собака"}
		// };
		// dictionary.insert(std::begin(words), std::end(words));

		std::cout << std::endl << "Содержимое словаря:" << std::endl;
		for (const auto& pair : dictionary) {
			std::cout << pair.first << ": " << pair.second << std::endl;
		}

		std::string key = "C++";
		auto lower = dictionary.lower_bound(key);
		auto upper = dictionary.upper_bound(key);
		std::cout << "\nПереводы для ключа \"" << key << "\":" << std::endl;
		for (auto it = lower; it != upper; ++it) {
			std::cout << it->second << std::endl;
		}
	}
	///////////////////////////////////////////////////////////////////

		//Итераторы

		//Реверсивные итераторы. Сформируйте set<Point>. Подумайте, что
		//нужно перегрузить в классе Point. Создайте вектор, элементы которого 
		//являются копиями элементов set, но упорядочены по убыванию
	std::set<Point> pointSetIt = { {1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10} };

	std::vector<Point> reversedVector;
	std::reverse_copy(pointSetIt.begin(), pointSetIt.end(), std::back_inserter(reversedVector));

	std::cout << "Элементы вектора в убывающем порядке:" << std::endl;
	for (const auto& point : reversedVector) {
		std::cout << "(" << point.getX() << ", " << point.getY() << ")" << std::endl;
	}


	//Потоковые итераторы. С помощью ostream_iterator выведите содержимое
	//vector и set из предыдущего задания на экран.
    std::cout << "Содержимое vector:" << std::endl;
    std::copy(reversedVector.begin(), reversedVector.end(), std::ostream_iterator<Point>(std::cout, "\n"));

    std::cout << "\nСодержимое set:" << std::endl;
    std::copy(pointSetIt.begin(), pointSetIt.end(), std::ostream_iterator<Point>(std::cout, "\n"));

	//Итераторы вставки. С помощью возвращаемых функциями:
	//back_inserter()
	//front_inserter()
	//inserter()
	//итераторов вставки добавьте элементы в любой из созданных контейнеров. Подумайте:
	//какие из итераторов вставки можно использовать с каждым контейнером.

	std::list<int> lst = { 2,2,2,2,2,2 };
	std::deque<int> deq = { 2,2,2,2,2,2 };
	std::set<int> st = {2,2,2,2,2,2};


	std::copy_n(std::istream_iterator<int>(std::cin), 5, std::back_inserter(vec)); // back_inserter для vector
	std::copy_n(std::istream_iterator<int>(std::cin), 5, std::front_inserter(lst)); // front_inserter для list
	std::copy_n(std::istream_iterator<int>(std::cin), 5, std::back_inserter(deq)); // back_inserter для deque
	std::copy_n(std::istream_iterator<int>(std::cin), 5, std::inserter(st, st.begin())); // inserter для set

	std::cout << "Vector: ";
	for (const auto& elem : vec) {
		std::cout << elem << " ";
	}
	std::cout << std::endl;

	std::cout << "List: ";
	for (const auto& elem : lst) {
		std::cout << elem << " ";
	}
	std::cout << std::endl;

	std::cout << "Deque: ";
	PrintDeque(deq);

	std::cout << "Set: ";
	for (const auto& elem : st) {
		std::cout << elem << " ";
	}
	std::cout << std::endl;



	///////////////////////////////////////////////////////////////////

		//Обобщенные алгоритмы (заголовочный файл <algorithm>). Предикаты.

		// алгоритм for_each() - вызов заданной функции для каждого элемента любой последовательности
		//(массив, vector, list...)
		//С помощью алгоритма for_each в любой последовательности с элементами любого типа
		//распечатайте значения элементов
		//Подсказка : неплохо вызываемую функцию определить как шаблон

	std::vector<int> vec2 = { 1, 2, 3, 4, 5 };
	std::list<double> lst2 = { 1.1, 2.2, 3.3, 4.4, 5.5 };

	// Используем алгоритм for_each для печати значений элементов
	std::cout << "Vector: ";
	std::for_each(vec2.begin(), vec2.end(), printElement<int>);
	std::cout << std::endl;

	std::cout << "List: ";
	std::for_each(lst2.begin(), lst2.end(), printElement<double>);
	std::cout << std::endl;

	//stop

	//С помощью алгоритма for_each в любой последовательности с элементами типа Point
	//измените "координаты" на указанное значение (такой предикат тоже стоит реализовать 
	//как шаблон) и выведите результат с помощью предыдущего предиката


	{
		std::vector<Point> points = { {1, 2}, {3, 4}, {5, 6} };

		std::for_each(points.begin(), points.end(), [](Point& point) {
			changePointCoordinates(point, 10, 20);
			});

		std::for_each(points.begin(), points.end(), [](const Point& point) {
			std::cout << point << std::endl;
			});

		//С помощью алгоритма find() найдите в любой последовательности элементов Point
		//все итераторы на элемент Point с указанным значением.
		
		Point targetPoint(1, 2);
		points = { {5, 6}, {1, 2}, {3, 4} };

		auto it = points.begin();
		while ((it = std::find(it, points.end(), targetPoint)) != points.end()) {
			std::cout << "Найден элемент в позиции: " << std::distance(points.begin(), it) << std::endl;
			++it; 
		}



		//С помощью алгоритма sort() отсортируйте любую последовательность элементов Point. 
		////По умолчанию алгоритм сортирует последовательность по возрастанию.
		//Что должно быть определено в классе Point?
		// Замечание: обобщенный алгоритм sort не работает со списком, так как
		//это было бы не эффективно => для списка сортировка реализована методом класса!!!

		std::sort(points.begin(), points.end());

		// Выводим отсортированные точки
		std::cout << "Отсортированные точки:" << std::endl;
		for (const auto& point : points) {
			std::cout << "(" << point.getX() << ", " << point.getY() << ")" << std::endl;
		}


		//Создайте глобальную функцию вида: bool Pred1_1(const Point& ), которая будет вызываться
		//алгоритмом find_if(), передавая в качестве параметра очередной элемент последовательности.
		//С помощью алгоритма find_if() найдите в любой последовательности элементов Point
		//итератор на элемент Point, удовлетворяющий условию: координаты x и y лежат в промежутке
		//[-n, +m].

		auto it2 = std::find_if(points.begin(), points.end(), Pred1_1);

		// Проверяем, был ли найден элемент
		if (it2 != points.end()) {
			std::cout << "Найден элемент с координатами: (" << it2->getX() << ", " << it2->getY() << ")" << std::endl;
		}
		else {
			std::cout << "Элемент не найден" << std::endl;
		}
	}

	//С помощью алгоритма sort() отсортируйте любую последовательность элементов Rect,
	//располагая прямоугольники по удалению центра от начала координат.


    std::vector<Rect> rects = { {1, 1, 3, 2}, {2, 2, 4, 3}, {3, 3, 5, 4}, {4, 4, 6, 5} };

    // Сортируем прямоугольники по удалению от начала координат
    std::sort(rects.begin(), rects.end());

    // Выводим отсортированные прямоугольники
    std::cout << "Отсортированные прямоугольники:" << std::endl;
    for (const auto& rect : rects) {
	    std::cout << "Rect: (" << rect.getX() << ", " << rect.getY() << "), Width: "
		    << rect.getWidth() << ", Height: " << rect.getHeight() << std::endl;
    }




    //transform
	//Напишите функцию, которая с помощью алгоритма transform переводит 
	//содержимое объекта string в нижний регистр.
	//Подсказка: класс string - это "почти" контейнер, поэтому для него
	// определены методы begin() и end()

		std::string str = "Hello, World!";
		std::cout << "Исходная строка: " << str << std::endl;

		// Переводим строку в нижний регистр
		toLowercase(str);

		std::cout << "Строка в нижнем регистре: " << str << std::endl;

	//Заполните list объектами string. С помощью алгоритма transform сформируте
	//значения "пустого" set, конвертируя строки в нижний регистр


		std::list<std::string> strList = { "Hello", "World", "C++", "Programming" };

		std::set<std::string> strSet;

		std::transform(strList.begin(), strList.end(), std::inserter(strSet, strSet.end()), [](const std::string& str) {
			std::string lowercaseStr = str; // cоздаем копию строки, чтобы не изменять оригинал
			toLowercase(lowercaseStr); // переводим строку в нижний регистр
			return lowercaseStr; 
		});

		std::cout << "Пустое множество со значениями в нижнем регистре:" << std::endl;
		for (const auto& str : strSet) {
			std::cout << str << std::endl;
		}


    // map

	//Сформируйте любым способом вектор с элементами типа string.
	//Создайте (и распечатайте для проверки) map<string, int>, который будет
	//содержать упорядоченные по алфавиту строки и
	//количество повторений каждой строки в векторе


	std::vector<std::string> strings = { "apple", "polytech", "apple", "math", "polytech", "apple" };
	std::map<std::string, int> stringCountMap;

	std::for_each(strings.begin(), strings.end(), [&](const std::string& str) {
		stringCountMap[str]++;
	});

	std::cout << "Количество повторений каждой строки:" << std::endl;
	for (const auto& pair : stringCountMap) {
		std::cout << pair.first << ": " << pair.second << std::endl;
	}




	return 0;
}

