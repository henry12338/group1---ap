#include <stdio.h>
#include <string.h>
#include "JSON_request_handle.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <curl/curl.h>
struct FTPFile {
  const char *filename;
  FILE *stream;
};

static size_t my_fwrite(void *buffer, size_t size, size_t nmemb, void *stream)
{
	struct FTPFile *out = (struct FTPFile *)stream;
	if(out && !out->stream)
	{
		/* open file for writing */ 
		out->stream = fopen(out->filename, "wb");
		if(!out->stream)
			return -1; /* failure, can't open file to write */ 
	}
	return fwrite(buffer, size, nmemb, out->stream);
}
size_t my_fread(void * ptr, size_t size, size_t nmemb, void * stream)
{
	curl_off_t nread;
	size_t retcode = fread(ptr, size, nmemb, stream);
	nread = (curl_off_t)retcode;
	fprintf(stderr, "*** We read %" CURL_FORMAT_CURL_OFF_T
          " bytes from file\n", nread);
	return retcode;
}

int main()
{
	char InputBuf[1000];
	strcpy(InputBuf, "{\n	\"Action\" : 2\n}\n");
	Handle_Action(InputBuf, 0);
	printf("%s\n", InputBuf);

// upload
	CURL * curl;
	CURLcode res;
	FILE * hd_src;
	struct stat file_info;
	curl_off_t fsize;
	


	if(stat("./test.c", &file_info))
	{
		printf("Couldn't open '%s'\n", "./test.c");
		exit(1);
	}

	fsize = (curl_off_t)file_info.st_size;

	hd_src = fopen("./test.c", "rb");

	curl_global_init(CURL_GLOBAL_ALL);

	curl = curl_easy_init();
	if(curl)
	{

		/* we want to use our own read function */ 
		curl_easy_setopt(curl, CURLOPT_READFUNCTION, my_fread);

		/* enable uploading */ 
		curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
		
		/* specify target */ 
		curl_easy_setopt(curl, CURLOPT_URL, "ftp://35.221.194.17/ggwp.c");


//		curl_easy_setopt(curl, CURLOPT_FTP_ACCOUNT, "anonymous");
		curl_easy_setopt(curl, CURLOPT_USERPWD, "uftp:seg1");


		/* now specify which file to upload */ 
		curl_easy_setopt(curl, CURLOPT_READDATA, hd_src);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

		/* Set the size of the file to upload (optional).  If you give a *_LARGE
		option you MUST make sure that the type of the passed-in argument is a
		curl_off_t. If you use CURLOPT_INFILESIZE (without _LARGE) you must
		make sure that to pass in a type 'long' argument. */ 
		curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE,
			     (curl_off_t)fsize);

		/* Now run off and do what you've been told! */ 
		res = curl_easy_perform(curl);
		
		/* Check for errors */ 
		if(res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

		/* always cleanup */ 
		curl_easy_cleanup(curl);
	}
	fclose(hd_src); /* close the local file */ 

	curl_global_cleanup();

/* download
	CURL *curl;
	CURLcode res;
	struct FTPFile ftpfile =
	{
		"test.php",
		NULL
	};


	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();

	if(curl)
	{
		/*
		* You better replace the URL with one that works!
		*/ 
//		curl_easy_setopt(curl, CURLOPT_URL, "http://35.229.204.49/test.php");
		/* Define our callback to get called when there's data to be written */ 
//		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);
		/* Set a pointer to our struct to pass to the callback */ 
//		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile);

		/* Switch on full protocol/debug output */ 
//		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

//		res = curl_easy_perform(curl);

		/* always cleanup */ 
//		curl_easy_cleanup(curl);

//		if(CURLE_OK != res)
//		{
			/* we failed */ 
//			fprintf(stderr, "curl told us %d\n", res);
//		}
//	  }
	 
//	  if(ftpfile.stream)
//	    fclose(ftpfile.stream); /* close the local file */ 
	 
//	  curl_global_cleanup();
 	
}
