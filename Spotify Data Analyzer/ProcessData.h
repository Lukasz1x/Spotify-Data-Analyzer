#pragma once
#include <filesystem>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <thread>
#include <future>
#include <chrono>
#include "nlohmann/json.hpp"
#include "Song.h"

using namespace std;
namespace fs = std::filesystem;

class ProcessData
{
public:
	static void create_folder();
	static void read_file_names();
	static vector<Song> parse_files(string type);
private:
	ProcessData();
	static vector<string> filenames;
	static vector<Song> parse_file(string path);
};

