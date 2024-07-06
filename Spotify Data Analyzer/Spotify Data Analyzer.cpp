#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <chrono>
#include <thread>
#include <future>
#include "ProcessData.h"
#include "Song.h"

using namespace std;
using namespace std::chrono;

int main()
{
	setlocale(LC_CTYPE, "Polish");
	ProcessData::create_folder();
	//cout << "Wrzuæ pliki .json do folderu Spotify Data i potwierdŸ to przez wpisanie Y" << endl;
	//string answer;
	//do
	//{
	//	cin >> answer;
	//} while (answer != "Y");
	ProcessData::read_file_names();
	vector<Song> songs = ProcessData::parse_files("Audio");
	vector<pair<string, int>> licznik = Song::count_songs(songs);
	vector<pair<string, unsigned long long>> czas_sluchania = Song::count_ms_songs(songs);
	unsigned long long ms = Song::get_total_ms_played(songs);

	setlocale(LC_CTYPE, "Polish");
	cout << "\nCa³kowity czas s³uchania: " << ms/60000 << " minut \n";
	std::setlocale(LC_CTYPE, "pl_PL.UTF-8");

	ofstream f("count.txt");
	for (auto& p : licznik)
	{
		f << p.second << " " << p.first << endl;
	}
	f.close();
	ofstream f2("time.txt");
	for (auto& p : czas_sluchania)
	{
		f2 << p.second/60000 << " " << p.first << endl;
	}
	f2.close();


	return 0;
}
