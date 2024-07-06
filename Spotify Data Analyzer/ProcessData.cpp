#include "ProcessData.h"

vector<string> ProcessData::filenames;

void ProcessData::create_folder()
{
    const std::string folderName = "Spotify Data";

    try {
        if (!std::filesystem::exists(folderName)) {
            if (std::filesystem::create_directory(folderName)) {
                //std::cout << "Folder został utworzony." << std::endl;
            }
            else {
                std::cerr << "Nie udało się utworzyć folderu." << std::endl;
            }
        }
        else {
            //std::cout << "Folder już istnieje." << std::endl;
        }
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Błąd: " << e.what() << std::endl;
    }
}

void ProcessData::read_file_names()
{
    std::string path = "./Spotify Data";

    // Sprawdzamy czy podana ścieżka jest folderem
    if (fs::is_directory(path)) {
        // Iterujemy po zawartości folderu
        for (const auto& entry : fs::directory_iterator(path)) {
            filenames.push_back(entry.path().filename().string());
            //std::cout << entry.path().filename().string() << std::endl;
        }
    }
    else {
        std::cerr << "Podana ścieżka nie jest folderem." << std::endl;
    }
}

vector<Song> ProcessData::parse_files(string type)
{
    auto start = std::chrono::high_resolution_clock::now();
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

    // Tu uruchamiamy parse_file w osobnych wątkach
    std::vector<std::future<std::vector<Song>>> futures;
    for (const auto& file : files_to_parse) {
        futures.push_back(std::async(std::launch::async, &ProcessData::parse_file, path + file));
    }

    // Czekamy na zakończenie wszystkich wątków i łączymy wyniki w jeden wektor
    for (auto& future : futures) {
        std::vector<Song> partial_result = future.get();
        songs.insert(songs.end(), std::make_move_iterator(partial_result.begin()), std::make_move_iterator(partial_result.end()));
    }

    // Koniec pomiaru czasu
    auto end = std::chrono::high_resolution_clock::now();

    // Obliczanie czasu wykonania
    auto duration = duration_cast<std::chrono::milliseconds>(end - start);

    // Wyświetlanie czasu wykonania
    std::cout << "parse_files - czas wykonania: " << duration.count() << " ms" << std::endl;
        
    return songs;
}

vector<Song> ProcessData::parse_file(string path)
{
    vector<Song> songs;
    std::ifstream i(path);

    // Sprawdź czy plik jest otwarty poprawnie
    if (!i.is_open()) {
        std::cerr << "Nie można otworzyć pliku " << path << std::endl;
        exit(0);
    }

    // Wczytaj dane JSON z pliku
    nlohmann::json j;
    try {
        i >> j;
    }
    catch (nlohmann::json::parse_error& e) {
        i.close();
        return songs; // Pomijamy ten plik i kontynuujemy
    }

    // Zamknij plik
    i.close();
    // Wyświetl zawartość załadowaną z pliku JSON
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
            //std::cerr << "Error in json file " << path << ": " << e.what() << std::endl;
            continue; // Pomijamy ten wpis i kontynuujemy
        }
    }
    return songs;
}