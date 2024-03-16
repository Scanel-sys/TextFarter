#include "text_farter.hpp"



#ifdef BUILD_DYNAMIC //При динамической сборке необходимо указании флага gcc «–D BUILD_DYNAMIC»
    #include "text_farter.hpp"
	#include <stdio.h>
	#include <string.h>
	#include <dlfcn.h> //Подключение функций работы с динамическими библиотеками
	int (*lib_func1)(int, int); //Создание указателей на функции, которые в дальнейшем
	int (*lib_func2)(int, int); // будут загружены из динамической библиотеки «libmy.so»
#elif BUILD_STATIC //При статической сборке необходимо указании флага gcc «–D BUILD_STATIC»
    #include "text_farter.hpp"
    #include <stdio.h>
	#include <string.h>
#elif BUILD_BLOB
	// Заголовочный файлы stdio.h и string.h подключать не нужно, так как функции strlen и printf 
	// будут получены от загрузчика loader
#endif


#ifdef BUILD_BLOB // Для компоновки в виде blob необходимо модифицировать набор аргументов функции entry, 
	              // которая будет использоваться загрузчиком loader в качестве входной точки 
				  // программы app вместо main
	int entry(int argc, char** argv, void** funcs) { //Дополнительный аргумент func предназанчен для передачи 
													 // массива указательей на отсутсвующие в app
													 // стандартные функции printf и strlen
		int (*printf)(const char*, ...); //Создание указателя на функцию с аргументами, аналогичными printf
		int (*strlen)(const char*); //Создание указателя на функцию с аргументами, аналогичными strlen
		printf = funcs[0]; //Присвоение указателю printf значения из массива, переданого загрузчиком loader
		strlen = funcs[1]; //Присвоение указателю strlen значения из массива, переданого загрузчиком loader
#else
	int entry(int argc, char** argv) 
{
#endif

	if (argc != 2) {
		printf("USAGE: <app_name> <string>\n");
		return 0;
	}

#ifdef BUILD_DYNAMIC
	void* libso = dlopen("./libmy.so", RTLD_LAZY); //Подгружаем динамическую библиотеку libmy.so
	if (libso == NULL) {
		printf("[!] Error: Can't load libmy.so\n");
		return 1;
	}
	lib_func1 = dlsym(libso, "lib_func1"); //Загружаем функцию lib_func1 из libmy.so по её символьному имени
	lib_func2 = dlsym(libso, "lib_func2"); //Загружаем функцию lib_func2 из libmy.so по её символьному имени
	if (lib_func1 == NULL || lib_func2 == NULL) {
		printf("[!] Error: Can't load symbols from so\n");
		return 1;
	}
#endif

	int sum = 0;
	for (int i = 0; i < strlen(argv[1]); i++) {
		sum += argv[1][i];
	}

	// printf("SUM: %d\n", lib_func1(sum, strlen(argv[1])));
	// printf("MUL: %d\n", lib_func2(sum, strlen(argv[1])));

#ifdef BUILD_DYNAMIC
	dlclose(libso); //Уменьшаем счетчик ссылок на libmy.so.
					//Так как ссылок на неё больше нет, библиотека будет выгружена.
#endif

	return 0;
}