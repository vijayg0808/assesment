/**                                                                                                                                           
 * @file       : move_copy_cmd.c
 * 
 * @brief      : This file contains C code for implementing the "mv" and "cp" command
 *               in linux.
 *
 * @author     : Vijay G (vijay.g0808@gmail.com)
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SUCCESS 0
#define FAILURE -1

/**
* @function    : display_usage
* @return      : void
* @brief       : This function is to print the proper usage of this binary file
*                incase of any invalid input.
*/
void display_usage(char *bin_file)
{
	printf("Usage:\n");
	printf("  %s mv <source> <destination>\n", bin_file);
	printf("  %s cp <source> <destination>\n", bin_file);
	return;
}

/**
* @function    : cp
* @return      : void
* @brief       : This function is to copy the source file content into destination
*/
void cp(char *source, char *destination){
	FILE *src_fp, *dest_fp;
	if ((src_fp = fopen(source,"r")) == NULL) {
		printf("Can't open source file\n");
		exit(EXIT_FAILURE);
	}
	if ((dest_fp = fopen(destination,"w")) == NULL) {
		printf("Can't open destination file\n");
		exit(EXIT_FAILURE);
	}

	char buff[4096];
	size_t bytes;

	//Copying file from source to destination
	while ((bytes = fread(buff, 1, sizeof(buff), src_fp)) > 0) {
		if(fwrite(buff, 1, bytes, dest_fp) != bytes) {
			printf("cp : Failed while writing to destination file\n");
			fclose(src_fp);
			fclose(dest_fp);
			exit(EXIT_FAILURE);
		}
	}

	fclose(src_fp);
	fclose(dest_fp);
}

/**
* @function    : mv
* @return      : void
* @brief       : This function is to move the source file
*/
void mv(char *source, char *destination)
{
	cp(source, destination);

	if(remove(source) != 0){
		printf("mv : Failed while moving the source");
		exit(EXIT_FAILURE);
	}
}

/**
* @function    : main
* @return      : int (status)
* @brief       : This main function will get the inputs as CLI and calls the respective
*                functions (cp or mv) for the further process.
*/
int main(int argc, char *argv[])
{
	if (argc != 4){
		display_usage(argv[0]);
		return FAILURE;
	}

	if (strcmp(argv[1], "mv") == 0){
		mv(argv[2], argv[3]);
	} else if (strcmp(argv[1], "cp") == 0){
		cp(argv[2], argv[3]);
	} else {
		display_usage(argv[0]);
		return FAILURE;
	}
  
	return SUCCESS;
}
