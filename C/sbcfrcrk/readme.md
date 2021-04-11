While this isn't in the usual format of the various tools, this should be of interest.
The program allows up to 600 bytes of ciphertext including spaces and punctuation
with a frequency count, an index of coincidence and the Sukhotin vowel
identification method compiled as it loads the ciphertext file.

Arrow keys move the cursor left or right and hitting any letter key automatically places
that letter below the ciphertext. An additional feature adds hitting shift and any letter
(upper case) to jump to a letter. There are no checks if you use a letter more than once
and this is actually a feature for cracking substitution ciphers that allow it.
You can create a key file or otherwise save your work by giving it a second save file.

There isn't a Linux version of this program as it uses the old Borland conio.h extensions.
If you use an old Borland C++ 4.5 or maybe 5.0 compiler or earlier, you don't need conio2.
To get those extensions with Mingw and 32/64 bit Windows, conio2 has been added.
Please read the conio2 files for further information. The alternatives to conio2
are coniow, conio3, and hacking a console demo. Using conio2 works well and saved
me the trouble of making my own. These are the rough equivalent of some QB statements
that do the same job. A future version may take advantage of pdcurses or ncurses which
does a similar job in both Windows and Linux environments.

While most of my programs are simple command line programs and are very portable,
There is a Linux equivalent of the conio extensions that usees curses, but if you
go to that trouble, you might as well just use curses for the few things used here.

If you must run it on Linux, you could run most any DOS or Win95-Win7 in a Vitual Box VM.
It is an easy port to QB so that may be another path to Linux availability.
