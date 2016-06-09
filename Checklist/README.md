## Checklist ##
`checklist` is a very simple terminal based application to run through a checklist. 

###Build###
Build has been tested with `Ubuntu 14.04` and `Ubuntu 16.04` releases with the system `gcc`. To build, simply run `make` in the folder containing the source files. There are no additional dependencies.

###Run###
To run the program on a checklist, pass the name of the text file containing the checklist to the program. For example, `./checklist joels_codereview_checklist`. A sample checklist for code review based (based on http://blog.fogcreek.com/increase-defect-detection-with-our-code-review-checklist-example/)is included.

###Screenshots###
See the `screenshots` folder.

###Checklist Fileformat###
* The checklist file used by the program is a simple plaintext file
* The first line of the file (that is not a comment) is assumed to be the name of the checklist
* All lines from Line Num 2 onwards are assumed to the checklist items
* Comments must begin with `#` as the first character of the line (i.e. `#` in col 1 of the line) and continue to the end of the line
* There is no notion of sub-sections or sub-checklists as of now. Use comments to logically demarcate sub-sections of a checklist
* See file `joels_codereview_checklist` for further details

###Additional Notes###
This is a quick-and-dirty (pre-alpha quality) tool and hasn't been tested thoroughly. Expect bugs. It seems to run just fine with `urvtx` and `xfce4-terminal` under `i3wm` and `xfce-desktop` respectively.
