#include "ProcessData.h"

vector<string> ProcessData::filenames;

void ProcessData::create_folder()
{
    const std::string folderName = "Spotify Data";

    try {
        if (!std::filesystem::exists(folderName)) {
            if (std::filesystem::create_directory(folderName)) {
                //std::cout << "Folder zosta³ utworzony." << std::endl;
            }
            else {
                std::cerr << "Nie uda³o siê utworzyæ folderu." << std::endl;
            }
        }
        else {
            //std::cout << "Folder ju¿ istnieje." << std::endl;
        }
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "B³¹d: " << e.what() << std::endl;
    }
}

void ProcessData::read_file_names()
{
    std::string path = "./Spotify Data";

    // Sprawdzamy czy podana œcie¿ka jest folderem
    if (fs::is_directory(path)) {
        // Iterujemy po zawartoœci folderu
        for (const auto& entry : fs::directory_iterator(path)) {
            filenames.push_back(entry.path().filename().string());
            //std::cout << entry.path().filename().string() << std::endl;
        }
    }
    else {
        std::cerr << "Podana œcie¿ka nie jest folderem." << std::endl;
    }
}

vector<Song> ProcessData::parse_files(string type)
{
    vector<Song> songs;
    std::setlocale(LC_CTYPE, "pl_PL.UTF-8");
    std::string path = "./Spotify Data/";
    vector<string>files_to_parse;
    for (auto& s : filenames)
    {
        if (s.find(type) != std::string::npos)
        {
            files_to_parse.push_back(s);
            cout << s << endl;
        }
    }
    for (auto& f : files_to_parse)
    {
        std::ifstream i(path + f);

        // SprawdŸ czy plik jest otwarty poprawnie
        if (!i.is_open()) {
            std::cerr << "Nie mo¿na otworzyæ pliku " << path + f << std::endl;
            exit(0);
        }

        // Wczytaj dane JSON z pliku
        nlohmann::json j;
        try {
            i >> j;
        }
        catch (nlohmann::json::parse_error& e) {
            i.close();
            continue; // Pomijamy ten plik i kontynuujemy
        }

        // Zamknij plik
        i.close();
        // Wyœwietl zawartoœæ za³adowan¹ z pliku JSON
        for (const auto& entry : j) {
            try {
                songs.emplace_back(
                    entry.value("master_metadata_album_album_name", ""),
                    entry.value("master_metadata_album_artist_name", ""),
                    entry.value("master_metadata_track_name", ""),
                    entry.value("ms_played", 0),
                    entry.value("offline_timestamp", 0),
                    entry.value("platform", ""),
                    entry.value("spotify_track_uri", "")
                );
            }
            catch (nlohmann::json::type_error& e) {
                std::cerr << "Error in json file " << path + f << ": " << e.what() << std::endl;
                continue; // Pomijamy ten wpis i kontynuujemy
            }
        }
    }
    return songs;
}