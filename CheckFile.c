#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
int getAllFiles(char *_path) {

	//open path
	DIR *_path_dp = opendir(_path);

	//if path is not exist
	if (_path_dp == NULL) {
		return -1;
	}

	int _path_length = strlen(_path);
	struct dirent *_dirp;

	//traverse change_path
	while ((_dirp = readdir(_path_dp)) != NULL) {

		//subdirentory is "." or ".."
		if (strcmp(_dirp->d_name, ".") == 0 || strcmp(_dirp->d_name, "..") == 0) {
			continue;
		}

		//if dirp is direntory
		if (_dirp->d_type == DT_DIR) {

			//count and set length of path name
			int _subdirentory_path_length = _path_length + 1 + strlen(_dirp->d_name);
			char *_subdirentory_path = (char*)malloc((_subdirentory_path_length+1) * sizeof(char));

			//malloc failure
			if (_subdirentory_path == NULL) {
				closedir(_path_dp);
				return -2;
			}

			//set subdirentory path
			sprintf(_subdirentory_path, "%s/%s", _path, _dirp->d_name);

			//recur subdirentory
			getAllFiles(_subdirentory_path);

			//free memory
			free(_subdirentory_path);
		}

		//if dirp is file
		else {
			//print the file name
			printf("%s/%s\n", _path ,_dirp->d_name);
			char command[200];
			snprintf(command, sizeof(command), "mkdir -p ./backup%s && cp %s/%s ./backup%s/%s", _path, _path, _dirp->d_name, _path, _dirp->d_name);
			printf("mkdir -p ./backup%s && cp %s/%s ./backup%s/%s\n", _path, _path, _dirp->d_name, _path, _dirp->d_name);
			system(command);
		}

	}

	//clsoe DIR
	closedir(_path_dp);

	return 0;	//success
}

int getDifferentFiles(char *_original_path, char *_change_path) {


	//open path

	//open change path
	DIR *_change_dp = opendir(_change_path);

	//if change path is not exist then return error
	if (_change_dp == NULL) {
		return -1;
	}

	//open original path
	DIR *_original_dp = opendir(_original_path);

	//change path is exist, but original path is not exist
	//all files are different then get all files
	if (_original_dp == NULL) {

		closedir(_change_dp);

		//recur all file
		getAllFiles(_change_path);

		return 0;	//success
	}


	int _original_path_length = strlen(_original_path);
	int _change_path_length = strlen(_change_path);
	struct dirent *_dirp;

	//traverse change_path
	while ((_dirp = readdir(_change_dp)) != NULL) {

		//subdirentory is "." or ".."
		if (strcmp(_dirp->d_name, ".") == 0 || strcmp(_dirp->d_name, "..") == 0) {
			continue;
		}

		//if dirp is direntory
		//DT_DIR = 4
		if (_dirp->d_type == DT_DIR) {

			//count and set length of path name
			int _subdirentory_name_length = strlen(_dirp->d_name);

			int _original_subdirentory_path_length = _original_path_length + 1 + _subdirentory_name_length;
			int _change_subdirentory_path_length = _change_path_length + 1 + _subdirentory_name_length;

			char *_original_subdirentory_path = (char*)malloc((_original_subdirentory_path_length+1) * sizeof(char));
			char *_change_subdirentory_path = (char*)malloc((_change_subdirentory_path_length+1) * sizeof(char));

			//malloc failure
			if (_original_subdirentory_path == NULL || _change_subdirentory_path == NULL) {
				free(_original_subdirentory_path);
				free(_change_subdirentory_path);
				closedir(_original_dp);
				closedir(_change_dp);
				return -2;
			}

			//set subdirentory path
			sprintf(_original_subdirentory_path, "%s/%s", _original_path, _dirp->d_name);
			sprintf(_change_subdirentory_path, "%s/%s", _change_path, _dirp->d_name);

			//recur subdirentory
			getDifferentFiles(_original_subdirentory_path, _change_subdirentory_path);

			//free memory
			free(_original_subdirentory_path);
			free(_change_subdirentory_path);
		}

		//if dirp is file
		else {

			//count and set length of path name
			int _file_name_length = strlen(_dirp->d_name);
			int _original_file_path_length = _original_path_length + 1 + _file_name_length;
			char *_original_file_path = (char*)malloc((_original_file_path_length+1) * sizeof(char));

			//malloc failure
			if (_original_file_path == NULL) {
				closedir(_original_dp);
				closedir(_change_dp);
				return -2;
			}

			//set file path
			sprintf(_original_file_path, "%s/%s", _original_path, _dirp->d_name);

			//open file in original path
			FILE *_original_file = fopen(_original_file_path, "r");
			free(_original_file_path);

			//if original file is exist
			if (_original_file != NULL) {

				//count and set length of command
				int _original_file_command_length = 7 + _original_path_length + 1 + _file_name_length;
				int _change_file_command_length = 7 + _change_path_length + 1 + _file_name_length;

				char *_original_file_command = (char*)malloc((_original_file_command_length+1) * sizeof(char));
				char *_change_file_command = (char*)malloc((_change_file_command_length+1) * sizeof(char));

				char *_original_file_md5hash = (char*)malloc((_file_name_length+35) * sizeof(char));
				char *_change_file_md5hash = (char*)malloc((_file_name_length+35) * sizeof(char));

				//malloc failure
				if (_original_file_command == NULL || _change_file_command == NULL || _original_file_md5hash == NULL || _change_file_md5hash == NULL) {
					free(_original_file_command);
					free(_change_file_command);
					free(_original_file_md5hash);
					free(_change_file_md5hash);
					closedir(_original_dp);
					closedir(_change_dp);
					return -2;
				}

				//set file command
				sprintf(_original_file_command, "md5sum %s/%s", _original_path, _dirp->d_name);
				sprintf(_change_file_command, "md5sum %s/%s", _change_path, _dirp->d_name);

				//get md5hash
				FILE *_original_file_exec = popen(_original_file_command, "r");
				FILE *_change_file_exec = popen(_change_file_command, "r");
				fgets(_original_file_md5hash, sizeof(_original_file_md5hash), _original_file_exec);
				fgets(_change_file_md5hash, sizeof(_change_file_md5hash), _change_file_exec);
				pclose(_original_file_exec);
				pclose(_change_file_exec);

				//compare two file
				//if different then print file
				if (strcmp(_original_file_md5hash, _change_file_md5hash) != 0) {
					printf("%s/%s\n", _change_path, _dirp->d_name);
					char command[200];
					snprintf(command, sizeof(command), "mkdir -p ./backup%s && cp %s/%s ./backup%s/%s", _change_path, _change_path, _dirp->d_name, _change_path, _dirp->d_name);
					printf("mkdir -p ./backup%s && cp %s/%s ./backup%s/%s\n", _change_path, _change_path, _dirp->d_name, _change_path, _dirp->d_name);
					system(command);
				}

				//free memory
				free(_original_file_command);
				free(_change_file_command);
				free(_original_file_md5hash);
				free(_change_file_md5hash);

				//close FILE
				fclose(_original_file);
			}

			//original file is not exist
			else
			{
				printf("%s/%s\n", _change_path, _dirp->d_name);
				char command[1000];
				snprintf(command, sizeof(command), "mkdir -p ./backup%s && cp %s/%s ./backup%s/%s", _change_path, _change_path, _dirp->d_name, _change_path, _dirp->d_name);
				printf("mkdir -p ./backup%s && cp %s/%s ./backup%s/%s\n", _change_path, _change_path, _dirp->d_name, _change_path, _dirp->d_name);
				system(command);
			}

		}

	}

	//clsoe DIR
	closedir(_original_dp);
	closedir(_change_dp);

	return 0; //success
}
