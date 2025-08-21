## AUREP
*Short for Audio Repeat*

## About

A simple CLI program to select a starting point and ending point to loop your favourite parts of a song.

### Arguments:

prefix aurep
</br>
`--path <PATH_TO_AUDIO_FILE>`
</br>
`--start <START_TIME>`
</br>
`--end <END_TIME>`
</br>
`--jump <JUMP_TIME>`

path: The path to the given audio file (common formats supported)
</br>
start: The time position to start the audio from (format MM.SS e.g "2.01")
</br>
end: The end position of the song (format MM.SS e.g "2.01")
</br>
jump: Once the song hits this threshold, it will loop back. If not mentioned, it will loop when it reaches the specified end time. (format MM.SS e.g "2.01")

## Notices
Supports macOS 10+ only.

`Copyright (c) 2025, shab. See LICENSE for more.`