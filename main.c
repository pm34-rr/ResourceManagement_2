#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>

const int CURRENT_DIR_SIZE = 1024;

struct file
{
	char *	name;
	int		length;
};

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

void printHead()
{
	char nameStr[] = "Name";
	char sizeStr[] = "size";
	printf( "%-*s", 30, nameStr );
	printf( "%s\n", sizeStr );
}

void printArray( struct file files[], int filesSize )
{
	if ( filesSize == 0 )
		return;

	char isFile = (files[0].length > -1);
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
	char currentDirName[CURRENT_DIR_SIZE];
	getcwd( currentDirName, CURRENT_DIR_SIZE );

	DIR * currentDir = opendir( currentDirName );
	if ( !currentDir ) {
		printf( "Oops! Can't open current directory!\n" );
		return 1;
	}

	const int ARRAY_SIZE = 300;
	struct file files[ARRAY_SIZE];
	struct file dirs[ARRAY_SIZE];
	int filesCount = 0;
	int dirsCount = 0;

	currentFile = readdir( currentDir );
	while ( currentFile ) {
		stat( currentFile->d_name, &fileInfo );
		if ( fileInfo.st_mode & S_IFREG ) {
			// file
			files[filesCount].name		= currentFile->d_name;
			files[filesCount].length	= fileInfo.st_size;
			++filesCount;
		}
		else if ( fileInfo.st_mode & S_IFDIR ) {
			// dir
			dirs[dirsCount].name		= currentFile->d_name;
			dirs[dirsCount].length		= -1;
			++dirsCount;
		}
		currentFile = readdir( currentDir );
	}
	closedir( currentDir );

	sort( files, filesCount );
	printHead();
	printArray( dirs, dirsCount );
	printArray( files, filesCount );

	return 0;
}
