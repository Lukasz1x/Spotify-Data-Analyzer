#pragma once

#include <string>
#include <vector>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Song
{
private:
	string master_metadata_album_album_name;
	string master_metadata_album_artist_name;
	string master_metadata_track_name;
	int ms_played;
	int offline_timestamp;
	string platform;
	string spotify_track_uri;
public:
	Song(const std::string& album_name, const std::string& artist_name, const std::string& track_name,
		int ms_played_value, int timestamp_value, const std::string& platform_name, const std::string& track_uri);
	string get_track_name();
	int get_ms_played();
	static unsigned long long get_total_ms_played(vector<Song>songs);
	static vector<pair<string, int>> count_songs(vector<Song>songs);
	static vector<pair<string, unsigned long long>> count_ms_songs(vector<Song>songs);
};

