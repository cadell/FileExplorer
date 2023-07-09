#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <thread>
#include <functional>
#include <chrono>
#include <cctype>
#include <cassert>
#include <span>



// TODO:: remove this later by having spawn task take in any task???? its 4:00am ...
enum class SEARCH_FLAG
{
    EXT_SEARCH          = 0,
    FILE_SEARCH         = 1,
    DIRECTORY_SEARCH    = 2
};

enum class SEARCH_OPTIONS
{
    CASE_SENSITIVE      = 0,
    CASE_INSENSITIVE    = 1
};

enum class PROGRAM_INPUTS
{
    PROGRAM_NAME        = 0,
    DIRECTORY_NAME      = 1,
    FILE_NAME           = 2,
    SEARCH_TYPE         = 3,
    CASE_SENSITIVITY    = 4
};

std::string str_tolower(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) { return std::tolower(c); } 
    );
    return s;
}

std::vector<std::filesystem::path> SearchPathSetup (std::string & path, std::string file_name)
{
    std::vector<std::filesystem::path> recursive_paths;

    for (auto& p : std::filesystem::directory_iterator(path, std::filesystem::directory_options::skip_permission_denied))
    {
        if (p.is_directory())
        {
            recursive_paths.push_back(p);
        }

        std::string string_lower_token = str_tolower((p.path().stem().string()));
        if (string_lower_token.find(str_tolower(file_name)) != std::string::npos)
        {
            //std::cout << p.path().stem().string() << '\n';
            std::cout << p.path().string() << '\n';
        }

    }
    return recursive_paths;
}

void SearchExtTask(std::string sub_path, std::string ext, SEARCH_OPTIONS option = SEARCH_OPTIONS::CASE_SENSITIVE)
{
    try
    {

        switch (option)
        {
        case SEARCH_OPTIONS::CASE_SENSITIVE:
        {
            for (auto& p : std::filesystem::recursive_directory_iterator(sub_path, std::filesystem::directory_options::skip_permission_denied))
            {
                if (p.path().extension() == ext)
                {
                    std::cout << p.path().stem().string() << '\n';
                }
            }
            break;
        }
        case SEARCH_OPTIONS::CASE_INSENSITIVE:
        {
            for (auto& p : std::filesystem::recursive_directory_iterator(sub_path, std::filesystem::directory_options::skip_permission_denied))
            {
                if (str_tolower(p.path().extension().string()) == str_tolower(ext))
                {
                    std::cout << p.path().stem().string() << '\n';
                }
            }
            break;
        }
        default:
        {
            option = SEARCH_OPTIONS::CASE_INSENSITIVE;
            break;
        }
        }
    }
    catch (const std::exception& e) // reference to the base of a polymorphic object
    {
        std::cout << e.what(); // information from length_error printed
    }


}


// TODO:: JUST PAST THE FILE NAME WITH EXT and remove use a delimiter instead ...
void SearchFileTask(std::string sub_path, std::string file_name, std::string ext, SEARCH_OPTIONS option = SEARCH_OPTIONS::CASE_INSENSITIVE)
{
    try
    {
        switch (option)
        {
            case SEARCH_OPTIONS::CASE_SENSITIVE:
            {
                for (auto& p : std::filesystem::recursive_directory_iterator(sub_path, std::filesystem::directory_options::skip_permission_denied))
                {
                    if (ext.empty() == false)
                    {
                        if (p.path().extension() == ext)
                        {
                            if (p.path().stem().string() == file_name)
                            {
                                //std::cout << p.path().stem().string() << '\n';
                                std::cout << p.path().string() << '\n';
                            }
                        }
                    }
                    else
                    {
                        //if (p.path().stem().string() == file_name)
                        std::string string_lower_token = ((p.path().stem().string()));
                        if (string_lower_token.find((file_name)) != std::string::npos)
                        {
                            //std::cout << p.path().stem().string() << '\n';
                            std::cout << p.path().string() << '\n';
                        }
                    }

                }
                break;
            }
            case SEARCH_OPTIONS::CASE_INSENSITIVE:
            {
                for (auto& p : std::filesystem::recursive_directory_iterator(sub_path, std::filesystem::directory_options::skip_permission_denied))
                {
                    if (ext.empty() == false)
                    {
                        if (p.path().extension() == ext)
                        {
                            std::string string_lower_token = str_tolower((p.path().stem().string()));
                            if (string_lower_token == str_tolower(file_name))
                            {
                                //std::cout << p.path().stem().string() << '\n';
                                std::cout << p.path().string() << '\n';
                            }
                        }
                    }
                    else
                    {
                        std::string string_lower_token = str_tolower((p.path().stem().string()));
                        if (string_lower_token.find(str_tolower(file_name)) != std::string::npos )
                        {
                            //std::cout << p.path().stem().string() << '\n';
                            std::cout << p.path().string() << '\n';
                        }
                    }
                }
                break;
            }
            default:
            {
                option = SEARCH_OPTIONS::CASE_INSENSITIVE;
                break;
            }
        }

    }
    catch (const std::exception& e) // reference to the base of a polymorphic object
    {
        std::cout << e.what(); // information from length_error printed
    }


}

void SearchDirectoryTask(std::string sub_path, std::string dir_name, SEARCH_OPTIONS option = SEARCH_OPTIONS::CASE_INSENSITIVE)
{
    try
    {
        switch (option)
        {
        case SEARCH_OPTIONS::CASE_SENSITIVE:
        {
            for (auto& p : std::filesystem::recursive_directory_iterator(sub_path, std::filesystem::directory_options::skip_permission_denied))
            {
                if (p.path().string().find(dir_name) != std::string::npos)
                {
                    std::cout << p.path().stem().string() << '\n';
                }
            }
            break;
        }
        case SEARCH_OPTIONS::CASE_INSENSITIVE:
        {
            for (auto& p : std::filesystem::recursive_directory_iterator(sub_path, std::filesystem::directory_options::skip_permission_denied))
            {
                std::string string_lower_token = str_tolower((p.path().string()));
                if (string_lower_token.find(str_tolower(dir_name)) != std::string::npos)
                {
                    //std::cout << p.path().stem().string() << '\n';
                    std::cout << p.path().string() << '\n';
                }
               
            }
            break;
        }
        default:
        {
            option = SEARCH_OPTIONS::CASE_INSENSITIVE;
            break;
        }
        }

    }
    catch (const std::exception& e) // reference to the base of a polymorphic object
    {
        std::cout << e.what(); // information from length_error printed
    }

}

void SpawnSearchThreads(SEARCH_FLAG flag, std::vector<std::filesystem::path> & sub_path, std::string file_name, std::string & ext, SEARCH_OPTIONS option = SEARCH_OPTIONS::CASE_INSENSITIVE)
{
    std::vector<std::thread> thread_container; /// lets just say only one instance of this is running lol



    switch (flag)
    {  
        case SEARCH_FLAG::EXT_SEARCH:
        {
            assert(ext.empty() == false);

            for (auto&& member : sub_path)
            {
                std::string path_name = member.string();
                thread_container.push_back(std::thread(SearchExtTask, path_name, ext, option)); // ignore thread handler for now)
                thread_container.back().join();
            }
            break;
        }
        case SEARCH_FLAG::FILE_SEARCH:
        {
            assert(ext.empty() == false);
            assert(file_name.empty() == false);
            for (auto&& member : sub_path)
            {
                std::string path_name = member.string();
                thread_container.push_back(std::thread(SearchFileTask, path_name, file_name, ext, option)); // ignore thread handler for now)
                thread_container.back().join();
            }
            break;
        }
        case SEARCH_FLAG::DIRECTORY_SEARCH:
        {
            for (auto&& member : sub_path)
            {
                std::string path_name = member.string();
                thread_container.push_back(std::thread(SearchDirectoryTask, path_name, file_name, option)); // ignore thread handler for now)
                thread_container.back().join();
            }

            break;
        }
        default:
            // Default case shall search for file and directory, ignoring ext
            break;
    }

}

int main(int argc, char* argv[])
{
    std::cout << "Usage "  << std::endl;
    std::cout << "path=/dir/" << std::endl;
    std::cout << "file=name.log" << std::endl;

    std::cout << "options" << std::endl;
    std::cout << "Search Flag" << std::endl;
    std::cout << "    f - File Search" << std::endl;
    std::cout << "        If file search has no extension itll be generic" << std::endl;
    std::cout << "    e - Extension Search" << std::endl;
    std::cout << "    d - directory Search" << std::endl;
    std::cout << "    i - Case Insensitive" << std::endl;
    std::cout << "        Default option is case insensitive" << std::endl;
    std::cout << "    d - Case Sensitive" << std::endl;



    std::string executable_name{};
    std::string path_input{};
    std::string name_input{};
    unsigned int flag = 0;
    unsigned int case_sensitivity = 0;

#if 1
    int input_count = argc;
    if (argc <= 1)
    {
        return 0;
    }

    for (int element = 0; element < argc; element++)
    {
        PROGRAM_INPUTS input = (PROGRAM_INPUTS)element;

        switch (input)
        {
        case PROGRAM_INPUTS::PROGRAM_NAME:
        {
            executable_name = std::string(argv[0]);
            break;
        }
        case PROGRAM_INPUTS::DIRECTORY_NAME:
        {
            // TODO::Check for empty strings and whatnot
            path_input = std::string(argv[1]);
            break;
        }
        case PROGRAM_INPUTS::FILE_NAME:
        {
            name_input = std::string(argv[2]);
            break;
        }
        case PROGRAM_INPUTS::SEARCH_TYPE:
        {
            flag = *(unsigned int*)argv[3];
            break;
        }
        case PROGRAM_INPUTS::CASE_SENSITIVITY:
        {
            case_sensitivity = *(unsigned int*)argv[4];
            break;
        }
        default:
            break;
        }
    }


   const std::string path_token = path_input.substr(path_input.find("=") + 1, path_input.size() - path_input.find("="));
   const std::string name_token = name_input.substr(name_input.find("=") + 1, name_input.size() - name_input.find("="));


    //std::cout << "Inputs "  << path_input << " " << name_input << " " << flag << " " << "case_sensitivity" << " " << std::endl;
#endif

    // TODO::Pass these as actual const later ... add new delimiter to file name to check for extension....
    std::string path = path_token;
    std::string file_name = name_token;
    //std::string ext(".log");
    std::string ext("");

    auto hold = SearchPathSetup(path, file_name);
    const auto start = std::chrono::steady_clock::now();
    SpawnSearchThreads(SEARCH_FLAG::FILE_SEARCH,hold,file_name ,ext, SEARCH_OPTIONS::CASE_INSENSITIVE);
    const auto end = std::chrono::steady_clock::now();
    const std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << elapsed_seconds.count() << "s\n";

}