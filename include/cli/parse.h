/**
 * This file is part of the aurep distribution (https://github.com/shabman/aurep)
 * Copyright (c) 2025 shab.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

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
