#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include "ProcessData.h"
#include "Song.h"

using namespace std;

int main()
{
	setlocale(LC_CTYPE, "Polish");
	ProcessData::create_folder();
	cout << "Wrzu� pliki .json do folderu Spotify Data i potwierd� to przez wpisanie Y" << endl;
	string answer;
	do
	{
		cin >> answer;
	} while (answer != "Y");
	ProcessData::read_file_names();
	vector<Song> songs = ProcessData::parse_files("Audio");
	vector<pair<string, int>> licznik;
	unsigned long long ms = 0;
	for (auto& song : songs)
	{
		ms += song.get_ms_played();
		bool found = false;
		for (auto& p : licznik)
		{
			if (song.get_track_name() == p.first)
			{
				found = true;
				p.second++;
			}
		}
		if (!found)
		{
			licznik.emplace_back(song.get_track_name(), 1);
		}
	}
	setlocale(LC_CTYPE, "Polish");
	cout << "\nCa�kowity czas s�uchania: " << ms/60000 << " minut \n";
	cout << "\nNajcz�ciej s�uchane nuty od za�o�enia konta na spotify:\n";
	std::setlocale(LC_CTYPE, "pl_PL.UTF-8");
	std::sort(licznik.begin(), licznik.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
		return a.second > b.second;
		});
	ofstream f("output.txt");
	for (auto& p : licznik)
	{
		f << p.second << " " << p.first << endl;
		cout << p.second << " " << p.first << endl;
	}
	f.close();
	return 0;
}
