/*!
 * \brief	Данная программа может быть использована для просмотра содержимого текущей директории. Содержимое сортируется по размеру.
 * \author	Рогоза А. А.
 * \author	Романов С. А.
 * \date	11/02/2016
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>

/*!
 * \brief Структура для представления файла
 */
struct file
{
	char *	name;
	int		length;
};

/*!
 * \brief Сортировка массива данных
 * \param files Массив данных
 * \param filesSize Размер массива
 *
 * \details Сортирует массив данных методов вставки.
 */
void sort( struct file files[], int filesSize )
{
	for ( int i = 0; i < filesSize; ++i ) {
		struct file currentElement = files[i];
		int j;
		for ( j = i - 1; j >= 0 && files[j].length > currentElement.length; --j )
			files[j+1] = files[j];

		files[j+1] = currentElement;
	}
}

/*!
 * \brief Вывод шапки таблицы
 */
void printHead()
{
	char nameStr[] = "Name";
	char sizeStr[] = "size";
	printf( "%-*s", 30, nameStr );
	printf( "%s\n", sizeStr );
}

/*!
 * \brief Вывод массива данных
 * \param files Массив данных
 * \param filesSize Размер массива
 */
void printArray( struct file files[], int filesSize )
{
	if ( filesSize == 0 )
		return;

	char isFile = (files[0].length != -1);
	for ( int i = 0; i < filesSize; ++i ) {
		printf( "%-*s", 30, files[i].name );
		if ( isFile )
			printf( "%d", files[i].length );

		printf( "\n" );
	}
}

int main()
{
	struct dirent * currentFile;
	struct stat fileInfo;
	const int CURRENT_DIR_SIZE = 1024;

	char currentDirName[CURRENT_DIR_SIZE];
	//! Получение имени текущей дериктории
	getcwd( currentDirName, CURRENT_DIR_SIZE );

	//! Открытие текущей директории
	DIR * currentDir = opendir( currentDirName );
	if ( !currentDir ) {
		printf( "Oops! Can't open current directory!\n" );
		return 1;
	}

	const int ARRAY_SIZE = 300;
	struct file files[ARRAY_SIZE]; ///< Массив файлов
	struct file dirs[ARRAY_SIZE]; ///< Массив директорий
	int filesCount = 0;
	int dirsCount = 0;

	currentFile = readdir( currentDir );
	while ( currentFile ) {
		stat( currentFile->d_name, &fileInfo ); ///< Получение информации о файле по его имени
		if ( fileInfo.st_mode & S_IFREG ) {
			//! Файл является обычным
			files[filesCount].name		= currentFile->d_name;
			files[filesCount].length	= fileInfo.st_size;
			++filesCount;
			if ( filesCount > ARRAY_SIZE ) {
				printf( "Oops! Too much files!" );
				return 2;
			}
		}
		else if ( fileInfo.st_mode & S_IFDIR ) {
			//! Файл является директорией
			dirs[dirsCount].name		= currentFile->d_name;
			dirs[dirsCount].length		= -1;
			++dirsCount;
			if ( dirsCount > ARRAY_SIZE ) {
				printf( "Oops! Too much directories!" );
				return 2;
			}
		}
		currentFile = readdir( currentDir );
	}
	closedir( currentDir );

	sort( files, filesCount );

	//! Вывод результатов
	printHead();
	printArray( dirs, dirsCount );
	printArray( files, filesCount );

	return 0;
}
