/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   chamberIR_wav;
    const int            chamberIR_wavSize = 255862;

    extern const char*   conferenceRoom_wav;
    const int            conferenceRoom_wavSize = 131756;

    extern const char*   largeRoom_wav;
    const int            largeRoom_wavSize = 1639532;

    extern const char*   main_bg_png;
    const int            main_bg_pngSize = 116987;

    extern const char*   synth_bg_png;
    const int            synth_bg_pngSize = 76208;

    extern const char*   verb_bg_png;
    const int            verb_bg_pngSize = 175870;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 6;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
