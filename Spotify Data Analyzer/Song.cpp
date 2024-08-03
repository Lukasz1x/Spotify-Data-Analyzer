#include "Song.h"


Song::Song(const std::string& album_name, const std::string& artist_name, const std::string& track_name,
    int ms_played_value, int timestamp_value, const std::string& platform_name, const std::string& track_uri)
    : master_metadata_album_album_name(album_name),
    master_metadata_album_artist_name(artist_name),
    master_metadata_track_name(track_name),
    ms_played(ms_played_value),
    offline_timestamp(timestamp_value),
    platform(platform_name),
    spotify_track_uri(track_uri)
{
    // Dodatkowy kod inicjalizacyjny, jeœli jest potrzebny
}

string Song::get_track_name()
{
    return master_metadata_track_name;
}

int Song::get_ms_played()
{
    return ms_played;
}

unsigned long long Song::get_total_ms_played(vector<Song>songs)
{
    auto start = std::chrono::high_resolution_clock::now();
    unsigned long long ms=0;
    for (auto& song : songs)
    {
        ms += song.get_ms_played();
    }

    // Koniec pomiaru czasu
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::milliseconds>(end - start);
    //std::cout << "get_total_ms_played - czas wykonania: " << duration.count() << " ms" << std::endl;
    return ms;
}
vector<pair<string, int>> Song::count_songs(vector<Song>songs)
{
    auto start = std::chrono::high_resolution_clock::now();
    std::unordered_map<std::string, int> licznik;

    for (auto& song : songs) {
        licznik[song.get_track_name()]++;
    }

    std::vector<std::pair<std::string, int>> licznik_vector;
    for (const auto& pair : licznik) {
        licznik_vector.emplace_back(pair.first, pair.second);
    }
    std::sort(licznik_vector.begin(), licznik_vector.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        return a.second > b.second;
        });

    // Koniec pomiaru czasu
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::milliseconds>(end - start);
    //std::cout << "count_songs - czas wykonania: " << duration.count() << " ms" << std::endl;
    return licznik_vector;
}

vector<pair<string, unsigned long long>> Song::count_ms_songs(vector<Song>songs)
{
    auto start = std::chrono::high_resolution_clock::now();
    std::unordered_map<std::string, unsigned long long> licznik;

    for (auto& song : songs) {
        licznik[song.get_track_name()]+=song.get_ms_played();
    }

    std::vector<std::pair<std::string, unsigned long long>> licznik_vector;
    for (const auto& pair : licznik) {
        licznik_vector.emplace_back(pair.first, pair.second);
    }

    std::sort(licznik_vector.begin(), licznik_vector.end(), [](const std::pair<std::string, unsigned long long>& a, const std::pair<std::string, unsigned long long>& b) {
        return a.second > b.second;
        });

    // Koniec pomiaru czasu
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::milliseconds>(end - start);
    //std::cout << "count_ms_songs - czas wykonania: " << duration.count() << " ms" << std::endl;
    return licznik_vector;
}
