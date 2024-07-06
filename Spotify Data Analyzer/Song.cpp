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