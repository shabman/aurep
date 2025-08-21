#include "cli/parse.h"
#include <filesystem>
#include <iostream>
#include <map>
#include "util/time.h"

using namespace aurep::cli;
using namespace aurep::utils;

static std::map<std::string, std::string> g_arg_map;

static std::string
g_to_absolute(const std::string& path) noexcept
{
    if (path.empty())
    {
        return {};
    }

    if (path.at(0) == '~')
    {
        const char* home = getenv("HOME");

        if (home)
        {
            return std::string(home) + path.substr(1);
        }
    }

    return path;
}

parse::parse(int argc, char* argv[])
{
    m_args = std::vector<std::string>(argv + 1, argv + argc);
}

void
parse::read()
{
    for (size_t i = 0; i < m_args.size(); i++)
    {
        std::string arg = std::string(m_args[i]);
        std::string word;

        if (arg.find_first_of("--") == 0)
        {
            arg.erase(0, 2);

            if (i + 1 != m_args.size())
            {
                word = m_args[i + 1];
            }

            g_arg_map.emplace(arg, word);
        }
    }

    if (g_arg_map.empty())
    {
        std::cout << "empty input stream!\n";
        exit(EXIT_FAILURE);
    }

    for (const auto& [cmd, arg] : g_arg_map)
    {
        if (cmd == "path")
        {
            try
            {
                std::filesystem::path path = std::filesystem::canonical(arg);
                m_audio_path               = g_to_absolute(path);
            }
            catch (const std::filesystem::filesystem_error& err)
            {
                std::cout << "invalid file path!\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (cmd == "start")
        {
            m_start = f2dp(std::stof(arg));
        }
        else if (cmd == "end")
        {
            m_end = f2dp(std::stof(arg));
        }
        else if (cmd == "jump")
        {
            m_jump = f2dp(std::stof(arg));
        }
    }
}

std::string
parse::getAudioPath() const noexcept
{
    return m_audio_path;
}

float
parse::getStartPos() const noexcept
{
    return m_start;
}

float
parse::getEndPos() const noexcept
{
    return m_end;
}

std::optional<float>
parse::getJumpPos() const noexcept
{
    return m_jump;
}
