DECLARE SUB UsageWork ()
DECLARE FUNCTION MainWork! ()
DECLARE FUNCTION InitWork! ()
DECLARE FUNCTION DoneWork! ()
DECLARE FUNCTION main! (argc!, argv$())
'*************************************************************************
' QB doesn't have a lot of the features of C so it takes some extra code
' to make things somewhat similar. While we can't do header files, we
' don't really need them. Some things that have to be made global in C
' are global by default in QB.
'
' File error trapping is not done in the QB version. All the extra code
' that is needed becomes distracting. The extra command line code is
' distracting enough.
'
' There is no functionality to specify an error exit code as in C.
'*************************************************************************

' Some constant definitions
CONST True = 1
CONST False = 0
CONST ARGSMAX = 10
DIM argv$(ARGSMAX)
'*************************************************************************
' Any other constants and globals will need to be added here
'*************************************************************************

'*************************************************************************
' Get args from COMMAND$. This is designed to fail without crashing.
' However, what you do with the args list could still cause crashes.
' C includes the equivalent of this code by default.
'*************************************************************************
cl$ = "QB-CORE " + COMMAND$ + " "
l = LEN(cl$)
f = True
argc = 0
IF l > 1 THEN
  'Parse the command line
  FOR x = 1 TO l
    lk$ = MID$(cl$, x, 1)
    IF lk$ <> CHR$(9) AND lk$ <> CHR$(32) THEN
      argv$(argc) = argv$(argc) + lk$
      f = True
    ELSE
      IF f = True THEN
        argc = argc + 1
        f = False
      END IF
      IF argc > ARGSMAX THEN PRINT "To many Arguments"
      GOTO errorexit
    END IF
  NEXT
END IF

' Test code to display the args.
CLS
PRINT cl$, argc
FOR x = 0 TO 10
  PRINT x; ":"; argv$(x)
NEXT

'**************************************************************************
' This is functionally the same as in C main(argc,argv[]).
'**************************************************************************
errmain = main(argc, argv$())
IF errmain <> 0 THEN
  PRINT "Error exit"; errmain
errorexit:
  STOP
END IF

DEFINT A
FUNCTION DoneWork
  DoneWork = 0
END FUNCTION

FUNCTION InitWork
  InitWork = 0
END FUNCTION

DEFSNG A
FUNCTION main (argc, argv$())
  '**********************************************************************
  ' The main function.
  ' This is intended to look similar to the C version.
  '**********************************************************************
CONST ARGLMTL = 3
CONST ARGLMTU = 3

'Error check argc and display usage
  IF argc < ARGLMTL OR argc > ARGLMTU THEN
    UsageWork
    main = 1
    EXIT FUNCTION
  END IF

'Open files. Note: Error trapping is messy in QB. So no error checks.
  OPEN argv$(1) FOR INPUT AS 1
  OPEN argv$(2) FOR OUTPUT AS 2

'Initialize the work function
  errcode = InitWork
  IF errcode <> 0 THEN
    main = errcode
    EXIT FUNCTION
  END IF

'Call the work function
  errcode = MainWork
  IF errcode <> 0 THEN
    main = errcode
    EXIT FUNCTION
  END IF

'Clean up things after work is done.
  errcode = DoneWork
  IF errorcode <> 0 THEN
    main = errcode
    EXIT FUNCTION
  END IF

'Close files
  CLOSE 1
  CLOSE 2

'No error exit
  main = 0
END FUNCTION

DEFINT A
FUNCTION MainWork
  MainWork = 0
END FUNCTION

DEFSNG A
SUB UsageWork
END SUB

