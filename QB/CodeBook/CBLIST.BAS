DECLARE FUNCTION Myrand# (seed!)
DECLARE FUNCTION sortcmp% (i!(), p$(), s$(), pstn!)
DECLARE SUB sort (i!(), p$(), s$(), twc!)
DIM we$(610), wd$(610)
DIM indx1(610), indx2(610)
OPEN "e:\codebook\codebook.csv" FOR INPUT AS 1
OPEN "e:\codebook\codebook.txt" FOR OUTPUT AS 2
CLS
PRINT "Initializing..."
vwl$ = "AEIOU"
con$ = "BCDFGHJKLMNPQRSTVWXYZ"
FOR x = 0 TO 603
    indx1(x) = x
    indx2(x) = x
NEXT
PRINT "Reading File..."
DO
    LINE INPUT #1, a$
    FOR x = 1 TO LEN(a$)
        c$ = MID$(a$, x, 1)
        IF c$ = "(" THEN
            f = 1
            c$ = " "
        END IF
        IF c$ = ")" THEN
            f = 0
            c$ = " "
        END IF
        IF c$ = ";" THEN
            we$(wc) = w$
            wc = wc + 1
            w$ = ""
            f = 0
        ELSE
            IF c$ <> " " AND f = 0 THEN
                w$ = w$ + c$
            END IF
        END IF
    NEXT
    we$(wc) = w$
    wc = wc + 1
    w$ = ""
    f = 0
LOOP UNTIL EOF(1)
PRINT "Word count = "; wc
DO
    INPUT "Enter a number from 0 to 999999 "; ss
    IF ss < 0 OR ss > 1000000 THEN
        PRINT "Outside of limits"
        rnl = rnl + 1
        IF rnl > 5 THEN
            PRINT "Excessive stupidity detected. Terminating."
            END
        END IF
    END IF
LOOP WHILE ss < 0 OR ss > 999999
PRINT "Spinning the wheel..."
ss = Myrand#(ss)
f = 0
rnl = 0
DO
    ss = Myrand#(0)
    rnl = rnl + 1
    IF f = 0 AND rnl > 1000000 THEN
        f = 1
        PRINT "Hit a key"
    END IF
LOOP WHILE INKEY$ = ""
PRINT "Creating Code Words..."
FOR x = 0 TO wc - 1
    DO
        f = 0
        ' Generate CvCvC words
        t$ = MID$(con$, Myrand#(0) MOD (21) + 1, 1)
        t$ = t$ + MID$(vwl$, Myrand#(0) MOD (5) + 1, 1)
        t$ = t$ + MID$(con$, Myrand#(0) MOD (21) + 1, 1)
        t$ = t$ + MID$(vwl$, Myrand#(0) MOD (5) + 1, 1)
        t$ = t$ + MID$(con$, Myrand#(0) MOD (21) + 1, 1)
        ' Verify word doesn't exist
        FOR y = 0 TO wc - 1
            IF t$ = wd$(y) THEN
                f = 1
                EXIT FOR
            END IF
        NEXT
    LOOP UNTIL f = 0
    wd$(x) = t$
NEXT
PRINT "Sorting English..."
CALL sort(indx1(), we$(), wd$(), wc)
PRINT "Sorting Code..."
CALL sort(indx2(), wd$(), we$(), wc)
PRINT "Writing File..."
FOR x = 0 TO wc - 1
    PRINT #2, LEFT$(we$(indx1(x)) + ";               ", 15); CHR$(9); wd$(indx1(x))
NEXT
FOR x = 0 TO wc - 1
    PRINT #2, wd$(indx2(x)); ":  "; CHR$(9); we$(indx2(x))
NEXT
PRINT "Done..."
CLOSE 1
CLOSE 2

FUNCTION Myrand# (seed)
STATIC s AS DOUBLE
IF seed <> 0 THEN
    'New seed
    s = seed
END IF
'Make a new number
prng# = (s * 3877 + 29573) MOD (139968)
s = prng#
Myrand# = prng#
END FUNCTION

SUB sort (i(), p$(), s$(), twc)
drtn = 1
pstn = 0
ordr = 0
lcnt = 0
lmt = twc - 2
stp = twc - 3
DO
    IF sortcmp%(i(), p$(), s$(), pstn) >= 0 THEN
        'No swap highest is first or equal.
        ' Inc proper order counter
        ordr = ordr + 1
    ELSE
        ' Swap pointer
        temp = i(pstn)
        i(pstn) = i(pstn + 1)
        i(pstn + 1) = temp
    END IF
    ' Chnge direction if limit reached.
    IF (drtn = -1 AND pstn = 0) OR (drtn = 1 AND pstn = lmt) THEN
        drtn = drtn * -1
        ordr = 0
        lcnt = lcnt + 1
    END IF
    pstn = pstn + drtn
LOOP WHILE ordr <> stp
PRINT "Loops ="; lcnt
END SUB

FUNCTION sortcmp% (i(), p$(), s$(), pstn)
IF UCASE$(p$(i(pstn))) < UCASE$(p$(i(pstn + 1))) THEN
    sortcmp% = 1
    EXIT FUNCTION
END IF
IF UCASE$(p$(i(pstn))) > UCASE$(p$(i(pstn + 1))) THEN
    sortcmp% = -1
    EXIT FUNCTION
END IF
IF UCASE$(s$(i(pstn))) < UCASE$(s$(i(pstn + 1))) THEN
    sortcmp% = 1
    EXIT FUNCTION
END IF
IF UCASE$(s$(i(pstn))) > UCASE$(s$(i(pstn + 1))) THEN
    sortcmp% = -1
    EXIT FUNCTION
END IF
sortcmp% = 0
END FUNCTION

