/*
Пример тестов с расшифровкой
Это псевдо код, он не скомпилится


Любые указанные файлы не совпадают, если иное не оговороено
Большое количество одноименных файлов,отлмчающихся номером, нужно для того, чтобы исключить возможную перезапись результатов

Необходимые входные данные: 
f1_in_correct.txt - корректный файл с несколькими текстовыми строками
f1_in_double.txt - файл являющийся конкатинацией (склейкой) дважды файла f1_in_correct.txt
f1_in_empty.txt - пустой файл
f1_in_null.txt - такого файла не существует
f1_N - правильное число входных строк

f2_in_correct1.txt - корректный файл с числами, больше одного числа в строке, больше одной строки, половина файлов через ".", половина через ",", кроме того есть числа без дробной части
f2_in_correct2.txt - корректный файл с числами, одна строка, одно число
f2_in_correct3.txt - корректный файл с нулем
f2_in_incorrect1.txt - файл с текстом или нарушением формата
f2_in_incorrect2.txt - файл с хотя бы одним отрицательным числом
f2_in_incorrect3.txt - файл с несколькими отрицательными числами, сумма которых меньше нуля
f2_in_empty.txt - пустой файл
f2_in_null.txt - такого файла не существует
f2_N1 - известная сумма для f2_in_correct1.txt
f2_N2 - известная сумма для f2_in_correct2.txt

f3_in_correct.txt - текстовый файл с каким-то текстом в несколько строк (удобочитаемым).
f3_in_empty.txt - пустой файл
f3_in_null.txt - такого файла не существует
key1 - текстовый ключ для шифрования
key2 - текстовый ключ для шифрования
f3_N - известный размер файла f3_in_correct.txt

Выходные данные:
Файлы будут создаваться автоматически и потом должны быть в репозитории
f1_out_correct1.txt - правильный файл (не существует перед вызовом функции)
f1_out_correct2.txt - правильный файл (не существует перед вызовом функции)
f1_out_correct3.txt - правильный файл (не существует перед вызовом функции)
f1_out_correct4.txt - правильный файл (не существует перед вызовом функции)
f1_out_correct5.txt - правильный файл (не существует перед вызовом функции)
f1_out_empty.txt - пустой файл (существует)
f1_out_incorrect.txt - несуществующий файл с несуществующим путем (директория)

f3_out_correct1.txt - правильный файл (не существует перед вызовом функции) - будет использоваться для первого шифрования
f3_out_correct2.txt - правильный файл (не существует перед вызовом функции) - будет использоваться для второго шифрования
f3_out_correct3.txt - правильный файл (не существует перед вызовом функции) - будет использоваться для проверки перезаписи
f3_out_correct4.txt - правильный файл (не существует перед вызовом функции)
f3_out_correct5.txt - правильный файл (не существует перед вызовом функции)
f3_out_correct6.txt - правильный файл (не существует перед вызовом функции)
f3_out_correct_exist1.txt - правильный файл (существует перед вызовом функции) - будет использоваться для проверки перезаписи
f3_out_correct_exist2.txt - правильный файл совпадает с одноименным 1 (существует перед вызовом функции) - будет использоваться для проверки перезаписи
f3_out_empty.txt - пустой файл (существует)
f3_out_incorrect.txt - несуществующий файл с несуществующим путем (директория)


Функции:
1.
res=FUNC1(in,out) - функция построчного копирования файла in в файл out.
res:
положительное число >=0 - число скопированых строк
-1 - ошибка открытия входного файла
-2 - ошибка открытия выходного файла

2.
res=FUNC2(in) - функция суммирования положительных чисел из файла in
res:
положительное число >=0 - сумма чисел из файла
-1 - ошибка открытия входного файла
-3 - ошибка содержимого файла  //-3 так как -2 зарезервировано для ошибки выходного файла

3.
res=FUNC3(in,out,key) - функция шифрования файла in в файл out ключем (строкой) key
положительное число >=0 - число зашифрованных байт
-1 - ошибка открытия входного файла
-2 - ошибка открытия выходного файла

4.
res=DIFF(in,out) - функция побайтового сравнения файлов in и out
res:
0 - файлы не отличаются
положительное число >0 - первый байт с которого они отличаются
-1 - ошибка открытия входного файла
-2 - ошибка открытия выходного файла


*/
/********************************************************************************************************************/
TEST_CASE(diff,[diff]) //проверка функции DIFF
{
	REQUIRE(DIFF(f1_in_correct.txt,f1_in_correct.txt)==0) //сранвнение с самим собой
	REQUIRE(DIFF(f1_in_correct.txt,f2_in_correct1.txt)>0) //разные файлы
	REQUIRE(DIFF(f1_in_correct.txt,f1_in_empty.txt)>0) //один файл пустой
	REQUIRE(DIFF(f1_in_correct.txt,f1_in_null.txt)==-2) //нет файла
	REQUIRE(DIFF(f1_in_null.txt,f1_in_correct.txt)==-1) //нет файла
}
/*********************************************************************************************************************/

TEST_CASE(f1_correct_correct,[func1][correct tests]) //тестирование нормальной работы функции, файл создается
{
	in=f1_in_correct.txt
	out=f1_out_correct.txt
	REQUIRE_NOTHROW(res=FUNC1(in,out))
	CHECK(res>0)
	CНECK(res==f1_N)
	CHECK(DIFF(in,out)==0)
}
TEST_CASE(f1_correct_empty,[func1][correct tests]) //тестирование нормальной работы функции, выходной файл существует и пустой, происходит дописывание в пустой файл
{
	in=f1_in_correct.txt
	out=f1_out_empty.txt
	REQUIRE_NOTHROW(res=FUNC1(in,out))
	CHECK(res>0)
	CНECK(res==f1_N)
	CHECK(DIFF(in,out)==0)
}
TEST_CASE(f1_correct_double,[func1][correct tests]) //тестирование нормальной работы функции, выходной файл существует, происходит дописывание в пустой файл
{
	in=f1_in_correct.txt
	out=f1_out_correct2.txt
	REQUIRE_NOTHROW(res=FUNC1(in,out))
	CHECK(res>0) //один раз
	CНECK(res==f1_N)
	CHECK(DIFF(in,out)==0)  
	
	REQUIRE_NOTHROW(res2=FUNC1(in,out))
	CHECK(res2>0)
	CНECK(res2==2*f1_N)
	CHECK(DIFF(f1_in_double.txt,out)==0)
}
TEST_CASE(f1_correct_incorrect,[func1][incorrect tests]) //тестирование работы функции с ошибкой выходного файла
{
	in=f1_in_correct.txt
	out=f1_out_incorrect.txt
	REQUIRE_NOTHROW(res=FUNC1(in,out))
	CHECK(res==-2)
}
TEST_CASE(f1_null_correct,[func1][incorrect tests]) //тестирование работы функции с несуществующим входным файлом
{
	in=f1_in_null.txt
	out=f1_out_correct3.txt
	REQUIRE_NOTHROW(res=FUNC1(in,out))
	CHECK(res==-1)
}
TEST_CASE(f1_empty_correct,[func1][empty tests]) //тестирование работы функции c пустым входным
{
	in=f1_in_empty.txt
	out=f1_out_correct4.txt
	REQUIRE_NOTHROW(res=FUNC1(in,out))
	CHECK(res==0)
	CHECK(DIFF(in,out)==0)
}
TEST_CASE(f1_correct_null,[func1][incorrect tests]) //тестирование работы функции с пустым именем выходного файла
{
	in=f1_in_correct.txt
	out=""
	REQUIRE_NOTHROW(res=FUNC1(in,out))
	CHECK(res==-2)
}
TEST_CASE(f1_null_correct,[func1][incorrect tests]) //тестирование работы функции с пуствым именем входного файла
{
	in=""
	out=f1_out_correct5.txt
	REQUIRE_NOTHROW(res=FUNC1(in,out))
	CHECK(res==-1)
}
/*************************************************************************************************************************/
TEST_CASE(f2_null,[func2][incorrect tests]) //тестирование работы функции с несуществующим входным файлом
{
	in=f2_in_null.txt
	REQUIRE_NOTHROW(res=FUNC2(in))
	CHECK(res==-1)
}
TEST_CASE(f2_empty,[func2][empty tests]) //тестирование работы функции c пустым входным
{
	in=f2_in_empty.txt
	REQUIRE_NOTHROW(res=FUNC2(in))
	CHECK(res==-3)
}
TEST_CASE(f2_null_correct,[func2][incorrect tests]) //тестирование работы функции с пуствым именем входного файла
{
	in=""
	REQUIRE_NOTHROW(res=FUNC2(in))
	CHECK(res==-1)
}
TEST_CASE(f2_incorrect,[func2][incorrect tests]))  //тестирование работы функции с неправильным входным файлом
{
	in1=f2_in_incorrect1.txt
	in2=f2_in_incorrect2.txt
	in3=f2_in_incorrect3.txt
	REQUIRE_NOTHROW(res1=FUNC2(in1))
	REQUIRE_NOTHROW(res2=FUNC2(in2))
	REQUIRE_NOTHROW(res3=FUNC2(in3))
	CHECK(res1<0)
	CHECK(res2<0)
	CHECK(res3<0)
}
TEST_CASE(f2_correct,[func2][correct tests]) //тестирование нормальной работы функции
{
	in1=f2_in_correct1.txt
	in2=f2_in_correct2.txt
	in3=f2_in_correct3.txt	
	REQUIRE_NOTHROW(res1=FUNC2(in1))
	CHECK(res1>=0)
	CHECK(res1==f2_N1)

	REQUIRE_NOTHROW(res2=FUNC2(in2))
	CHECK(res2>=0)
	CHECK(res2==f2_N2)

	REQUIRE_NOTHROW(res3=FUNC2(in3))
	CHECK(res3==0)
}

/***************************************************************************************************************************/
TEST_CASE(f3_null_correct,[func3][incorrect tests]) //тестирование работы функции с несуществующим входным файлом
{
	in=f3_in_null.txt
	out=f3_out_correct.txt
	REQUIRE_NOTHROW(res=FUNC3(in,out))
	CHECK(res==-1)
}
TEST_CASE(f3_correct_incorrect,[func3][incorrect tests]) //тестирование работы функции с ошибкой выходного файла
{
	in=f3_in_correct.txt
	out=f3_out_incorrect.txt
	REQUIRE_NOTHROW(res=FUNC3(in,out))
	CHECK(res==-2)
}
TEST_CASE(f3_correct_exist,[func3][correct tests])  //тестирование с перезаписью , при расшифровке тестируется несуществующий файл
{
	in=f3_in_correct.txt		
	out=f3_out_correct_exist1.txt
	CHECK(DIFF(out,f3_out_correct_exist2.txt)==0)  //проверка что файлы изначально совпадают
	REQUIRE_NOTHROW(res1=FUNC3(in,out,key1))
	CHECK(DIFF(out,f3_out_correct_exist2.txt)>0)  //проверка несовпадения файлов после перезаписи
	CHECK(res1>0)
	CHECK(res1==f3_N)

	out2=f3_out_correct1.txt
	REQUIRE_NOTHROW(res2=FUNC3(out,out2,key1))		//расшифровка
	CHECK(res2>0)
	CHECK(res2==f3_N)
	CHECK(res1==res2)
	CHECK(DIFF(in,out2)==0)	//проверка корректности расшифровки
}
TEST_CASE(f3_correct_empty,[func3][correct tests])  //тестирование с выходным пустым файлом, при расшифровке тестируется несуществующий файл
{
	in=f3_in_correct.txt		
	out=f3_out_empty.txt
	REQUIRE_NOTHROW(res1=FUNC3(in,out,key1))
	CHECK(res1>0)
	CHECK(res1==f3_N)

	out2=f3_out_correct2.txt
	REQUIRE_NOTHROW(res2=FUNC3(out,out2,key1))		//расшифровка
	CHECK(res2>0)
	CHECK(res2==f3_N)
	CHECK(res1==res2)
	CHECK(DIFF(in,out2)==0)	//проверка корректности расшифровки
}
TEST_CASE(f3_incorrect_key,[func3][incorrect tests])  //тестирование с неправильным ключом
{
	in=f3_in_correct.txt
	out=f3_out_correct3.txt
	REQUIRE_NOTHROW(res1=FUNC3(in,out,key1))
	CHECK(res1>0)
	CHECK(res1==f3_N)

	out2=f3_out_correct4.txt
	REQUIRE_NOTHROW(res2=FUNC3(out,out2,key2))		//расшифровка c другим ключом
	CHECK(res2>0)
	CHECK(res2==f3_N)
	CHECK(res1!=res2)
	CHECK(DIFF(in,out2)>0)	//проверка корректности - расшифровка не должна пройти
}
TEST_CASE(f3_incorrect_key,[func3][incorrect tests])  //тестирование с пустым ключом
{
	in=f3_in_correct.txt
	out=f3_out_correct5.txt
	REQUIRE_NOTHROW(res1=FUNC3(in,out,""))
	CHECK(res1>0)
	CHECK(res1==f3_N)
	CHECK(DIFF(in,out)==0)	//проверка корректности файл не должен защифроваться с пустым ключом
}
TEST_CASE(f3_correct_null,[func3][incorrect tests]) //тестирование работы функции с пустым именем выходного файла
{
	in=f3_in_correct.txt
	out=""
	REQUIRE_NOTHROW(res=FUNC3(in,out,key1))
	CHECK(res==-2)
}
TEST_CASE(f3_null_correct,[func3][incorrect tests]) //тестирование работы функции с пуствым именем входного файла
{
	in=""
	out=f3_out_correct6.txt
	REQUIRE_NOTHROW(res=FUNC3(in,out,key1))
	CHECK(res==-1)
}


