#ifndef AUREP_PARSE_H
#define AUREP_PARSE_H

#include <optional>
#include <vector>

namespace aurep::cli
{

class parse final
{

public:
    parse(int argc, char* argv[]);
    ~parse() = default;

public:
    void read();

    std::string          getAudioPath() const noexcept;
    float                getStartPos() const noexcept;
    float                getEndPos() const noexcept;
    std::optional<float> getJumpPos() const noexcept;

private:
    std::vector<std::string> m_args;
    std::string              m_audio_path;
    std::optional<float>     m_jump;
    float                    m_start;
    float                    m_end;
};

} // namespace aurep::cli

#endif /* AUREP_PARSE_H */