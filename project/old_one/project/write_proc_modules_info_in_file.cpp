#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <cstring>

using namespace std;

#define READ_PROC_ERR 1
#define WRITE_MODULE_ERR 2
#define READ_MODULE_ERR 3
#define OK 0

#define FILE_WRITE_NAME "/home/ilalevuskin/Desktop/example/new_modules.txt"


int get_last_module_to_kernel(string &buff)
{
	ifstream rfile;
	rfile.open("/proc/modules", fstream::in);
	getline(rfile, buff);
	rfile.close();
	return 0;
}

int get_last_added_module_to_kernel(string &res)
{
	ifstream rfile;
	rfile.open(FILE_WRITE_NAME, fstream::in);
	string buf;
	while (getline(rfile, buf))
	{
        res = buf;
	}
	rfile.close();
	return 0;
}

int new_module_added(const char *last_module, const char* before_module)
{
	if (strcmp(last_module, before_module) != 0)
	{
		return 1;
	}
	return 0;
}

int write_added_module_in_file(string buff)
{
	ofstream wfile;
	wfile.open(FILE_WRITE_NAME, ios::out | ios::app);

	wfile << buff << endl;

	wfile.close();
	return 0;
}

int main(int argc, char *argv[])
{
	string buff_1, buff_2;
	if (get_last_module_to_kernel(buff_1))
	{
		return READ_PROC_ERR;
	}
	if (get_last_added_module_to_kernel(buff_2))
	{
		return READ_MODULE_ERR;
	}
	if (new_module_added(buff_1.c_str(), buff_2.c_str()))
	{
		if (write_added_module_in_file(buff_1))
		{
			return WRITE_MODULE_ERR;
		}
	}
	return OK;
}