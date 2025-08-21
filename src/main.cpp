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

#include <CoreFoundation/CoreFoundation.h>
#include <iomanip>
#include <iostream>
#include "audio/au_engine.h"
#include "cli/parse.h"
#include "util/time.h"

#ifdef UNUSED
#elif defined(__GNUC__)
#define UNUSED(x) UNUSED_##x __attribute__((unused))
#elif defined(__LCLINT__)
#define UNUSED(x) /*@unused@*/ x
#else
#define UNUSED(x) x
#endif

#define AUREP_SEEK_AND_REPEAT()                                                                    \
    repeats++;                                                                                     \
    std::cout << "aurep: " << "repeating count: " << repeats << "\n";                              \
    player->seek(start);

using namespace aurep::cli;
using namespace aurep::audio;
using namespace aurep::utils;

static AudioPlayer* player = nullptr;

void
g_ctl_signal(int UNUSED(status))
{
    if (player)
    {
        std::cout << "\naurep: safely shutting down engine\n";
        delete player;
    }
    exit(EXIT_SUCCESS);
}

int
main(int argc, char* argv[])
{
    parse parser(argc, argv);
    parser.read();

#if AUREP_DEBUG
    std::cout << "---------------------------\n";
    std::cout << "Path file: " << parser.getAudioPath() << "\n";
    std::cout << "Start Pos: " << parser.getStartPos() << "\n";
    std::cout << "End Pos: " << parser.getEndPos() << "\n";
    std::cout << "Jump Pos: " << *parser.getJumpPos() << "\n";
    std::cout << "---------------------------\n";
#endif

    signal(SIGINT, g_ctl_signal);

    std::cout << "aurep: preparing engine...\n";
    player = AudioPlayer::file(parser.getAudioPath().c_str());

    if (!player)
    {
        std::cout << "aurep: failed to initialise engine\n";
        exit(EXIT_FAILURE);
    }

    uint16_t    repeats     = 0;
    bool        should_jump = parser.getJumpPos().has_value();
    const float start       = parser.getStartPos() * 60;

    player->play();
    player->seek(start);

    std::cout << "aurep: Now playing audio\n";
    do
    {
        CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0.25, false);
        const float progress = player->progress();
        float       sec      = progress;

        if (should_jump)
        {
            if (formatTimeFloat(sec) >= parser.getJumpPos())
            {
                AUREP_SEEK_AND_REPEAT()
            }
        }
        else
        {
            if (formatTimeFloat(sec) >= parser.getEndPos())
            {
                AUREP_SEEK_AND_REPEAT()
            }
        }
    } while (player->isPlaying());

    delete player;
}
