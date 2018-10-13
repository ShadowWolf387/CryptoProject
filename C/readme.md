This folder will contain all the C files.
Incompatibilites will typically be with the int sizes. Where there are potentially large counts, type unsigned long is used with the hope that it is at least a 32 bit integer. Otherwise, int is specified where a 16 bit int would be large enough.
